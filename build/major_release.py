#! /usr/bin/env python3

import version
from release_details import build

if __name__ == '__main__':
    build(version.update_major)
