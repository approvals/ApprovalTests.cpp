#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.hpp"

#include "../ApprovalTests/namers/ApprovalTestNamer.h"

using namespace doctest;

struct DocTestApprovalListener : IReporter
{
//    using TestEventListenerBase::TestEventListenerBase;
    TestName currentTest;

    std::ostream&         stdout_stream;
    const ContextOptions& opt;
    const TestCaseData*   tc;
    std::mutex            mutex;

    // constructor has to accept the ContextOptions by ref as a single argument
    DocTestApprovalListener(const ContextOptions& in)
        : stdout_stream(*in.cout)
        , opt(in)
        , tc(nullptr)
    {
        stdout_stream << "DocTestApprovalListener created ***************************************** \n";
    }
    
    void test_case_start(const TestCaseData& testInfo) override
    {
        currentTest.setFileName(testInfo.m_file);
        ApprovalTestNamer::currentTest(&currentTest);
        stdout_stream << "file name " << currentTest.getFileName() << '\n';
    }

    void test_case_end(const CurrentTestCaseStats& /*in*/) override
    {
        while (!currentTest.sections.empty()) {
            currentTest.sections.pop_back();
        }
    }

    void report_query(const QueryData &data) override
    {

    }

    void test_run_start() override
    {

    }

    void test_run_end(const TestRunStats &stats) override
    {

    }

    void test_case_exception(const TestCaseException &exception) override
    {

    }

    void subcase_start(const SubcaseSignature &signature) override
    {
        currentTest.sections.push_back(signature.m_name);

    }

    void subcase_end() override
    {
        currentTest.sections.pop_back();
    }

    void log_assert(const AssertData &data) override
    {

    }

    void log_message(const MessageData &data) override
    {

    }

    void test_case_skipped(const TestCaseData &data) override
    {

    }

//    void subcase_start(const SubcaseSignature& /*in*/) override {
//        std::lock_guard<std::mutex> lock(mutex);
//    }
//
//    void subcase_end() override {
//        std::lock_guard<std::mutex> lock(mutex);
//    }
    
//    Catch2ApprovalListener(DocTest::ReporterConfig const &_config) : DocTest::TestEventListenerBase(_config) {}
//
//    virtual void testCaseStarting(DocTest::TestCaseInfo const &testInfo) override {
//
//        currentTest.setFileName(testInfo.lineInfo.file);
//        ApprovalTestNamer::currentTest(&currentTest);
//    }
//
//    virtual void testCaseEnded(DocTest::TestCaseStats const &/*testCaseStats*/) override {
//        while (!currentTest.sections.empty()) {
//            currentTest.sections.pop_back();
//        }
//    }
//
//    virtual void sectionStarting(DocTest::SectionInfo const &sectionInfo) override {
//        currentTest.sections.push_back(sectionInfo.name);
//    }
//
//    virtual void sectionEnded(DocTest::SectionStats const &/*sectionStats*/) override {
//        currentTest.sections.pop_back();
//    }
};
//CATCH_REGISTER_LISTENER(Catch2ApprovalListener)

REGISTER_REPORTER("approvals", 0, DocTestApprovalListener);

//int main(int argc, char** argv) {
//    doctest::Context context;
//
//    // !!! THIS IS JUST AN EXAMPLE SHOWING HOW DEFAULTS/OVERRIDES ARE SET !!!
//
//    // defaults
//    context.applyCommandLine(argc, argv);
//
//    // overrides
//
//    int res = context.run(); // run queries, or run tests unless --no-run is specified
//
//    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
//        return res;          // propagate the result of the tests
//
//    context.clearFilters(); // removes all filters added up to this point
//
//    // your program - if the testing framework is integrated in your production code
//
//    return res; // the result from doctest is propagated here as well
//}
int main(int argc, char** argv)
{
    char *myargv[] = {"program name", "--reporters=approvals", NULL};
    int myargc = sizeof(myargv) / sizeof(char*) - 1;

    return doctest::Context(myargc, myargv).run();
}
