import shutil
import time

from scripts.release_constants import release_constants
from scripts.utilities import read_file, use_directory, replace_text_in_file, run, check_step


class PrepareDocumentationRelease:
    @staticmethod
    def prepare_documentation(details):
        PrepareDocumentationRelease.update_features_page(details)
        PrepareDocumentationRelease.update_readme_and_docs(details)
        PrepareDocumentationRelease.prepare_release_notes(details)
        PrepareDocumentationRelease.regenerate_markdown()

    @staticmethod
    def prepare_update_features_page(old_version, new_version, content):
        missing_features = ('\n'
                            '## v.x.y.z\n'
                            '\n'
                            f'## {old_version}\n'
                            )
        if missing_features in content:
            def check(features_file, action = check_step):
                return action("the Features page is empty: are you sure you want this?")
            return check
        else:
            update_version = ('\n'
                              '## v.x.y.z\n'
                              '\n'
                              f'## {new_version}\n'
                              )

            def replace(features_file, replace_text_in_file_action = replace_text_in_file):
                return replace_text_in_file_action(features_file, '\n## v.x.y.z\n', update_version)
            return replace

    @staticmethod
    def update_features_page(details):
        features_file = '../doc/mdsource/Features.source.md'
        content = read_file(features_file)
        update_file = PrepareDocumentationRelease.prepare_update_features_page(details.old_version, details.new_version, content)
        update_file(features_file)

    @staticmethod
    def update_readme_and_docs(details):
        with use_directory(".."):
            replace_text_in_file("mdsource/README.source.md", details.old_version, details.new_version)

    @staticmethod
    def prepare_release_notes(details):
        replace_text_in_file(release_constants.xxx_release_notes_path, 'v.x.y.z', details.new_version)
        shutil.move(release_constants.xxx_release_notes_path, details.new_release_notes_path)

        # Make sure the above move has finished, before we create the new xxx file:
        time.sleep(1)

        shutil.copyfile(release_constants.template_release_notes_path, release_constants.xxx_release_notes_path)

    @staticmethod
    def regenerate_markdown():
        with use_directory(".."):
            run(["./run_markdown_templates.sh"])