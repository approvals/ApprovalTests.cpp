import unittest
import textwrap
import inspect
from approvaltests.approvals import verify

from scripts.multiline_string_utilities import remove_indentation, remove_indentation_from
from tests.helpers import diff_merge_reporter


class TestMultilineStringUtilities(unittest.TestCase):

    def test_remove_indentation_from_works_perfectly(self) -> None:
        text = remove_indentation_from('''
        
            ^^ Blank line above ^^
            
            Here is some text
              1. with some indentation
              2. and more
                a. even more
              3. little less
            
            VV Blank line Below VV 
            
            ''')
        verify("remove_indentation_from\n" + text, diff_merge_reporter)

    def test_remove_indentation_works_perfectly(self) -> None:
        text = remove_indentation << '''
        
            ^^ Blank line above ^^
            
            Here is some text
              1. with some indentation
              2. and more
                a. even more
              3. little less
            
            VV Blank line Below VV 
            
            '''
        verify("remove_indentation\n" + text, diff_merge_reporter)

    def test_dedent_extra_line_above(self) -> None:
        text = textwrap.dedent('''
        
            ^^ Blank line above ^^
            
            Here is some text
              1. with some indentation
              2. and more
                a. even more
              3. little less
            
            VV Blank line Below VV 
            
            ''')
        verify("dedent\n" + text, diff_merge_reporter)

    def test_inspect_removes_all_surounding_blank_lines(self) -> None:
        text = inspect.cleandoc('''
        
            ^^ Blank line above ^^
            
            Here is some text
              1. with some indentation
              2. and more
                a. even more
              3. little less
            
            VV Blank line Below VV 
            
            ''')
        verify("inspect.cleandoc\n" + text, diff_merge_reporter)

if __name__ == '__main__':
    unittest.main()
