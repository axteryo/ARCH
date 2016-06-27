#include <iostream>
#include <math.h>

using namespace std;

int maini()
{
    int sum = 0;

    for(int i = 0; i<1000; i = i+1)
    {

        if(i%3 == 0 || i%5 == 0)
        {
            sum +=i;

        }
    }
    std::cout << sum << std::endl;
    return 0;
}
