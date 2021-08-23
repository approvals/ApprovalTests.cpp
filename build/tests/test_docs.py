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

        def filter(source_file):
            content = read_file(source_file)
            snippet = "begin-snippet"
            namespace = "using namespace ApprovalTests;"
            return snippet in content and namespace in content

        all_files = []
        for root, directories, files in os.walk("../tests"):
            for file in files:
                source_file = os.path.join(root, file)
                if file.endswith(".cpp") and filter(source_file):
                    all_files.append(source_file)
        all_files.sort()
        verify_all("Files that have both snippets and using namespace ApprovalTests", all_files)


if __name__ == '__main__':
    unittest.main()
