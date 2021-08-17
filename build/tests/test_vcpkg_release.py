import unittest

from approvaltests.approvals import verify

from scripts.vcpkg_release import PrepareVcpkgRelease, DeployVcpkgRelease
from scripts.vcpkg_release_details import VcpkgReleaseDetails
from scripts.project_details import ProjectDetails
from scripts.version import Version
from tests.helpers import set_home_directory


class TestVcpkgRelease(unittest.TestCase):
    def disable_test_entry_point_for_sync_vcpkg(self) -> None:
        set_home_directory()
        # PrepareVcpkgRelease.reset_and_clean_vcpkg_repo()

    def test_vcpkg_json(self) -> None:
        text = PrepareVcpkgRelease.create_vcpkg_vcpkg_json_text(Version(1, 2, 3))
        verify(text)

    def test_portfile_cmake(self) -> None:
        text = PrepareVcpkgRelease.create_portfile_cmake_text(Version(1, 2, 3),
                                                                  "single_header_sha",
                                                                  "licence_sha")
        verify(text)

    def test_vcpkg_approvaltests_dir(self) -> None:
        set_home_directory()
        vcpkg_release_details = VcpkgReleaseDetails(ProjectDetails())
        self.assertTrue(vcpkg_release_details.vcpkg_approvaltests_dir.endswith('approval-tests-cpp'))

    def test_can_find_vcpkg_repo(self) -> None:
        set_home_directory()
        # Validate that function does not throw exception.
        # Will fail if person running test has not cloned vcpkg-center-index
        directory = VcpkgReleaseDetails.get_vcpkg_repo_directory()
        print(directory)

    def test_vcpkg_version_number(self) -> None:
        releases = PrepareVcpkgRelease.get_accepted_approval_releases(ProjectDetails())
        #print(f'Release: {releases}')
        self.assertIn('10.9.1', releases)

    def test_get_new_branch_name(self) -> None:
        self.assertEqual('approval-tests-cpp.1.2.3',
                         PrepareVcpkgRelease.get_new_branch_name(ProjectDetails(), Version(1, 2, 3)))



