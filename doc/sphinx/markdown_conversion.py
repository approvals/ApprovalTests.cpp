import pypandoc
from pypandoc.pandoc_download import download_pandoc


def convertMarkdownDocsToRst():
    # TODO Only download pandoc if it's not found
    download_pandoc()

    # TODO make various edits to improve conversion, like removing the Table of Contents
    file_base_name = 'UsingCatch'
    output = pypandoc.convert_file(f'../../doc/{file_base_name}.md', 'rst',
                                   outputfile=f'generated_docs/{file_base_name}.rst')

    assert output == ""
