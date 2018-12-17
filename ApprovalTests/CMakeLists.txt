cmake_minimum_required(VERSION 3.8)
project(ApprovalTests CXX)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
        ApprovalException.h
        Approvals.h
        ApprovalWriter.h
        Catch2Approvals.h
        FileApprover.h
        FileUtils.h
        Macros.h
        StringWriter.h
        SystemUtils.h
        CombinationApprovals.h
        namers/ApprovalNamer.h
        namers/ApprovalTestNamer.h
        reporters/CommandLauncher.h
        reporters/ClipboardReporter.h
        reporters/Reporter.h 
        reporters/FirstWorkingReporter.h
        reporters/DiffReporter.h
        reporters/DiffPrograms.h
        reporters/DiffInfo.h
        reporters/WindowsReporters.h
        reporters/MacReporters.h
        reporters/LinuxReporters.h StringUtils.h reporters/GenericDiffReporter.h reporters/CommandReporter.h OkraApprovals.h
        GoogleTestApprovals.h
        reporters/SystemLauncher.h writers/ExistingFile.h writers/ExistingFile.h namers/ExistingFileNamer.h)
add_library(ApprovalTests ${SOURCE_FILES} )
set_target_properties(ApprovalTests PROPERTIES LINKER_LANGUAGE CXX)
