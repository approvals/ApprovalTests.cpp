
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;


Context(A_context_with_attribute)
{
  struct ContextHavingAttribute : public ContextProvider<ContextHavingAttribute, ContextWithAttribute<void> >
  {
    ContextAttribute("name of attribute", "value of attribute")

  } context_having_attribute;

  Spec(attribute_can_be_retrieved)
  {
    const std::string& attribute = context_having_attribute.GetAttribute("name of attribute");

    AssertThat(attribute, Is().EqualTo("value of attribute"));
  }

  Spec(empty_string_is_returned_if_attribute_doesnt_exists)
  {
    const std::string& attribute = context_having_attribute.GetAttribute("non-existing attribute");

    AssertThat(attribute, Is().Empty());
  }
};
