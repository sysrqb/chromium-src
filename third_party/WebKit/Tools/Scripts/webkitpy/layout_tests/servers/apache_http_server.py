#!/usr/bin/env python
# Copyright (C) 2011 Google Inc. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#     * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
#     * Neither the name of Google Inc. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

"""A class to start/stop the apache http server used by layout tests."""


import logging
import os
import re
import sys

from webkitpy.layout_tests.servers import http_server_base

_log = logging.getLogger("webkitpy.layout_tests.servers.apache_http_server")


class LayoutTestApacheHttpd(http_server_base.HttpServerBase):

    def __init__(self, port_obj, output_dir):
        """Args:
          port_obj: handle to the platform-specific routines
          output_dir: the absolute path to the layout test result directory
        """
        http_server_base.HttpServerBase.__init__(self, port_obj)
        # We use the name "httpd" instead of "apache" to make our paths (e.g. the pid file: /tmp/WebKit/httpd.pid)
        # match old-run-webkit-tests: https://bugs.webkit.org/show_bug.cgi?id=63956
        self._name = 'httpd'
        self._mappings = [{'port': 8000},
                          {'port': 8080},
                          {'port': 8081},
                          {'port': 8443, 'sslcert': True}]
        self._output_dir = output_dir
        port_obj.maybe_make_directory(output_dir)

        self._pid_file = self._filesystem.join(self._runtime_path, '%s.pid' % self._name)

        test_dir = self._port_obj.layout_tests_dir()
        js_test_resources_dir = self._cygwin_safe_join(test_dir, "fast", "js",
            "resources")
        media_resources_dir = self._cygwin_safe_join(test_dir, "media")
        mime_types_path = self._cygwin_safe_join(test_dir, "http", "conf",
            "mime.types")
        cert_file = self._cygwin_safe_join(test_dir, "http", "conf",
            "webkit-httpd.pem")
        access_log = self._cygwin_safe_join(output_dir, "access_log.txt")
        error_log = self._cygwin_safe_join(output_dir, "error_log.txt")
        document_root = self._cygwin_safe_join(test_dir, "http", "tests")

        # FIXME: We shouldn't be calling a protected method of _port_obj!
        executable = self._port_obj._path_to_apache()
        if self._is_cygwin():
            executable = self._get_cygwin_path(executable)

        start_cmd = [executable,
            '-f', "\"%s\"" % self._get_apache_config_file_path(test_dir, output_dir),
            '-C', "\'DocumentRoot \"%s\"\'" % document_root,
            '-c', "\'Alias /js-test-resources \"%s\"'" % js_test_resources_dir,
            '-c', "\'Alias /media-resources \"%s\"'" % media_resources_dir,
            '-C', "\'Listen %s\'" % "127.0.0.1:8000",
            '-C', "\'Listen %s\'" % "127.0.0.1:8081",
            '-c', "\'TypesConfig \"%s\"\'" % mime_types_path,
            '-c', "\'CustomLog \"%s\" common\'" % access_log,
            '-c', "\'ErrorLog \"%s\"\'" % error_log,
            '-C', "\'User \"%s\"\'" % os.environ.get("USERNAME",
                os.environ.get("USER", "")),
            '-c', "\'PidFile %s'" % self._pid_file,
            '-k', "start"]

        stop_cmd = [executable,
            '-f', "\"%s\"" % self._get_apache_config_file_path(test_dir, output_dir),
            '-c', "\'PidFile %s'" % self._pid_file,
            '-k', "stop"]

        if self._is_cygwin():
            cygbin = self._port_obj._path_from_base('third_party', 'cygwin',
                'bin')
            # Not entirely sure why, but from cygwin we need to run the
            # httpd command through bash.
            self._start_cmd = [
                os.path.join(cygbin, 'bash.exe'),
                '-c',
                'PATH=%s %s' % (self._get_cygwin_path(cygbin), " ".join(start_cmd)),
              ]
            self._stop_cmd = [
                os.path.join(cygbin, 'bash.exe'),
                '-c',
                'PATH=%s %s' % (self._get_cygwin_path(cygbin), " ".join(stop_cmd)),
              ]
        else:
            # TODO(ojan): When we get cygwin using Apache 2, use set the
            # cert file for cygwin as well.
            start_cmd.extend(['-c', "\'SSLCertificateFile %s\'" % cert_file])
            # Join the string here so that Cygwin/Windows and Mac/Linux
            # can use the same code. Otherwise, we could remove the single
            # quotes above and keep cmd as a sequence.
            self._start_cmd = " ".join(start_cmd)
            self._stop_cmd = " ".join(stop_cmd)

    def _is_cygwin(self):
        return sys.platform in ("win32", "cygwin")

    def _cygwin_safe_join(self, *parts):
        """Returns a platform appropriate path."""
        path = os.path.join(*parts)
        if self._is_cygwin():
            return self._get_cygwin_path(path)
        return path

    def _get_cygwin_path(self, path):
        """Convert a Windows path to a cygwin path.

        The cygpath utility insists on converting paths that it thinks are
        Cygwin root paths to what it thinks the correct roots are.  So paths
        such as "C:\b\slave\webkit-release\build\third_party\cygwin\bin"
        are converted to plain "/usr/bin".  To avoid this, we
        do the conversion manually.

        The path is expected to be an absolute path, on any drive.
        """
        drive_regexp = re.compile(r'([a-z]):[/\\]', re.IGNORECASE)

        def lower_drive(matchobj):
            return '/cygdrive/%s/' % matchobj.group(1).lower()
        path = drive_regexp.sub(lower_drive, path)
        return path.replace('\\', '/')

    def _get_apache_config_file_path(self, test_dir, output_dir):
        """Returns the path to the apache config file to use.
        Args:
          test_dir: absolute path to the LayoutTests directory.
          output_dir: absolute path to the layout test results directory.
        """
        httpd_config = self._port_obj._path_to_apache_config_file()
        httpd_config_copy = os.path.join(output_dir, "httpd.conf")
        httpd_conf = self._filesystem.read_text_file(httpd_config)
        if self._is_cygwin():
            # This is a gross hack, but it lets us use the upstream .conf file
            # and our checked in cygwin. This tells the server the root
            # directory to look in for .so modules. It will use this path
            # plus the relative paths to the .so files listed in the .conf
            # file. We have apache/cygwin checked into our tree so
            # people don't have to install it into their cygwin.
            cygusr = self._port_obj._path_from_base('third_party', 'cygwin',
                'usr')
            httpd_conf = httpd_conf.replace('ServerRoot "/usr"',
                'ServerRoot "%s"' % self._get_cygwin_path(cygusr))

        self._filesystem.write_text_file(httpd_config_copy, httpd_conf)

        if self._is_cygwin():
            return self._get_cygwin_path(httpd_config_copy)
        return httpd_config_copy

    def _spawn_process(self):
        _log.debug('Starting %s server, cmd="%s"' % (self._name, str(self._start_cmd)))
        retval, err = self._run(self._start_cmd)
        if retval or len(err):
            raise http_server_base.ServerError('Failed to start %s: %s' % (self._name, err))

        # For some reason apache isn't guaranteed to have created the pid file before
        # the process exits, so we wait a little while longer.
        if not self._wait_for_action(lambda: self._filesystem.exists(self._pid_file)):
            raise http_server_base.ServerError('Failed to start %s: no pid file found' % self._name)

        return int(self._filesystem.read_text_file(self._pid_file))

    def _stop_running_server(self):
        retval, err = self._run(self._stop_cmd)
        if retval or len(err):
            raise http_server_base.ServerError('Failed to stop %s: %s' % (self._name, err))

        # For some reason apache isn't guaranteed to have actually stopped after
        # the stop command returns, so we wait a little while longer for the
        # pid file to be removed.
        if not self._wait_for_action(lambda: not self._filesystem.exists(self._pid_file)):
            raise http_server_base.ServerError('Failed to stop %s: pid file still exists' % self._name)

    def _run(self, cmd):
        # Use shell=True because we join the arguments into a string for
        # the sake of Window/Cygwin and it needs quoting that breaks
        # shell=False.
        # FIXME: We should not need to be joining shell arguments into strings.
        # shell=True is a trail of tears.
        # Note: Not thread safe: http://bugs.python.org/issue2320
        process = self._executive.popen(cmd, shell=True, stderr=self._executive.PIPE)
        process.wait()
        retval = process.returncode
        err = process.stderr.read()
        return (retval, err)
