import os
import unittest
from scripts.utilities import pushdir, popdir, use_directory, write_file, replace_text_in_file, read_file, get_file_name


class TestUtilities(unittest.TestCase):
    def test_push_and_pop_directory(self):
        cwd = os.getcwd()
        pushdir('..')
        self.assertNotEqual(cwd, os.getcwd())
        popdir()
        self.assertEqual(cwd, os.getcwd())

    def test_with_push_directory(self):
        cwd = os.getcwd()
        with use_directory('..'):
            self.assertNotEqual(cwd, os.getcwd())
        self.assertEqual(cwd, os.getcwd())

    def test_file_reading_and_writing(self):
        text = '<caterpillar>blue</caterpillar>'
        file_name = 'bug.txt'
        write_file(file_name, text)
        replace_text_in_file(file_name, 'caterpillar', 'butterfly')
        new_text = read_file(file_name)
        self.assertEqual(new_text, '<butterfly>blue</butterfly>')
        os.remove(file_name)

    def test_get_file_name(self):
        self.assertEqual('file.txt', get_file_name('directory/file.txt'))
        self.assertEqual('file.txt', get_file_name('file.txt'))

if __name__ == '__main__':
    unittest.main()
