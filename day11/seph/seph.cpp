#include <vector>
#include <tuple>
#include <iostream>
#include <deque>
#include <map>
#include <unordered_map>
#include <cstdint>
#include <complex>

namespace IntCode {
    struct Storage {
        std::vector<std::int64_t> main;
        std::map<std::int64_t,std::int64_t> extra{};
        std::int64_t& operator[](std::size_t loc) {
            return loc < main.size() ? main[loc] : extra[loc];
        }
    };

    struct ins {
        std::int64_t op;
        std::array<std::int64_t,3> modes;
    };

    ins decode(std::int64_t instruction) {
        return {instruction % 100, {instruction / 100 % 10, instruction / 1000 % 10, instruction / 10000 % 10}};
    }

    int iter1 = 0;

    class Program {
        public:
            Program(Storage s) : prog(s) {};
            struct RunResult {
                std::vector<std::int64_t> output;
                bool input_requested;
            };
            RunResult run(std::deque<std::int64_t> input) {
                std::array sizes = {0,4,4,2,2,3,3,4,4,2};
                std::vector<std::int64_t> output;
                while(prog[loc] != 99) {
                    iter1++;

                    auto [op,modes] = decode(prog[loc]);
                    auto fetch = [&,modes=modes](std::int64_t num) -> std::int64_t& {
                        auto& address = prog[loc+num];
                        switch(modes[num-1]) {
                            case 0:
                                return prog[address];
                            case 1:
                                return address;
                            case 2:
                                return prog[address+relative_base];
                        }
                        return modes[num-1] ? prog[loc+num] : prog[prog[loc + num]];
                    };
                    switch(op) {
                        case 1:
                            fetch(3) = fetch(1) + fetch(2);
                            break;
                        case 2:
                            fetch(3) = fetch(1) * fetch(2);
                            break;
                        case 3:
                            if(input.empty()) return {output,true};
                            fetch(1) = input.front();
                            input.pop_front();
                            break;
                        case 4:
                            output.push_back(fetch(1));
                            break;
                        case 5:
                            if(fetch(1)) loc = fetch(2) - 3;
                            break;
                        case 6:
                            if(not fetch(1)) loc = fetch(2) - 3;
                            break;
                        case 7:
                            fetch(3) = fetch(1) < fetch(2);
                            break;
                        case 8:
                            fetch(3) = fetch(1) == fetch(2);
                            break;
                        case 9:
                            relative_base += fetch(1);
                            break;
                    }
                    loc += sizes[op];
                }
                return {output,false};
            }
        private:
            Storage prog;
            std::size_t loc = 0;
            std::int64_t relative_base = 0;
    };

    template<typename InputFunc, typename OutputFunc>
    void run(Storage prog, InputFunc&& input, OutputFunc&& out) {
        Program p(std::move(prog));
        Program::RunResult res = p.run({});
        for(auto o : res.output) out(o);
        while(res.input_requested) {
            res = p.run({input()});
            for(auto o : res.output) out(o);
        }
    }

    template<int N, typename F>
    auto output_every(F output) {
        return [output, a = std::array<std::int64_t,N>{},current=0](std::int64_t in) mutable {
            a[current++] = in;
            if(current == N) {
                std::apply(output,a);
                current = 0;
            }
        };
    }
}

struct Robot {
    IntCode::Storage program;
    using pos = std::complex<std::int64_t>;
    struct Cmp {
        bool operator()(pos a, pos b) const {
            if(a.real() == b.real()) return a.imag() < b.imag();
            return a.real() < b.real();
        }
    };
    pos position{0,0};
    pos orientation{0,1};
    std::map<pos,int,Cmp> painted{};
    auto find(pos p) {
        if(painted.contains(p)) return painted[p];
        return 0;
    }
    void run() {
        IntCode::run(program,
            [this](){return find(position);},
            IntCode::output_every<2>([this](auto color, auto turn) {
                painted[position] = color;
                orientation *= (turn == 0 ? pos(0,1) : pos(0,-1));
                position += orientation;
            }));
    }
    void draw() {
        auto minmax = [this](auto&& key) {
            auto [min,max] = std::minmax_element(painted.begin(),painted.end(),[&key](auto a, auto b) {return key(a.first) < key(b.first);});
            return std::pair{key(min->first),key(max->first)};
        };
        auto [min_x,max_x] = minmax([](auto c){return c.real();});
        auto [min_y, max_y] = minmax([](auto c){return c.imag();});
        for(int y = max_y; y >= min_y; --y) {
            for(int x = min_x; x <= max_x; ++x) {
                std::cout << (find({x,y}) ? 'X' : ' ');
            }
            std::cout << '\n';
        }
    }
};

int main() {
    IntCode::Storage program = {{3,8,1005,8,326,1106,0,11,0,0,0,104,1,104,0,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,1,10,4,10,1001,8,0,29,2,1003,17,10,1006,0,22,2,106,5,10,1006,0,87,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,1,10,4,10,1001,8,0,65,2,7,20,10,2,9,17,10,2,6,16,10,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,0,10,4,10,101,0,8,99,1006,0,69,1006,0,40,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,1,10,4,10,101,0,8,127,1006,0,51,2,102,17,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,1,8,10,4,10,1002,8,1,155,1006,0,42,3,8,1002,8,-1,10,101,1,10,10,4,10,108,0,8,10,4,10,101,0,8,180,1,106,4,10,2,1103,0,10,1006,0,14,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1001,8,0,213,1,1009,0,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,0,8,10,4,10,1002,8,1,239,1006,0,5,2,108,5,10,2,1104,7,10,3,8,102,-1,8,10,101,1,10,10,4,10,108,0,8,10,4,10,102,1,8,272,2,1104,12,10,1,1109,10,10,3,8,102,-1,8,10,1001,10,1,10,4,10,108,1,8,10,4,10,102,1,8,302,1006,0,35,101,1,9,9,1007,9,1095,10,1005,10,15,99,109,648,104,0,104,1,21102,937268449940,1,1,21102,1,343,0,1105,1,447,21101,387365315480,0,1,21102,1,354,0,1105,1,447,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,21101,0,29220891795,1,21102,1,401,0,1106,0,447,21101,0,248075283623,1,21102,412,1,0,1105,1,447,3,10,104,0,104,0,3,10,104,0,104,0,21101,0,984353760012,1,21102,1,435,0,1105,1,447,21102,1,718078227200,1,21102,1,446,0,1105,1,447,99,109,2,21202,-1,1,1,21102,40,1,2,21101,0,478,3,21101,468,0,0,1106,0,511,109,-2,2106,0,0,0,1,0,0,1,109,2,3,10,204,-1,1001,473,474,489,4,0,1001,473,1,473,108,4,473,10,1006,10,505,1102,1,0,473,109,-2,2105,1,0,0,109,4,1202,-1,1,510,1207,-3,0,10,1006,10,528,21102,1,0,-3,22102,1,-3,1,22101,0,-2,2,21101,0,1,3,21102,1,547,0,1105,1,552,109,-4,2105,1,0,109,5,1207,-3,1,10,1006,10,575,2207,-4,-2,10,1006,10,575,21202,-4,1,-4,1105,1,643,21202,-4,1,1,21201,-3,-1,2,21202,-2,2,3,21102,1,594,0,1106,0,552,22102,1,1,-4,21101,1,0,-1,2207,-4,-2,10,1006,10,613,21101,0,0,-1,22202,-2,-1,-2,2107,0,-3,10,1006,10,635,22101,0,-1,1,21101,0,635,0,106,0,510,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2105,1,0
}};
    {
        Robot painter{program};
        painter.run();
        std::cout << "Part 1: " << painter.painted.size() << '\n';
    }
    {
        Robot painter{program};
        painter.painted[{0,0}] = 1;
        painter.run();
        std::cout << "Part 2:\n";
        painter.draw();
    }

    std::cout << iter1 << std::endl;
}
