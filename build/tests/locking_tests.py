import os
import unittest

from approvaltests.approvals import verify_file, verify

from scripts.documentation_release import PrepareDocumentationRelease
from scripts.prepare_release import PrepareRelease
from scripts.release_details import ReleaseDetails
from scripts.utilities import run
from scripts.version import create_version
from tests.helpers import set_home_directory, diff_merge_reporter


class TestForRegression(unittest.TestCase):

    def test_create_single_header_file_approvals(self):
        # The output of this depends on the current C++ code, so changes
        # over time. It is here to help when refactoring the release process.
        prepare_release = self.get_prepare_release()
        output = prepare_release.create_single_header_file()
        verify_file(output, diff_merge_reporter)

    def disabled_locking_test_create_simulated_single_header_file(self):
        # The output of this depends on the current C++ code, so changes
        # over time. It is here to help when refactoring the release process.
        prepare_release = self.get_prepare_release()
        output = prepare_release.create_simulated_single_header_file()
        verify_file(output, diff_merge_reporter)

    def get_prepare_release(self):
        set_home_directory()
        old_version = create_version(8, 4, 0)
        new_version = create_version(8, 5, 0)
        deploy = False
        release_details = ReleaseDetails(old_version, new_version, deploy)
        prepare_release = PrepareRelease(release_details)
        return prepare_release
