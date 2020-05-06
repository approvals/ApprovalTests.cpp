import unittest
from approvaltests.approvals import verify_with_namer, Namer

# from .. import markdown_conversion
from doc.sphinx import markdown_conversion


class HyperlinkUpdatingTestCase(unittest.TestCase):
    def test_file_in_doc_links_to_top_in_file_in_doc(self):
        self.check(
            '["Target 1"](/doc/DisposableObjects.md#top)',
            '["Target 1"](DisposableObjects.html)')

    def test_anchor_is_not_top(self):
        self.check(
            r'[requirements for using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#requirements).',
            r'[requirements for using Approval Tests With \[Boost\].UT](UsingUT.html#requirements).')

    def test_file_in_subdir_links_to_file_in_dir_above(self):
        self.check(
            r'See [Target 1](/doc/Doc1.md#target1).',
            r'See [Target 1](../Doc1.html#target1).',
            'subdir')

    def test_file_in_parent_dir_links_to_file_in_subdir(self):
        self.check(
            r'See [Target 1](/doc/subdir/Doc1.md#target1).',
            r'See [Target 1](subdir/Doc1.html#target1).')

    def test_file_in_one_subdir_links_to_file_in_different_subdir(self):
        self.check(
            r'See [Target 1](/doc/subdir1/Doc1.md#target1).',
            r'See [Target 1](../subdir1/Doc1.html#target1).',
            'subdir2')

    def test_link_to_doc_directory(self):
        self.check(
            r'[doc](/doc/).',
            r'[doc](https://github.com/approvals/ApprovalTests.cpp/tree/master/doc).',
            'subdir2')

    def test_anchor_with_multiple_non_standard_characters(self):
        self.check(
            r'[Existing Project - with your main()](/doc/UsingCatch.md#existing-project---with-your-main).',
            r'[Existing Project - with your main()](UsingCatch.html#existing-project-with-your-main).')

        self.check(
            r'[TCR](/doc/Glossary.md#test--commit--revert-tcr).',
            r'[TCR](Glossary.html#test-commit-revert-tcr).')

    def test_multiple_links_on_one_line(self):
        self.check(
            r'See [Target 1](/doc/Doc1.md#target1) join1 [Target 2](/doc/Doc2.md#target3) join2 [Target 3](/doc/Doc3.md#target3).',
            r'See [Target 1](Doc1.html#target1) join1 [Target 2](Doc2.html#target3) join2 [Target 3](Doc3.html#target3).')

    def test_file_in_doc_links_to_top_in_file_outside_doc(self):
        self.check(
            r'[How To Release](/build/HowToRelease.md#top)',
            r'[How To Release](https://github.com/approvals/ApprovalTests.cpp/blob/master/build/HowToRelease.md#top)')

    def test_link_to_directory_outside_doc(self):
        self.check(
            r'[the build directory](/build/)',
            r'[the build directory](https://github.com/approvals/ApprovalTests.cpp/tree/master/build)')

    def test_link_to_sub_directory_outside_doc(self):
        self.check(
            r'[/ApprovalTests/integrations/](/ApprovalTests/integrations/)',
            r'[/ApprovalTests/integrations/](https://github.com/approvals/ApprovalTests.cpp/tree/master/ApprovalTests/integrations)')

    def test_link_to_file_file_outside_source_doc(self):
        self.check(
            r'[tests/GoogleTest_Tests/main.cpp](/tests/GoogleTest_Tests/main.cpp)',
            r'[tests/GoogleTest_Tests/main.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/main.cpp)')

    def test_link_that_is_already_a_hyperlink(self):
        # https:
        self.check_unchanged(
            r'[Quickly Testing Legacy Code](https://youtu.be/dtm8V3TIB6k)')

        # http:
        self.check_unchanged(
            r'[Quickly Testing Legacy Code](http://youtu.be/dtm8V3TIB6k)')

    def test_mailto_link(self):
        self.check_unchanged(
            r'[Llewellyn](mailto:llewellyn.falco@gmail.com)')

    def test_link_to_png_image(self):
        # For now, link to image online. Later, try embedding it in the Sphinx docs
        self.check(
            r'Tutorial ![New Failure](/doc/images/tutorial/01_new_failure.png?raw=true)',
            r'Tutorial ![New Failure](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/images/tutorial/01_new_failure.png?raw=true)',
            '')

    def test_link_to_gif(self):
        # For now, link to image online. Later, try embedding it in the Sphinx docs
        self.check(
            r'Tutorial ![Intro Graphic](/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true)',
            r'Tutorial ![Intro Graphic](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true)',
            '')

    def test_to_anchor_in_same_document(self):
        self.check_unchanged(
            r'[1](#footnote1)')

    def check(self, content, expected, subdir=''):
        actual = markdown_conversion.fixup_markdown_hyperlinks(content, subdir, 'SomeDocFile')
        self.assertEqual(expected, actual)

    def check_unchanged(self, content, subdir=''):
        actual = markdown_conversion.fixup_markdown_hyperlinks(content, subdir, 'SomeDocFile')
        self.assertEqual(content, actual)


class TestWholeConversion(unittest.TestCase):
    def test_convert_github_markdown_for_input_to_pandoc_in_root_docdir(self) -> None:
        with open('test_markdown_conversion_input.md') as f:
            input = f.read()
        converted = markdown_conversion.fix_up_markdown_content(
            '', 'test_markdown_conversion_input', input)

        namer = Namer('.md')
        verify_with_namer(converted, namer, None)


if __name__ == '__main__':
    unittest.main()
