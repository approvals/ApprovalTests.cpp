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
