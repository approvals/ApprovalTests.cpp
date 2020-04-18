import os
import unittest

from approvaltests.approvals import verify_file, verify

from scripts.code_generation import CppGeneration
from scripts.documentation_release import PrepareDocumentationRelease
from scripts.prepare_release import PrepareRelease
from scripts.release_details import ReleaseDetails
from scripts.utilities import run
from scripts.version import create_version, Version
from tests.helpers import set_home_directory


class TestForLocking(unittest.TestCase):

    def test_create_single_header_file_approvals(self) -> None:
        prepare_release = self.get_prepare_release()
        output = prepare_release.create_single_header_file()

        # The output of this depends on the current C++ code, so changes
        # over time. It is here to help when refactoring the release process.
        # verify_file(output)

    def test_create_simulated_single_header_file(self) -> None:
        prepare_release = self.get_prepare_release()
        output = prepare_release.create_simulated_single_header_file()

        # The output of this depends on the current C++ code, so changes
        # over time. It is here to help when refactoring the release process.
        # verify_file(output)

    def get_prepare_release(self) -> CppGeneration:
        set_home_directory()
        old_version = Version(8, 4, 0)
        new_version = Version(8, 5, 0)
        deploy = False
        release_details = ReleaseDetails(old_version, new_version, deploy)
        return CppGeneration(release_details)
