#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

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

void read(std::map<std::string, reaction> &catalogue) {
    std::ifstream read;
    read.open("../input2.txt");

    std::string line;

    while(std::getline(read, line)) {
        reaction temp(line);
        catalogue[temp.output.name] = temp;
    }

    read.close();
}

void scale(int &ofct, std::vector<reaction>::iterator init, int const ifct, std::vector<reaction>::iterator temp) {
    while(init->output.quantity*ofct < temp->input[0].quantity*ifct) {
        ofct++;
    }
}

void print(std::map<std::string, reaction> catalogue) {
    auto it = catalogue.begin();
    while (it != catalogue.end()) {
        it->second.print(1);
        it++;
    }
}

int main() {
    std::map<std::string, reaction> catalogue;
    read(catalogue);

    print(catalogue);

    //catalogue["A"].print(1);


    int counter = 0;

    //auto init = std::find_if(catalogue.begin(), catalogue.end(), [](reaction r){return r.output.name == "FUEL";});
    //tree(0, catalogue, init);

    return 0;
}
