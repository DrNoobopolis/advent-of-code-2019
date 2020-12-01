
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <memory>
#include <utility>
#include <cstdlib>

struct program
{
private:
    std::vector<int> intcode; // does this need to be long?
    int iterator = 0;
    int relative_base = 0;

    int find(int, int);

public:
    program(std::vector<int> &);

    void run(std::vector<int> &);
};

program::program(std::vector<int> &source_code)
{
    intcode = std::move(source_code);
    intcode.resize(1000);
}

void program::run(std::vector<int> &output)
{
    for (; iterator < intcode.size();)
    {
        switch (intcode[iterator] % 100)
        {

        case 1: //add
            intcode[find(iterator, 3)] = intcode[find(iterator, 1)] + intcode[find(iterator, 2)];
            iterator += 4;
            break;

        case 2: //multiply
            intcode[find(iterator, 3)] = intcode[find(iterator, 1)] * intcode[find(iterator, 2)];
            iterator += 4;
            break;

        case 3: //input
            int input;
            std::cin >> input;
            intcode[find(iterator, 1)] = input;
            iterator += 2;
            break;

        case 4: //output
            output.push_back(intcode[find(iterator, 1)]);
            iterator += 2;
            break;

        case 5: //jump-if-true
            if (intcode[find(iterator, 1)] != 0)
            {
                iterator = intcode[find(iterator, 2)];
            }
            else
            {
                iterator += 3;
            }
            break;

        case 6: //jump-if-false
            if (intcode[find(iterator, 1)] == 0)
            {
                iterator = intcode[find(iterator, 2)];
            }
            else
            {
                iterator += 3;
            }
            break;

        case 7: //less than
            if (intcode[find(iterator, 1)] < intcode[find(iterator, 2)])
            {
                intcode[find(iterator, 3)] = 1;
            }
            else
            {
                intcode[find(iterator, 3)] = 0;
            }
            iterator += 4;
            break;

        case 8: //equals
            if (intcode[find(iterator, 1)] == intcode[find(iterator, 2)])
            {
                intcode[find(iterator, 3)] = 1;
            }
            else
            {
                intcode[find(iterator, 3)] = 0;
            }
            iterator += 4;
            break;

        case 9: //adjusts the relative base
            relative_base += intcode[find(iterator, 1)];
            iterator += 2;
            break;

        case 99: //hault
            iterator = intcode.size();
            return;

        default: //error
            std::cerr << "opcode unkown: " << intcode[iterator] % 100 << '\n';
            exit(EXIT_FAILURE);
            return;
        }
    }
}

// should be safer

int program::find(int const _iterator, int const _offset)
{
    int mode = this->intcode[_iterator];
    mode /= 10 * pow(10, _offset);

    mode %= 10;

    if (mode == 0)
    {
        return this->intcode[_iterator + _offset];
    }
    else if (mode == 1)
    {
        return _iterator + _offset;
    }
    else if (mode == 2)
    {
        return this->intcode[_iterator + _offset] + relative_base;
    }
    else
    {
        std::cerr << "mode unknown: " << mode << '\n';
        exit(EXIT_FAILURE);
        return 0;
    }
}
