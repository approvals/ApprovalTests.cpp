#!/usr/bin/env bash

OS="$(uname)"

if [ "$OS" == "Darwin" ]; then
  find ./doc -name \*.md | grep -v googletest-src | xargs sed -i '' -f fix_markdown.sed
elif [ "$OS" == "Linux" ]; then
  find ./doc -name \*.md | grep -v googletest-src | xargs sed -i -f fix_markdown.sed
fi

echo
echo "The following files, if any, are missing their 'top' anchor:"
find ./doc -name \*.md | grep -v .include.md | grep -v .approved.md | grep -v googletest-src | grep -v README.md | grep -v cmake-build- | grep -v '/venv/' | xargs grep -L '<a id="top"></a>' | grep -v 'relnotes_'

echo
echo "The following files in doc, if any, are missing the 'Back to User Guide' line at the end:"
find ./doc -name \*.md | grep -v .include.md | grep -v .approved.md | grep -v googletest-src | grep -v README.md | xargs grep -L 'Back to User Guide'

echo
echo "The following files, if any, are not in the User Guide (doc/README.md)"
pushd doc > /dev/null
for file in `find . -name sphinx -prune -o  ! -name \*.include.md -name \*.md -print`
do
    if [ $file = "./README.md" ] || [ $file = "./TemplatePage.md" ]
    then
       continue
    fi
    grep -q $file README.md || echo $file
done
popd > /dev/null
