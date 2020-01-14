#include <boost/ut.hpp>

int main()
{
    using namespace boost::ut;
    "hello world"_test = [] {
        int i = 42;
        expect(42_i == i);
    };
}
