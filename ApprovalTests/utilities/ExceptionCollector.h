#ifndef APPROVALTESTS_CPP_EXCEPTIONCOLLECTOR_H
#define APPROVALTESTS_CPP_EXCEPTIONCOLLECTOR_H

#include <sstream>
#include <exception>
#include <string>
#include <vector>
#include <functional>

namespace ApprovalTests
{
    class ExceptionCollector
    {
        std::vector<std::string> exceptionMessages;

    public:
        void gather(std::function<void(void)> functionThatThrows)
        {
            try
            {
                functionThatThrows();
            }
            catch (const std::exception& e)
            {
                exceptionMessages.emplace_back(e.what());
            }
        }
        ~ExceptionCollector()
        {
            if (!exceptionMessages.empty())
            {
                exceptionMessages.emplace_back(
                    "ERROR: Calling code forgot to call "
                    "exceptionCollector.release()");
            }
            release();
        }

        void release()
        {
            if (!exceptionMessages.empty())
            {
                std::stringstream s;
                s << exceptionMessages.size() << " exceptions were thrown:\n\n";
                int count = 1;
                for (const auto& error : exceptionMessages)
                {
                    s << count++ << ") " << error << '\n';
                }
                exceptionMessages.clear();
                throw std::runtime_error(s.str());
            }
        }
    };
}

#endif //APPROVALTESTS_CPP_EXCEPTIONCOLLECTOR_H
