#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "ccwc.test.cpp"
#include "FileInputException.test.cpp"
#include "InvalidOptionException.test.cpp"

int main() {
    doctest::Context ctx;

    ctx.setOption("no-breaks", true);

    int res = ctx.run();
    return res;
}
