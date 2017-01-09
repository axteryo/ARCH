#include "collisionFactory.h"

collisionFactory::collisionFactory()
{
    //ctor
}

void collisionFactory::BeginContact(b2Contact* contact)
{
    GameObject* A;
    GameObject* B;
    fixtureUserData* f_data;
    std::string id_A;
    std::string id_B;
    std::string data_A;
    std::string data_B;

    A = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
    B = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());
    if(A && B)
    {
        id_A = A->objectId;
        id_B = B->objectId;
        f_data = static_cast<fixtureUserData*>(contact->GetFixtureA()->GetUserData());

        if(f_data)
        {
            //std::cout<<f_data->data<<std::endl;

            data_A = f_data->data;

            f_data = static_cast<fixtureUserData*>(contact->GetFixtureB()->GetUserData());
            if(f_data)
            {

                data_B = f_data->data;
                //std::cout<<A->objectId<<std::endl;
                //std::cout<<B->objectId<<std::endl;
                ///This Object hit you! this is the part that hit you! this is the part of you that was hit!
                A->handleCollision(B,data_B,data_A);
                B->handleCollision(A,data_A,data_B);
            }
        }

    }
/*
/**
   First check which GameObjects have come into contact
   Second check which of their fixtures have come into contact
   Third resolve
*/
/*
gObj = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
id_A = gObj->objectId;
gObj = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());
id_B = gObj->objectId;
if(id_A.compare("object_player")==0)
{
    //std::cout<<"The PLAYER has made contact"<<std::endl;

    if(id_B.compare("object_enemy")==0)
    {

        //std::cout<<"The PLAYER has made contact with an ENEMY"<<std::endl;
        f_data = static_cast<fixtureUserData*>(contact->GetFixtureA()->GetUserData());
        data_A = f_data->data;
        f_data = static_cast<fixtureUserData*>(contact->GetFixtureB()->GetUserData());
        data_B = f_data->data;
        //std::cout<<data_B<<std::endl;
        if(data_A.compare("alert_radius")==0)
        {

            if(data_B.compare("alert_radius")==0)
            {
                ///The players and enemies alert radi have collided
                //std::cout<<"The PLAYERS RADIUS has come in contact with the ENEMIES RADIUS"<<std::endl;
            }
            else if(data_B.compare("body")==0)
            {
                //std::cout<<"The PLAYERS RADIUS has come in contact with the ENEMIES BODY"<<std::endl;
            }
            //the players radius has come in contactst
        }
        else if(data_A.compare("body")==0)
            {
                if(data_B.compare("alert_radius")==0)
                {
                   // std::cout<<"The PLAYERS BODY has made contact with the enemies radius"<<std::endl;
                }
                else if(data_B.compare("body")==0)
                {
                    //std::cout<<"The PLAYERS BODY has come in contact with the ENEMIES BODY"<<std::endl;
                }
            }
    }*/
/*}
else if(id_A.compare("object_enemy")==0)
{
    if(id_B.compare("object_player")==0)
    {
        f_data = static_cast<fixtureUserData*>(contact->GetFixtureA()->GetUserData());
        data_A = f_data->data;
        f_data = static_cast<fixtureUserData*>(contact->GetFixtureB()->GetUserData());
        data_B = f_data->data;

         if(data_A.compare("body")==0)
        {
            //std::cout<<"Collision occured"<<std::endl;
            //std::cout<<"The ENEMies BODY has collided with the PLAYERs RADIUS"<<std::endl;
        }
    }
}
   f_data = static_cast<fixtureUserData*>(contact->GetFixtureA()->GetUserData());
    if(f_data)
    {
        std::string data1 = f_data->data;
        f_data = static_cast<fixtureUserData*>(contact->GetFixtureB()->GetUserData());
        if(f_data)
        {

            std::string data2 = f_data->data;
            if(data1.compare("alert_radius")==0)
            {
                ///this means the player has encountered another alert_radius
                ///Now we check
                if(data2.compare("alert_radius")==0)
                {
                    gObj = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
                    if(gObj->objectId.compare("object_player")==0)
                    {
                        std::cout<<gObj->objectId<<std::endl;
                    }
                    else if(gObj->objectId.compare("object_enemy")== 0)
                    {
                        std::cout<<gObj->objectId<<std::endl;
                    }
                }

                //if(data2)

            }
            ///The players radius has encountered the enemies Body
            else if(data1.compare("body")==0)
            {

                 gObj = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
                 std::cout<<gObj->objectId<<std::endl;
            }
        }


    }

    //switch
*/
}

collisionFactory::~collisionFactory()
{
    //dtor
}
