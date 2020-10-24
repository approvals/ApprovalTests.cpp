#!/usr/bin/env bash

# Force execution to halt if there are any errors in this script:
set -e
set -o pipefail

# To update, use:
#   pip3 install --upgrade --no-cache-dir
sudo apt-get install pandoc
pandoc --version
python3 -m pip install --upgrade pip
pip3 install flake8 pytest
pip3 install -r requirements.txt
pip3 install -r ../doc/requirements.txt
