import unittest

from approvaltests import ApprovalException, StackFrameNamer
from approvaltests.approvals import verify_with_namer

import sys

sys.path.append('../../..')

from doc.sphinx import markdown_conversion


class HyperlinkUpdatingTestCase(unittest.TestCase):
    def test_file_in_subdir_links_to_file_in_dir_above(self):
        self.check(
            r'See [Target 1](/doc/Doc1.md#target1).',
            r'See [Target 1](../Doc1.html#target1).',
            'subdir')

    def test_file_in_parent_dir_links_to_file_in_subdir(self):
        self.check(
            r'See [Target 1](/doc/subdir/Doc1.md#target1).',
            r'See [Target 1](subdir/Doc1.html#target1).')

    def test_file_in_one_subdir_links_to_file_in_different_subdir(self):
        self.check(
            r'See [Target 1](/doc/subdir1/Doc1.md#target1).',
            r'See [Target 1](../subdir1/Doc1.html#target1).',
            'subdir2')

    def check(self, content, expected, subdir=''):
        actual = markdown_conversion.fixup_markdown_hyperlink_destinations(content, subdir)
        self.assertEqual(expected, actual)


class TestWholeConversion(unittest.TestCase):
    def test_convert_markdown_for_pandoc(self) -> None:
        with open('test_markdown_conversion_input.md') as f:
            input = f.read()

        converted_markdown, converted_rst = markdown_conversion.convert_markdown_text_to_restructured_text(input, '')

        # reporter = GenericDiffReporterFactory().get('AraxisMergeMac')
        reporter = None

        failure_count = 0

        try:
            namer = StackFrameNamer('.md')
            verify_with_namer(converted_markdown, namer, reporter)
        except(ApprovalException):
            failure_count += 1

        try:
            namer = StackFrameNamer('.rst')
            verify_with_namer(converted_rst, namer, reporter)
        except(ApprovalException):
            failure_count += 1

        self.assertEqual(failure_count, 0)

if __name__ == '__main__':
    unittest.main()
