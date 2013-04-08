
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>

using namespace igloo;

class ProgressWritingTestListener : public TestListener
{
  public:
  void TestRunStarting()
  {
    std::cout << "Test run is starting..." << std::endl;
  }

  void TestRunEnded(const TestResults& )
  {
    std::cout << "Test run ended." << std::endl;
  }

  void ContextRunStarting(const ContextBase& context)
  {
    std::cout << "Starting test for context " << context.Name() << " with category " << context.GetAttribute("category") << std::endl;
  }

  void ContextRunEnded(const ContextBase& context)
  {
    std::cout << "Ending test for context " << context.Name() << " with category " << context.GetAttribute("category") << std::endl;
  }

  void SpecRunStarting(const ContextBase& context, const std::string& specName)
  {
    std::cout << "Spec run starting for " << context.Name() << " and spec " << specName << std::endl;
  }

  void SpecSucceeded(const ContextBase& context, const std::string& specName)
  {
    std::cout << "Spec succeeded for " << context.Name() << " and spec " << specName << std::endl;
  }
  void SpecFailed(const ContextBase& context, const std::string& specName)
  {
    std::cout << "Spec failed for " << context.Name() << " and spec " << specName << std::endl;
  }
};

//int main()
//{
//  DefaultTestResultsOutput output;
//  TestRunner runner(output);
//
//  ProgressWritingTestListener listener;
//
//  runner.AddListener(&listener);
//
//  runner.Run();
//}

int main()
{
  return TestRunner::RunAllTests();
}
