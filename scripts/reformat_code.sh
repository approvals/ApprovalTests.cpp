#!/usr/bin/env bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

# This needs to be run from the project root directory

for source_dir in ApprovalTests examples tests ; do
  cd $source_dir
  pwd
  find . -name \*.h -o -name \*.hpp -o -name \*.cpp | xargs clang-format -i
  cd ..
done
