#include <iostream>

#include "Game.h"
using namespace std;


int main()
{
    Game* arch = new Game;

    arch->start();
    delete arch;

    return 0;
}
