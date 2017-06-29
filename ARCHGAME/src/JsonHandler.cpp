#include "JsonHandler.h"

JsonHandler::JsonHandler()
{
    //ctor
}

JsonHandler::~JsonHandler()
{
    //dtor
}

Json::Value JsonHandler::loadJson(std::string f)
{
    root.clear();
    file.open(f);
    bool parsedSuccess = reader.parse(file,root,false);
    if(!parsedSuccess)
    {
         std::cout<<"failed to parse JSON"<< std::endl
            <<reader.getFormattedErrorMessages()<<std::endl;
        std::cout<<"FAILED TO LOAD: "<<f<< std::endl;
    }
    file.close();
    return root;
}
