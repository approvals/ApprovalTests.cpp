#include <sstream>
#include "ApprovalTests/namers/FileNameSanitizerDisposer.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"

namespace ApprovalTests
{
    FileNameSanitizer FileNameSanitizerDisposer::current = [](std::string fileName){
      std::stringstream result;
      for (auto ch : fileName)
      {
          if (!ApprovalTestNamer::isForbidden(ch))
          {
              result << ch;
          }
          else
          {
              result << "_";
          }
      }
      return result.str();
    };

    FileNameSanitizerDisposer::FileNameSanitizerDisposer(FileNameSanitizer sanitizer)
    {
        previous_result = std::move(FileNameSanitizerDisposer::current);
        FileNameSanitizerDisposer::current = std::move(sanitizer);
    }

    FileNameSanitizerDisposer::~FileNameSanitizerDisposer()
    {
        FileNameSanitizerDisposer::current = std::move(previous_result);
    }
}
