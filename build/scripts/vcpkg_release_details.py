import os

from scripts.project_details import ProjectDetails


class VcpkgReleaseDetails:
    def __init__(self, project_details: ProjectDetails) -> None:
        self.vcpkg_repo_dir = VcpkgReleaseDetails.get_vcpkg_repo_directory()
        self.vcpkg_approvaltests_dir = os.path.join(self.vcpkg_repo_dir, 'ports',
                                                    project_details.vcpkg_directory_name)

    @staticmethod
    def get_vcpkg_repo_directory() -> str:
        possibles = [
            '../../vcpkg',  # llewellyn
        ]
        for dir in possibles:
            if os.path.isdir(dir):
                return dir
        raise RuntimeError("Could not find fork of vcpkg")