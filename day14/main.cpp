#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

struct chemical {
    int quantity;
    std::string name;

    std::string to_string() {
        return std::to_string(this->quantity) + " " + this->name;
    }

    chemical() {}

    chemical(int quantity, std::string name) {
        this->quantity = quantity;
        this->name = name;
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
        std::stringstream ss(line);

        std::vector<chemical> input;

        char next;
        while(next != '=') {
            if(next == ',') {
                next = ' ';
            }

            input.push_back(quantity_name(next, ss));
        }

        this->input = input;

        ss >> next; //>

        this->output = quantity_name(next, ss);
    }

    void print() {
        for(int i=0; i<input.size(); i++) { //input
            std::cout << input[i].to_string();
            if(input.size() > 1 && i < input.size()-1) {
                std::cout << ",";
            }
            std::cout << " ";
        }

        std::cout << "=> " << output.to_string() << std::endl;
    }

private:
    //reading thing using stringstream
    //should only be used to assist constructor
    chemical quantity_name(char &next, std::stringstream &ss) {
        int quantity;
        ss >> quantity; //quantity

        std::string name;

        while (!ss.eof() && next != ',' && next != '=') { //name
            next = ' ';
            ss >> next;
            if (next != ' ' && next != ',' && next != '=') {
                name += next;
            }
        }

        return {quantity, name};
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

    std::string name = "FUEL";
    auto initial = std::find_if(catalogue.begin(), catalogue.end(), [name](reaction r){return r.output.name == name;});
    initial->print();

    name = initial->input[0].name;
    initial = std::find_if(catalogue.begin(), catalogue.end(), [name](reaction r){ return r.output.name == name;});
    initial->print();

    name = initial->input[0].name;
    initial = std::find_if(catalogue.begin(), catalogue.end(), [name](reaction r){ return r.output.name == name;});
    initial->print();

    //this sort of thing

    return 0;
}

/*
for(reaction element : catalogue) {
    element.print();
}
need to use find to find FUEL

reaction first({2, "A"}, {{9, "ORE"}});
first.print();

---

list of reactions - puzzle input

input chemical -> output chemical (quantities)

ORE is input only
While others are only

ORE -> FUEL
*/