#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct chemical {
    int quantity;
    std::string id;

    std::string to_string() {
        return std::to_string(this->quantity) + " " + this->id;
    }

    chemical() {}

    chemical(int quantity, std::string id) {
        this->quantity = quantity;
        this->id = id;
    }
};

struct reaction {
    chemical output;
    std::vector<chemical> input;

    reaction() {}

    reaction(chemical output, std::vector<chemical> input) {
        this->output = output;
        this->input = input;
    }

    void print() {
        for(chemical element : input) {
            std::cout << element.to_string() << " ";
        }

        std::cout << "=> " << output.to_string() << std::endl;
    }
};

int main() {
    std::ifstream read;
    read.open("input.txt");

    std::cout << "good() = " << read.good() << std::endl;
    std::cout << "eof() = " << read.eof() << std::endl;
    std::cout << "fail() = " << read.fail() << std::endl;
    std::cout << "bad() = " << read.bad() << std::endl;

    /*
    std::string line;
    while(std::getline(read, line)) {
        std::cout << line << std::endl;
    }
    */

    read.close();

    std::vector<std::string> container = {
        "9 ORE => 2 A",
        "8 ORE => 3 B",
        "7 ORE => 5 C",
        "3 A, 4 B => 1 AB",
        "5 B, 7 C => 1 BC",
        "4 C, 1 A => 1 CA",
        "7 A, 1 E => 1 FUEL"
    };

    reaction first({2, "A"}, {{9, "ORE"}});
    first.print();

    return 0;
}

//std::vector<chemical> input = {{1, "a"}};
//input.push_back({1, "a"});

/*
list of reactions - puzzle input

input chemical -> output chemical (quantities)

ORE is input only
While others are only

ORE -> FUEL
*/