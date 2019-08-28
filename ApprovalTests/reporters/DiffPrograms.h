#ifndef APPROVALTESTS_CPP_DIFFPROGRAMS_H
#define APPROVALTESTS_CPP_DIFFPROGRAMS_H

#include "DiffInfo.h"

///////////////////////////////////////////////////////////////////////////////
#define APPROVAL_TESTS_MACROS_ENTRY(name, defaultValue) \
        static DiffInfo name() { return defaultValue; }
///////////////////////////////////////////////////////////////////////////////

namespace ApprovalTests {
namespace DiffPrograms {


    namespace Mac {
        APPROVAL_TESTS_MACROS_ENTRY(DIFF_MERGE,
              DiffInfo("/Applications/DiffMerge.app/Contents/MacOS/DiffMerge", "%s %s -nosplash", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(BEYOND_COMPARE, DiffInfo("/Applications/Beyond Compare.app/Contents/MacOS/bcomp", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(KALEIDOSCOPE, DiffInfo("/Applications/Kaleidoscope.app/Contents/MacOS/ksdiff", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(KDIFF3, DiffInfo("/Applications/kdiff3.app/Contents/MacOS/kdiff3", "%s %s -m", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(P4MERGE, DiffInfo("/Applications/p4merge.app/Contents/MacOS/p4merge", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(TK_DIFF, DiffInfo("/Applications/TkDiff.app/Contents/MacOS/tkdiff", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(VS_CODE, DiffInfo("/Applications/Visual Studio Code.app/Contents/Resources/app/bin/code", "-d %s %s", Type::TEXT))
    }
    namespace Linux {
        // More ideas available from: https://www.tecmint.com/best-linux-file-diff-tools-comparison/
        APPROVAL_TESTS_MACROS_ENTRY(KDIFF3, DiffInfo("kdiff3", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(MELD, DiffInfo("meld", Type::TEXT))
    }
    namespace Windows {
        APPROVAL_TESTS_MACROS_ENTRY(BEYOND_COMPARE_3, DiffInfo("{ProgramFiles}Beyond Compare 3\\BCompare.exe", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(BEYOND_COMPARE_4, DiffInfo("{ProgramFiles}Beyond Compare 4\\BCompare.exe", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(TORTOISE_IMAGE_DIFF,
              DiffInfo("{ProgramFiles}TortoiseSVN\\bin\\TortoiseIDiff.exe", "/left:%s /right:%s", Type::IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(TORTOISE_TEXT_DIFF, DiffInfo("{ProgramFiles}TortoiseSVN\\bin\\TortoiseMerge.exe", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(WIN_MERGE_REPORTER, DiffInfo("{ProgramFiles}WinMerge\\WinMergeU.exe", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(ARAXIS_MERGE, DiffInfo("{ProgramFiles}Araxis\\Araxis Merge\\Compare.exe", Type::TEXT_AND_IMAGE))

        APPROVAL_TESTS_MACROS_ENTRY(CODE_COMPARE, DiffInfo("{ProgramFiles}Devart\\Code Compare\\CodeCompare.exe", Type::TEXT))

        APPROVAL_TESTS_MACROS_ENTRY(KDIFF3, DiffInfo("{ProgramFiles}KDiff3\\kdiff3.exe", Type::TEXT))
        APPROVAL_TESTS_MACROS_ENTRY(VS_CODE, DiffInfo("{ProgramFiles}Microsoft VS Code\\Code.exe", "-d %s %s", Type::TEXT))

    }
}
}

#endif //APPROVALTESTS_CPP_DIFFPROGRAMS_H
