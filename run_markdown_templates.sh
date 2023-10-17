#!/usr/bin/env bash

# ---------------------------------------------------
# Update code examples
# ---------------------------------------------------
# For info on mdsnippets, see https://github.com/SimonCropp/MarkdownSnippets

# install dotnet SDK from http://go.microsoft.com/fwlink/?LinkID=798306&clcid=0x409
# Then install MarkdownSnippets.Tool with
#   dotnet tool install -g MarkdownSnippets.Tool
# To update:
#   dotnet tool update  -g MarkdownSnippets.Tool
# To uninstall (e.g. to downgrade to a lower version)
# dotnet tool uninstall -g MarkdownSnippets.Tool

# Maintenance Note:
#   Before updating the pinned version of MarkdownSnippets.Tool to a new
#   pinned version, the new version needs to be installed and run via this
#   this script, and then the python tests in doc/sphinx/tests need to be run.
#
#   This is because, occasionally, updates to MarkdownSnippets.Tool change
#   the hidden comments that it adds to .md files, and this can
#   break doc/sphinx/markdown_conversion.py and therefore result in
#   broken formatting or hyperlinks in ReadTheDocs.
#
#   See https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/BuildingDocumentation.md#top
dotnet tool update  -g MarkdownSnippets.Tool || exit
mdsnippets || exit 1

echo "------------------------------------------"
echo "Custom Markdown linting:"
./fix_markdown.sh | grep -v cmake-build
