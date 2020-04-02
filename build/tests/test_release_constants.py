import unittest

from approvaltests import verify_as_json

from scripts.release_details import release_constants


class TestReleaseConstants(unittest.TestCase):
    def test(self):
        verify_as_json(release_constants)


if __name__ == '__main__':
    unittest.main()
