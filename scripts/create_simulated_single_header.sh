#!/usr/bin/env bash

# This script regenerates the file allows
# development builds to include 'ApprovalTests.hpp',
# just as users of the released single-header would do.
#
# Run this after adding new header files (*.h) in ApprovalTests

output_file='ApprovalTests/ApprovalTests.hpp'

cat << HERE > $output_file
#ifndef APPROVALTESTS_CPP_APPROVALS_HPP
#define APPROVALTESTS_CPP_APPROVALS_HPP

// Created with:
//   cd ApprovalTests.cpp
//   ./scripts/create_simulated_single_header.sh

HERE

find ApprovalTests -depth -name \*.h | sed -e 's/^/#include "/' | sed -e 's/$/"/' | sort >> $output_file

cat << HERE >> $output_file

#endif // APPROVALTESTS_CPP_APPROVALS_HPP
HERE
