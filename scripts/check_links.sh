#!/usr/bin/env bash

# Current working directory should be the root directory of the repository
find . -name cmake-build\* -prune -o -name \*.md -exec \
  markdown-link-check --config mlc_config.json --quiet  {} \; 2> error.txt | grep -v ' links checked.' | grep -v '^$'

if [ -e error.txt ] ; then
  if grep -q "ERROR:" error.txt; then
    echo "At least one error found!"
    rm  error.txt
    exit 113
  fi
else
  echo -e "All good!"
fi
