import os
from datetime import datetime
from typing import List

from scripts.embed import create_single_header_file
from scripts.multiline_string_utilities import remove_indentation
from scripts.project_details import ProjectDetails
from scripts.release_details import ReleaseDetails
from scripts.single_header_file import SingleHeaderFile
from scripts.utilities import read_file, write_file, use_directory
from scripts.version import Version


class CppGeneration:
    def __init__(self, details: ReleaseDetails) -> None:
        self.details = details

    def update_version_number_header(self) -> None:
        with use_directory(self.details.locations.approval_tests_dir):
            version_header = os.path.join(self.details.project_details.version_header)

            text = CppGeneration.get_version_number_hpp_text(self.details.new_version, self.details.project_details)
            write_file(version_header, text)

    @staticmethod
    def append_continuation_character(line: str) -> str:
        return line.ljust(89, ' ') + '\\'

    @staticmethod
    def get_version_number_hpp_text(version_object: Version, project_details: ProjectDetails) -> str:
        version_string = version_object.get_version_text_without_v()
        macro_prefix = project_details.macro_prefix
        # TODO Need to adjust amount of whitespace before trailing '`', depending on length of macro_prefix
        text = remove_indentation << f'''
                #pragma once

                #define {macro_prefix}_VERSION_MAJOR {version_object.major}
                #define {macro_prefix}_VERSION_MINOR {version_object.minor}
                #define {macro_prefix}_VERSION_PATCH {version_object.patch}
                #define {macro_prefix}_VERSION_STR "{version_string}"

                '''

        line1 = f'#define {macro_prefix}_VERSION'
        line2 = f'    ({macro_prefix}_VERSION_MAJOR * 10000 + {macro_prefix}_VERSION_MINOR * 100 +'
        second_part = remove_indentation << f'''
                {CppGeneration.append_continuation_character(line1)}
                {CppGeneration.append_continuation_character(line2)}
                     {macro_prefix}_VERSION_PATCH)
                '''
        return text + second_part

    def create_simulated_single_header_file(self, include_cpps: bool) -> str:
        return SingleHeaderFile.create('.', self.details.project_details, include_cpps=include_cpps)

    def create_single_header_file(self) -> str:
        self.create_simulated_single_header_file(include_cpps=True)

        simulated_single_header = os.path.abspath(self.details.locations.simulated_single_header_file_path)
        with use_directory("../build"):
            print(os.getcwd())
            self.run_for_approval_tests(simulated_single_header, self.details.release_new_single_header)
            text = read_file(self.details.release_new_single_header)

            year = datetime.now().year
            text = (
                f'// {self.details.project_details.github_project_name} version {self.details.new_version_as_text()}\n'
                f'// More information at: {self.details.project_details.github_project_url}\n'
                f'//\n'
                f'// Copyright (c) {year} Llewellyn Falco and Clare Macrae. All rights reserved.\n'
                f'//\n'
                f'// Distributed under the Apache 2.0 License\n'
                f'// See https://opensource.org/licenses/Apache-2.0\n'
                f'\n'
                '//----------------------------------------------------------------------\n'
                '// Welcome to Approval Tests.\n'
                '//\n'
                '// If you experience linker errors about missing symbols, it means\n'
                '// you have forgotten to configure your test framework for Approval Tests.\n'
                '//\n'
                '// For help with this, please see:\n'
                '//     https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredMain.md\n'
                '//----------------------------------------------------------------------\n'
                f'{text}'
            )
            write_file(self.details.release_new_single_header, text)

        # HACK! A side-effect of this method is that it overwrites
        # the version-controlled simulated single-header, including .cpp
        # files.
        # Revert that change:
        self.create_simulated_single_header_file(include_cpps=False)

        # Check for broken headers in the generated text
        # (but only after we have reverted any modified source code)
        header_files_h = SingleHeaderFile.get_all_files('.', '.h')
        header_files_hpp = SingleHeaderFile.get_all_files('.', '.hpp')
        errors = CppGeneration.validate_single_header_file_content(header_files_h, header_files_hpp, text)
        if errors != "":
            raise RuntimeError(errors)

        return os.path.abspath(self.details.release_new_single_header)

    @staticmethod
    def validate_single_header_file_content(header_files_h: List[str], header_files_hpp: List[str], text: str) -> str:
        all_header_files = header_files_h + header_files_hpp

        errors = ""
        for file in all_header_files:
            filename = os.path.split(file)[1]
            if filename + '>' in text:
                message = f"""
ERROR: There is an incorrect #include line somewhere in the library source.
The file {filename} is incorrectly include via <>.
Search for "{filename}>" in all the library source, and convert to double-quotes instead.\n"""
                errors += message
        return errors

    def run_for_approval_tests(self, initial_file: str, output_file: str) -> None:
        def mdsnippets_discarder(line: str) -> bool:
            return line.strip().startswith('// begin-snippet:') or line.strip().startswith('// end-snippet')

        include_search_path1 = ".."
        include_search_path2 = os.path.join("..", self.details.project_details.library_folder_name)

        discardables = [mdsnippets_discarder]

        create_single_header_file(initial_file, output_file, include_search_path1, include_search_path2,
                                  discardables)

    @staticmethod
    def prepare_release(details: ReleaseDetails) -> None:
        code = CppGeneration(details)
        code.update_version_number_header()
        code.create_single_header_file()


