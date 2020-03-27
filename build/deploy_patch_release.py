#! /usr/bin/env python3

from scripts import version
from scripts.release_details import build

if __name__ == '__main__':
    build(version.update_patch, deploy = True)
