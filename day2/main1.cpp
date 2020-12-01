
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::string input;

    std::ifstream read;
    read.open("input.txt");
    read >> input;
    read.close();

    std::vector<int> container;

    int temp = 0;

    for (auto i = 0; i < input.size(); i++)
    {
        //

        if (input[i] == ',')
        {
            container.push_back(temp);
            temp = 0;
            continue;
        }

        temp *= 10;
        temp += input[i] - 48;
    }
    container.push_back(temp);

    int noun, verb;

    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {

            std::vector<int> clone = container;

            clone[1] = x;
            clone[2] = y;

            for (int i = 0; i < clone.size(); i++)
            {
                //std::cout << clone[i] << std::endl;

                switch (clone[i])
                {
                case 1:
                    clone[clone[i + 3]] = clone[clone[i + 1]] + clone[clone[i + 2]];
                    i += 3;
                    break;

                case 2:
                    clone[clone[i + 3]] = clone[clone[i + 1]] * clone[clone[i + 2]];
                    i += 3;
                    break;

                case 99:
                    i = clone.size();
                    break;

                default:
                    std::cerr << "error" << std::endl;
                    break;
                }

                //
            }

            if (clone[0] == 19690720)
            {
                noun = x;
                verb = y;
            }
        }
    }

    std::cout << 100 * noun + verb << std::endl;

    return 0;
}
