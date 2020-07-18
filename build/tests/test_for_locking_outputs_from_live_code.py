import unittest

from approvaltests.approvals import verify, verify_file

from scripts.code_generation import CppGeneration
from scripts.project_details import ProjectDetails
from scripts.release_details import ReleaseDetails
from scripts.single_header_file import SingleHeaderFile
from scripts.version import Version
from tests.helpers import set_home_directory


class TestForLocking(unittest.TestCase):

    def disabled_test_create_single_header_file_approvals(self) -> None:
        prepare_release = self.get_prepare_release()
        output = prepare_release.create_single_header_file()

        # The output of this depends on the current C++ code, so changes
        # over time. It is here to help when refactoring the release process.
        verify_file(output)

    def disabled_test_create_simulated_single_header_file(self) -> None:
        # The output of this depends on the current C++ code, so changes
        # over time. It is here to help when refactoring the release process.
        prepare_release = self.get_prepare_release()
        verify(SingleHeaderFile.create_content('.', prepare_release.details.project_details, include_cpps=False))

    def disabled_test_create_simulated_single_header_file_with_cpps(self) -> None:
        # The output of this depends on the current C++ code, so changes
        # over time. It is here to help when refactoring the release process.
        prepare_release = self.get_prepare_release()
        verify(SingleHeaderFile.create_content('.', prepare_release.details.project_details, include_cpps=True))

    def get_prepare_release(self) -> CppGeneration:
        set_home_directory()
        old_version = Version(8, 4, 0)
        new_version = Version(8, 5, 0)
        deploy = False
        release_details = ReleaseDetails(old_version, new_version, deploy, ProjectDetails())
        return CppGeneration(release_details)
