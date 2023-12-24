#pragma once

#ifdef APPROVAL_TESTS_USE_CATCH2V3
#include <catch2/catch_test_case_info.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/catch_all.hpp>
#else
#include <catch2/catch.hpp>
// using CatchListener = Catch::TestEventListenerBase;
#endif
