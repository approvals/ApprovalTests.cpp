#include "ApprovalTests/reporters/CrossPlatformReporters.h"

#include "DiffPrograms.h"

namespace ApprovalTests
{
    namespace CrossPlatform
    {
        VisualStudioCodeReporter::VisualStudioCodeReporter()
            : GenericDiffReporter(DiffPrograms::CrossPlatform::VS_CODE())
        {
        }

        CrossPlatformDiffReporter::CrossPlatformDiffReporter()
            : FirstWorkingReporter({
                  // begin-snippet: cross_platform_diff_reporters
                  new VisualStudioCodeReporter(),
                  // end-snippet
              })
        {
        }
    }
}
