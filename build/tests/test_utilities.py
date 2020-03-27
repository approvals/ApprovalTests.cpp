import os
import unittest
from scripts.utilities import pushdir, popdir, use_directory


class TestUtilities(unittest.TestCase):
    def test_push_and_pop_directory(self):
        cwd = os.getcwd()
        pushdir('..')
        self.assertNotEqual(cwd, os.getcwd())
        popdir()
        self.assertEqual(cwd, os.getcwd())

    def test_with_push_directory(self):
        cwd = os.getcwd()
        with use_directory('..') as dir:
            self.assertNotEqual(cwd, os.getcwd())
        self.assertEqual(cwd, os.getcwd())


if __name__ == '__main__':
    unittest.main()
