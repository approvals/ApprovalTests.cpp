#!/usr/bin/env bash

find . -name \*.md | grep -v googletest-src | xargs sed -i -f fix_markdown.sed

echo
echo "The following files, if any, are missing their 'top' anchor:"
find -name \*.md | grep -v googletest-src | grep -v README.md | grep -v README.source.md | xargs grep -L '<a id="top"></a>' | grep -v 'relnotes_'

echo
echo "The following files in doc, if any, are missing the 'Back to User Guide' line at the end:"
find ./doc -name \*.md | grep -v googletest-src | grep -v README.md | grep -v README.source.md | xargs grep -L 'Back to User Guide'

echo
echo "The following files, if any, need to have relative references converted to absolute ones"
find -name \*.source.md | grep -v googletest-src | xargs grep -P '\]\((?!#|http|/|mailto)'
