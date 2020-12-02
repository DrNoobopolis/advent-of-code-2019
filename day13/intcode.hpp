
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <utility>

#include <cstdlib>
#include <math.h>

void display(std::vector<int> screen_changes)
{
    std::vector<int> x_coordinates, y_coordinates, tile_ids;

    for (int i = 0; i < screen_changes.size(); i++)
    {
        switch (i % 3)
        {
        case 0:
            x_coordinates.push_back(screen_changes[i]);
            break;
        case 1:
            y_coordinates.push_back(screen_changes[i]);
            break;
        case 2:
            tile_ids.push_back(screen_changes[i]);
            break;
        }
    }

    std::vector<std::vector<int>> arcade_cabinet(23);
    for (auto &row : arcade_cabinet)
        row.resize(35);

    for (int i = 0; i < x_coordinates.size(); i++)
    {
        arcade_cabinet[y_coordinates[i]][x_coordinates[i]] = tile_ids[i];
    }

    for (auto row : arcade_cabinet)
    {
        for (auto pixel : row)
        {
            switch (pixel)
            {
            case 0:
                std::cout << " ";
                break;
            default:
                std::cout << pixel;
                break;
            }
        }

        std::cout << '\n';
    }
}

struct program
{
private:
    std::vector<int> intcode; // does this need to be int?
    int iterator = 0;
    int relative_base = 0;
    int find(int, int);
    int valid_index(int);
    std::vector<int> screen_changes;

public:
    program(std::vector<int>);
    std::vector<int> run();
};

program::program(std::vector<int> const source_code)
{
    intcode = source_code;
    intcode.resize(100000);

    // intcode.push_back(10);
    // std::move()
}

std::vector<int> program::run()
{
    for (; iterator < intcode.size();)
    {
        int const opcode = intcode[valid_index(iterator)] % 100;

        switch (opcode)
        {

        case 1: //add
            intcode[valid_index(find(iterator, 3))] = intcode[valid_index(find(iterator, 1))] + intcode[valid_index(find(iterator, 2))];
            iterator += 4;
            break;

        case 2: //multiply
            intcode[valid_index(find(iterator, 3))] = intcode[valid_index(find(iterator, 1))] * intcode[valid_index(find(iterator, 2))];
            iterator += 4;
            break;

        case 3: //input
            display(screen_changes);

            int input;
            std::cin >> input;
            intcode[valid_index(find(iterator, 1))] = input;
            iterator += 2;
            break;

        case 4: //output
            screen_changes.push_back(intcode[valid_index(find(iterator, 1))]);
            iterator += 2;
            break;

        case 5: //jump-if-true
            if (intcode[valid_index(find(iterator, 1))] != 0)
            {
                iterator = intcode[valid_index(find(iterator, 2))];
            }
            else
            {
                iterator += 3;
            }
            break;

        case 6: //jump-if-false
            if (intcode[valid_index(find(iterator, 1))] == 0)
            {
                iterator = intcode[valid_index(find(iterator, 2))];
            }
            else
            {
                iterator += 3;
            }
            break;

        case 7: //less than
            if (intcode[valid_index(find(iterator, 1))] < intcode[valid_index(find(iterator, 2))])
            {
                intcode[valid_index(find(iterator, 3))] = 1;
            }
            else
            {
                intcode[valid_index(find(iterator, 3))] = 0;
            }
            iterator += 4;
            break;

        case 8: //equals
            if (intcode[valid_index(find(iterator, 1))] == intcode[valid_index(find(iterator, 2))])
            {
                intcode[valid_index(find(iterator, 3))] = 1;
            }
            else
            {
                intcode[valid_index(find(iterator, 3))] = 0;
            }
            iterator += 4;
            break;

        case 9: //adjusts the relative base
            relative_base += intcode[valid_index(find(iterator, 1))];
            iterator += 2;
            break;

        case 99: //hault
            iterator = intcode.size();
            return intcode;

        default: //error
            std::cerr << "opcode unkown: " << opcode << '\n';
            exit(EXIT_FAILURE);
            return intcode;
        }
    }

    return intcode;
}

int program::find(int const _iterator, int const _offset)
{
    int const mode = int(intcode[valid_index(_iterator)] / (10 * pow(10, _offset))) % 10;

    if (mode == 0)
    {
        return intcode[valid_index(_iterator + _offset)];
    }
    else if (mode == 1)
    {
        return _iterator + _offset;
    }
    else if (mode == 2)
    {
        return intcode[valid_index(_iterator + _offset)] + relative_base;
    }
    else
    {
        std::cerr << "mode unknown: " << mode << '\n';
        exit(EXIT_FAILURE);
        return 0;
    }
}

int program::valid_index(int const index)
{
    if (index >= 0 && index < intcode.size())
    {
        return index;
    }
    else
    {
        std::cerr << "index greater than vector size" << '\n';
        exit(EXIT_FAILURE);
        return 0;
    }
}