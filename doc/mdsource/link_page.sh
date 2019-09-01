#!/usr/bin/env bash

# Make it easy to add links to *source* markdown files
#   ./link_page.sh TestingSingleObjects.source.md TestingContainers.source.md
#
# This writes out text that can be pasted in to Markdown files, to link to 
# the generated versions of these source files. 

# TODO Make this link to more types of files, and more locations
# TODO Only add #top if it's a markdown file
# TODO Link to directories - files at multiple levels etc
# TODO Document this in Contributing page

for source_file in "$@"
do
    doc_base=$(echo "$source_file" | sed -e "s/.source.md//")
    doc_title=$(grep '^# ' "$source_file" | head -1 | sed -e "s/^# //")
    echo "* [$doc_title](/doc/$doc_base.md#top)"
done
