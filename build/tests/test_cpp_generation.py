import unittest

from approvaltests.approvals import verify

from scripts.code_generation import CppGeneration
from scripts.version import create_version


class TestCppGeneration(unittest.TestCase):

    def test_update_version_number_header(self) -> None:
        new_version = create_version(8, 5, 0)
        output = CppGeneration.get_version_number_hpp_text(new_version)
        verify(output)




if __name__ == '__main__':
    unittest.main()
