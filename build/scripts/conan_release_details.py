import os

from scripts.project_details import ProjectDetails


class ConanReleaseDetails:
    def __init__(self, project_details: ProjectDetails) -> None:
        self.conan_repo_dir = ConanReleaseDetails.get_conan_repo_directory()
        self.conan_approvaltests_dir = os.path.join(self.conan_repo_dir, 'recipes',
                                                    project_details.conan_directory_name)

    @staticmethod
    def get_conan_repo_directory() -> str:
        possibles = [
            '../../conan-center-index-claremacrae',  # llewellyn
            '../../../conan/conan-center-index-claremacrae'  # clare
        ]
        for dir in possibles:
            if os.path.isdir(dir):
                return dir
        raise RuntimeError("Could not find fork of conan-center-index")