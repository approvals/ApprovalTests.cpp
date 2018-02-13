cmake_minimum_required(VERSION 3.8)
project(ApprovalTests CXX)
set(SOURCE_FILES
        ApprovalException.h
        Approvals.h
        ApprovalTests.h
        Catch2Approvals.h
        FileApprover.h
        Macros.h
        StringWriter.h
        SystemUtils.h
        namers/ApprovalNamer.h
        reporters/CommandLauncher.h
        reporters/Reporter.h 
        reporters/FirstWorkingReporter.h
        reporters/DiffReporter.h
        reporters/DiffPrograms.h
        reporters/DiffInfo.h
        reporters/WindowsReporters.h
        reporters/MacReporters.h
        reporters/LinuxReporters.h StringUtils.h reporters/GenericDiffReporter.h reporters/CommandReporter.h)
add_library(ApprovalTests ${SOURCE_FILES} )
set_target_properties(ApprovalTests PROPERTIES LINKER_LANGUAGE CXX)
