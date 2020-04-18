import unittest

from approvaltests.approvals import verify_all

from scripts.single_header_file import SingleHeaderFile, Parts


class TestSingleHeaderFile(unittest.TestCase):
    def test_sort_parts_by_dependencies(self) -> None:
        parts = [
            Parts('higher.h', ['lower.h']),
            Parts('lower.h', [])]
        self.assertTrue(SingleHeaderFile.depends_on(parts[0], parts[1]))
        self.assertFalse(SingleHeaderFile.depends_on(parts[1], parts[0]))

        parts = SingleHeaderFile.sort_parts_by_dependencies(parts)
        verify_all('sorted', parts)

    def test_depends_on_uses_whole_file_name(self) -> None:
        file1 = Parts('file1.h', [])
        file2 = Parts('file2.h', ['prefixed_file1.h'])
        self.assertFalse(SingleHeaderFile.depends_on(file2, file1))


if __name__ == '__main__':
    unittest.main()
