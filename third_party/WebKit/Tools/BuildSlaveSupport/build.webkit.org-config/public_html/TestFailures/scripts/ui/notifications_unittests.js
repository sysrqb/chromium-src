/*
 * Copyright (C) 2011 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

(function () {

module('ui.notifications');

test('ui.notifications.Stream', 5, function() {
    var stream = new ui.notifications.Stream();
    equal(stream.tagName, 'OL');
    equal(stream.className, 'notifications');
    stream.push(document.createElement('li')).textContent = 'o-matic';
    equal(stream.childElementCount, 1);
    stream.push(document.createElement('li')).textContent = 'garden-';
    equal(stream.childElementCount, 2);
    equal(stream.textContent, 'garden-o-matic');
});

test('ui.notifications.Info', 3, function() {
    var info = new ui.notifications.Info('info');
    equal(info.tagName, 'LI');
    equal(info.innerHTML, '<div class="what">info</div>');
    // FIXME: Really need to figure out how to mock/test animated removal.
    ok(info.dismiss);
});

test('ui.notifications.FailingTest', 4, function() {
    var failingTest = new ui.notifications.FailingTest({testName: 'test'});
    equal(failingTest.tagName, 'LI');
    equal(failingTest.innerHTML, 'test');
    ok(failingTest.equals({testName: 'test'}));
    ok(!failingTest.equals({testName: 'foo'}));
});

test('ui.notifications.SuspiciousCommit', 2, function() {
    var suspiciousCommit = new ui.notifications.SuspiciousCommit({revision: 1, title: "title", author: "author", reviewer: "reviewer"});
    equal(suspiciousCommit.tagName, 'LI');
    equal(suspiciousCommit.innerHTML, '<div class="description"><a href="">1</a>title author (reviewer)</div><ul class="actions"><li><button>Roll out</button></li></ul>');
});

test('ui.notifications.TestFailures', 7, function() {
    var testFailures = new ui.notifications.TestFailures();
    equal(testFailures.tagName, 'LI');
    equal(testFailures.innerHTML, '<time>Just now</time><div class="what"><div class="problem"><ul class="effects"></ul><ul class="causes"></ul></div></div>');
    testFailures.addFailureAnalysis({testName: 'test'});
    equal(testFailures.innerHTML, '<time>Just now</time><div class="what"><div class="problem"><ul class="effects"><li>test</li></ul><ul class="causes"></ul></div></div>');
    ok(testFailures.containsFailureAnalysis({testName: 'test'}));
    ok(!testFailures.containsFailureAnalysis({testName: 'foo'}));
    testFailures.addFailureAnalysis({testName: 'test'});
    equal(testFailures.innerHTML, '<time>Just now</time><div class="what"><div class="problem"><ul class="effects"><li>test</li></ul><ul class="causes"></ul></div></div>');
    testFailures.addCommitData({revision: 1, title: "title", author: "author", reviewer: "reviewer"});
    equal(testFailures.innerHTML, '<time>Just now</time><div class="what"><div class="problem"><ul class="effects"><li>test</li></ul><ul class="causes"><li><div class="description"><a href="">1</a>title author (reviewer)</div><ul class="actions"><li><button>Roll out</button></li></ul></li></ul></div></div>');
});

}());