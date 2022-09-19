#pragma once

#include "ApprovalTests/reporters/DiffInfo.h"

namespace ApprovalTests
{
    namespace DiffPrograms
    {
        namespace CrossPlatform
        {
            DiffInfo VS_CODE();
        }

        namespace Mac
        {
            DiffInfo DIFF_MERGE();

            // begin-snippet: add_reporter_macro_header
            DiffInfo ARAXIS_MERGE();
            // end-snippet

            DiffInfo BEYOND_COMPARE();

            DiffInfo KALEIDOSCOPE();

            DiffInfo SUBLIME_MERGE();

            DiffInfo KDIFF3();

            DiffInfo P4MERGE();

            DiffInfo TK_DIFF();

            DiffInfo VS_CODE();

            DiffInfo CLION();
        }

        namespace Linux
        {
            DiffInfo SUBLIME_MERGE_SNAP();

            DiffInfo SUBLIME_MERGE_FLATPAK();

            DiffInfo SUBLIME_MERGE_REPOSITORY_PACKAGE();

            DiffInfo SUBLIME_MERGE_DIRECT_DOWNLOAD();

            // More ideas available from: https://www.tecmint.com/best-linux-file-diff-tools-comparison/
            DiffInfo KDIFF3();

            DiffInfo MELD();

            DiffInfo BEYOND_COMPARE();
        }

        namespace Windows
        {
            DiffInfo BEYOND_COMPARE_3();

            DiffInfo BEYOND_COMPARE_4();

            DiffInfo TORTOISE_IMAGE_DIFF();

            DiffInfo TORTOISE_TEXT_DIFF();

            DiffInfo TORTOISE_GIT_IMAGE_DIFF();

            DiffInfo TORTOISE_GIT_TEXT_DIFF();

            DiffInfo WIN_MERGE_REPORTER();

            DiffInfo ARAXIS_MERGE();

            DiffInfo CODE_COMPARE();

            DiffInfo SUBLIME_MERGE();

            DiffInfo KDIFF3();

            DiffInfo VS_CODE();
        }
    }
}
