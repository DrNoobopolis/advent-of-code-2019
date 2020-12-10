
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <utility>

#include <cstdlib>
#include <math.h>

/*
valgrind
gdb
ASan/MSan - never seen this before

debugging 
clang++ -g main.cpp
valgrind --tool=memcheck --vgdb=yes --vgdb-error=0 ./a.out 
[new terminal window]
gdb ./a.out
target remote | /usr/lib/valgrind/../../bin/vgdb --pid=34714
detach
target remote | /usr/lib/valgrind/../../bin/vgdb --pid=34714
p x_coordinates[i] 

start building models for refactoring?

using patterns to change between human and bot mode?
*/

enum class intcode_operations
{
    add,
    multiply,
    input,
    output,
    jump_if_true,
    jump_if_false,
    less_than,
    equals,
    adjusts_the_relative_base, // are you sure about that?
    hault,
    error
};

class arcade_cabinet
{
private:
    std::vector<std::vector<int>> screen;

    int score;

public:
    int next_move();

    arcade_cabinet();

    void update(std::vector<int>);

    void print_score()
    {
        std::cout << score << '\n';
    }

    void display();
};

void arcade_cabinet::update(std::vector<int> screen_changes)
{
    if (screen_changes.size() % 3 != 0)
    {
        std::cerr << "Unexpected length" << '\n';
        exit(EXIT_FAILURE);
    }

    int x_position, y_position, value;

    for (int i = 0; i < screen_changes.size(); i++)
    {
        switch (i % 3)
        {
        case 0:
            x_position = screen_changes[i];
            break;
        case 1:
            y_position = screen_changes[i];
            break;
        case 2:
            value = screen_changes[i];

            if (x_position == -1 && y_position == 0)
            {
                this->score = value;
            }
            else if (x_position < 0 || y_position < 0 || value < 0 || value > 4)
            {
                std::cerr << "Unexpected value" << '\n';
                exit(EXIT_FAILURE);
            }
            else
            {
                this->screen[y_position][x_position] = value;
            }

            break;
        }
    }
}

arcade_cabinet::arcade_cabinet()
{
    this->screen.resize(23);
    for (auto &row : this->screen)
        row.resize(35);
}

void arcade_cabinet::display()
{
    for (auto row : this->screen)
    {
        for (auto pixel : row)
        {
            switch (pixel)
            {
            case 0:
                std::cout << " ";
                break;
            case 1:
                std::cout << "█";
                break;
            case 2:
                std::cout << "■";
                break;
            default:
                std::cout << pixel;
                break;
            }
        }

        std::cout << '\n';
    }
}

// the default destructor works fine unless we have dynamically allocated memory or pointer in class

class Actor
{
public:
    virtual void output() = 0; // pure virtual interface
    virtual void input() = 0;  // pure virtual interface
};

/*
class User implements Actor
{
public:
    void output;
    void input;
};
*/

int index_x(std::vector<std::vector<int>> table, int target)
{
    for (std::vector<int> row : table)
    {
        auto const target_find = find(row.begin(), row.end(), target);
        bool const target_found = target_find != row.end();

        if (target_found)
            return row.end() - target_find;
    }

    return -1;
}

//

int arcade_cabinet::next_move()
{
    int const paddle_x = index_x(this->screen, 3);
    int const ball_x = index_x(this->screen, 4);

    // assumes paddle_x and ball_x are found
    // assumes paddle_x - ball_x in {-1, 0, 1}

    return paddle_x - ball_x;
}

class program
{
private:
    std::vector<int> intcode; // does this need to be int?
    int iterator = 0;
    int relative_base = 0;
    int find(int, int);
    int valid_index(int);
    std::vector<int> screen_changes;
    arcade_cabinet game;

public:
    program(std::vector<int>);
    std::vector<int> run();
};

program::program(std::vector<int> const source_code)
{
    intcode = source_code;
    intcode.resize(100000);
    std::cout << '\n';
}

std::vector<int> program::run()
{
    for (; iterator < intcode.size();)
    {
        int const opcode = intcode[valid_index(iterator)] % 100;

        switch (opcode) // should be an enum class
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
            //int input;
            //std::cin >> input;
            //intcode[valid_index(find(iterator, 1))] = input;

            this->game.display();
            std::cout << '\n';

            //std::cout << "\x1B[25F";

            intcode[valid_index(find(iterator, 1))] = this->game.next_move();

            iterator += 2;
            break;

        case 4: //output
            this->screen_changes.push_back(intcode[valid_index(find(iterator, 1))]);

            if (this->screen_changes.size() % 3 == 0)
            {
                this->game.update(this->screen_changes);
                screen_changes.clear();
            }

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
            this->game.print_score();

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

    if (mode == 0) // should be an enum
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
