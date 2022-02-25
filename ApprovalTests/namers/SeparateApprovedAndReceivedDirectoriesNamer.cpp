#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/utilities/SystemUtils.h"

namespace ApprovalTests
{
    std::string separateDirectoryPath()
    {
        // clang-format off
        // begin-snippet: separate_approved_and_received_directory_names
        auto path = "{TestSourceDirectory}/{ApprovalsSubdirectory}/{ApprovedOrReceived}/{TestFileName}.{TestCaseName}.{FileExtension}";
        // end-snippet
        // clang-format on
        return path;
    }

    SeparateApprovedAndReceivedDirectoriesNamer::
        SeparateApprovedAndReceivedDirectoriesNamer()
        : TemplatedCustomNamer(separateDirectoryPath())
    {
    }

    DefaultNamerDisposer SeparateApprovedAndReceivedDirectoriesNamer::useAsDefaultNamer()
    {
        return Approvals::useAsDefaultNamer([]() {
            return std::make_shared<SeparateApprovedAndReceivedDirectoriesNamer>();
        });
    }
}
