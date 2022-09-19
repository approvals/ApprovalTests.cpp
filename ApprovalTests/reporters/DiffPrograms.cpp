#include "ApprovalTests/reporters/DiffPrograms.h"

///////////////////////////////////////////////////////////////////////////////
#define APPROVAL_TESTS_MACROS_ENTRY(name, defaultValue)                                  \
    DiffInfo name()                                                                      \
    {                                                                                    \
        return defaultValue;                                                             \
    }
///////////////////////////////////////////////////////////////////////////////

namespace ApprovalTests
{
    namespace DiffPrograms
    {

        namespace CrossPlatform
        {
            APPROVAL_TESTS_MACROS_ENTRY(
                VS_CODE, DiffInfo("code", "-d {Received} {Approved}", Type::TEXT))
        }

        namespace Mac
        {
            APPROVAL_TESTS_MACROS_ENTRY(
                DIFF_MERGE,
                DiffInfo("/Applications/DiffMerge.app/Contents/MacOS/DiffMerge",
                         "{Received} {Approved} -nosplash",
                         Type::TEXT))

            // begin-snippet: add_reporter_macro_implementation
            APPROVAL_TESTS_MACROS_ENTRY(
                ARAXIS_MERGE,
                DiffInfo("/Applications/Araxis Merge.app/Contents/Utilities/compare",
                         Type::TEXT_AND_IMAGE))
            // end-snippet

            APPROVAL_TESTS_MACROS_ENTRY(
                BEYOND_COMPARE,
                DiffInfo("/Applications/Beyond Compare.app/Contents/MacOS/bcomp",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                KALEIDOSCOPE,
                DiffInfo("/Applications/Kaleidoscope.app/Contents/MacOS/ksdiff",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE,
                DiffInfo("/Applications/Sublime "
                         "Merge.app/Contents/SharedSupport/bin/smerge",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                KDIFF3,
                DiffInfo("/Applications/kdiff3.app/Contents/MacOS/kdiff3",
                         "{Received} {Approved} -m -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                P4MERGE,
                DiffInfo("/Applications/p4merge.app/Contents/MacOS/p4merge",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                TK_DIFF,
                DiffInfo("/Applications/TkDiff.app/Contents/MacOS/tkdiff", Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                VS_CODE,
                DiffInfo("/Applications/Visual Studio "
                         "Code.app/Contents/Resources/app/bin/code",
                         "-d {Received} {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(CLION,
                                        DiffInfo("clion",
                                                 "nosplash diff {Received} {Approved}",
                                                 Type::TEXT))
        }

        namespace Linux
        {
            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE_SNAP,
                DiffInfo("/snap/bin/sublime-merge",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE_FLATPAK,
                DiffInfo("/var/lib/flatpak/exports/bin/com.sublimemerge.App",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE_REPOSITORY_PACKAGE,
                DiffInfo("smerge",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE_DIRECT_DOWNLOAD,
                DiffInfo("/opt/sublime_merge/sublime_merge",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            // More ideas available from: https://www.tecmint.com/best-linux-file-diff-tools-comparison/
            APPROVAL_TESTS_MACROS_ENTRY(KDIFF3,
                                        DiffInfo("kdiff3",
                                                 "{Received} {Approved} -m -o {Approved}",
                                                 Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(MELD, DiffInfo("meld", Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(BEYOND_COMPARE,
                                        DiffInfo("bcompare", Type::TEXT_AND_IMAGE))
        }

        namespace Windows
        {
            APPROVAL_TESTS_MACROS_ENTRY(
                BEYOND_COMPARE_3,
                DiffInfo("{ProgramFiles}Beyond Compare 3\\BCompare.exe",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                BEYOND_COMPARE_4,
                DiffInfo("{ProgramFiles}Beyond Compare 4\\BCompare.exe",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                TORTOISE_IMAGE_DIFF,
                DiffInfo("{ProgramFiles}TortoiseSVN\\bin\\TortoiseIDiff.exe",
                         "/left:{Received} /right:{Approved}",
                         Type::IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                TORTOISE_TEXT_DIFF,
                DiffInfo("{ProgramFiles}TortoiseSVN\\bin\\TortoiseMerge.exe", Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                TORTOISE_GIT_IMAGE_DIFF,
                DiffInfo("{ProgramFiles}TortoiseGit\\bin\\TortoiseGitIDiff.exe",
                         "/left:{Received} /right:{Approved}",
                         Type::IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                TORTOISE_GIT_TEXT_DIFF,
                DiffInfo("{ProgramFiles}TortoiseGit\\bin\\TortoiseGitMerge.exe",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(WIN_MERGE_REPORTER,
                                        DiffInfo("{ProgramFiles}WinMerge\\WinMergeU.exe",
                                                 Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                ARAXIS_MERGE,
                DiffInfo("{ProgramFiles}Araxis\\Araxis Merge\\Compare.exe",
                         Type::TEXT_AND_IMAGE))

            APPROVAL_TESTS_MACROS_ENTRY(
                CODE_COMPARE,
                DiffInfo("{ProgramFiles}Devart\\Code Compare\\CodeCompare.exe",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                SUBLIME_MERGE,
                DiffInfo("{ProgramFiles}Sublime Merge\\smerge.exe",
                         "mergetool --no-wait {Received} {Approved} -o {Approved}",
                         Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(KDIFF3,
                                        DiffInfo("{ProgramFiles}KDiff3\\bin\\kdiff3.exe",
                                                 "{Received} {Approved} -m -o {Approved}",
                                                 Type::TEXT))

            APPROVAL_TESTS_MACROS_ENTRY(
                VS_CODE,
                DiffInfo("{ProgramFiles}Microsoft VS Code\\Code.exe",
                         "-d {Received} {Approved}",
                         Type::TEXT))
        }

    }
}
