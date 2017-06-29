#include "AudioSystem.h"
#include "PhysicsComponent.h"

AudioSystem::AudioSystem()
{
    musicVolume = 10;
    narrationVolume = 10;
    sfxVolume = 10;
    isNarrationActive = false;
}

AudioSystem::~AudioSystem()
{
    //dtor
    if(!audioList.empty())
    {
        for(int i = 0;i<audioList.size();i++)
        {
            delete audioList[i];
        }
        audioList.clear();
    }
}

void AudioSystem::loadAudio()
{
    Json::Value dataRoot;
    Json::Reader dataReader;
    std::ifstream dataFile;

    dataFile.open("data/audioData.json");
    bool parsedSuccess = dataReader.parse(dataFile,dataRoot,false);
    if(!parsedSuccess)
    {
         std::cout<<"failed to parse JSON"<< std::endl
            <<dataReader.getFormattedErrorMessages()<<std::endl;

    }
    dataFile.close();

    for(int i = 0;i<dataRoot["sfx"].size();i++)
    {
        std::string id = dataRoot["sfx"][i]["id"].asString();
        int limit = dataRoot["sfx"][i]["countLimit"].asInt();
        std::string src = dataRoot["sfx"][i]["source"].asString();

        AudioSource* audio = new AudioSource(id,limit);
        audio->load(src);
        audioList.push_back(audio);
    }
}

void AudioSystem::playAudio(std::string srcID)
{
    for(int i = 0;i<audioList.size();i++)
    {
        if(audioList[i]->getID().compare(srcID)==0)
        {
            audioList[i]->play();
            break;
        }
    }
}

void AudioSystem::setBackGroundMusic(std::string src)
{
    if(!musicChannel.openFromFile(src))
    {
        std::cout<<"failed to open background music: "<<src<<std::endl;
    }

	musicChannel.setLoop(true);
	musicChannel.play();
	//musicChannel.setVolume(musicVolume);
	musicChannel.setVolume(0);
}

void AudioSystem::update()
{
    for(int i = 0;i<audioList.size();i++)
    {
        if(audioList[i]->getActive())
        {
            audioList[i]->update();
        }
    }
}

void AudioSystem::handleEvent(GameEvent* e)
{
    switch(e->getEventType())
    {
    case GameEvent::EVENT_COLLISION:

        GameEvent_Collision* colEvent = static_cast<GameEvent_Collision*>(e);
        if(colEvent->A_Data->type.compare("bodyFixture")==0&&colEvent->B_Data->type.compare("bodyFixture")==0)
        {
            playAudio("metalClang1");
        }
        break;

    }

}


