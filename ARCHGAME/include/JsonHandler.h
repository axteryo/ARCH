#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <iostream>
#include <fstream>
#include "json/json.h"


class JsonHandler
{
    public:
        JsonHandler();
        virtual ~JsonHandler();
        Json::Value loadJson(std::string f);
    protected:

        Json::Value root;
        Json::Reader reader;
        std::ifstream file;
    private:
};

#endif // JSONHANDLER_H
