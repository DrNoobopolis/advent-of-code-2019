
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#include <math.h>
//#include <algorithm>

int main() {

    std::vector<std::vector<int>> storage;

    std::ifstream read;
    read.open("input.txt");

    std::string s;
    while(std::getline(read,s)) {
        std::stringstream ss(s);
        
        std::vector<int> row;

        char c;
        while(!ss.eof()) {
            ss >> c;

            if(c == '.') {
                row.push_back(0);
            }
            else if(c == '#') {
                row.push_back(1);
            }
            else {
                std::cerr << "error" << std::endl;
            }
        }

        storage.push_back(row);
    }

    read.close();

    for(auto row_temp : storage) {
        for(auto column_temp : row_temp) {
            if(column_temp == 0) {
                std::cout << '.';
            }
            else {
                std::cout << column_temp;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}

    /*
    . empty
    # asteroid

    X, Y
    distance from the top edge (X)
    distance from the left edge (Y) 

    0,0 0,1 0,2
    1,0 
    2,0       

    */
