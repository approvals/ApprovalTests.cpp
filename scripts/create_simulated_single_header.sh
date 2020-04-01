#!/usr/bin/env bash

# This script regenerates the file allows
# development builds to include 'ApprovalTests.hpp',
# just as users of the released single-header would do.
#
# Run this after adding new header files (*.h) in ApprovalTests
#
# It is also run as part of the release process.

cd build
./create_simulated_single_header_file.py
