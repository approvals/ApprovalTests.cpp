import pypandoc
import glob
import os
import re


def convertMarkdownDocsToRst():
    pypandoc.ensure_pandoc_installed()

    # TODO make various edits to improve conversion, like removing the Table of Contents
    print("Converting all .md files to .rst...")
    input_dir = '../../doc'
    output_dir = 'generated_docs'
    subdirs = ['', 'how_tos', 'explanations', 'reference']
    for subdir in subdirs:
        # print(f'>>>> {subdir}')
        input_sub_dir = f'{input_dir}/{subdir}'
        if not os.path.isdir(input_sub_dir):
            print(f'Directory {input_sub_dir} does not exist. Skipping)')
        output_sub_dir = f'{output_dir}/{subdir}'
        convert_all_markdown_files_in_dir(subdir, input_sub_dir, output_sub_dir)


def convert_all_markdown_files_in_dir(subdir, input_sub_dir, output_sub_dir):
    md_files = glob.glob(f'{input_sub_dir}/*.md')
    if not md_files:
        return
    if not os.path.isdir(output_sub_dir):
        os.makedirs(output_sub_dir)
    for file in md_files:
        # Prevent Sphinx warnings about include files not being in the table of contents
        if file.endswith('.include.md'):
            continue
        file_base_file = os.path.split(file)[1]
        file_base_name = os.path.splitext(file_base_file)[0]

        # print(file_base_name, input_sub_dir, output_sub_dir)
        convert_markdown_file_to_restructured_text(subdir, file_base_name, input_sub_dir, output_sub_dir)


def convert_markdown_file_to_restructured_text(subdir, file_base_name, input_dir, output_dir):
    with open(f'{input_dir}/{file_base_name}.md') as markdown_file:
        content = markdown_file.read()

    converted_markdown, converted_rst = convert_markdown_text_to_restructured_text(content, subdir)

    # Temporary code for reviewing changes made, on all input files:
    # with open(file_base_name + '_hacked.md', 'w') as w:
    #     w.write(converted_markdown)

    with open(f'{output_dir}/{file_base_name}.rst', 'w') as rst_output:
        rst_output.write(converted_rst)


def convert_markdown_text_to_restructured_text(content, subdir):
    converted_markdown = fix_up_markdown_content(subdir, content)
    converted_rst = pypandoc.convert_text(''.join(converted_markdown), 'rst', format='md')
    return converted_markdown, converted_rst


def fix_up_markdown_content(subdir, content):
    content = fixup_boilerplate_text(content)
    content = fixup_generated_snippets(content)
    content = fixup_included_snippets(content)
    content = fixup_code_languages_for_pygments(content)
    content = fixup_markdown_hyperlink_text(content)
    content = fixup_markdown_hyperlink_destinations(content, subdir)

    return content


def fixup_boilerplate_text(content):
    # Remove 'top' anchor (and the following blank line)
    content = content.replace('<a id="top"></a>\n\n', '')

    # Remove table of contents
    content = re.sub(r'<!-- toc -->.*<!-- endToc -->', '', content, count=1, flags=re.DOTALL)

    # Remove 'Back to User Guide'
    back_to_user_guide = (
        '---\n'
        '\n'
        '[Back to User Guide](/doc/README.md#top)\n'
    )
    content = content.replace(back_to_user_guide, '')
    return content


def fixup_generated_snippets(content):
    """
    Adjust the expanded code snippets that were generated
    by mdsnippets, to improve rendering by Sphinx
    """

    # Remove lines like: <!-- snippet: verify_exception_message_example -->
    content = re.sub(
        r"<!-- snippet: .* -->\n",
        r"", content)

    # Remove lines like: <a id='snippet-verify_exception_message_example'/></a>
    content = re.sub(
        r"<a id='snippet-.*'/></a>\n",
        r"", content)

    # Remove 'snippet source' links from all code snippets
    content = re.sub(
        r"<sup><a href='([^']+)' title='Snippet source file'>snippet source</a> ",
        r"(See [snippet source](\1))", content)

    # Remove 'anchor' links from all code snippets
    content = re.sub(
        r"\| <a href='#snippet-[^']+' title='Start of snippet'>anchor</a></sup>",
        '', content)

    content = content.replace('<!-- endsnippet -->\n', '')

    return content


def fixup_included_snippets(content):
    """
    Adjust the expanded code snippets that were included
    by mdsnippets, to improve rendering by Sphinx
    """

    #  Remove '<!-- include:' lines at the start of included snippet
    content = re.sub(
        r"\n\s*<!-- include:.*-->\n",
        '', content)

    # simplify the hyperlink, remove superscript tags
    content = re.sub(
        # r"<sup><a href='([^']+)' title='File snippet `[^`]+` was extracted from'>snippet source</a> ",
        r"<sup><a href='([^']+)' title='File snippet was copied from'>snippet source</a></sup>",
        r"(See [snippet source](\1))", content)

    #  Remove '<!-- end include:' lines at the end of included snippet
    content = re.sub(
        r"\n\s*<!-- end include:.*-->",
        '', content)

    return content


def fixup_code_languages_for_pygments(content):
    # Fix "WARNING: Pygments lexer name 'h' is not known"
    # Todo: find out how to fix this in conf.py - this is a horrible hack!
    content = content.replace(
        '\n```h\n',
        '\n```cpp\n')

    # Fix "WARNING: Pygments lexer name 'txt' is not known"
    # Text files don't need any markup
    content = content.replace(
        '\n```txt\n',
        '\n```\n')
    return content


def fixup_markdown_hyperlink_text(content):
    hyperlink_regex = re.compile(
        r"""\[ # the opening that surrounds the link text
            (  # start capturing the link text
            [^]]+ # the link text
            )  # finish capturing the link text
            \] # the closing that surrounds the link text
            \( # the escaped ( at the start of the destination""", re.VERBOSE)

    def convert_github_markdown_url_to_sphinx(matched_obj):
        # This works around rst not displaying hyperlinked text with fixed-width formatting
        # as described in https://stackoverflow.com/questions/4743845/format-text-in-a-link-in-restructuredtext
        # For now, we just removed the fixed-width formatting from any hyperlinked text
        full_link_text = matched_obj.group(1)
        new_link_text = full_link_text.replace('`', '')
        return f'[{new_link_text}]('

    content = hyperlink_regex.sub(convert_github_markdown_url_to_sphinx, content)

    return content


def fixup_markdown_hyperlink_destinations(content, subdir):
    hyperlink_regex = re.compile(
        r"""\] # the closing ] that surrounds the link text
            \( # the escaped ( at the start of the destination
            (  # start capturing the destination
            [^() ]+ # the destination
            )  # finish capturing the destination
            \) # the escaped ) at the end of the destination""", re.VERBOSE)

    def convert_github_markdown_url_to_sphinx(matched_obj):
        full_match = matched_obj.group(0)
        full_url = matched_obj.group(1)

        # Check if it is a kind of URL will be embedded in Sphinx docs:
        will_include_in_sphix_docs = True
        if not full_url.startswith('/doc'):
            will_include_in_sphix_docs = False
        if '.include.md' in full_url:
            will_include_in_sphix_docs = False
        if '.md' not in full_url:
            will_include_in_sphix_docs = False
        if 'README.md' in full_url:
            will_include_in_sphix_docs = False

        if not will_include_in_sphix_docs:
            if full_url.startswith('/'):
                # It's an internal link, to a file or directory in our github repo
                # TODO Instead of master, use the changeset that this was generated from
                if full_url.endswith('/'):
                    new_full_url = 'https://github.com/approvals/ApprovalTests.cpp/tree/master' + full_url[0:-1]
                else:
                    new_full_url = 'https://github.com/approvals/ApprovalTests.cpp/blob/master' + full_url
                return f']({new_full_url})'
            else:
                # It's a link to somewhere else, e.g. http, mailto, or anchor ('#') in current document,
                # so return it unchanged
                return full_match

        # Split the url and the anchor
        if '#' in full_url:
            original_url, original_anchor = full_url.split('#')
        else:
            original_url = full_url
            original_anchor = ''

        current_path = '/doc'
        if subdir != '':
            current_path = f'{current_path}/{subdir}'
        new_url = os.path.relpath(original_url, current_path)
        new_url = new_url.replace('.md', '.html')

        new_anchor = original_anchor
        if new_anchor == 'top':
            new_anchor = ''

        # mdsnippets puts a hyphen in for each unusual character in an anchor
        # Sphinx puts a hyphen in for each run of one or more unusual characters in an anchor
        if '--' in new_anchor:
            new_anchor = re.sub('--+', '-', new_anchor)

        if new_anchor != '':
            new_full_url = f'{new_url}#{new_anchor}'
        else:
            new_full_url = new_url
        return f']({new_full_url})'

    content = hyperlink_regex.sub(convert_github_markdown_url_to_sphinx, content)

    # Revert a very specific unwanted edit in a markdown code block,
    # in the Contributing page.
    # This is supposed to demonstrate how to correctly express links to
    # other markdown documentation pages, and so it should appear
    # unchanged in the Sphinx documentation.
    content = content.replace(
        '* [this link will work everywhere](Reporters.html)',
        '* [this link will work everywhere](/doc/Reporters.md#top)')

    return content
