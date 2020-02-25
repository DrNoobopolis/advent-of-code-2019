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

    reaction(std::string line) {
        //stringstream
        //read in each bit

        //checkpoint here
    }

    void print() {
        for(chemical element : input) {
            std::cout << element.to_string() << " ";
        }

        std::cout << "=> " << output.to_string() << std::endl;
    }
};

void diagnose(std::ifstream &read) {
    std::cout << "good() = " << read.good() << std::endl;
    std::cout << "eof() = " << read.eof() << std::endl;
    std::cout << "fail() = " << read.fail() << std::endl; //cannot find file!
    std::cout << "bad() = " << read.bad() << std::endl;
}

void locate() {
    std::ofstream write;
    write.open("where.txt");
    write << "example text";
    write.close();
}

void read(std::vector<reaction> &catalogue) {
    std::ifstream read;
    read.open("../input.txt");

    std::string line;
    while(std::getline(read, line)) {
        catalogue.push_back(line);
    }

    read.close();
}

int main() {
    std::vector<reaction> catalogue;
    read(catalogue);

    //

    //reaction first({2, "A"}, {{9, "ORE"}});
    //first.print();

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