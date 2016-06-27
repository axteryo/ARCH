#include "GameObj.h"
#include "BoxWiz.h"

GameObj::GameObj()
{
     /** sprite texture**/
    texture.loadFromFile("box.png");
    sprite.setTexture(texture);
    sprite.setOrigin(16.0f,16.0f);


    /**Physics body**/
    goBodyDef.type = b2_staticBody;
    goBodyDef.fixedRotation = true;
    goBodyDef.position.Set(0,0);
    goBody = world.CreateBody(&goBodyDef);
    b2Vec2 v1(0,-(sprite.getGlobalBounds().height/2)/30);
    b2Vec2 v2(sprite.getGlobalBounds().width/30,-(sprite.getGlobalBounds().height/2)/30);
    goPolyShape.Set(v1,v2);
    //goPolyShape.SetAsBox((sprite.getGlobalBounds().width/2)/30,(sprite.getGlobalBounds().height/2)/30);
    goFixtureDef.shape = &goPolyShape;
    goFixtureDef.density = 1.0f;
    goFixtureDef.friction = 0.0f;
    goBody->CreateFixture(&goFixtureDef);
    objId = 2;
    goBody->SetUserData((void*)objId);



}

void GameObj::update()
{
    sprite.setPosition(goBody->GetTransform().p.x*30,goBody->GetTransform().p.y*30);
    sprite.setRotation(goBody->GetAngle()*(180/3.14159));

}

void GameObj::setLocation(float lX,float lY)
{
    goBody->SetTransform(b2Vec2(lX/30,lY/30),goBody->GetAngle());
}
sf::Sprite GameObj::getSprite()
{
    return sprite;
}


