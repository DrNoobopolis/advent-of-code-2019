
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::string input;

    std::ifstream read;
    read.open("input.txt");
    read >> input;
    read.close();

    std::vector<int> container;

    int temp = 0;

    for(auto i=0; i<input.size(); i++) { 
        //

        if(input[i] == ',') {
            container.push_back(temp);
            temp = 0;
            continue;
        }

        temp *= 10;
        temp += input[i]-48;
    }
    container.push_back(temp);

    for(int i=0; i<container.size(); i++) {
        //std::cout << container[i] << std::endl;
        
        switch (container[i]) {
            case 1 :
                container[container[i+3]] = container[container[i+1]] + container[container[i+2]];
                i += 3;
                break;
            
            case 2 :
                container[container[i+3]] = container[container[i+1]] * container[container[i+2]];
                i += 3;
                break;

            case 99 :
                i = container.size();
                break;

            default:
                std::cerr << "error" << std::endl;
                break;
            }
        
        //
    }

    std::cout << container[0] << std::endl;

    for(auto element : container) {
        //std::cout << element << std::endl;
    }

    return 0;
}

/*
"1202 program alarm" 

container[1] = 12
container[2] = 2

what value is left at position 0 after the program halts?
*/
