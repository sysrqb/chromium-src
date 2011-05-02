# Copyright (c) 2011 Google Inc. All rights reserved.
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

import unittest

from webkitpy.common.system.filesystem_mock import MockFileSystem
from webkitpy.common.system.outputcapture import OutputCapture
from webkitpy.common.net.layouttestresults import LayoutTestResults
from webkitpy.tool.bot.layouttestresultsreader import *
from webkitpy.tool.mocktool import MockTool


class LayoutTestResultsReaderTest(unittest.TestCase):
    def test_missing_layout_test_results(self):
        tool = MockTool()
        reader = LayoutTestResultsReader(tool, "/var/logs")
        results_path = '/mock/results.html'
        tool.filesystem = MockFileSystem({results_path: None})
        # Make sure that our filesystem mock functions as we expect.
        self.assertRaises(IOError, tool.filesystem.read_text_file, results_path)
        # layout_test_results shouldn't raise even if the results.html file is missing.
        self.assertEquals(reader.results(), None)

    def test_layout_test_results(self):
        reader = LayoutTestResultsReader(MockTool(), "/var/logs")
        reader._read_file_contents = lambda path: None
        self.assertEquals(reader.results(), None)
        reader._read_file_contents = lambda path: ""
        self.assertEquals(reader.results(), None)
        reader._create_layout_test_results = lambda: LayoutTestResults([])
        results = reader.results()
        self.assertNotEquals(results, None)
        self.assertEquals(results.failure_limit_count(), 20)  # This value matches RunTests.NON_INTERACTIVE_FAILURE_LIMIT_COUNT

    def test_archive_last_layout_test_results(self):
        tool = MockTool()
        reader = LayoutTestResultsReader(tool, "/var/logs")
        patch = tool.bugs.fetch_attachment(128)
        # Should fail because the results_directory does not exist.
        expected_stderr = "/mock does not exist, not archiving.\n"
        archive = OutputCapture().assert_outputs(self, reader.archive, [patch], expected_stderr=expected_stderr)
        self.assertEqual(archive, None)

        results_directory = "/mock"
        # Sanity check what we assume our mock results directory is.
        self.assertEqual(reader._results_directory(), results_directory)
        tool.filesystem.maybe_make_directory(results_directory)
        self.assertTrue(tool.filesystem.exists(results_directory))

        self.assertNotEqual(reader.archive(patch), None)
        self.assertFalse(tool.filesystem.exists(results_directory))
