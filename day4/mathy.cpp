#include <iostream>
#include <stack>
#include <array>
#include <string>
#include <vector>

constexpr int fact(int);
constexpr int factup(int, int);
constexpr int multiset_coeff(int, int);
int remaining(int, int);
int no_doubles_yet(int, int, bool, int);
int calc(bool);
int Part1();
int Part2();

//clang++ -std=c++2a mathy.cpp

int main() {
    std::cout << Part1() << '\n';
    std::cout << Part2();
    std::cout << std::endl;
}

constexpr int fact(int n) {
    int total = 1;
    while(n)
        total *= n--;
    return total;
}

constexpr int factup(int x, int m) {
    int total = 1;
    while(m--) {
        total *= (x+m);
    }
    return total;
}

constexpr auto coeffs = []() {
    std::array<int,7*10> ret{};
    for(int n = 0; n < 7; ++n)
        for(int k = 0; k < 10; ++k)
            ret[n*10+k] = factup(n,k)/fact(k);
    return ret;
}();

constexpr int multiset_coeff(int n, int k) {
    return coeffs[n*10+k];
}

int remaining(int digits_left, int start) {
    /*
    Calculates combinations of valid(non-decrementing) strings of numbers.
    
    How it works:
    We have `9-start` +1's to divide up amongst our remaining digits.
    Which is the same as taking digits_left cuts into a list of that length
    Which turns out to be the same as the multiset coefficient below
    */
    if(start > 9) {
        return digits_left == 0;
    }
    return multiset_coeff(digits_left+1,9-start);
}

int no_doubles_yet(int start, int digits_left, bool exact_double, int max=9) {
    if(digits_left <= 0) {
        return 0;
    }
    int total = 0;
    for(;start <= max; ++start) {
        //Number of combinations when this starts the first double
        total += remaining(digits_left-1,start+exact_double);
        //Next digit increments, find double starting at that point
        total += no_doubles_yet(start+1,digits_left-1,exact_double);
        if(exact_double) {
            //We have three or more same digits in a row
            for(int digits = 3; digits < digits_left; ++digits) {
                total += no_doubles_yet(start+1,digits_left-digits,exact_double);
            }
        }
    }
    return total;
}

int calc(bool exact_double) {
    //Start at 246... -> find all between 246... and 250..., find all between 25.... and 30.... and between 3..... and 7.....
    return no_doubles_yet(6,3,exact_double) + no_doubles_yet(5,4,exact_double) + no_doubles_yet(3,5,exact_double,6);
}

int Part1() {
    return calc(false);
}

int Part2() {
    return calc(true);
}
