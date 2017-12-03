cmake_minimum_required(VERSION 3.8)
project(ApprovalTests CXX)
set(SOURCE_FILES
        ApprovalException.h
        Approvals.h
        ApprovalTests.h
        Catch2Approvals.h
        FileApprover.h
        FileUtils.h
        Macros.h
        StringWriter.h
        namers/ApprovalNamer.h
        reporters/CommandLauncher.h
        reporters/Reporter.h reporters/FirstWorkingReporter.h reporters/DiffReporter.h)
add_library(ApprovalTests ${SOURCE_FILES} )