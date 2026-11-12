from approvaltests import set_default_reporter
from approvaltests.reporters import PythonNativeReporter

# Print differences to the command line instead of opening a diff tool
set_default_reporter(PythonNativeReporter())
