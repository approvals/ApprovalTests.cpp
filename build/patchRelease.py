#! /usr/bin/env python3

import Version
from build_hpp import build

if __name__ == '__main__':
    build(Version.update_patch)
