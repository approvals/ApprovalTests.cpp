import os
import unittest

from scripts.version import load_version, get_version_text, get_version_without_v, update_minor, update_patch, \
    update_major, create_version, no_version_change


class TestVersion(unittest.TestCase):
    def test_starting_point(self):
        version = self.load_test_version_ini()
        self.assertEqual('1.1.1', get_version_without_v(get_version_text(version)))

    def test_create_version(self):
        version = create_version(2, 3, 4)
        self.assertEqual('v.2.3.4', get_version_text(version))

    def test_updates(self):
        self.assert_version('v.1.1.1', no_version_change)
        self.assert_version('v.1.1.2', update_patch)
        self.assert_version('v.1.2.0', update_minor)
        self.assert_version('v.2.0.0', update_major)

    @staticmethod
    def load_test_version_ini():
        source_dir = os.path.split(__file__)[0]
        version = load_version(source_dir)
        return version

    def assert_version(self, expected_version, update_method):
        version = self.load_test_version_ini()
        version = update_method(version)
        self.assertEqual(expected_version, get_version_text(version))


if __name__ == '__main__':
    unittest.main()
