import unittest
import pyperclip

from approvaltests import verify
from scripts.multiline_string_utilities import remove_indentation
from tests.helpers import diff_merge_reporter
# Convenience variable, so we can paste in code and run test_demo_convert_to_concatenation.
# This is at global scope to prevent PyCharm reformatting the indentation when we
# paste code in.

to_concatened_string = 'your string here'

to_multiline_string = ('your string here')

class CodeGeneration:
    @staticmethod
    def convert_concatenation_to_multiline(content):
        stripped = content.strip()[1:-1]
        lines = stripped.splitlines()
        code = "remove_indentation << f'''\n"
        for line in lines[:-1]:
            if line.startswith("f"):
                line = line [1:]
            cleaned = line[1:-1].replace("\\n", "\n")
            code += cleaned
        code += "'''"
        return code

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

    def test_concatentation_to_multiline(self):

        input = remove_indentation << r"""
            ('\n'
            'toc\n'
            '\n'
            '## v.x.y.z\n'
            '\n'
            f'{self.old_feature_text()}\n'
            '\n'
            )"""
        output = CodeGeneration.convert_concatenation_to_multiline(input)
        verify(output, diff_merge_reporter)

    def test_entry_point_for_convert_to_concatenation(self):
        if to_concatened_string != 'your string here':
            pyperclip.copy(CodeGeneration.convert_string_to_concatenation(to_concatened_string))
            print("converted concatened text copied to clipboard")

    def test_entry_point_for_convert_to_multiline(self):
        if to_multiline_string != 'your string here':
            pyperclip.copy(CodeGeneration.convert_string_to_concatenation(to_multiline_string))
            print("converted multiline text copied to clipboard")


if __name__ == '__main__':
    unittest.main()
