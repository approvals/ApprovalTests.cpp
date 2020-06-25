#include "ApprovalTests/reporters/ClipboardReporter.h"
#include "ApprovalTests/utilities/SystemUtils.h"

namespace ApprovalTests
{
    std::string ClipboardReporter::getCommandLineFor(const std::string& received,
                                                     const std::string& approved,
                                                     bool isWindows)
    {
        if (isWindows)
        {
            return std::string("move /Y ") + "\"" + received + "\" \"" + approved + "\"";
        }
        else
        {
            return std::string("mv ") + "\"" + received + "\" \"" + approved + "\"";
        }
    }

    bool ClipboardReporter::report(std::string received, std::string approved) const
    {
        copyToClipboard(
            getCommandLineFor(received, approved, SystemUtils::isWindowsOs()));
        return true;
    }

    void ClipboardReporter::copyToClipboard(const std::string& newClipboard)
    {
        /*
     This will probably not work on Linux.

     From https://stackoverflow.com/a/750466/104370
     In case of X, yes, there's xclip (and others). xclip -selection c will send data to the clipboard that
     works with Ctrl-C, Ctrl-V in most applications.

     If you're trying to talk to the Mac OS X clipboard, there's pbcopy.

     If you're in Linux terminal mode (no X) then maybe you need to look into gpm.

     There's also GNU screen which has a clipboard. To put stuff in there, look at the screen command "readreg".

     Under Windows/cygwin, use /dev/clipboard or clip for newer versions of Windows (at least Windows 10).
     */

        std::string clipboardCommand;
        if (SystemUtils::isWindowsOs())
        {
            clipboardCommand = "clip";
        }
        else if (SystemUtils::isMacOs())
        {
            clipboardCommand = "pbcopy";
        }
        else
        {
            clipboardCommand = "pbclip";
        }
        auto cmd = std::string("echo ") + newClipboard + " | " + clipboardCommand;
        SystemUtils::runSystemCommandOrThrow(cmd);
    }
}
