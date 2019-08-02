#!/usr/bin/env bash

# Copy the template to create new pages.
# Supply one or more new file names as arguments: 
#   ./create_page.sh TestingSingleObjects TestingContainers TestingCombinations

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
    sed -i -e "s/Put Title Here/${page}/" "$new_source_file"

    # Make it easy to add links to the file
    echo "Created $new_source_file - use this for links to it:"
    ./link_page $new_source_file
done
