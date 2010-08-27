/*
 * Copyright (C) 2007 Apple Inc.  All rights reserved.
 * Copyright (C) 2009 Joseph Pecoraro
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

WebInspector.EventListenersSidebarPane = function()
{
    WebInspector.SidebarPane.call(this, WebInspector.UIString("Event Listeners"));
    this.bodyElement.addStyleClass("events-pane");

    this.sections = [];

    this.settingsSelectElement = document.createElement("select");

    var option = document.createElement("option");
    option.value = "all";
    option.label = WebInspector.UIString("All Nodes");
    this.settingsSelectElement.appendChild(option);

    option = document.createElement("option");
    option.value = "selected";
    option.label = WebInspector.UIString("Selected Node Only");
    this.settingsSelectElement.appendChild(option);

    WebInspector.applicationSettings.addEventListener("loaded", this._settingsLoaded, this);
    this.settingsSelectElement.addEventListener("click", function(event) { event.stopPropagation() }, false);
    this.settingsSelectElement.addEventListener("change", this._changeSetting.bind(this), false);

    this.titleElement.appendChild(this.settingsSelectElement);
}

WebInspector.EventListenersSidebarPane.prototype = {
    _settingsLoaded: function()
    {
        var filter = WebInspector.applicationSettings.eventListenersFilter;
        if (filter === "all")
            this.settingsSelectElement[0].selected = true;
        if (filter === "selected")
            this.settingsSelectElement[1].selected = true;
    },

    update: function(node)
    {
        var body = this.bodyElement;
        body.removeChildren();
        this.sections = [];

        var self = this;
        function callback(nodeId, eventListeners) {
            var sectionNames = [];
            var sectionMap = {};
            for (var i = 0; i < eventListeners.length; ++i) {
                var eventListener = eventListeners[i];
                eventListener.node = WebInspector.domAgent.nodeForId(eventListener.nodeId);
                delete eventListener.nodeId; // no longer needed
                if (/^function _inspectorCommandLineAPI_logEvent\(/.test(eventListener.listenerBody.toString()))
                    continue; // ignore event listeners generated by monitorEvent
                var type = eventListener.type;
                var section = sectionMap[type];
                if (!section) {
                    section = new WebInspector.EventListenersSection(type, nodeId);
                    sectionMap[type] = section;
                    sectionNames.push(type);
                    self.sections.push(section);
                }
                section.addListener(eventListener);
            }
            
            if (sectionNames.length === 0) {
                var div = document.createElement("div");
                div.className = "info";
                div.textContent = WebInspector.UIString("No Event Listeners");
                body.appendChild(div);
                return;
            }

            sectionNames.sort();
            for (var i = 0; i < sectionNames.length; ++i) {
                var section = sectionMap[sectionNames[i]];
                section.update();
                body.appendChild(section.element);
            }
        }

        WebInspector.EventListeners.getEventListenersForNodeAsync(node, callback);
    },

    _changeSetting: function(event)
    {
        var selectedOption = this.settingsSelectElement[this.settingsSelectElement.selectedIndex];
        WebInspector.applicationSettings.eventListenersFilter = selectedOption.value;

        for (var i = 0; i < this.sections.length; ++i)
            this.sections[i].update();
    }
}

WebInspector.EventListenersSidebarPane.prototype.__proto__ = WebInspector.SidebarPane.prototype;

WebInspector.EventListenersSection = function(title, nodeId)
{
    this.eventListeners = [];
    this._nodeId = nodeId;
    WebInspector.PropertiesSection.call(this, title);

    // Changed from a Properties List
    this.propertiesElement.parentNode.removeChild(this.propertiesElement);
    delete this.propertiesElement;
    delete this.propertiesTreeOutline;

    this.eventBars = document.createElement("div");
    this.eventBars.className = "event-bars";
    this.element.appendChild(this.eventBars);
}

WebInspector.EventListenersSection.prototype = {
    update: function()
    {
        // A Filtered Array simplifies when to create connectors
        var filteredEventListeners = this.eventListeners;
        if (WebInspector.applicationSettings.eventListenersFilter === "selected") {
            filteredEventListeners = [];
            for (var i = 0; i < this.eventListeners.length; ++i) {
                var eventListener = this.eventListeners[i];
                if (eventListener.node.id === this._nodeId)
                    filteredEventListeners.push(eventListener);
            }
        }

        this.eventBars.removeChildren();
        var length = filteredEventListeners.length;
        for (var i = 0; i < length; ++i) {
            var eventListener = filteredEventListeners[i];
            var eventListenerBar = new WebInspector.EventListenerBar(eventListener, this._nodeId);
            if (i < length - 1) {
                var connector = document.createElement("div");
                connector.className = "event-bar-connector";
                eventListenerBar.element.appendChild(connector);
            }

            this.eventBars.appendChild(eventListenerBar.element);
        }
    },

    addListener: function(eventListener)
    {
        this.eventListeners.push(eventListener);
    }
}

WebInspector.EventListenersSection.prototype.__proto__ = WebInspector.PropertiesSection.prototype;

WebInspector.EventListenerBar = function(eventListener, nodeId)
{
    this.eventListener = eventListener;
    this._nodeId = nodeId;
    WebInspector.ObjectPropertiesSection.call(this);
    this._setNodeTitle();
    this._setFunctionSubtitle();
    this.editable = false;
    this.element.className = "event-bar"; /* Changed from "section" */
    this.propertiesElement.className = "event-properties source-code"; /* Changed from "properties" */
}

WebInspector.EventListenerBar.prototype = {
    update: function()
    {
        function updateWithNodeObject(nodeObject)
        {
            var properties = [];
            if (nodeObject)
                properties.push(new WebInspector.RemoteObjectProperty("node", nodeObject));

            for (var propertyName in this.eventListener) {
                var value = WebInspector.RemoteObject.fromPrimitiveValue(value);
                properties.push(new WebInspector.RemoteObjectProperty(propertyName, value));
            }
            this.updateProperties(properties);
        }
        var node = this.eventListener.node;
        delete this.eventListener.node;
        WebInspector.RemoteObject.resolveNode(node, updateWithNodeObject.bind(this));
    },

    _setNodeTitle: function()
    {
        var node = this.eventListener.node;
        if (!node)
            return;

        if (node.nodeType === Node.DOCUMENT_NODE) {
            this.titleElement.textContent = "document";
            return;
        }

        if (node.id === this._nodeId) {
            this.titleElement.textContent = appropriateSelectorForNode(node);
            return;
        }

        this.titleElement.removeChildren();
        this.titleElement.appendChild(WebInspector.panels.elements.linkifyNodeReference(this.eventListener.node));
    },

    _setFunctionSubtitle: function()
    {
        // Requires that Function.toString() return at least the function's signature.
        if (this.eventListener.sourceName) {
            this.subtitleElement.removeChildren();
            this.subtitleElement.appendChild(WebInspector.linkifyResourceAsNode(this.eventListener.sourceName, "scripts", this.eventListener.lineNumber));
        } else {
            var match = this.eventListener.listenerBody.match(/function ([^\(]+?)\(/);
            if (match)
                this.subtitleElement.textContent = match[1];
            else
                this.subtitleElement.textContent = WebInspector.UIString("(anonymous function)");
        }
    }
}

WebInspector.EventListenerBar.prototype.__proto__ = WebInspector.ObjectPropertiesSection.prototype;
