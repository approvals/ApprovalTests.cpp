import unittest

from approvaltests.approvals import verify_as_json

from scripts.release_constants import release_constants


class TestReleaseConstants(unittest.TestCase):
    def test(self) -> None:
        verify_as_json(release_constants)


if __name__ == '__main__':
    unittest.main()
