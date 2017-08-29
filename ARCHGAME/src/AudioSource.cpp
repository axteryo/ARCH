#include "AudioSource.h"

AudioSource::AudioSource(std::string srcID, int limit,float vol,GameEventListener* e)
{
    audioID = srcID;
    isActive = false;
    volume = vol;
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
    if(soundQueue.size()>soundLimit)
    {
          soundQueue.front().stop();
    }
    isActive = true;
    sf::Sound sound;
    sound.setBuffer(buffer);
    soundQueue.push(sound);
    soundQueue.back().play();
    soundQueue.back().setVolume(volume);

    GameEvent_Audio* a = new GameEvent_Audio(audioID,AUDIO_START);
    _listener->notifyEvent(a);

}

void AudioSource::update()
{
    //std::cout<<"ACTIVE_SOUND"<<std::endl;
    if(!soundQueue.empty())
    {
        switch(soundQueue.front().getStatus())
        {
        case sf::Sound::Stopped:
            soundQueue.pop();
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
    int i = soundQueue.size();
    while(i>0)
    {
        i-=1;
        soundQueue.front().pause();
        pauseList.push_back(soundQueue.front());
        soundQueue.pop();
    }
}

void AudioSource::unPause()
{
    for(int i = 0;i<pauseList.size();i++)
    {
        pauseList[i].play();
        soundQueue.push(pauseList[i]);
    }
    pauseList.clear();
}
