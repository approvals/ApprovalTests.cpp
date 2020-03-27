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

## How to add a new release to Conan

The release process needs to submit a pull request to add the new release to [https://github.com/conan-io/conan-center-index/blob/master/recipes/approvaltests.cpp/all/conandata.yml](https://github.com/conan-io/conan-center-index/blob/master/recipes/approvaltests.cpp/all/conandata.yml)

This is only partially automated at the moment.

You will need to:

* Once-off Preparation
    * Fork the [conan-center-index](https://github.com/conan-io/conan-center-index/) repo.
    * Clone that fork to your machine
    * Install Conan
* Before each release
    * Syncronise your Conan fork with the main repo
    * Create a branch for the patch
    * Edit [build/scripts/release_details.py](/build/scripts/release_details.py) to give the relative path to your cloned fork
* Run the release process as normal - this appends lines for your new release to your copy of `conandata.yml`
* The 'deploy' step will test the changes, and prompt you to submit a pull request
