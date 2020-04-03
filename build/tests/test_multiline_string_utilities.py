import unittest

from approvaltests import verify

from scripts.multiline_string_utilities import remove_indentation
from tests.helpers import diff_merge_reporter


class TestMultilineStringUtilities(unittest.TestCase):

    def test_dedent(self):
        text = remove_indentation << '''
            Here is some text
              1. with some indentation
              2. and more
                a. even more
              3. little less
            '''
        verify(text, diff_merge_reporter)


if __name__ == '__main__':
    unittest.main()
