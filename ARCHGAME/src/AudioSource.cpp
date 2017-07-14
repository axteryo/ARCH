#include "AudioSource.h"

AudioSource::AudioSource(std::string srcID, int limit,GameEventListener* e)
{
    audioID = srcID;
    isActive = false;
    volume = 5;
    soundLimit = limit;
    _listener = e;
}

AudioSource::~AudioSource()
{
    delete _listener;
}

std::string AudioSource::getID()
{
    return audioID;
}

bool AudioSource::getActive()
{
    return isActive;
}

void AudioSource::load(std::string src)
{
    if(!buffer.loadFromFile(src))
    {
        std::cout<<"The sound source "<<src<<" could not be loaded"<<std::endl;
    }
}


void AudioSource::play()
{
    if(soundStack.size()<soundLimit)
    {
        isActive = true;
        sf::Sound sound;
        sound.setBuffer(buffer);
        soundStack.push(sound);
        soundStack.top().setVolume(volume);
        soundStack.top().play();

        GameEvent_Audio* a = new GameEvent_Audio(audioID,AUDIO_START);
        _listener->notifyEvent(a);
    }
}

void AudioSource::update()
{
    //std::cout<<"ACTIVE_SOUND"<<std::endl;
    if(!soundStack.empty())
    {
        switch(soundStack.top().getStatus())
        {
        case sf::Sound::Stopped:
            soundStack.pop();
            GameEvent_Audio* a = new GameEvent_Audio(audioID,AUDIO_END);
            _listener->notifyEvent(a);
            break;
        }

    }
    else
    {
        isActive = false;
    }
}
void AudioSource::pause()
{
    int i = soundStack.size();
    while(i>0)
    {
        i-=1;
        soundStack.top().pause();
        pauseList.push_back(soundStack.top());
        soundStack.pop();
    }
}

void AudioSource::unPause()
{
    for(int i = 0;i<pauseList.size();i++)
    {
        pauseList[i].play();
        soundStack.push(pauseList[i]);
    }
    pauseList.clear();
}
