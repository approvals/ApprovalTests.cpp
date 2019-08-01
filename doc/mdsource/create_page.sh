#!/usr/bin/env bash

# Copy the template to create new pages.
# Supply one or more new file names as arguments: 

for page in "$@"
do
    new_source_file="${page}.source.md"

    # Don't overwrite existing files
    if test -f "$new_source_file"; then
        echo "ERROR: $new_source_file exists: not overwriting"
        continue
    fi

    # Create the file
    cp TemplatePage.source.md "$new_source_file"

    # Make it easy to add links to the file
    echo "Created $new_source_file - use this for links to it:"
    new_doc_file="${page}.md"
    echo "* [$new_doc_file](/doc/$new_doc_file.md#top)"
done
