<a id="top"></a>
# How To Release

## Update ApprovalTests.cpp

Preparation:

- Determine the type of semantic release - major, minor or patch 

Doing the release:

```bash
cd build

# Run one of:

deploy_major_release.py
deploy_minor_release.py
deploy_patch_release.py

prepare_major_release.py
prepare_minor_release.py
prepare_patch_release.py
```

## Overview of steps

![Flow of files during release](../doc/images/release_files_mindmap.png?raw=true)

## How to add a new release to Conan

The release process needs to submit a pull request to add the new release to [https://github.com/conan-io/conan-center-index/blob/master/recipes/approvaltests.cpp/all/conandata.yml](https://github.com/conan-io/conan-center-index/blob/master/recipes/approvaltests.cpp/all/conandata.yml)

This is only partially automated at the moment.

You will need to:

* Once-off Preparation
    * Either:
    * Either:
        * Fork the [conan-center-index](https://github.com/conan-io/conan-center-index/) repo.
    * Or:
        * Request write-permission to [claremacrae/conan-center-index](https://github.com/claremacrae/conan-center-index)
    * Clone chosen conan-center-index fork to your machine
    * Edit [build/scripts/conan_release.py](/build/scripts/conan_release.py)'s `get_conan_repo_directory()()` to add the relative path to your cloned fork
    * Install Conan
    * Install the [conan-center hook](https://github.com/conan-io/conan-center-index/blob/master/docs/how_to_add_packages.md#test-the-recipe-locally)
* Run the release process as normal - this appends lines for your new release to your copy of `conandata.yml`
* The 'deploy' step will test the changes, and prompt you to submit a pull request
