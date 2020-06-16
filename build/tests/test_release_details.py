import unittest

from approvaltests.approvals import verify_as_json

from scripts.project_details import ProjectDetails
from scripts.release_details import ReleaseDetails
from scripts.version import Version


class TestReleaseDetails(unittest.TestCase):
    def test(self) -> None:
        details = ReleaseDetails(
            Version(1, 2, 3),
            Version(1, 2, 4),
            True,
            ProjectDetails())
        verify_as_json(details)


if __name__ == '__main__':
    unittest.main()
