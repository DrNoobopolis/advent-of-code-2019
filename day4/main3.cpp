#include <iostream>

bool valid(int, bool);

int main() {
    int output=0;

    for(int i=387638; i<919123+1; i++) {
        if( valid(i, false) ) {
            output++;
        }
    }

    std::cout << output << std::endl;

    return 0;
}

bool valid(int input, bool part2) {
    int current = input*10; //offset, because of a requirement of "true double"
    bool doublef = false; 

    while(input > 0) {
        if(current/10%10 < current/100%10) { //next > current
            return false;
        }
        
        if(part2) {
            if(current%10 != current/10%10 && current/10%10 == current/100%10 && current/100%10 != current/1000%10) { //true double
                doublef = true;
            }
        }
        else {
            if(current/10%10 == current/100%10) {
                doublef = true;
            } 
        }

        current /= 10; //next digit

        input /= 10; //length, using current allowed another cycle to occur after initializing current = input*10 
    }

    if(doublef) {
        return true;
    }
    else {
        return false;
    }

}
