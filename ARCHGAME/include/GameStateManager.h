#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H


class GameStateManager
{
    public:
        GameStateManager();
        virtual ~GameStateManager();

         enum SystemGameState
        {
            SYSTEM_START_MAIN_MENU,
            SYSTEM_IN_MAIN_MENU,
            SYSTEM_START_LEVEL,
            SYSTEM_IN_LEVEL
        }system_game_state;
        enum LevelGameState
        {
            NONE,
            LEVEL_IN_GAME,
            LEVEL_PAUSED,
            LEVEL_COMPLETE,
            LEVEL_LOADING
        }level_game_state;
        enum DebugState
        {
            DEBUG_ON,
            DEBUG_OFF
        }debug_state;
        /*void setBaseStateInGame();
        void setBaseStateStartLevel();
        void setBaseState*/
    protected:
    private:


};

#endif // GAMESTATEMANAGER_H
