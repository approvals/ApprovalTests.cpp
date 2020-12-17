import os
import unittest

from scripts.version import Version

from typing import Callable


class TestVersion(unittest.TestCase):
    def test_starting_point(self) -> None:
        version = self.load_test_version_ini()
        self.assertEqual('1.1.1', version.get_version_text_without_v())

    def test_create_version(self) -> None:
        version = Version(2, 3, 4)
        self.assertEqual('v.2.3.4', version.get_version_text())

    def test_updates(self) -> None:
        self.assert_version('v.1.1.1', (lambda v: v.clone()))
        self.assert_version('v.1.1.2', (lambda v: v.update_patch()))
        self.assert_version('v.1.2.0', (lambda v: v.update_minor()))
        self.assert_version('v.2.0.0', (lambda v: v.update_major()))

    def test_sorting(self) -> None:
        versions = ['10.2.3', '10.10.4', '9.1.1', '10.2.4']
        m = max(versions, key=lambda x: Version.from_string_without_v(x))
        self.assertEqual(m, '10.10.4')

    @staticmethod
    def load_test_version_ini() -> Version:
        source_dir = os.path.split(__file__)[0]
        version = Version.read(source_dir)
        return version

    def assert_version(self, expected_version: str, update_method: Callable[[Version], Version]) -> None:
        version = self.load_test_version_ini()
        version = update_method(version)
        self.assertEqual(expected_version, version.get_version_text())


if __name__ == '__main__':
    unittest.main()
