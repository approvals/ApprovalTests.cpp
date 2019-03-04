#!/usr/bin/env bash
# For info on mdsnippets, see https://github.com/SimonCropp/MarkdownSnippets

# install dotnet SDK from http://go.microsoft.com/fwlink/?LinkID=798306&clcid=0x409
# Then install GitHubMarkdownSnippets with
#   dotnet tool install -g GitHubMarkdownSnippets
# To update:
#   dotnet tool update  -g GitHubMarkdownSnippets

# TODO Update for the renaming of the project
# See https://github.com/SimonCropp/MarkdownSnippets/issues/5
# Use the following to change over:

# dotnet tool uninstall -g GitHubMarkdownSnippets
# dotnet tool install -g MarkdownSnippets.Tool

mdsnippets
