import os


class ConanReleaseDetails:
    def __init__(self) -> None:
        self.conan_repo_dir = ConanReleaseDetails.get_conan_repo_directory()
        self.conan_approvaltests_dir = os.path.join(self.conan_repo_dir, 'recipes', 'approvaltests.cpp')

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