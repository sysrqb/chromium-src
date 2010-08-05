/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
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

#include "PluginInfoStore.h"

#include "NotImplemented.h"
#include <WebCore/FileSystem.h>
#include <wtf/OwnArrayPtr.h>

using namespace WebCore;

namespace WebKit {

Vector<String> PluginInfoStore::pluginsDirectories()
{
    // FIXME: <http://webkit.org/b/43510> Migrate logic here from PluginDatabase::defaultPluginDirectories.
    notImplemented();
    return Vector<String>();
}

class PathWalker : public Noncopyable {
public:
    PathWalker(const String& directory)
    {
        String pattern = directory + "\\*";
        m_handle = ::FindFirstFileW(pattern.charactersWithNullTermination(), &m_data);
    }

    ~PathWalker()
    {
        if (!isValid())
            return;
        ::FindClose(m_handle);
    }

    bool isValid() const { return m_handle != INVALID_HANDLE_VALUE; }
    const WIN32_FIND_DATAW& data() const { return m_data; }

    bool step() { return ::FindNextFileW(m_handle, &m_data); }

private:
    HANDLE m_handle;
    WIN32_FIND_DATAW m_data;
};

Vector<String> PluginInfoStore::pluginPathsInDirectory(const String& directory)
{
    Vector<String> paths;

    PathWalker walker(directory);
    if (!walker.isValid())
        return paths;

    do {
        if (walker.data().dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        String filename = walker.data().cFileName;
        if ((!filename.startsWith("np", false) || !filename.endsWith("dll", false)) && (!equalIgnoringCase(filename, "Plugin.dll") || !directory.endsWith("Shockwave 10", false)))
            continue;

        paths.append(directory + "\\" + filename);
    } while (walker.step());

    return paths;
}

static String getVersionInfo(const LPVOID versionInfoData, const String& info)
{
    LPVOID buffer;
    UINT bufferLength;
    String subInfo = "\\StringfileInfo\\040904E4\\" + info;
    if (!::VerQueryValueW(versionInfoData, const_cast<UChar*>(subInfo.charactersWithNullTermination()), &buffer, &bufferLength) || !bufferLength)
        return String();

    // Subtract 1 from the length; we don't want the trailing null character.
    return String(reinterpret_cast<UChar*>(buffer), bufferLength - 1);
}

bool PluginInfoStore::getPluginInfo(const String& pluginPath, Plugin& plugin)
{
    String pathCopy = pluginPath;
    DWORD versionInfoSize = ::GetFileVersionInfoSizeW(pathCopy.charactersWithNullTermination(), 0);
    if (!versionInfoSize)
        return false;

    OwnArrayPtr<char> versionInfoData(new char[versionInfoSize]);
    if (!::GetFileVersionInfoW(pathCopy.charactersWithNullTermination(), 0, versionInfoSize, versionInfoData.get()))
        return false;

    String name = getVersionInfo(versionInfoData.get(), "ProductName");
    String description = getVersionInfo(versionInfoData.get(), "FileDescription");
    if (name.isNull() || description.isNull())
        return false;

    Vector<String> types;
    getVersionInfo(versionInfoData.get(), "MIMEType").split('|', types);
    Vector<String> extensionLists;
    getVersionInfo(versionInfoData.get(), "FileExtents").split('|', extensionLists);
    Vector<String> descriptions;
    getVersionInfo(versionInfoData.get(), "FileOpenName").split('|', descriptions);

    Vector<MimeClassInfo> mimes(types.size());
    for (size_t i = 0; i < types.size(); i++) {
        String type = types[i].lower();
        String description = i < descriptions.size() ? descriptions[i] : "";
        String extensionList = i < extensionLists.size() ? extensionLists[i] : "";

        Vector<String> extensionsVector;
        extensionList.split(',', extensionsVector);

        // Get rid of the extension list that may be at the end of the description string.
        int pos = description.find("(*");
        if (pos != -1) {
            // There might be a space that we need to get rid of.
            if (pos > 1 && description[pos - 1] == ' ')
                pos--;
            description = description.left(pos);
        }

        mimes[i].type = type;
        mimes[i].desc = description;
        mimes[i].extensions.swap(extensionsVector);
    }

    plugin.path = pluginPath;
    plugin.info.desc = description;
    plugin.info.name = name;
    plugin.info.file = pathGetFileName(pluginPath);
    plugin.info.mimes.swap(mimes);
    return true;
}

bool PluginInfoStore::shouldUsePlugin(const Plugin& plugin, const Vector<Plugin>& loadedPlugins)
{
    // FIXME: <http://webkit.org/b/43509> Migrate logic here from
    // PluginDatabase::getPluginPathsInDirectories and PluginPackage::isPluginBlacklisted.
    notImplemented();
    return true;
}

} // namespace WebKit
