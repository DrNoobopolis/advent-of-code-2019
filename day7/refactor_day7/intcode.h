
int batch(std::vector<int>);

void printArray(std::vector<int> const &);
void printVector(std::vector<int> const &);

struct program {
    private:
        std::vector<int> intcode;
        bool first = true;
        std::vector<int> read();
        int find(std::vector<int> const &, int, int);

    public:   
        int phase = 0;
        int iterator = 0;
        int get_duration();
        program(int);
        program();
        void run(int &);
};

const int duration = program().get_duration();
