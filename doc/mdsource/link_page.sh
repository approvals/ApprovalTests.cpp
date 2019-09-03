#!/usr/bin/env bash

# Make it easy to add links to *source* markdown files
#   ./link_page.sh TestingSingleObjects.source.md TestingContainers.source.md
#
# This writes out text that can be pasted in to Markdown files, to link to 
# the generated versions of these source files. 

# Use doc/mdsource/link_file.sh to link to an arbitrary file or directory

# TODO Document this in Contributing page

for source_file in "$@"
do
    doc_base=$(echo "$source_file" | sed -e "s/.source.md//")
    doc_title=$(grep '^# ' "$source_file" | head -1 | sed -e "s/^# //")
    doc_abs_path="/doc/$doc_base.md"
    echo "[$doc_title]($doc_abs_path#top)"
done
