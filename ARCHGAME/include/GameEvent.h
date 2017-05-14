#ifndef GAMEEVENT_H
#define GAMEEVENT_H


class GameEvent
{
    public:
        GameEvent();
        virtual ~GameEvent();
        enum eventType
        {
            EVENT_SEQUENCE,
            EVENT_COMBAT,
            EVENT_GAMESTATE,
            EVENT_ACTION,
            EVENT_MENU
        };
    protected:
    private:
};

#endif // GAMEEVENT_H
