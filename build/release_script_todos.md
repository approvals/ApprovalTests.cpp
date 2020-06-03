# Approvals Release Scripts

* [x] Conan - commit changes

* [x] Conan - push changes

* [x] Conan - fix whitespace in text for pasting in to PR

* [ ] Don't open Conan PR page if previous PR not accepted

* [ ] Check that the starter project is published

  -----

* [ ] Upgrade DeployRelease to use GitPython instead of the git command line

* [ ] Clean up experimental Conan release that's not pushed
  * If we had previously created the branch for this release version, and then
changes were pushed to conan master, we will get an error about the
branch already existing, but pointing to a different change.
This only occurs if an experimental run of the release process was done.
The workaround in this case is to say "No, the previous Conan PR
was not accepted"
  
* [ ] Add CI step to check this prepare process works on every push

* [ ] Automate the creation of release on GitHub (uploading the header, pasting in text)

  * See https://pygithub.readthedocs.io/en/latest/github_objects/GitRelease.html
  * https://developer.github.com/v3/repos/releases/

* [ ] Automate the check_steps

* [ ] Create screenshot image of release notes, and include in Tweet

* [ ] Improve the chdir to start at the top-level directory - and check that we are the top-level

* [ ] Add a reminder to close any release milestone

* [ ] When we create a file, add it to git straight away - so that reverting interrupted releases is easier
