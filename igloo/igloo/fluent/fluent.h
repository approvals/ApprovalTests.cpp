
//          Copyright Joakim Karlsson & Kim Gräsman 2010-2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef IGLOO_FLUENT_H
#define IGLOO_FLUENT_H

#include <igloo/fluent/constraintlist.h>
#include <igloo/fluent/constraintadapter.h>
#include <igloo/fluent/operators/constraintoperator.h>
#include <igloo/fluent/operators/andoperator.h>
#include <igloo/fluent/operators/oroperator.h>
#include <igloo/fluent/operators/collections/collectionconstraintevaluator.h>
#include <igloo/fluent/operators/collections/alloperator.h>
#include <igloo/fluent/operators/collections/noneoperator.h>
#include <igloo/fluent/operators/collections/atleastoperator.h>
#include <igloo/fluent/operators/collections/exactlyoperator.h>
#include <igloo/fluent/operators/collections/atmostoperator.h>
#include <igloo/fluent/operators/notoperator.h>
#include <igloo/fluent/expressionbuilder.h>

namespace igloo {

  inline ExpressionBuilder<Nil> Is()
  {
    return ExpressionBuilder<Nil>(Nil());
  }

  inline ExpressionBuilder<Nil> Has()
  {
     return ExpressionBuilder<Nil>(Nil());
  }

}

#endif
