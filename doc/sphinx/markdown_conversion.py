import pypandoc
from pypandoc.pandoc_download import download_pandoc


def convertMarkdownDocsToRst():
    # TODO Only download pandoc if it's not found
    download_pandoc()

    # TODO make various edits to improve conversion, like removing the Table of Contents
    input_dir = '../../doc'
    output_dir = 'generated_docs'
    file_base_name = 'UsingCatch'
    convert_markdown_to_restructured_text(file_base_name, input_dir, output_dir)


def convert_markdown_to_restructured_text(file_base_name, input_dir, output_dir):
    with open(f'{input_dir}/{file_base_name}.md') as markdown_file:
        content = markdown_file.read()

        content = fix_up_markdown_content(content)
    output = pypandoc.convert_text(''.join(content), 'rst', format='md',
                                   outputfile=f'{output_dir}/{file_base_name}.rst')


def fix_up_markdown_content(content):
    back_to_user_guide = (
        '---\n'
        '\n'
        '[Back to User Guide](/doc/README.md#top)\n'
    )
    content = content.replace(back_to_user_guide, '')
    return content
