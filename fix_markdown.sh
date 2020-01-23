#!/usr/bin/env bash

find . -name \*.md | grep -v googletest-src | xargs sed -i '' -f fix_markdown.sed

echo
echo "The following files, if any, are missing their 'top' anchor:"
find . -name \*.md | grep -v .include.md | grep -v .approved.md | grep -v googletest-src | grep -v README.md | grep -v README.source.md | xargs grep -L '<a id="top"></a>' | grep -v 'relnotes_'

echo
echo "The following files in doc, if any, are missing the 'Back to User Guide' line at the end:"
find ./doc -name \*.md | grep -v .include.md | grep -v googletest-src | grep -v README.md | grep -v README.source.md | xargs grep -L 'Back to User Guide'

echo
echo "The following files, if any, are not in the User Guide (doc/README.md)"
pushd doc > /dev/null
for file in *.md
do
    if [ $file = "README.md" ] || [ $file = "TemplatePage.md" ]
    then
       continue
    fi
    grep -q $file README.md || echo $file
done
popd > /dev/null
