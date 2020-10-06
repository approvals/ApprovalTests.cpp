#!/usr/bin/env bash

# Make it easy to add links to any files in the repo
#   ./file_link.sh ../ApprovalTests/core/Reporter.h ../ApprovalTests/core
#
# This writes out text that can be pasted in to Markdown files.
#
# All paths must be given relative to the directory containing this script,
# and must begin with ../

# Use doc/page_link.sh to link to documentation pages (and headings)

# TODO Document this in Contributing page

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

for source_file in "$@"
do
    abs_path=$(echo "$source_file" | sed -e "s|../||")
    github_url=$(echo "$source_file" | sed -e "s|..|https://github.com/approvals/ApprovalTests.cpp/blob/master|")
    echo "[$abs_path]($github_url)"
done
