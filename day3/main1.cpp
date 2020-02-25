
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <bits/stdc++.h> 

void print(std::vector<std::vector<char>>);
int bigger(int, int);
bool isline(char);
std::vector<std::vector<char>> join(std::vector<std::vector<char>> &, std::vector<std::vector<char>> &);
std::pair<int,int> locate(std::vector<std::vector<char>>);
void process(std::vector<std::vector<char>> &, std::vector<std::pair<char,int>> &);
void size(std::vector<std::vector<char>> &, std::vector<std::pair<char,int>> &);
void distance(std::vector<std::vector<char>>);
void trace(std::vector<int> &, std::vector<std::pair<int,int>> &, std::vector<std::vector<char>> &, std::vector<std::pair<char,int>> &);
void minimum(std::vector<int>, std::vector<std::pair<int,int>>, std::vector<int>, std::vector<std::pair<int,int>>);

int main() {
    //auto start = std::chrono::steady_clock::now();

    std::vector<std::vector<char>> field1 = {{'.', '.', '.'}, {'.', 'o', '.'}, {'.', '.', '.'}};

    std::vector<std::pair<char,int>> set1;
    std::vector<std::pair<char,int>> set2;

    {
        // htop

        // ./a.out | cat > save.txt

        std::ifstream read;

        read.open("input2.txt");
    
        char temp1;
        int temp2;

        std::string input;
        read >> input;
        std::stringstream ss(input);    
        
        while(!ss.eof()) {
            ss >> temp1;
            ss >> temp2;
            set1.push_back({temp1, temp2});
            ss >> temp1;
        }

        read >> input;
        std::stringstream ss1(input);    

        while(!ss1.eof()) {
            ss1 >> temp1;
            ss1 >> temp2;
            set2.push_back({temp1, temp2});
            ss1 >> temp1;
        }

        read.close();
    }

    size(field1, set1);
    size(field1, set2);

    std::vector<std::vector<char>> field2 = field1;
    
    process(field1, set1);
    process(field2, set2);

    std::vector<std::vector<char>> field3 = join(field1, field2);

    print(field1);
    std::cout << std::endl;
    print(field2);
    std::cout << std::endl;
    print(field3);
    std::cout << std::endl;

    std::vector<int> dist1;
    std::vector<std::pair<int,int>> cross1;
    trace(dist1, cross1, field3, set1); 

    std::vector<int> dist2;
    std::vector<std::pair<int,int>> cross2;
    trace(dist2, cross2, field3, set2);

    //

    /*
    for(int i=0; i<dist1.size(); i++) {
        std::cout << "cross1[" << cross1[i].first << ", " << cross1[i].second << "], " << dist1[i] << std::endl; 
    }
    std::cout << std::endl;
    for(int i=0; i<dist2.size(); i++) {
        std::cout << "cross2[" << cross2[i].first << ", " << cross2[i].second << "], " << dist2[i] << std::endl; 
    }
    std::cout << std::endl;
    */

    std::cout << "manhattan distance: " << std::flush;
    distance(field3);

    std::cout << std::endl;

    std::cout << "minimum steps: " << std::flush;
    minimum(dist1, cross1, dist2, cross2);
    
    //auto end = std::chrono::steady_clock::now();    
    //double duration = std::chrono::duration<double>(end-start).count();

    //std::cout << std::endl;
    //std::cout << std::fixed << duration << std::endl;  

    return 0;
}
    
void minimum(std::vector<int> dist1, std::vector<std::pair<int,int>> cross1, std::vector<int> dist2, std::vector<std::pair<int,int>> cross2) {
    //y cross1 dist1
    //x cross2 dist2

    int minimum = 0;

    for(int y=0; y<dist1.size(); y++) {  
        for(int x=0; x<dist2.size(); x++) {
            if(cross1[y].first == cross2[x].first && cross1[y].second == cross2[x].second) {
                if(minimum == 0) {
                    minimum = dist1[y]+dist2[x];
                }

                if(dist1[y]+dist2[x] < minimum) {
                    minimum = dist1[y]+dist2[x];
                }
            }
        }
    }

    std::cout << minimum << std::endl;
    return;
}

void trace(std::vector<int> &dist, std::vector<std::pair<int,int>> &cross, std::vector<std::vector<char>> &field, std::vector<std::pair<char,int>> &set) {
    std::pair<int,int> position = locate(field);

    int steps = 0;

    for(int z=0; z<set.size(); z++) {        
        auto element = set[z];
        
        switch(element.first) {
            case 'R' :
                for(int i=0; i<element.second; i++) {         
                    position.first += 1;
                    
                    steps++;

                    if(field[position.second][position.first] == 'X') {
                        dist.push_back(steps);
                        cross.push_back({position.first,position.second});
                    }
                }
                break;
            
            case 'L' :
                for(int i=0; i<element.second; i++) {         
                    position.first -= 1;

                    steps++;

                    if(field[position.second][position.first] == 'X') {
                        dist.push_back(steps);
                        cross.push_back({position.first,position.second});
                    }
                }
                break;
                
            case 'U' :
                for(int i=0; i<element.second; i++) {
                    position.second -= 1;

                    steps++;

                    if(field[position.second][position.first] == 'X') {
                        dist.push_back(steps);
                        cross.push_back({position.first,position.second});
                    }
                }
                break;
                
            case 'D' :
                for(int i=0; i<element.second; i++) {
                    position.second += 1;

                    steps++;

                    if(field[position.second][position.first] == 'X') {
                        dist.push_back(steps);
                        cross.push_back({position.first,position.second});
                    }
                }
                break;
        }
    }

    //
}

void distance(std::vector<std::vector<char>> field) {
    std::pair<int,int> position = locate(field);
    std::pair<int,int> temp = {0,0};
    int minimum = 0;

    for(int y=0; y<field.size(); y++) {
        for(int x=0; x<field[0].size(); x++) {

            if(field[y][x] == 'X') {    
                if(x > position.first) {
                    temp.first = x-position.first;
                }
                else {
                    temp.first = position.first-x;
                }

                if(y > position.second) {
                    temp.second = y-position.second;
                }
                else {
                    temp.second = position.second-y;
                }

                if(minimum == 0) {
                    minimum = temp.first+temp.second;
                }
                else {
                    if(minimum > temp.first+temp.second) {
                        minimum = temp.first+temp.second;
                    }
                }  

            }

        }
    }

    std::cout << minimum << std::endl;
}

std::pair<int,int> locate(std::vector<std::vector<char>> input) {
    for(int y=0; y<input.size(); y++) {
        for(int x=0; x<input[0].size(); x++) {
            if(input[y][x] == 'o') {
                return {x, y};
            }
        }
    } 
    
    return {-1, -1};
}

void print(std::vector<std::vector<char>> input) {
    for(auto row : input) {
        for(auto column : row) {
            std::cout << column;
        }
        std::cout << std::endl;
    }
}

int bigger(int left, int right) {
    if(right > left) {
        return right;    
    }

    return left;
}

bool isline(char input) {
    if(input == '|' || input == '-' || input == '+') {
        return true;
    }
    return false;
}

std::vector<std::vector<char>> join(std::vector<std::vector<char>> &field1, std::vector<std::vector<char>> &field2) {
    
    std::vector<std::vector<char>> output = field1;

    for(int y=0; y<output.size(); y++) {
        for(int x=0; x<output[0].size(); x++) {
            char temp1 = field1[y][x];
            char temp2 = field2[y][x];
            
            if(isline(temp1) && isline(temp2)) {
                output[y][x] = 'X';
            }
            else {
                if(isline(temp1)) {
                    output[y][x] = field1[y][x];
                }
                if(isline(temp2)) {
                    output[y][x] = field2[y][x];
                }
            } 
        }
    }

    return output;
}

void process(std::vector<std::vector<char>> &field, std::vector<std::pair<char,int>> &set) {
    std::pair<int,int> position = locate(field);

    for(int z=0; z<set.size(); z++) {
        auto element = set[z];

        switch(element.first) {
            case 'R' :
                for(int i=0; i<element.second; i++) {         
                    position.first += 1;
                    
                    if(i == element.second-1 && z < set.size()-1) {
                        field[position.second][position.first] = '+';
                    }
                    else {
                        field[position.second][position.first] = '-';
                    }
                }
                break;
            
            case 'L' :
                for(int i=0; i<element.second; i++) {         
                    position.first -= 1;
                
                    if(i == element.second-1 && z < set.size()-1) {
                        field[position.second][position.first] = '+';
                    }
                    else {
                        field[position.second][position.first] = '-';
                    } 
                }
                break;
                
            case 'U' :
                for(int i=0; i<element.second; i++) {
                    position.second -= 1;
                
                    if(i == element.second-1 && z < set.size()-1) {
                        field[position.second][position.first] = '+';
                    }
                    else {
                        field[position.second][position.first] = '|';
                    }
                }
                break;
                
            case 'D' :
                for(int i=0; i<element.second; i++) {
                    position.second += 1;
                
                    if(i == element.second-1 && z < set.size()-1) {
                        field[position.second][position.first] = '+';
                    }
                    else {
                        field[position.second][position.first] = '|';
                    }
                }
                break;
        }
    }
}

void size(std::vector<std::vector<char>> &field, std::vector<std::pair<char,int>> &set) {
    std::pair<int,int> position = locate(field);

    for(auto element : set) {
        switch(element.first) {
            case 'R' :
                for(int i=0; i<element.second; i++) {         
                    position.first += 1;
                
                    if(position.first == field[0].size()-1) {
                        for(auto &row : field) {
                            row.push_back('.');
                        } 
                    } 

                }
                break;
            
            case 'L' :
                for(int i=0; i<element.second; i++) {         
                    position.first -= 1;
                
                    if(position.first == 0) {
                        for(auto &row : field) {
                            row.insert(row.begin(), '.');
                        } 
                        position.first += 1;
                    } 

                }
                break;
                
            case 'U' :
                for(int i=0; i<element.second; i++) {
                    position.second -= 1;

                    if(position.second == 0) {
                        std::vector<char> row;
                        for(int x=0; x<field[0].size(); x++) {
                            row.push_back('.');
                        }
                        field.insert(field.begin(), row);
                        position.second += 1;
                    }
                    
                }
                break;
                
            case 'D' :
                for(int i=0; i<element.second; i++) {
                    position.second += 1;
                
                    if(position.second == field.size()-1) {
                        std::vector<char> row;
                        for(int x=0; x<field[0].size(); x++) {
                            row.push_back('.');
                        }
                        field.push_back(row);
                    }
                    
                }
                break;
        }
    }
}

/*
for(int i=0; i<dist1.size(); i++) {
    std::cout << "[" << cross1[i].first << ", " << cross1[i].second << "] " << dist1[i] << std::endl;
}
std::cout << std::endl;

for(int i=0; i<dist2.size(); i++) {
    std::cout << "[" << cross2[i].first << ", " << cross2[i].second << "] " << dist2[i] << std::endl;
}
*/
