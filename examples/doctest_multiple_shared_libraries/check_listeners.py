"""Require a separate ApprovalTests listener for the runner and each library."""
import re
import subprocess
import sys

result = subprocess.run(sys.argv[1:] + ["--list-reporters"],
                        stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
print(result.stdout, end="")
if result.returncode:
    sys.exit(result.returncode)

names = re.findall(r"name: (\S+)", result.stdout)
expected = {"approvals", "TestModuleOne", "TestModuleTwo"}
missing = expected.difference(names)
if missing:
    sys.exit("Missing ApprovalTests listeners: " + ", ".join(sorted(missing)))
