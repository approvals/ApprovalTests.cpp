import shutil
import time
from collections import Callable

from scripts.release_constants import release_constants
from scripts.utilities import read_file, use_directory, replace_text_in_file, run, check_step


from scripts.release_details import ReleaseDetails
from typing import Callable
class PrepareDocumentationRelease:
    @staticmethod
    def prepare_documentation(details: ReleaseDetails) -> None:
        if not details.project_details.update_documentation:
            return

        PrepareDocumentationRelease.update_features_page(details)
        PrepareDocumentationRelease.update_readme_and_docs(details)
        PrepareDocumentationRelease.prepare_release_notes(details)
        PrepareDocumentationRelease.regenerate_markdown()

    @staticmethod
    def prepare_update_features_page(old_version: str, new_version: str, content: str) -> Callable:
        missing_features = ('\n'
                            '## v.x.y.z\n'
                            '\n'
                            f'## v.'
                            )
        if missing_features in content:
            def check(features_file: str, action:Callable = check_step) -> Callable:
                return action("the Features page is empty: are you sure you want this?")
            return check
        else:
            update_version = ('\n'
                              '## v.x.y.z\n'
                              '\n'
                              f'## {new_version}\n'
                              )

            def replace(features_file: str, replace_text_in_file_action: Callable = replace_text_in_file) -> Callable:
                return replace_text_in_file_action(features_file, '\n## v.x.y.z\n', update_version)
            return replace

    @staticmethod
    def update_features_page(details: ReleaseDetails) -> None:
        features_file = '../doc/Features.md'
        content = read_file(features_file)
        update_file = PrepareDocumentationRelease.prepare_update_features_page(details.old_version_as_text(), details.new_version_as_text(), content)
        update_file(features_file)

    @staticmethod
    def update_readme_and_docs(details: ReleaseDetails) -> None:
        with use_directory(".."):
            replace_text_in_file("README.md", details.old_version_as_text(), details.new_version_as_text())

    @staticmethod
    def prepare_release_notes(details: ReleaseDetails) -> None:
        replace_text_in_file(release_constants.xxx_release_notes_path, 'v.x.y.z', details.new_version_as_text())
        shutil.move(release_constants.xxx_release_notes_path, details.new_release_notes_path)

        # Make sure the above move has finished, before we create the new xxx file:
        time.sleep(1)

        shutil.copyfile(release_constants.template_release_notes_path, release_constants.xxx_release_notes_path)

    @staticmethod
    def regenerate_markdown() -> None:
        with use_directory(".."):
            # run(["./run_markdown_templates.sh"])
            pass # disabled to enable running on WSL
