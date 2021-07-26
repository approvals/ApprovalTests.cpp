# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys

sys.path.insert(0, os.path.abspath('.'))

# -- Project information -----------------------------------------------------
# For explanations of this script, see:
# https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/BuildingDocumentation.md#top

from markdown_conversion import convertMarkdownDocsToRst

project = 'ApprovalTests.cpp'
copyright = '2020, Llewellyn Falco, Clare Macrae'
author = 'Llewellyn Falco, Clare Macrae'

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = ["breathe"]

# Breathe Configuration
breathe_default_project = "ApprovalTests.cpp"

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store', 'tests', 'generated_docs/README.rst',
                    'generated_docs/TemplatePage.rst']

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# -- Teach RtD to use CMake config  ------------------------------------------

import subprocess, os

def print_versions():
    import platform
    print(f"Python Version: {platform.python_version()}")
    print("Doxygen version:")
    subprocess.call('doxygen --version', shell=True)
    print("Spinx version:")
    subprocess.call('sphinx-build --version', shell=True)

def add_folder_paths_to_doxygen_config_file(doxygen_dir, input_dir, output_dir):
    with open(doxygen_dir + '/Doxyfile.in', 'r') as file:
        filedata = file.read()

    filedata = filedata.replace('@DOXYGEN_INPUT_DIR@', input_dir)
    filedata = filedata.replace('@DOXYGEN_OUTPUT_DIR@', output_dir)

    with open(doxygen_dir + '/Doxyfile', 'w') as file:
        file.write(filedata)

print_versions()

# Check if we're running on Read the Docs' servers
read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

breathe_projects = {}

convertMarkdownDocsToRst()

if read_the_docs_build:
    input_dir = os.path.abspath('../../ApprovalTests')
    output_dir = os.path.abspath('build')
    doxygen_dir = os.path.abspath('../doxygen')
    sphinx_dir = os.path.abspath('../sphinx')

    add_folder_paths_to_doxygen_config_file(doxygen_dir, input_dir, output_dir)

    os.chdir(doxygen_dir)
    subprocess.call('doxygen', shell=True)
    os.chdir(sphinx_dir)

    breathe_projects['ApprovalTests.cpp'] = output_dir + '/xml'
