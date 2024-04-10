#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "FileInputException.test.cpp"
#include "InvalidOptionException.test.cpp"
#include "Options.test.cpp"

int main() {
    doctest::Context ctx;

    ctx.setOption("no-breaks", true);

    int res = ctx.run();
    return res;
}
