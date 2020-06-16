import unittest

from approvaltests.approvals import verify_as_json

from scripts.project_details import ProjectDetails


class TestProjectDetails(unittest.TestCase):
    def test(self) -> None:
        details = ProjectDetails()
        verify_as_json(details)


if __name__ == '__main__':
    unittest.main()
