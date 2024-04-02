#include "doctest/doctest.h"
#include "ApprovalTests.hpp"

#include <string>
#include <ostream>
#include <utility>

// begin-snippet: using_namespace_approvaltests
using namespace ApprovalTests;
// end-snippet

// See the tutorial at:
//   https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Tutorial.md#top

// Maintainance note: keep the 'ApprovalTests::' - for the docs
// begin-snippet: hello_approvals
TEST_CASE("HelloApprovals")
{
    ApprovalTests::Approvals::verify("Hello Approvals");
}
// end-snippet

// begin-snippet: library_book
class LibraryBook
{
public:
    LibraryBook(std::string title_,
                std::string author_,
                int available_copies_,
                std::string language_,
                int pages_,
                std::string isbn_)
        : title(title_)
        , author(author_)
        , available_copies(available_copies_)
        , language(language_)
        , pages(pages_)
        , isbn(isbn_)
    {
    }
    // Data public for simplicity of test demo case.
    // In production code, we would have accessors instead.
    std::string title;
    std::string author;
    int available_copies;
    std::string language;
    int pages;
    std::string isbn;
};
// end-snippet

#if 0
// Non-compiling example for documentation
// begin-snippet: non_printable_object
TEST_CASE("WritableBooks")
{
    LibraryBook harry_potter(
        "Harry Potter and the Goblet of Fire", "J.K. Rowling",
        30, "English", 752, "978-0439139595");

    Approvals::verify(harry_potter); // This does not compile
}
// end-snippet
#endif

TEST_CASE("WritableBooks1")
{
    LibraryBook harry_potter("Harry Potter and the Goblet of Fire",
                             "J.K. Rowling",
                             30,
                             "English",
                             752,
                             "978-0439139595");

    // begin-snippet: printable_object_simple
    Approvals::verify(harry_potter, [](const LibraryBook& b, std::ostream& os) {
        os << "title: " << b.title;
    });
    // end-snippet
}

TEST_CASE("WritableBooks2")
{
    LibraryBook harry_potter("Harry Potter and the Goblet of Fire",
                             "J.K. Rowling",
                             30,
                             "English",
                             752,
                             "978-0439139595");

    // begin-snippet: printable_object
    Approvals::verify(harry_potter, [](const LibraryBook& b, std::ostream& os) {
        os << "title: " << b.title << "\n"
           << "author: " << b.author << "\n"
           << "available_copies: " << b.available_copies << "\n"
           << "language: " << b.language << "\n"
           << "pages: " << b.pages << "\n"
           << "isbn: " << b.isbn << "\n";
    });
    // end-snippet
}
