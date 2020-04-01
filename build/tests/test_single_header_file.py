import unittest

from approvaltests import verify_all

from scripts.single_header_file import SingleHeaderFile


class TestSingleHeaderFile(unittest.TestCase):
    def test_sort_parts_by_dependencies(self):
        parts = [
            {'file': 'higher.h', 'include': ['lower.h']},
            {'file': 'lower.h', 'include': []}]
        self.assertTrue(SingleHeaderFile.depends_on(parts[0], parts[1]))

        parts = SingleHeaderFile.sort_parts_by_dependencies(parts)
        verify_all('sorted', parts)


if __name__ == '__main__':
    unittest.main()
