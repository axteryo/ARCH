#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include <stack>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

#include "GameEvent_Audio.h"
#include "GameEventListener.h"



class AudioSource
{
    public:
        AudioSource(std::string srcID, int limit,GameEventListener* e);
        virtual ~AudioSource();
        std::string getID();
        bool getActive();
        void play();
        void pause();
        void unPause();
        void update();
        void load(std::string src);

    protected:
        std::string audioID;
        bool isActive;
        int soundLimit;
        float volume;
        sf::SoundBuffer buffer;
        std::stack<sf::Sound> soundStack;
        std::vector<sf::Sound> pauseList;
        GameEventListener* _listener;
    private:
};

#endif // AUDIOSOURCE_H
