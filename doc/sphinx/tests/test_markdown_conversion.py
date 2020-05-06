import unittest
from approvaltests.approvals import verify_with_namer, Namer
from approvaltests.reporters.generic_diff_reporter_factory import GenericDiffReporterFactory

from doc.sphinx import markdown_conversion


class TestWholeConversion(unittest.TestCase):
    def test_convert_github_markdown_for_input_to_pandoc_in_root_docdir(self) -> None:
        with open('test_markdown_conversion_input.md') as f:
            input = f.read()
        converted = markdown_conversion.fix_up_markdown_content(
            '', 'test_markdown_conversion_input', input)

        namer = Namer('.md')

        reporter = GenericDiffReporterFactory().get('AraxisMergeMac')
        verify_with_namer(converted, namer, reporter)


if __name__ == '__main__':
    unittest.main()
