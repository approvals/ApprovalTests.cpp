import unittest

from approvaltests.approvals import verify

from scripts.deploy_release import DeployRelease
from scripts.project_details import ProjectDetails
from scripts.release_details import ReleaseDetails
from scripts.version import Version
from tests.helpers import set_home_directory


class TestDeployRelease(unittest.TestCase):
    def test_get_github_release_url(self) -> None:
        deploy_release = self.get_deploy_release()
        verify(deploy_release.get_github_release_url())

    def test_get_tweet_text(self) -> None:
        deploy_release = self.get_deploy_release()
        verify(deploy_release.get_tweet_text())

    def get_deploy_release(self) -> DeployRelease:
        set_home_directory()
        old_version = Version(0, 0, 1)
        new_version = Version(0, 1, 0)
        deploy = False
        release_details = ReleaseDetails(old_version, new_version, deploy, ProjectDetails())
        return DeployRelease(release_details)
