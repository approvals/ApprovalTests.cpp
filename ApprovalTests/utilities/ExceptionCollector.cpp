#include "ApprovalTests/utilities/ExceptionCollector.h"

namespace ApprovalTests
{
    void ExceptionCollector::gather(std::function<void(void)> functionThatThrows)
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

    ExceptionCollector::~ExceptionCollector()
    {
        if (!exceptionMessages.empty())
        {
            exceptionMessages.emplace_back("ERROR: Calling code forgot to call "
                                           "exceptionCollector.release()");
        }
        release();
    }

    void ExceptionCollector::release()
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
}
