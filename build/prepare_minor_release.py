#! /usr/bin/env python3

# pip3 install -r requirements.txt

import version
from release_details import build

if __name__ == '__main__':
    build(version.update_minor, deploy=False)
