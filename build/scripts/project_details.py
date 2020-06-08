from dataclasses import dataclass


@dataclass
class ProjectDetails:
    github_project_name: str = 'ApprovalTests.cpp'
    github_project_raw_content_url: str = f"https://raw.githubusercontent.com/approvals/{github_project_name}"
    github_project_url: str = f"https://github.com/approvals/{github_project_name}"
    library_folder_name: str = 'ApprovalTests'
    simulated_single_header_file: str = 'ApprovalTests.hpp'
    version_header: str = 'ApprovalTestsVersion.h'
    macro_prefix: str = 'APPROVAL_TESTS'
    conan_directory_name: str = 'approvaltests.cpp'
    update_documentation: bool = True
    update_conan: bool = True

# The __init__() is generated automatically
