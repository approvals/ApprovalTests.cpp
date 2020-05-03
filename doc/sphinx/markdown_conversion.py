import pypandoc
from pypandoc.pandoc_download import download_pandoc


def convertMarkdownDocsToRst():
    # TODO Only download pandoc if it's not found
    download_pandoc()

    # TODO make various edits to improve conversion, like removing the Table of Contents
    output = pypandoc.convert_file('../../doc/UsingCatch.md', 'rst', outputfile="generated_docs/UsingCatch.rst")

    assert output == ""
