import unittest

# Convenience variable, so we can paste in code and run test_demo_convert_to_concatenation.
# This is at global scope to prevent PyCharm reformatting the indentation when we
# paste code in.
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
        content = '''
toc

## v.x.y.z

{self.old_feature_text()}

'''
        result = CodeGeneration.convert_string_to_concatenation(content)
        expected = r"""('\n'
'toc\n'
'\n'
'## v.x.y.z\n'
'\n'
f'{self.old_feature_text()}\n'
'\n'
)"""
        self.assertEqual(expected, result)

    def test_convert_string_to_joined_list(self):
        content = '''
toc

## v.x.y.z

{self.old_feature_text()}

'''
        result = CodeGeneration.convert_string_to_joined_list(content)
        expected = r"""'\n'.join([
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
        print(CodeGeneration.convert_string_to_concatenation(concatened_string))


if __name__ == '__main__':
    unittest.main()
