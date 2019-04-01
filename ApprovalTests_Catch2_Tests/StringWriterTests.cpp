#include "Catch.hpp"
#include <ApprovalTests/StringWriter.h>
#include <ApprovalTests/Approvals.h>

using namespace std;

string readFileAndDelete(const char *fileName) {
    ifstream in(fileName, ios_base::in);
    stringstream written;
    written << in.rdbuf();
    in.close();
    remove(fileName);

    string text = written.str();
    return text;
}

TEST_CASE("ItWritesTheContentsToAFile") {
    StringWriter s("Hello");
    auto fileName = "out.txt";
    s.write(fileName);

    string text = readFileAndDelete(fileName);
    REQUIRE(text == "Hello\n");
}

TEST_CASE("ItWritesTheContentsToAStream") {
    stringstream out;
    StringWriter s("Hello");
    s.Write(out);
    REQUIRE(out.str() == "Hello\n");
}

TEST_CASE("TheDefaultExtensionIsText") {
    StringWriter s("Hello");
    REQUIRE(s.getFileExtensionWithDot() == ".txt");
}

TEST_CASE("TheExtensionIsConfigurable") {
    StringWriter s("Hello", ".html");
    REQUIRE(s.getFileExtensionWithDot() == ".html");
}

TEST_CASE("ItGivesMeaningfulErrorIfWritingFails") {
    StringWriter s("Hello");
    auto fileName = "I/do/not/exist/out.txt";
    std::string message;
    try
    {
        s.write(fileName);
    }
    catch(const std::runtime_error& e)
    {
        message = e.what();
    }
    Approvals::verify(message);
}
