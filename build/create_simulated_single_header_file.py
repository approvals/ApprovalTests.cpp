#! /usr/bin/env python3
import os

from scripts.project_details import ProjectDetails
from scripts.single_header_file import SingleHeaderFile

if __name__ == '__main__':
    os.chdir("../ApprovalTests")
    SingleHeaderFile.create('.', ProjectDetails(), include_cpps=False)
