import textwrap

import pyperclip
import unittest

# Convenience variable, so we can paste in code and run test_demo_convert_to_concatenation.
# This is at global scope to prevent PyCharm reformatting the indentation when we
# paste code in.
from approvaltests import verify
from approvaltests.reporters import GenericDiffReporterFactory
from approvaltests.reporters.generic_diff_reporter import GenericDiffReporter

from scripts.multiline_string_utilities import remove_indentation

concatened_string = 'your string here'


class CodeGeneration:
    @staticmethod
    def convert_string_to_concatenation(content):
        lines = content.splitlines()
        code = '('
        for line in lines:
            if '{' in line:
                code += 'f'
            code += f"'{line}\\n'\n"
        code += ')'
        return code

    @staticmethod
    def convert_string_to_joined_list(content):
        lines = content.splitlines()
        code = "'\\n'.join([\n"
        for line in lines:
            if '{' in line:
                code += 'f'
            code += f"'{line}',\n"
        code += '])'
        return code



class TestCodeGeneration(unittest.TestCase):

    def test_convert_string_to_concatentation(self):
        content = remove_indentation << '''
        
            toc
            
            ## v.x.y.z
            
            {self.old_feature_text()}
            
            '''
        result = CodeGeneration.convert_string_to_concatenation(content)
        expected = remove_indentation << r"""
            ('\n'
            'toc\n'
            '\n'
            '## v.x.y.z\n'
            '\n'
            f'{self.old_feature_text()}\n'
            '\n'
            )"""
        self.assertEqual(expected, result)

    def test_convert_string_to_joined_list(self):
        content = remove_indentation << '''
        
            toc
            
            ## v.x.y.z
            
            {self.old_feature_text()}
            
            '''
        result = CodeGeneration.convert_string_to_joined_list(content)
        expected = remove_indentation << r"""
        '\n'.join([
        '',
        'toc',
        '',
        '## v.x.y.z',
        '',
        f'{self.old_feature_text()}',
        '',
        ])"""
        self.assertEqual(expected, result)

    def test_entry_point_for_convert_to_concatenation(self):
        if concatened_string != 'your string here':
            pyperclip.copy(CodeGeneration.convert_string_to_concatenation(concatened_string))
            print("converted text copied to clipboard")


if __name__ == '__main__':
    unittest.main()
