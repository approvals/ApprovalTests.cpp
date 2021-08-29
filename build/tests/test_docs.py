import os
import unittest
from typing import Callable, List

from approvaltests import verify_all

from scripts.utilities import read_file
from tests.helpers import set_home_directory


class TestDocs(unittest.TestCase):

    def test_snippet_samples_compile(self) -> None:
        set_home_directory()

        def with_both(filename: str) -> bool:
            content = read_file(filename)
            snippet = "begin-snippet"
            namespace = "\nusing namespace ApprovalTests;"
            return snippet in content and namespace in content

        all_files = self.find_all_files(".cpp", with_both)
        verify_all("Files that have both snippets and using namespace ApprovalTests", all_files, lambda f: str(f))

    def find_all_files(self, suffix: str, with_filter: Callable, directory: str = "../tests") -> List[str]:
        all_files = []
        for root, directories, files in os.walk(directory):
            for file in files:
                source_file = os.path.join(root, file)
                if file.endswith(suffix) and with_filter(source_file):
                    all_files.append(source_file)
        all_files.sort()
        return all_files


if __name__ == '__main__':
    unittest.main()
