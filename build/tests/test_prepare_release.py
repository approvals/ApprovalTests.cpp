import os
import unittest

from approvaltests.approvals import verify_file

from scripts.documentation_release import PrepareDocumentationRelease
from scripts.prepare_release import PrepareRelease
from scripts.release_details import ReleaseDetails
from scripts.utilities import run
from scripts.version import create_version
from tests.test_conan_release import set_home_directory


class TestPrepareRelease(unittest.TestCase):
    def test_update_features_with_new_features(self):
        content = f'''
toc

## v.x.y.z

{self.new_feature_text()}

{self.old_feature_text()}

'''
        expected_new_content = f'''
toc

## v.x.y.z

## v.1.2.4

{self.new_feature_text()}

{self.old_feature_text()}

'''
        old_version = "v.1.2.3"
        new_version = "v.1.2.4"
        action = PrepareDocumentationRelease.prepare_update_features_page(old_version, new_version, content)
        new_content = action("", lambda _, old, new: content.replace(old, new))
        self.assertEqual(expected_new_content, new_content)

    def test_update_features_with_no_new_features(self):
        content = f'''
toc

## v.x.y.z

{self.old_feature_text()}

'''
        old_version = "v.1.2.3"
        new_version = "v.1.2.4"
        action = PrepareDocumentationRelease.prepare_update_features_page(old_version, new_version, content)
        new_content = action("", lambda text: f'CHECK: {text}')
        self.assertEqual(new_content, 'CHECK: the Features page is empty: are you sure you want this?')

    def test_create_single_header_file_approvals(self):
        prepare_release = self.get_prepare_release()
        output = prepare_release.create_single_header_file()
        verify_file(output)

    def test_create_simulated_single_header_file(self):
        prepare_release = self.get_prepare_release()
        output = prepare_release.create_simulated_single_header_file()
        verify_file(output)

    def get_prepare_release(self):
        set_home_directory()
        old_version = create_version(8, 4, 0)
        new_version = create_version(8, 5, 0)
        deploy = False
        release_details = ReleaseDetails(old_version, new_version, deploy)
        prepare_release = PrepareRelease(release_details)
        return prepare_release

    @staticmethod
    def new_feature_text():
        return (
            '### New Feature\n'
            '\n'
            'New feature details.'
        )

    @staticmethod
    def old_feature_text():
        return (
            '## v.1.2.3\n'
            '\n'
            '### Old Feature\n'
            '\n'
            'Old feature details.'
        )


if __name__ == '__main__':
    unittest.main()
