
#include <iostream>
#include <vector>

#include "intcode.hpp"

// does not stop it?
// how can we do an unsafe exit?
// write a testing module using constexpr and static assert
// to do
// not safe should throw an exception?

int main()
{
    std::vector<int> source_code = {104, 100, 99};

    program single(source_code);

    // &source_code[0] == NULL

    std::vector<int> output;
    single.run(output);

    for (auto e : output)
        std::cout << e << '\n';

    static_assert(10 == 10, "");

    //

    // x_position, y_position, tile_id

    /*
    int max_x = 0, max_y = 0, counter = 0;

    for (auto element : pinball) //what is this about?
    {
        if (counter == 0)
        {
            if (element > max_x)
            {
                max_x = element;
            }
        }
        else if (counter == 1)
        {
            if (element > max_y)
            {
                max_y = element;
            }
        }
        counter++;
        if (counter == 3)
        {
            counter = 0;
        }
    }

    std::vector<std::vector<int>> screen(max_y);
    std::fill(screen.begin(), screen.end(), std::vector<int>(max_x));

    int ans = 0; // what is this calculating?

    counter = 0;
    for (auto element : pinball)
    {
        int x, y;

        if (counter == 0)
        {
            x = element;
        }
        else if (counter == 1)
        {
            y = element;
        }
        else if (counter == 2)
        {
            screen[y][x] = element;

            if (element == 2)
            {
                ans++;
            }
        }
        counter++;
        if (counter == 3)
        {
            counter = 0;
        }
    }

    for (int yi = 0; yi < max_y; yi++)
    {
        for (int xi = 0; xi < max_x; xi++)
        {
            std::cout << screen[yi][xi] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << ans << std::endl;
    */
}
