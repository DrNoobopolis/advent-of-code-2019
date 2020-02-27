#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

struct chemical {
    long quantity;
    std::string name;

    std::string to_string(long factor) {
        return std::to_string(this->quantity*factor) + " " + this->name;
    }

    chemical() {}

    chemical(long quantity, std::string name) {
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

    void prlong(long factor) {
        for(long i=0; i<input.size(); i++) { //input
            std::cout << input[i].to_string(factor);
            if(input.size() > 1 && i < input.size()-1) {
                std::cout << ",";
            }
            std::cout << " ";
        }

        std::cout << "=> " << output.to_string(factor) << std::endl;
    }

private:
    chemical quantity_name(char &next, std::stringstream &ss) {
        long quantity;
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
    read.open("../input.txt");

    std::string line;

    while(std::getline(read, line)) {
        reaction temp(line);
        catalogue[temp.output.name] = temp;
    }

    read.close();
}

void scale(long &ofct, std::vector<reaction>::iterator init, long const ifct, std::vector<reaction>::iterator temp) {
    while(init->output.quantity*ofct < temp->input[0].quantity*ifct) {
        ofct++;
    }
}

void prlong(std::map<std::string, reaction> catalogue) {
    auto it = catalogue.begin();
    while (it != catalogue.end()) {
        it->second.prlong(1);
        it++;
    }
}

void DFSUtil(long &ORE, double quantity, std::map<std::string, reaction> graph, std::map<std::string, long> &excess, reaction start, std::map<std::string, bool> &visited) {

    double factor;

    if (start.input.size() != 0)
    {
        visited[start.output.name] = true;

        factor = 1;

        while(start.output.quantity*factor < quantity) {
            factor++;
        }

        //start.prlong(factor);

        if(start.output.quantity*factor > quantity) { //need to collect excess
            //std::cout << "   " << start.output.name << " " << start.output.quantity*factor-quantity << std::endl;
            excess[start.output.name] += start.output.quantity*factor-quantity;
        }

        if(start.input.size() == 1 && start.input[0].name == "ORE") {
            //start.prlong(factor);
            ORE += start.input[0].quantity*factor;
        }
    }

    // recur
    for (auto it = graph[start.output.name].input.begin(); it != graph[start.output.name].input.end(); ++it)
    {
        //if (!visited[it->name])
        DFSUtil(ORE, it->quantity*factor, graph, excess, graph[it->name], visited);
    }
}

std::map<std::string, long>::iterator exists(std::map<std::string, long> &excess, std::map<std::string, reaction> graph) {
    auto it = excess.begin();

    for(; it != excess.end(); it++) {
        //.find() method is better as it returns an iterator
        //cannot exist outside of scope of map
        if(graph.find(it->first)->second.output.quantity <= it->second && graph.find(it->first) != graph.end()) {
            //std::cout << graph[it->first].output.quantity << " " << it->second << std::endl;
            return it;
        }
    }

    return excess.end();
}

long refund(std::map<std::string, long> &excess, std::map<std::string, reaction> graph) {
    long ORE = 0;

    while(exists(excess, graph) != excess.end()) {
        long factor = 1;

        auto it = exists(excess, graph);

        while(graph[it->first].output.quantity*factor <= it->second) { //ugly
            factor++;
        }
        factor--;

        it->second -= graph[it->first].output.quantity*factor;

        for(auto element : graph[it->first].input) {
            excess[element.name] += element.quantity*factor;
        }
    }

    return excess["ORE"];
}

void DFS(std::map<std::string, reaction> graph) {
    // mark all the vertices as not visited
    std::map<std::string, bool> visited;
    for (auto it = graph.begin(); it != graph.end(); it++)
        visited[it->first] = false;

    // collect excess and convert back to ORE where possible
    std::map<std::string, long> excess;
    for (auto it = graph.begin(); it != graph.end(); it++)
        visited[it->first] = 0;

    long ORE = 0;

    // call the recursive helper function
    DFSUtil(ORE, 1, graph, excess, graph["FUEL"], visited);

    //std::cout << std::endl;

    long savings = refund(excess, graph);

    std::cout << ORE - savings << std::endl;
}

/*
tree search
    depth first search
    breadth first search

tree traversal
    depth first traversals
        inorder (left, root, right)
        preorder (root, left, right)
        postorder (left, right, root)
    breadth first traversal
*/

int main() {
    std::map<std::string, reaction> graph;
    read(graph);

    DFS(graph);

    //prlong(catalogue);

    return 0;
}
