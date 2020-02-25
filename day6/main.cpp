#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

std::pair<std::string, std::string> split(std::string row) {

    ss.str(row); 

    if(row != "") {
        pass.clear();

        for(char element : ss.str()) {
            if(element == ')') { 
                output.insert(pass);
                pass.clear();
            }
            else {
                pass += element;
            }
        }
            
        output.push_back(pass);
    }

    return ;
}

std::map<std::string, std::vector<std::string>> read(std::string const & input) {
    std::map<std::string, std::vector<std::string>> output;

    std::ifstream read;
    read.open(input);

    std::stringstream ss;
    std::string row;
    std::string pass;

    while(!read.eof()) {
        row.clear();

        read >> row;

        split()
    }

    return output;
}

void print(std::vector<std::string> const & input) {
    int i = 0;
    
    for (std::string element : input) {
        std::cout << element << " "; 
        
        if(i % 2 == 1) {
            std::cout << std::endl;
        }

        i++;
    }
}

int main() {  

    std::map<std::string, std::vector<std::string>> edge_list = read("data.txt");

    //print(edge);

    //std::cout << "" << std::endl;

    return 0;
}
