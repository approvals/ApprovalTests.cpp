#!/usr/bin/env bash

find . -name \*.md | grep -v googletest-src | xargs sed -i -f fix_markdown.sed

echo
echo "The following files, if any, have headings (Level 2 or below) not in the Contents list"
find . -name \*.md | grep -v googletest-src | xargs grep -n '^##' | grep -v '<a name='

echo
echo "The following files in doc, if any, are missing the 'Back to User Guide' line at the end:"
find ./doc -name \*.md | grep -v googletest-src | grep -v README.md | xargs grep -L 'Back to User Guide'
