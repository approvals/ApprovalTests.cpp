from dataclasses import dataclass


@dataclass
class ProjectDetails:
    github_project_name: str = 'ApprovalTests.cpp'
    library_folder_name: str = 'ApprovalTests'
    simulated_single_header_file: str = 'ApprovalTests.hpp'
    version_header: str = 'ApprovalTestsVersion.h'
    macro_prefix: str = 'APPROVAL_TESTS'
    conan_directory_name: str = 'approvaltests.cpp'
    vcpkg_directory_name: str = 'approval-tests-cpp'
    update_documentation: bool = True
    update_conan: bool = True
    update_vcpkg: bool = True

    # The __init__() is generated automatically

    @property
    def github_project_raw_content_url(self) -> str:
        return f"https://raw.githubusercontent.com/approvals/{self.github_project_name}"

    @property
    def github_project_url(self) -> str:
        return f"https://github.com/approvals/{self.github_project_name}"
