#!/usr/bin/env bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

# Boost needs to be installed or cloned separately
git clone https://github.com/abseil/googletest.git
git clone https://github.com/boost-ext/ut.git
git clone https://github.com/catchorg/Catch2.git -b v2.x --single-branch
git clone https://github.com/cpputest/cpputest.git
git clone https://github.com/fmtlib/fmt.git --branch "7.1.3"
git clone https://github.com/gulrak/filesystem.git
git clone https://github.com/onqtam/doctest.git
