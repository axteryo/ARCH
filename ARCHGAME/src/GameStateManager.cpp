#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
    system_game_state = SYSTEM_IN_MAIN_MENU;
    level_game_state = LEVEL_LOADING;
    debug_state = DEBUG_ON;
}

GameStateManager::~GameStateManager()
{
    //dtor
}
