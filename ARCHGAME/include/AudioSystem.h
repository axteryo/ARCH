#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H
#include <SFML/Audio.hpp>
#include "AudioSource.h"
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "GameEventHandler.h"


class AudioSystem : GameEventHandler
{
    public:
        AudioSystem();
        virtual ~AudioSystem();
        void loadAudio();
        void update();
        void playAudio(std::string srcID);
        void setBackGroundMusic(std::string src);
        void handleEvent(GameEvent* e);
    protected:
    private:

        ///Channels for longer sounds/music. Narration will always have priority over other sounds
         sf::Music musicChannel;
         sf::Music narrationChannel;
         std::vector<AudioSource*> audioList;

         int narrationVolume;
         int sfxVolume;
         int musicVolume;

         bool isNarrationActive;

};

#endif // AUDIOSYSTEM_H
