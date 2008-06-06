/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "ProfileNode.h"

#include "Profiler.h"
#include "DateMath.h"

#include <stdio.h>

#if PLATFORM(WIN_OS)
#include <windows.h>
#endif

namespace KJS {

static const char* NonJSExecution = "(idle)";

static double getCount()
{
#if PLATFORM(WIN_OS)
    static LARGE_INTEGER frequency = {0};
    if (!frequency.QuadPart)
        QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return static_cast<double>(counter.QuadPart) / frequency.QuadPart;
#else
    return getCurrentUTCTimeWithMicroseconds();
#endif
}

ProfileNode::ProfileNode(const CallIdentifier& callIdentifier, ProfileNode* headNode, ProfileNode* parentNode)
    : m_callIdentifier(callIdentifier)
    , m_head(headNode)
    , m_parent(parentNode)
    , m_nextSibling(0)
    , m_startTime(0.0)
    , m_actualTotalTime(0.0)
    , m_visibleTotalTime(0.0)
    , m_actualSelfTime(0.0)
    , m_visibleSelfTime(0.0)
    , m_numberOfCalls(0)
    , m_visible(true)
{
    startTimer();
}

ProfileNode* ProfileNode::willExecute(const CallIdentifier& callIdentifier)
{
    for (StackIterator currentChild = m_children.begin(); currentChild != m_children.end(); ++currentChild) {
        if ((*currentChild)->callIdentifier() == callIdentifier) {
            (*currentChild)->startTimer();
            return (*currentChild).get();
        }
    }

    RefPtr<ProfileNode> newChild = ProfileNode::create(callIdentifier, m_head ? m_head : this, this);   // If this ProfileNode has no head it is the head.
    if (m_children.size())
        m_children.last()->setNextSibling(newChild.get());
    m_children.append(newChild.release());
    return m_children.last().get();
}

ProfileNode* ProfileNode::didExecute()
{
    endAndRecordCall();
    return m_parent;
}

void ProfileNode::addChild(PassRefPtr<ProfileNode> prpChild)
{
    RefPtr<ProfileNode> child = prpChild;
    child->setParent(this);
    if (m_children.size())
        m_children.last()->setNextSibling(child.get());
    m_children.append(child.release());
}
        
void ProfileNode::insertNode(PassRefPtr<ProfileNode> prpNode)
{
    RefPtr<ProfileNode> node = prpNode;

    for (unsigned i = 0; i < m_children.size(); ++i)
        node->addChild(m_children[i].release());

    m_children.clear();
    m_children.append(node.release());
}

void ProfileNode::stopProfiling()
{
    if (m_startTime)
        endAndRecordCall();

    m_visibleTotalTime = m_actualTotalTime;

    ASSERT(m_actualSelfTime == 0.0 && m_startTime == 0.0);

    // Because we iterate in post order all of our children have been stopped before us.
    for (unsigned i = 0; i < m_children.size(); ++i)
        m_actualSelfTime += m_children[i]->totalTime();

    ASSERT(m_actualSelfTime <= m_actualTotalTime);
    m_actualSelfTime = m_actualTotalTime - m_actualSelfTime;

    if (!m_head && m_actualSelfTime) {
        ProfileNode* idleNode = willExecute(CallIdentifier(NonJSExecution, 0, 0));

        idleNode->setTotalTime(m_actualSelfTime);
        idleNode->setSelfTime(m_actualSelfTime);
        idleNode->setNumberOfCalls(0);

        m_actualSelfTime = 0.0;
    }

    m_visibleSelfTime = m_actualSelfTime;
}

ProfileNode* ProfileNode::traverseNextNode() const
{
    ProfileNode* next = m_nextSibling;
    if (!next)
        return m_parent;
    while (ProfileNode* firstChild = next->firstChild())
        next = firstChild;
    return next;
}

void ProfileNode::sort(bool comparator(const RefPtr<ProfileNode>& , const RefPtr<ProfileNode>& ))
{
    std::sort(childrenBegin(), childrenEnd(), comparator);    
    resetChildrensSiblings();
}

void ProfileNode::setTreeVisible(bool visible)
{
    m_visible = visible;

    for (StackIterator currentChild = m_children.begin(); currentChild != m_children.end(); ++currentChild)
        (*currentChild)->setTreeVisible(visible);
}

void ProfileNode::focus(const CallIdentifier& callIdentifier, bool forceVisible)
{
    if (m_callIdentifier == callIdentifier) {
        m_visible = true;

        for (StackIterator currentChild = m_children.begin(); currentChild != m_children.end(); ++currentChild)
            (*currentChild)->focus(callIdentifier, true);
    } else {
        m_visible = forceVisible;
        double totalChildrenTime = 0.0;

        for (StackIterator currentChild = m_children.begin(); currentChild != m_children.end(); ++currentChild) {
            (*currentChild)->focus(callIdentifier, forceVisible);
            m_visible |= (*currentChild)->visible();
            totalChildrenTime += (*currentChild)->totalTime();
        }
        
        if (m_visible)
            m_visibleTotalTime = m_visibleSelfTime + totalChildrenTime;
    }
}

double ProfileNode::exclude(const CallIdentifier& callIdentifier)
{
    if (m_callIdentifier == callIdentifier) {
        m_visible = false;

        for (StackIterator currentChild = m_children.begin(); currentChild != m_children.end(); ++currentChild)
            (*currentChild)->setTreeVisible(false);

        return m_visibleTotalTime;
    }

    for (StackIterator currentChild = m_children.begin(); currentChild != m_children.end(); ++currentChild)
        m_visibleSelfTime += (*currentChild)->exclude(callIdentifier);

    return 0;
}

void ProfileNode::restore()
{
    m_visibleTotalTime = m_actualTotalTime;
    m_visibleSelfTime = m_actualSelfTime;
    m_visible = true;
}

void ProfileNode::endAndRecordCall()
{
    m_actualTotalTime += getCount() - m_startTime;
    m_startTime = 0.0;

    ++m_numberOfCalls;
}

void ProfileNode::startTimer()
{
    if (!m_startTime)
        m_startTime = getCount();
}

void ProfileNode::resetChildrensSiblings()
{
    unsigned size = m_children.size();
    for (unsigned i = 0; i < size; ++i)
        m_children[i]->setNextSibling(i + 1 == size ? 0 : m_children[i + 1].get());
}

#ifndef NDEBUG
void ProfileNode::debugPrintData(int indentLevel) const
{
    // Print function names
    for (int i = 0; i < indentLevel; ++i)
        printf("  ");

    printf("%d SelfTime %.3fms/%.3f%% TotalTime %.3fms/%.3f%% VSelf %.3fms VTotal %.3fms Function Name %s Visible %s Next Sibling %s\n",
        m_numberOfCalls, m_actualSelfTime, selfPercent(), m_actualTotalTime, totalPercent(),
        m_visibleSelfTime, m_visibleTotalTime, 
        functionName().UTF8String().c_str(), (m_visible ? "True" : "False"),
        m_nextSibling ? m_nextSibling->functionName().UTF8String().c_str() : "");

    ++indentLevel;

    // Print children's names and information
    for (StackIterator currentChild = m_children.begin(); currentChild != m_children.end(); ++currentChild)
        (*currentChild)->debugPrintData(indentLevel);
}

// print the profiled data in a format that matches the tool sample's output.
double ProfileNode::debugPrintDataSampleStyle(int indentLevel, FunctionCallHashCount& countedFunctions) const
{
    printf("    ");

    // Print function names
    const char* name = functionName().UTF8String().c_str();
    double sampleCount = m_actualTotalTime * 1000;
    if (indentLevel) {
        for (int i = 0; i < indentLevel; ++i)
            printf("  ");

         countedFunctions.add(functionName().rep());

        printf("%.0f %s\n", sampleCount ? sampleCount : 1, name);
    } else
        printf("%s\n", name);

    ++indentLevel;

    // Print children's names and information
    double sumOfChildrensCount = 0.0;
    for (StackIterator currentChild = m_children.begin(); currentChild != m_children.end(); ++currentChild)
        sumOfChildrensCount += (*currentChild)->debugPrintDataSampleStyle(indentLevel, countedFunctions);

    sumOfChildrensCount *= 1000;    //
    // Print remainder of samples to match sample's output
    if (sumOfChildrensCount < sampleCount) {
        printf("    ");
        while (indentLevel--)
            printf("  ");

        printf("%.0f %s\n", sampleCount - sumOfChildrensCount, functionName().UTF8String().c_str());
    }

    return m_actualTotalTime;
}
#endif

}   // namespace KJS
