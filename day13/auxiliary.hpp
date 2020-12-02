
#include <vector>
#include <fstream>
#include <string>

std::vector<int> read(std::string const file_name)
{
    std::ifstream read;

    read.open(file_name); // open file stream

    std::vector<int> intcode_source;

    while (!read.eof())
    {
        int useful;
        char discard;

        read >> useful;                   // read intcode
        intcode_source.push_back(useful); // store

        read >> discard; // remove separating commas (', ')
    }
    read.close(); // close file stream

    return intcode_source;
}
