
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
//#include <math.h>
#include <algorithm>
#include <cmath>

std::vector<std::pair<int,int>> edge_list;
std::vector<int> view;

void print() {
    for(int y=0; y<=edge_list.back().second; y++) {
        for(int x=0; x<=edge_list.back().first; x++) {
            if(std::find(edge_list.begin(), edge_list.end(), std::pair<int,int>({x, y})) != edge_list.end()) {
                std::cout << "#";
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}

double calc1(int y2, int y1, int x2, int x1) {
    return double(double(y2 - y1)/double(x2 - x1));
}

double hdr(std::pair<int,int> b, std::pair<int,int> a) {
    return calc1(b.second, a.second, b.first, a.first);
}

int main() {
    std::ifstream read;
    read.open("input.txt");

    int y=0;
    std::string s;
    while(std::getline(read,s)) {
        int x = 0;
        for(char& c : s) {
            if(c == '#') {
                edge_list.push_back({x, y});
                view.push_back(1);
            }
            x++;
        }
        y++;
    }

    read.close();

    for(int i=0; i<edge_list.size(); i++) {
        
        std::vector<double> gradient;
        gradient.reserve(edge_list.size());
        
        std::vector<double> distance;
        gradient.reserve(edge_list.size());

        for(int ix=0; ix<edge_list.size(); ix++) { //O(N^2)
            if(i != ix) {
                gradient.push_back(hdr(edge_list[ix], edge_list[i]));
                //y is in reverse

                /*
                00 10 20 30
                01 11 .. ..
                02 .. .. ..
                */ 

                distance.push_back(1);

            }
        }
    }

    //print();

    return 0;
}
