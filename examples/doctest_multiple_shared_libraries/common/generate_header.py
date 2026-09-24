"""Generate the release-style header in the build tree without editing sources."""
import os
import sys
from pathlib import Path

source = Path(sys.argv[1]).resolve()
output = Path(sys.argv[2]).resolve()
sys.path.insert(0, str(source / "build"))

from scripts.embed import create_single_header_file
from scripts.project_details import ProjectDetails
from scripts.single_header_file import SingleHeaderFile

output.mkdir(parents=True, exist_ok=True)
combined = output / "combined.hpp"
os.chdir(source / "ApprovalTests")
combined.write_text(SingleHeaderFile.create_content(
    '.', ProjectDetails(), include_cpps=True))
create_single_header_file(str(combined), str(output / "ApprovalTests.hpp"),
                          str(source), str(source / "ApprovalTests"))
