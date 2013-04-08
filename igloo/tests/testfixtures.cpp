
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

TestFixture(TestFixturesShouldStillWork)
{
  TestMethod(AndSoShouldTestMethods)
  {
    Assert::That(1, Equals(1));
  }
};

