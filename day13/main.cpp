
#include <iostream>
#include <vector>
#include <algorithm>

#include "intcode.hpp"
#include "auxiliary.hpp"

int main()
{
    std::vector<int> source_code = read("input.txt");

    program program(source_code);

    // &source_code[0] == NULL

    program.run();
}

// write a testing module using constexpr and static assert

// using exceptions?

// unit tests

// 1,0,0,0,99
// 2,0,0,0,99

// 2,3,0,3,99
// 2,3,0,6,99

// 2,4,4,5,99,0
// 2,4,4,5,99,9801

// 1,1,1,4,99,5,6,0,99
// 30,1,1,4,2,5,6,0,99

// static_assert(10 == 10, "");
