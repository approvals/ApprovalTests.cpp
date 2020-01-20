#! /usr/bin/env python
from __future__ import print_function
import sys,os,subprocess
class Bash2Py(object):
  __slots__ = ["val"]
  def __init__(self, value=''):
    self.val = value

# Force execution to halt if there are any errors in this script:
_rc0 = subprocess.call(["set","-e"],shell=True)
_rc0 = subprocess.call(["set","-o","pipefail"],shell=True)
# Constants
UNSET_VERSION=Bash2Py("v.X.X.X")
LAST_VERSION=Bash2Py("v.7.0.0")
VERSION=Bash2Py(UNSET_VERSION.val)
PUSH_TO_PRODUCTION=Bash2Py("true")
# Note that we won't push if the version number is unset
OLD_SINGLE_HEADER=Bash2Py("ApprovalTests."+str(LAST_VERSION.val)+".hpp")
NEW_SINGLE_HEADER=Bash2Py("ApprovalTests."+str(VERSION.val)+".hpp")
NEW_SINGLE_HEADER_TEMP=Bash2Py(str(NEW_SINGLE_HEADER.val)+".tmp")
RELEASE_DIR=Bash2Py("../build/releases")
RELEASE_NEW_SINGLE_HEADER=Bash2Py(str(RELEASE_DIR.val)+"/"+str(NEW_SINGLE_HEADER.val))
RELEASE_NEW_SINGLE_HEADER_TEMP=Bash2Py(str(RELEASE_DIR.val)+"/"+str(NEW_SINGLE_HEADER_TEMP.val))
STARTER_PROJECT_DIR=Bash2Py("../../ApprovalTests.Cpp.StarterProject")
STARTER_PATH_OLD_SINGLE_HEADER=Bash2Py(str(STARTER_PROJECT_DIR.val)+"/lib/"+str(OLD_SINGLE_HEADER.val))
STARTER_PATH_NEW_SINGLE_HEADER=Bash2Py(str(STARTER_PROJECT_DIR.val)+"/lib/"+str(NEW_SINGLE_HEADER.val))
# TODO copy in checks from https://github.com/pages-themes/minimal/blob/master/script/release
# ------------------------------------------------------------------------------------------------
# Create new single-header file
os.chdir("../ApprovalTests")
_rc0 = subprocess.call(["java","-jar","../build/SingleHpp.v.0.0.2.jar",str(RELEASE_NEW_SINGLE_HEADER_TEMP.val)],shell=True)
# TODO make sed command work on all platforms:
# https://stackoverflow.com/a/22084103/104370
_rc0 = subprocess.Popen("cat",shell=True,stdin=subprocess.PIPE,stdout=file(str(RELEASE_NEW_SINGLE_HEADER.val),'wb'))
_rc0.communicate("// Approval Tests version "+str(VERSION.val)+"\n// More information at: https://github.com/approvals/ApprovalTests.cpp\n")
_rc0 = _rc0.wait()print '''
// Approval Tests version $VERSION
// More information at: https://github.com/approvals/ApprovalTests.cpp
'''> $RELEASE_NEW_SINGLE_HEADER
_rc0 = subprocess.call("cat" + " " + str(RELEASE_NEW_SINGLE_HEADER_TEMP.val),shell=True,stdout=file(str(RELEASE_NEW_SINGLE_HEADER.val),'ab'))
>> $RELEASE_NEW_SINGLE_HEADER
_rc0 = subprocess.call(["rm",str(RELEASE_NEW_SINGLE_HEADER_TEMP.val)],shell=True)
# ------------------------------------------------------------------------------------------------
# Update Starter Project 
# Make sure starter project folder is clean
_rc0 = subprocess.call(["pushd",str(STARTER_PROJECT_DIR.val)],shell=True)
_rc0 = subprocess.call(["git","clean","-fx"],shell=True)
_rc0 = subprocess.call(["git","reset","--hard"],shell=True)
_rc0 = subprocess.call(["popd"],shell=True)
_rc0 = subprocess.call(["cp",str(RELEASE_NEW_SINGLE_HEADER.val),str(STARTER_PATH_NEW_SINGLE_HEADER.val)],shell=True)
# Delete the last release:
if (os.path.isfile(str(STARTER_PATH_OLD_SINGLE_HEADER.val)) ):
    subprocess.call(["rm",str(STARTER_PATH_OLD_SINGLE_HEADER.val)],shell=True)
# Update the version in the "redirect" header:
_rc0 = subprocess.call(["sed","-i",str(),"-e","s/"+str(LAST_VERSION.val)+"/"+str(VERSION.val)+"/",str(STARTER_PROJECT_DIR.val)+"/lib/ApprovalTests.hpp"],shell=True)
# Update the version number in the Visual Studio project:
_rc0 = subprocess.call(["sed","-i",str(),"-e","s/"+str(OLD_SINGLE_HEADER.val)+"/"+str(NEW_SINGLE_HEADER.val)+"/",str(STARTER_PROJECT_DIR.val)+"/visual-studio-2017/StarterProject.vcxproj"],shell=True)
# Check the starter project builds
_rc0 = subprocess.call(["pushd",str(STARTER_PROJECT_DIR.val)+"/cmake-build-debug"],shell=True)
_rc0 = subprocess.call(["cmake","--build","."],shell=True)
_rc0 = subprocess.call(["popd"],shell=True)
if (str(VERSION.val) == str(UNSET_VERSION.val) ):
    print("Everything worked - version number not set, so didn't commit or push")
    exit()
if (str(PUSH_TO_PRODUCTION.val) == "false" ):
    # Don't push to production if we haven't set the version number
    print("Everything worked - didn't commit or push")
    exit()
# Commit and push starter project
_rc0 = subprocess.call(["pushd",str(STARTER_PROJECT_DIR.val)],shell=True)
_rc0 = subprocess.call(["git","add","."],shell=True)
_rc0 = subprocess.call(["git","commit","-m","Update to Approvals "+str(VERSION.val)],shell=True)
_rc0 = subprocess.call(["git","push","origin","master"],shell=True)
_rc0 = subprocess.call(["popd"],shell=True)
# ------------------------------------------------------------------------------------------------
# Update the top-level readme file and other documentation
_rc0 = subprocess.call(["pushd",".."],shell=True)
_rc0 = subprocess.call(["sed","-i","-e","s/"+str(LAST_VERSION.val)+"/"+str(VERSION.val)+"/g","mdsource/README.source.md"],shell=True)
_rc0 = subprocess.call(["./run_markdown_templates.sh"],shell=True)
_rc0 = subprocess.call(["popd"],shell=True)
# Draft the tweet
_rc0 = subprocess.call(["open","https://twitter.com/intent/tweet?text=%23ApprovalTests.cpp+"+str(VERSION.val)+"+released%2C+now+with+___%21%0D%0Ahttps%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp%2Freleases%2Ftag%2F"+str(VERSION.val)+"+%0D%0Aor+try+the+starter+project%3A+https%3A%2F%2Fgithub.com%2Fapprovals%2FApprovalTests.cpp.StarterProject%0D%0AThanks+%40LlewellynFalco+%40ClareMacraeUK+%21"],shell=True)
# Draft the upload to github - do this last, so this tab appears on top
_rc0 = subprocess.call(["open","https://github.com/approvals/ApprovalTests.cpp/releases/new?tag="+str(VERSION.val)+"&title=Single%20Hpp%20File%20-%20"+str(VERSION.val)],shell=True)
_rc0 = subprocess.call(["open",str(RELEASE_DIR.val)+"/"],shell=True)
# The prefixes used in our commit messages come from: https://github.com/RefactoringCombos/ArlosCommitNotation
_rc0 = _rcr1, _rcw1 = os.pipe()
if os.fork():
    os.close(_rcw1)
    os.dup2(_rcr1, 0)
    _rcr2, _rcw2 = os.pipe()
    if os.fork():
        os.close(_rcw2)
        os.dup2(_rcr2, 0)
        _rcr3, _rcw3 = os.pipe()
        if os.fork():
            os.close(_rcw3)
            os.dup2(_rcr3, 0)
            _rcr4, _rcw4 = os.pipe()
            if os.fork():
                os.close(_rcw4)
                os.dup2(_rcr4, 0)
                _rcr5, _rcw5 = os.pipe()
                if os.fork():
                    os.close(_rcw5)
                    os.dup2(_rcr5, 0)
                    _rcr6, _rcw6 = os.pipe()
                    if os.fork():
                        os.close(_rcw6)
                        os.dup2(_rcr6, 0)
                        subprocess.call(["sort"],shell=True)
                    else:
                        os.close(_rcr6)
                        os.dup2(_rcw6, 1)
                        subprocess.call(["grep","-v","Update StyleGuide.h"],shell=True)
                        sys.exit(0)
                    
                else:
                    os.close(_rcr5)
                    os.dup2(_rcw5, 1)
                    subprocess.call(["grep","-v","Update README.md"],shell=True)
                    sys.exit(0)
                
            else:
                os.close(_rcr4)
                os.dup2(_rcw4, 1)
                subprocess.call(["grep","-v","Update HowToRelease.md"],shell=True)
                sys.exit(0)
            
        else:
            os.close(_rcr3)
            os.dup2(_rcw3, 1)
            subprocess.call(["grep","-v","Update to_do.txt"],shell=True)
            sys.exit(0)
        
    else:
        os.close(_rcr2)
        os.dup2(_rcw2, 1)
        subprocess.call(["grep","-v","^[dert] "],shell=True)
        sys.exit(0)
    
else:
    os.close(_rcr1)
    os.dup2(_rcw1, 1)
    subprocess.call(["git","log",str(LAST_VERSION.val)+"..HEAD","--pretty=format:%s"],shell=True)
    sys.exit(0)

# TODO In future - prompt for version number
#read -p "Enter the next version number (last was:  $LAST_VERSION )" VERSION
#sed -i -e "s/$LAST_VERSION/$VERSION/g" ../build/build_hpp.sh
