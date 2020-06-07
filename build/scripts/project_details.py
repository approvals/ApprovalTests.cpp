from dataclasses import dataclass

@dataclass
class ProjectDetails:
    github_project_name: str = 'ApprovalTests.cpp'
    library_folder_name: str = 'ApprovalTests'
    version_header: str = 'ApprovalTestsVersion.h'
    macro_prefix: str = 'APPROVAL_TESTS'
    conan_directory_name: str = 'approvaltests.cpp'
    update_documentation: bool = True
    update_conan: bool = True

# The __init__() is generated automatically
