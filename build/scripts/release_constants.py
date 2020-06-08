import os

from scripts.project_details import ProjectDetails


class ReleaseLocations:
    def __init__(self, project_details: ProjectDetails) -> None:
        self.approval_tests_dir = F"../{project_details.library_folder_name}"
        self.main_project_dir = F"../../{project_details.github_project_name}"
        self.starter_project_dir = F"../../{project_details.github_project_name}.StarterProject"
        self.simulated_single_header_file_path = os.path.join(self.approval_tests_dir, project_details.simulated_single_header_file)


class ReleaseConstants:
    def __init__(self, project_details: ProjectDetails) -> None:
        self.locations = ReleaseLocations(project_details)

        self.build_dir = F"../build"
        self.release_dir = F"../build/releases"

        self.xxx_release_notes_path = os.path.join(self.build_dir, F'relnotes_x.y.z.md')
        self.release_notes_dir = os.path.join(self.build_dir, 'release_notes')
        self.template_release_notes_path = os.path.join(self.release_notes_dir, F'relnotes_template.md')


release_constants = ReleaseConstants(ProjectDetails())
