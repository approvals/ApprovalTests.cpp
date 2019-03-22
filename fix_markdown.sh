#!/usr/bin/env bash

find . -name \*.md | grep -v googletest-src | xargs sed -i -f fix_markdown.sed


echo "The following files, if any, are missing the 'Back to User Guide' line at the end:"
find ./doc -name \*.md | grep -v googletest-src | grep -v README.md | xargs grep -L 'Back to User Guide'