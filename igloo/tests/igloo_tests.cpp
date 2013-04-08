
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

using namespace igloo;

Context(Assertions)
{
	Spec(ShouldHandleIntegerEquality)  
	{
		Assert::That(5, Is().EqualTo(5));		
	}
	
	Spec(ShouldDetectIntegerInequality)
	{
		AssertTestFails(Assert::That(5, Is().EqualTo(4)), "equal to 4");
	}
	
	Spec(ShouldDetectIfNotFails)
	{
		AssertTestFails(Assert::That(5, Is().Not().EqualTo(5)), "Expected: not equal to 5\nActual: 5\n");
	}
	
	Spec(ShouldHandleStrings)
	{
		Assert::That(std::string("joakim"), Is().EqualTo(std::string("joakim")));
	}
	
	Spec(ShouldHandleStringsWithoutExplicitTemplateSpecialization)
	{
		Assert::That("kim", Is().EqualTo("kim"));
	}
	
	Spec(ShouldHandleGreaterThan)
	{
		Assert::That(5, Is().GreaterThan(4));
	}
	
	Spec(ShouldDetectWhenGreaterThanFails)
	{
		AssertTestFails(Assert::That(5, Is().GreaterThan(5)), "Expected: greater than 5\nActual: 5\n");
	}
	
	Spec(ShouldHandleLessThan)
	{
		Assert::That(5, Is().LessThan(6));
	}
	
	Spec(ShouldDetectWhenLessThanFails)
	{
		AssertTestFails(Assert::That(6, Is().LessThan(5)), "Expected: less than 5\nActual: 6\n");
	}
	
	Spec(ShouldThrowExplicitFailureMessage)
	{
		AssertTestFails(Assert::Failure("foo"), "foo");
	}
};

Context(Assertions_EpressionTemplates)
{
	Spec(ShouldHandleIntegerEquality)
	{
		Assert::That(5, Equals(5));
	}                                                            
	
	Spec(ShouldDetectIntegerInequality)
	{
		AssertTestFails(Assert::That(5, Equals(4)), "equal to 4");
	}
	
	Spec(ShouldDetectIfNotFails)
	{
		AssertTestFails(Assert::That(5, !Equals(5)), "Expected: not equal to 5\nActual: 5\n");
	}
	
	Spec(ShouldHandleStrings)
	{
		Assert::That(std::string("joakim"), Equals(std::string("joakim")));
	}
	
	Spec(ShouldHandleStringsWithoutExplicitTemplateSpecialization)
	{
		Assert::That("kim", Equals("kim"));
	}
	
	Spec(ShouldHandleGreaterThan)
	{
		Assert::That(5, IsGreaterThan(4));
	}
	
	Spec(ShouldDetectWhenGreaterThanFails)
	{
		AssertTestFails(Assert::That(5, IsGreaterThan(5)), "Expected: greater than 5\nActual: 5\n");
	}
	
	Spec(ShouldHandleLessThan)
	{
		Assert::That(5, IsLessThan(6));
	}
	
	Spec(ShouldDetectWhenLessThanFails)
	{
		AssertTestFails(Assert::That(6, IsLessThan(5)), "Expected: less than 5\nActual: 6\n");
	}
};

