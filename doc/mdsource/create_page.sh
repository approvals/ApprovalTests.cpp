#!/usr/bin/env bash

# Copy the template to create new pages.
# Supply one or more new file names as arguments: 
#   ./create_page.sh TestingSingleObjects TestingContainers TestingCombinations

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

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
done

echo "Now run run_markdown_templates.sh, then use page_link.sh to create links to the new file "
