#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H
#include <SFML/Audio.hpp>
#include "AudioSource.h"


class AudioSystem
{
    public:
        AudioSystem();
        virtual ~AudioSystem();
        void loadAudio();
        void update();
        void playAudio(std::string srcID);
    protected:
    private:

         sf::Music musicChannel1;
         sf::Music musicChannel2;
         sf::music musicChannel3;
         sf::Music narrationChannel;
         std::vector<AudioSource*> audio;
};

#endif // AUDIOSYSTEM_H
