#pragma once

#include <doctest/doctest.h>

// Exported by the runner and imported by the dynamically loaded tests.
DOCTEST_INTERFACE void recordModuleTest(int module);
