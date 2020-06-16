#! /usr/bin/env python3

from scripts.prepare_release import build
from scripts.project_details import ProjectDetails

if __name__ == '__main__':
    build(lambda v: v.update_major(), deploy = False, project_details=ProjectDetails())
