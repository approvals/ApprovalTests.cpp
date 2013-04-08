
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_CONTEXTREGISTRY_H
#define IGLOO_CONTEXTREGISTRY_H

namespace igloo {

  template <typename ContextToCall>
  struct ContextRegistry  
  {
    static void RegisterSpec(const std::string& name, void (ContextToCall::*spec)())
    {
      GetSpecs().insert(std::make_pair(name, spec));
    }

    static void ClearRegisteredSpecs()
    {
      GetSpecs().clear();
    }

    template <typename ContextToCreate>
    static void Run(const std::string& contextName, TestResults& results, TestListener& testListener)
    {    
      const Specs& specs = GetSpecs();
      CallSpecs<ContextToCreate>(specs, contextName, results, testListener);
    }

    typedef void (ContextToCall::*SpecPtr)();
    typedef std::map<std::string, SpecPtr> Specs;
    
    template <typename ContextToCreate>
    static void CallSpecs(const Specs& specs, const std::string& contextName, TestResults& results, TestListener& testListener)
    {
      ContextToCreate::SetUpContext();

      ContextToCreate c;
      c.SetName(contextName);

      testListener.ContextRunStarting(c);

      typename Specs::const_iterator it;
      for (it = specs.begin(); it != specs.end(); it++)
      {
        const std::string& specName = (*it).first;
        SpecPtr spec = (*it).second;

        ContextToCreate context;
        context.SetName(contextName);

        testListener.SpecRunStarting(context, specName);
        
        if(CallSpec(context, specName, spec, results))
        {
          testListener.SpecSucceeded(context, specName); 
        }
        else
        {
          testListener.SpecFailed(context, specName);
        }
      }

      ContextToCreate::TearDownContext();

      testListener.ContextRunEnded(c);
    }

    static bool CallSpec(ContextToCall& context, const std::string& specName, SpecPtr spec, TestResults& results)
    {
      bool result = true;
      
      try
      {
        context.IglooFrameworkSetUp();
        (context.*spec)();
       }
      catch (const AssertionException& e)
      {
        results.AddResult(TestResultFactory(context.Name(), specName).CreateFromException(e));
        result = false;
      }
      catch (...)
      {
        results.AddResult(FailedTestResult(context.Name(), specName, "Caught unknown exception"));
        result = false;
      }
      
      try 
      {
        context.IglooFrameworkTearDown();
      }
      catch (const AssertionException& e) 
      {
        results.AddResult(TestResultFactory(context.Name(), specName).CreateFromException(e));
        result = false;
      }
      catch (...)
      {
        results.AddResult(FailedTestResult(context.Name(), specName, "Caught unknown exception"));
        result = false;
      }
      
      if(result)
      {
        results.AddResult(TestResultFactory(context.Name(), specName).CreateSuccessful());
      }
      
      return result;
    }

    static Specs& GetSpecs()
    {
      static Specs specs;
      return specs;
    }
  };  
}
#endif
