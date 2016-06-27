#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "ArchGame.h"


using namespace std;



int main()
{
    ArchGame* game = new ArchGame;
    game->start();
    return 0;
}
