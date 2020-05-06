import unittest
from approvaltests.approvals import verify_with_namer, Namer
from approvaltests.reporters.generic_diff_reporter_factory import GenericDiffReporterFactory

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
    def test_convert_github_markdown_for_input_to_pandoc_in_root_docdir(self) -> None:
        with open('test_markdown_conversion_input.md') as f:
            input = f.read()

        converted_markdown, converted_rst = markdown_conversion.convert_markdown_text_to_restructured_text(input, '')

        reporter = GenericDiffReporterFactory().get('AraxisMergeMac')

        namer = Namer('.md')
        verify_with_namer(converted_markdown, namer, reporter)

        namer = Namer('.rst')
        verify_with_namer(converted_rst, namer, reporter)


if __name__ == '__main__':
    unittest.main()
