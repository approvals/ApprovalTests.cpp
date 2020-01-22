#! /usr/bin/env python3

import Version
from release_details import build

if __name__ == '__main__':
    build(Version.update_patch)
