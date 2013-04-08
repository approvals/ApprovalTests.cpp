
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "igloo_self_test.h"
using namespace igloo;

Context(AFreshContext)
{
  AFreshContext() : member("unaltered")
  {
  }

  Spec(WhenAMethodIsCalledItShouldHaveItsOwnContext)
  {
    Assert::That(member, Equals("unaltered"));
    member = "altered";
  }

  Spec(WhenASecondMethodIsCalledItShouldAlsoHaveItsOwnContext)
  {
    Assert::That(member, Equals("unaltered"));
    member = "altered";
  }

  std::string member;
};

Context(AContextWithSetupAndTearDown)
{   
  Spec(WhenASpecIsExecutedSetUpAndTearDownIsCalled)
  {
    ContextToTest contextToTest;
    contextToTest.SetName("ContextToTest");

    ContextRegistry<ContextToTest>::CallSpec(contextToTest, "ASpec", &ContextToTest::ASpec, results);
    
    Assert::That(contextToTest.log, Equals("SetUp called TearDown called "));
  }
  
  Spec(WhenASpecInAnInnerContextIsCalledOuterSetUpAndTearDownShouldBeCalled)
  {
    ContextToTest::InnerContext innerContext;
    innerContext.SetName("InnerContext");

    ContextRegistry<ContextToTest::InnerContext>::CallSpec(innerContext, "ASpec", &ContextToTest::InnerContext::ASpec, results);
    
    Assert::That(innerContext.Parent().log, Equals("SetUp called Inner SetUp called Inner TearDown called TearDown called "));    
  }
  
  Spec(SetUpAndTearDownAreCalledForFailingSpecs)
  {
    ContextToTest contextToTest;
    contextToTest.SetName("ContextToTest");

    ContextRegistry<ContextToTest>::CallSpec(contextToTest, "AFailingSpec", &ContextToTest::AFailingSpec, results);
    
    Assert::That(contextToTest.log, Equals("SetUp called TearDown called "));    
  }
  
  Spec(SetUpAndTearDownAreCalledForFailingSpecInNestedContext)
  {
    ContextToTest::InnerContext innerContext;
    innerContext.SetName("InnerContext");

    ContextRegistry<ContextToTest::InnerContext>::CallSpec(innerContext, "AFailingSpec", &ContextToTest::InnerContext::AFailingSpec, results);
    
    Assert::That(innerContext.Parent().log, Equals("SetUp called Inner SetUp called Inner TearDown called TearDown called "));    
  } 
  
  struct ContextToTest : public ContextProvider<ContextToTest, ContextWithAttribute<void> >
  {
    void SetUp()
    {
      log = "SetUp called ";
    }
    
    void TearDown()
    {
      log += "TearDown called ";
    }
    
    Spec(ASpec)
    {
    }
    
    Spec(AFailingSpec)
    {
      Assert::Failure("This should fail");
    }
    
    struct InnerContext : public ContextProvider<InnerContext, ContextToTest>
    {
      void SetUp()
      {
        Parent().log += "Inner SetUp called ";
      }
      
      void TearDown()
      {
        Parent().log += "Inner TearDown called ";
      }
      
      Spec(ASpec)
      {
      }
      
      Spec(AFailingSpec)
      {
        Assert::Failure("This should fail");
      }      
    };
    
    std::string log;
  };  
  
  TestResults results;
};
