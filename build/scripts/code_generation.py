import os

from scripts import version
from scripts.embed import create_single_header_file
from scripts.multiline_string_utilities import remove_indentation
from scripts.release_constants import release_constants
from scripts.release_details import ReleaseDetails
from scripts.single_header_file import SingleHeaderFile
from scripts.utilities import read_file, write_file, use_directory
from scripts.version import Version


from typing import Dict
class CppGeneration:
    def __init__(self, details: ReleaseDetails) -> None:
        self.details = details

    def update_version_number_header(self) -> None:
        with use_directory(release_constants.approval_tests_dir):
            version_header = os.path.join("ApprovalTestsVersion.h")

            text = CppGeneration.get_version_number_hpp_text(self.details.new_version)
            write_file(version_header, text)

    @staticmethod
    def get_version_number_hpp_text(version_object: Version) -> str:
        version_string = version_object.get_version_text_without_v()
        text = remove_indentation << f'''
                #pragma once

                #include "ApprovalTests/ApprovalsMacroDefaults.h"

                #define APPROVAL_TESTS_VERSION_MAJOR {version_object.major}
                #define APPROVAL_TESTS_VERSION_MINOR {version_object.minor}
                #define APPROVAL_TESTS_VERSION_PATCH {version_object.patch}
                #define APPROVAL_TESTS_VERSION_STR "{version_string}"

                #define APPROVAL_TESTS_VERSION                                                           \\
                    (APPROVAL_TESTS_VERSION_MAJOR * 10000 + APPROVAL_TESTS_VERSION_MINOR * 100 +         \\
                     APPROVAL_TESTS_VERSION_PATCH)
                '''
        return text

    def create_simulated_single_header_file(self) -> str:
        return SingleHeaderFile.create('.')

    def create_single_header_file(self) -> str:
        self.create_simulated_single_header_file()

        simulated_single_header = os.path.abspath(release_constants.simulated_single_header_file_path)
        with use_directory("../build"):
            print(os.getcwd())
            self.run_for_approval_tests(simulated_single_header, self.details.release_new_single_header)
            text = read_file(self.details.release_new_single_header)
            text = (
                f'// Approval Tests version {self.details.new_version_as_text()}\n'
                '// More information at: https://github.com/approvals/ApprovalTests.cpp\n'
                '\n'
                f'{text}'
            )
            write_file(self.details.release_new_single_header, text)
            return os.path.abspath(self.details.release_new_single_header)

    def run_for_approval_tests(self, initial_file: str, output_file: str) -> None:
        def mdsnippets_discarder(line: str) -> bool:
            return line.strip().startswith('// begin-snippet:') or line.strip().startswith('// end-snippet')

        include_search_path1 = ".."
        include_search_path2 = "../ApprovalTests/"

        discardables = [mdsnippets_discarder]

        create_single_header_file(initial_file, output_file, include_search_path1, include_search_path2,
                                  discardables)

    @staticmethod
    def prepare_release(details: ReleaseDetails) -> None:
        code = CppGeneration(details)
        code.update_version_number_header()
        code.create_single_header_file()


