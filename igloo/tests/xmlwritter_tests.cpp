
//          Copyright Bertrand Cachet 2012
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <tests/igloo_self_test.h>
using namespace igloo;

#include <sstream>

Context(EmptyXMWriter)
{  
  std::stringstream ss;
  XmlWriter* ws;

  void SetUp()
  {
    ws = new XmlWriter(ss);
  }

  Spec(Should_generate_XML_header_when_empty)
  {
    Assert::That(ss.str(), Is().StartingWith("<?xml version=\"1.0\" encoding=\"utf-8\"?>"));
  }

  Context(XmlWriter_with_one_empty_element)
  {
    void SetUp()
    {
      XmlElement tag("tag", *Parent().ws);
    }

    Spec(Should_contain_one_tag_node)
    {
      Assert::That(Parent().ss.str(), Is().EndingWith("<tag/>"));
    }
    
    Context(XmlWriter_with_two_elements) {
      void SetUp()
      {
        XmlElement tag("tag", *Parent().Parent().ws);
      }

      Spec(Should_contain_two_tag_nodes)
      {
        Assert::That(Parent().Parent().ss.str(), Is().EndingWith("<tag/><tag/>"));
      }
    };
  };

  Context(XmlWriter_with_one_element_with_content)
  {
    void SetUp()
    {
      XmlElement tag("tag", *Parent().ws);
      tag.contents("some content");
    }

    Spec(Should_contain_one_tag_node)
    {
      Assert::That(Parent().ss.str(), Is().Containing("<tag>some content</tag>"));
    }
  };

  Context(XmlWriter_with_one_element_with_attribute)
  {
    void SetUp()
    {
      XmlElement tag("tag", *Parent().ws);
      tag.attr("name", "value");
    }

    Spec(Should_contain_one_tag_node)
    {
      Assert::That(Parent().ss.str(), Is().Containing("<tag name=\"value\"/>"));
    }
  };

  Context(XmlWriter_with_one_element_with_attribute_and_content)
  {
    void SetUp()
    {
      XmlElement tag("tag", *Parent().ws);
      tag.attr("name", "value");
      tag.contents("some text");
    }

    Spec(Should_contain_one_tag_node)
    {
      Assert::That(Parent().ss.str(), Is().Containing("<tag name=\"value\">some text</tag>"));
    }
  };

  Context(XmlWriter_with_nested_elements)
  {
    void SetUp()
    {
      {
        XmlElement tag("tag", *Parent().ws);
        XmlElement inner("inner", *Parent().ws);
      }
      XmlElement tag("tag", *Parent().ws);
    }

    Spec(Should_contain_one_tag_node)
    {
      Assert::That(Parent().ss.str(), Is().Containing("<tag><inner/></tag><tag/>"));
    }
  };

};

