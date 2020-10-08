#pragma once
#ifdef FMT_VERSION
namespace ApprovalTests
{
    class FmtToString
    {
    public:
        template <typename T> static std::string toString(const T& printable)
        {
            (void)printable;
            return fmt::to_string(printable);
        }
    };

}
#endif
