#include <iostream>

bool offset(int); //incorrect
bool simple(int);

int main() {

    //int i=100000; //0 //387638

    for(int i=100000; i<919123+1; i++) {
        if(offset(i) != simple(i)) {
            std::cout << i << std::endl;
        }
    }

    return 0;
}

bool offset(int input) {
    int current = input*10;
    bool doublef = false; 

    while(input > 0) {
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

bool simple(int input) {
    int current = input;
    bool doublef = false; 

    while(current > 0) {
        if(current%10 < current/10%10) {
            return false;
        }
        
        if(current%10 == current/10%10) {
            doublef = true;
        } 

        current /= 10;
    }

    if(doublef) {
        return true;
    }
    else {
        return false;
    }
}
