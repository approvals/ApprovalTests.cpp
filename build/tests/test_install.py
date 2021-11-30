import os
import re
import unittest
from typing import Callable, List

from approvaltests import verify_all

from scripts.utilities import read_file
from tests.helpers import set_home_directory


class TestInstall(unittest.TestCase):

    def test_includes_are_fully_qualified(self) -> None:
        set_home_directory()

        def with_invalid_include(filename: str) -> bool:
            content = read_file(filename)
            invalid_include = r'#include \"[^A]'
            return re.search(invalid_include, content) is not None

        all_files = self.find_all_files(".h", with_invalid_include, "../ApprovalTests")

        verify_all("Files that have include without ApprovalTests/ prefix",
                   all_files, lambda f: str(f))

    def find_all_files(self, suffix: str, with_filter: Callable, directory: str) -> List[str]:
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
