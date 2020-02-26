#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

struct chemical {
    int quantity;
    std::string name;

    std::string to_string(int factor) {
        return std::to_string(this->quantity*factor) + " " + this->name;
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

    void print(int factor) {
        for(int i=0; i<input.size(); i++) { //input
            std::cout << input[i].to_string(factor);
            if(input.size() > 1 && i < input.size()-1) {
                std::cout << ",";
            }
            std::cout << " ";
        }

        std::cout << "=> " << output.to_string(factor) << std::endl;
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

void scale(int &ofct, std::vector<reaction>::iterator init, int const ifct, std::vector<reaction>::iterator temp) {
    while(init->output.quantity*ofct < temp->input[0].quantity*ifct) {
        ofct++;
    }
    //return ofct;
}

/*
2 AB, 3 BC, 4 CA => 1 FUEL
    3 A, 4 B => 1 AB
        9 ORE => 2 A

    5 B, 7 C => 1 BC
        8 ORE => 3 B

    4 C, 1 A => 1 CA
        7 ORE => 5 C
*/

/*
2 AB, 3 BC, 4 CA => 1 FUEL
    3 A, 4 B => 1 AB
        9 ORE => 2 A
        8 ORE => 3 B
*/

void tree(int counter, std::vector<reaction> &catalogue, std::vector<reaction>::iterator old) {
    auto crnt = std::find_if(catalogue.begin(), catalogue.end(), [old, counter](reaction r){return r.output.name == old->input[counter].name;});

    old->print(1);
    crnt->print(1);
    //std::cout << counter << std::endl;
    std::cout << std::endl;

    //int factor = 1;

    if(crnt->input.size() == 1 && crnt->input[counter].name == "ORE") {
        return;
    }
    else {
        tree(0, catalogue, crnt);
    }

    if(counter < old->input.size()-1) {
        counter++;
        tree(counter, catalogue, crnt);
    }

    return;
}

int main() {
    std::vector<reaction> catalogue;
    read(catalogue);
    int counter = 0;

    auto init = std::find_if(catalogue.begin(), catalogue.end(), [](reaction r){return r.output.name == "FUEL";});
    tree(0, catalogue, init);

    /*
    std::string name = "FUEL";
    auto crnt = std::find_if(catalogue.begin(), catalogue.end(), [name](reaction r){return r.output.name == name;});
    crnt->print(1);

    auto old = crnt;
    name = crnt->input[0].name;
    crnt = std::find_if(catalogue.begin(), catalogue.end(), [name](reaction r){ return r.output.name == name;});

    int ifct = 1;
    int ofct = 1;
    scale(ifct, crnt, ofct, old);
    crnt->print(ifct);

    old = crnt;
    name = crnt->input[0].name;
    crnt = std::find_if(catalogue.begin(), catalogue.end(), [name](reaction r){ return r.output.name == name;});

    ofct = ifct;
    ifct = 1;
    scale(ifct, crnt, ofct, old);
    crnt->print(ifct);

    //Pre Order Traversal: Root, Left, Right.
    */

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
