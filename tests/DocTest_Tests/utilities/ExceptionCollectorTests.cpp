#include "doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/utilities/ExceptionCollector.h"

using namespace ApprovalTests;

TEST_CASE("ExceptionCollector")
{
    using namespace ApprovalTests;
    Approvals::verifyExceptionMessage([]()
      {
          ExceptionCollector exceptions;
          for (int i = 1; i <= 4; ++i) {
              exceptions.gather(
                      [&]() { throw std::runtime_error("error number " + StringUtils::toString(i)); });
          }
          exceptions.release();
      });
}
