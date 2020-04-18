import os
import unittest

from scripts.version import get_version_text, get_version_without_v, update_minor, update_patch, \
    update_major, no_version_change, Version

from typing import Callable, Dict
class TestVersion(unittest.TestCase):
    def test_starting_point(self) -> None:
        version = self.load_test_version_ini()
        self.assertEqual('1.1.1', version.get_version_text_without_v())

    def test_create_version(self) -> None:
        version = Version(2, 3, 4)
        self.assertEqual('v.2.3.4', version.get_version_text())

    def test_updates(self) -> None:
        self.assert_version('v.1.1.1', no_version_change)
        self.assert_version('v.1.1.2', update_patch)
        self.assert_version('v.1.2.0', update_minor)
        self.assert_version('v.2.0.0', update_major)

    @staticmethod
    def load_test_version_ini() -> Version:
        source_dir = os.path.split(__file__)[0]
        version = Version.read(source_dir)
        return version

    def assert_version(self, expected_version: str, update_method: Callable) -> None:
        version = self.load_test_version_ini().as_map()
        version = update_method(version)
        self.assertEqual(expected_version, get_version_text(version))


if __name__ == '__main__':
    unittest.main()
