import os

from scripts.project_details import ProjectDetails


class ReleaseLocations:
    def __init__(self, project_details: ProjectDetails) -> None:
        self.approval_tests_dir = F"../{project_details.library_folder_name}"
        self.main_project_dir = F"../../{project_details.github_project_name}"
        self.starter_project_dir = F"../../{project_details.github_project_name}.StarterProject"
        self.simulated_single_header_file_path = os.path.join(self.approval_tests_dir, project_details.simulated_single_header_file)