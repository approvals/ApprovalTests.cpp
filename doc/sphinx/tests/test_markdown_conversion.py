import unittest

# from .. import markdown_conversion
from doc.sphinx import markdown_conversion


class HyperlinkUpdatingTestCase(unittest.TestCase):
    def test_file_in_doc_links_to_top_in_file_in_doc(self):
        self.check(
            '["Target 1"](/doc/DisposableObjects.md#top)',
            '["Target 1"](DisposableObjects.html)',
            '',
            'CustomComparators')

    def test_anchor_is_not_top(self):
        self.check(
            r'[requirements for using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#requirements).',
            r'[requirements for using Approval Tests With \[Boost\].UT](UsingUT.html#requirements).',
            '',
            'CustomComparators')

    def test_file_in_subdir_links_to_file_in_dir_above(self):
        self.check(
            r'See [Target 1](/doc/Doc1.md#target1).',
            r'See [Target 1](../Doc1.html#target1).',
            'subdir',
            'CustomComparators')

    def test_file_in_parent_dir_links_to_file_in_subdir(self):
        self.check(
            r'See [Target 1](/doc/subdir/Doc1.md#target1).',
            r'See [Target 1](subdir/Doc1.html#target1).',
            '',
            'CustomComparators')

    def test_file_in_one_subdir_links_to_file_in_different_subdir(self):
        self.check(
            r'See [Target 1](/doc/subdir1/Doc1.md#target1).',
            r'See [Target 1](../subdir1/Doc1.html#target1).',
            'subdir2',
            'CustomComparators')

    def test_link_to_doc_directory(self):
        # For now, this will be unchanged. Eventually it will point to github
        self.check(
            r'[doc](/doc/).',
            r'[doc](/doc/).',
            'subdir2',
            'CustomComparators')

    # def test_multiple_links_on_one_line(self):
    #     self.check(
    #         r'See [Target 1](/doc/Doc1.md#target1) join1 [Target 2](/doc/Doc2.md#target3) join2 [Target 3](/doc/Doc3.md#target3).',
    #         r'See [Target 1](Doc1.html#target1) join1 [Target 2](Doc2.html#target3) join2 [Target 3](Doc3.html#target3).',
    #         '',
    #         'CustomComparators')

    def test_file_in_doc_links_to_top_in_file_outside_doc(self):
        # self.check(
        #     '["Target 1"](/doc/DisposableObjects.md#top)',
        #     '["Target 1"](DisposableObjects.html)',
        #     '',
        #     'CustomComparators')
        x = r'[How To Release](/build/HowToRelease.md#top)'

    def test_link_to_directory_outside_doc(self):
        x = r'[the build directory](/build/)'

    def test_link_to_sub_directory_outside_doc(self):
        x = r'[/ApprovalTests/integrations/](/ApprovalTests/integrations/)'

    def test_link_to_source_file(self):
        x = r'[tests/GoogleTest_Tests/main.cpp](/tests/GoogleTest_Tests/main.cpp)'

    def test_link_to_png_image(self):
        x = r'Tutorial ![New Failure](/doc/images/tutorial/01_new_failure.png?raw=true)'

    def test_link_to_gif(self):
        x = r'Tutorial ![Intro Graphic](/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true)'

    def check(self, content, expected, subdir, file_base_name):
        actual = markdown_conversion.fixup_markdown_hyperlinks(content, subdir, file_base_name)
        self.assertEqual(expected, actual)


if __name__ == '__main__':
    unittest.main()
