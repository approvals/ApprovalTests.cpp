import unittest

from approvaltests import verify
from approvaltests.reporters import GenericDiffReporterFactory

from scripts.multiline_string_utilities import remove_indentation


class TestMultilineStringUtilities(unittest.TestCase):

    def test_dedent(self):
        text = remove_indentation << '''
            Here is some text
              1. with some indentation
              2. and more
                a. even more
              3. little less
            '''
        verify(text, GenericDiffReporterFactory().get("DiffMerge"))


if __name__ == '__main__':
    unittest.main()
