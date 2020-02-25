#include <iostream>

bool offset(int);

int main() {

    if(offset(123456)) {
        std::cout << "fk" << std::endl;
    }
         
    return 0;
}

bool offset(int input) {
    int current = input*10;
    bool doublef = false; 

    while(input > 0) {
        std::cout << current/10%10 << " " << current/100%10 << std::endl; 

        if(current/10%10 < current/100%10) {
            return false;
        }
        
        if(current/10%10 == current/100%10) {
            doublef = true;
        } 

        current /= 10;
        input /= 10;
    }

    if(doublef) {
        return true;
    }
    else {
        return false;
    }
}
