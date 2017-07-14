#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
    system_game_state = SYSTEM_START_LEVEL;
    level_game_state = LEVEL_LOADING;
    debug_state = DEBUG_OFF;
}

GameStateManager::~GameStateManager()
{
    //dtor
}
