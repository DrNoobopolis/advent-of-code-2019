
void printArray(std::vector<long> const &);
void printVector(std::vector<long> const &);

struct program {
    private:
        std::vector<long> intcode;
        bool first = true;
        std::vector<long> read();
        long find(std::vector<long> const &, long, long);
        long iterator = 0;        
        long relative_base = 0;

    public:   
        long get_duration();
        program();
        void run();
};

const long duration = program().get_duration();
