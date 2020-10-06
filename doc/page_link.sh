#!/usr/bin/env bash

# Make it easy to add links to markdown files
#   ./page_link.sh TestingSingleObjects.md TestingContainers.md
#
# This writes out text that can be pasted in to Markdown files, to link to 
# markdown documentation pages.

# Use doc/file_link.sh to link to an arbitrary file or directory

# TODO Document this in Contributing page

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

echo
for source_file in "$@"
do
    doc_base=$(echo "$source_file" | sed -e "s/.md//")
    doc_title=$(grep '^# ' "$source_file" | head -1 | sed -e "s/^# //")
    doc_abs_path="/doc/$doc_base.md"
    doc_rel_path="$doc_base.md"

    # Write out the link to use to the top of the file
    echo "[$doc_title]($doc_abs_path#top)"

    # Write out links to all the entries in the table of contents
    sed -e '/-- endToc --/q' "$doc_rel_path" | grep '* \[' | sed -e "s/^ *\* //" | sed -e "s|#|$doc_abs_path#|"

    # Add blank line, for readability if we are linking to multiple files
    echo
done
