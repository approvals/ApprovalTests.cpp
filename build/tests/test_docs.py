import os
import unittest

from approvaltests import verify_all
from approvaltests.approvals import verify

from scripts.code_generation import CppGeneration
from scripts.project_details import ProjectDetails
from scripts.utilities import read_file
from scripts.version import Version
from tests.helpers import set_home_directory


class TestDocs(unittest.TestCase):

    def test_snippet_samples_compile(self) -> None:
        set_home_directory()
        all_files = []
        for root, directories, files in os.walk("../tests"):
            for file in files:
                if file.endswith(".cpp"):
                    file_text = os.path.join(root, file)
                    content = read_file(file_text)
                    if "begin-snippet" in content:
                        if "using namespace ApprovalTests;" in content:
                            all_files.append(file_text)
        all_files.sort()
        verify_all("Files that have both snippets and using namespace ApprovalTests", all_files)


if __name__ == '__main__':
    unittest.main()
