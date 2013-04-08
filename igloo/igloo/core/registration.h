
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_REGISTRATION_H
#define IGLOO_REGISTRATION_H

#define IGLOO_PRIVATE_GENERATE_CONTEXTREGISTRAR(contextName, baseContextName) \
  struct contextName; \
  struct ContextRegistrar_##contextName \
  { \
    ContextRegistrar_##contextName() \
    { \
      igloo::TestRunner::RegisterContext<igloo::ContextRunner<baseContextName, contextName> >(#contextName); \
    } \
  } contextName##_IglooRegistrar;

#define IGLOO_CONTEXT_REGISTRATION(contextName) \
  IGLOO_PRIVATE_GENERATE_CONTEXTREGISTRAR(contextName, void) \
  struct contextName : public ContextProvider<contextName, IGLOO_CURRENT_CONTEXT>

#define IGLOO_PARENT_CONTEXT_REGISTRATION(contextName) \
  struct contextName : public ContextProvider<contextName, IGLOO_CURRENT_CONTEXT>

#define IGLOO_SUBCONTEXT_REGISTRATION(contextName, baseContextName) \
  IGLOO_PRIVATE_GENERATE_CONTEXTREGISTRAR(contextName, baseContextName) \
  struct contextName : public baseContextName

#define IGLOO_SPEC_REGISTRATION(specName) \
  struct SpecRegistrar_##specName \
  { \
    SpecRegistrar_##specName() \
    { \
	  ContextRegistry<IGLOO_CURRENT_CONTEXT>::RegisterSpec(#specName, &IGLOO_CURRENT_CONTEXT::specName); \
    } \
  } SpecRegistrar_##specName; \
  virtual void specName()

#define IGLOO_CONTEXT_ATTRIBUTE_REGISTRATION(name, value) \
    struct AttributeRegistrar_##IGLOO_CURRENT_CONTEXT \
    {\
      AttributeRegistrar_##IGLOO_CURRENT_CONTEXT()\
      {\
        ContextAttributeStorage<IGLOO_CURRENT_CONTEXT>::Set(name, value);\
      }\
    } AttributeRegistrar_##IGLOO_CURRENT_CONTEXT;

#endif
