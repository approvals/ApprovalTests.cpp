#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/utilities/SystemUtils.h"

namespace ApprovalTests
{
    // clang-format off
    // begin-snippet: separate_approved_and_received_directory_names
    auto path = "{TestSourceDirectory}/{ApprovedOrReceived}/{TestFileName}.{TestCaseName}.{FileExtension}";
    // end-snippet
    // clang-format on
    SeparateApprovedAndReceivedDirectoriesNamer::
        SeparateApprovedAndReceivedDirectoriesNamer()
        : TemplatedCustomNamer(path)
    {
    }

    DefaultNamerDisposer SeparateApprovedAndReceivedDirectoriesNamer::useAsDefaultNamer()
    {
        return Approvals::useAsDefaultNamer([]() {
            return std::make_shared<SeparateApprovedAndReceivedDirectoriesNamer>();
        });
    }
}
