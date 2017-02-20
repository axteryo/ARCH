#include "Player.h"
Player::~Player()
{

    delete _alertRadius;
    delete _physicsBody;
    delete _graphicsBody;
}

Player::Player(MoveableBody* p, AnimatableGraphic* g)
{
    aliveState = ALIVE;
    objectId = "object_player";
    layerDepth = 6;
    b2V_position = b2Vec2(0,0);
    b2V_velocity = b2Vec2(0,0);
    b2V_acceleration = b2Vec2(0,0);
    impactDirection =b2Vec2(0,0);
    //fl_rotation = 180;
    thrustLevel = 0;
    turnRate = .1;
    topSpeed = 18;
    thrusting = false;
    rRotate= false;
    lRotate=false;
    firing = false;
    attackDuration = 20;
    attackCoolDown = 60;
    impactDuration = 0;

    maxHealthLevel = 100;
    minHealthLevel = 0;
    currentHealthLevel = 100;
    damageAmount = 0;


    thrustState = THRUST_F;
    turnRightState = TURN_RIGHT_F;
    turnLeftState = TURN_LEFT_F;
    //turnStack.push(TURN_F);
    attackTypeState = NO_ATTACK;

    _graphicsBody = g;
    _physicsBody = p;
    _alertRadius = new RadiusBody(300);
    _alertRadius->create(_physicsBody,"alert_radius");

    _physicsBody->body->SetUserData((void*)this);
    attackFixture = nullptr;


    //ctor
}
void Player::turnLeft()
{
    if(thrusting)
    {
        turnRate = .04;
    }
    else
    {
        turnRate = .1;
    }

        fl_rotation-=turnRate;
}
void Player::turnRight()
{
    if(thrusting)
    {
        turnRate = .04;
    }
    else
    {
        turnRate = .1;
    }

        fl_rotation+=turnRate;
}
void Player::thrust()
{
    b2Vec2 aim(0,0);
    //turnRate =.04;
    if(thrustLevel<1)
    {
        thrustLevel += .025;
    }
    else{thrustLevel = 1;}
    aim = b2Vec2(cos(fl_rotation),sin(fl_rotation));
    aim.Normalize();

    aim.x*=thrustLevel;
    aim.y*=thrustLevel;
    b2V_acceleration+=aim;



}
void::Player::arrive()
{
    b2Vec2 aim(0,0);
    //turnRate =.1;
    if(thrustLevel> 0)
    {  //std::cout<<"Thrust Level:"<<thrustLevel<<std::endl;
        thrustLevel = 0;
    }
    else{thrustLevel = 0;}


    if(sqrt(
        (b2V_velocity.x*b2V_velocity.x)
        +(b2V_velocity.y*b2V_velocity.y))>10)
       {
            b2Vec2 vel = b2V_velocity;
            vel.Normalize();
            b2V_velocity.x-=vel.x/30;
            b2V_velocity.y-=vel.y/30;

       }

    aim.x*=thrustLevel;
    aim.y*=thrustLevel;
    b2V_acceleration+=aim;
}
void Player::update()
{
    fl_rotation = _physicsBody->body->GetAngle();
    b2V_velocity = _physicsBody->body->GetLinearVelocity();

    //fl_rotation = _graphicsBody->sprite.getRotation();
    switch(thrustState)
    {
        case THRUST_T:
            ///Player Thrusters
            thrust();
            break;
        case THRUST_F:
            ///Player Stabalizing
            arrive();
            break;

    }
     switch(turnLeftState)
        {
            case TURN_LEFT:
            ///Player turning Left
                turnLeft();
            break;
            case TURN_LEFT_F:
            break;
        }
         switch(turnRightState)
        {
            case TURN_RIGHT:
            ///Player turning Left
                turnRight();
            break;
            case TURN_RIGHT_F:
            break;
        }

    switch(attackTypeState)
    {
        case NO_ATTACK:
            attackCoolDown-=1;
        break;
        case LASER:
                laser();
        break;

    }
     _physicsBody->applyImpact(impactTypeState,impactDirection);
      if(impactDuration<=0)
    {
        impactTypeState = NO_IMPACT;
        impactDuration = 30;
    }
    else
    {
        impactDuration-=1;
    }
     _physicsBody->update(this);


     b2V_acceleration = b2Vec2(0,0);

}
void Player::setPosition(float x, float y)
{
    _physicsBody->body->SetTransform(b2Vec2(x/30,y/30),_physicsBody->body->GetAngle());

}
b2Vec2 Player::getPosition()
{
    return b2V_position;
}
void Player::setRotation(float angle)
{

    _physicsBody->body->SetTransform(_physicsBody->body->GetPosition(),angle);
}

sf::Sprite Player::getSprite()
{
     _graphicsBody->update(this);
    return _graphicsBody->getSprite();
}

void Player::activateThrusters()
{
    thrusting= true;
    thrustState = THRUST_T;

}
void Player::cancelThrusters()
{
    thrusting=false;
    thrustState = THRUST_F;
}
void Player::setTurnLeft()
{
    turnLeftState = TURN_LEFT;
}
void Player::cancelLeftTurn()
{
    turnLeftState = TURN_LEFT_F;
}
void Player::setTurnRight()
{
    turnRightState = TURN_RIGHT;
}
void Player::cancelRightTurn()
{
    turnRightState = TURN_RIGHT_F;
}

void Player::setDamageAmount(int a)
{
    damageAmount = a;
}
void Player::takeDamage()
{
    currentHealthLevel -= damageAmount;
}

///PLAYER ATTACK FUNCTION
void Player::useAttack(int a)
{
    if(a==1)
	{
		attackTypeState = LASER;

	}

}
void Player::setNoAttack()
{
    attackTypeState = NO_ATTACK;
}

void Player::handleCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{

}
void Player::initiateCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{
    if(self_fixtureType.compare("body")==0)
        {

            if(fixtureType.compare("drain")==0)
            {
               gaugeAttack(fixtureType,obj->getPosition());
            }
        }

}
void Player::resolveCollision(GameObject* obj,std::string fixtureType,std::string self_fixtureType)
{

}

bool Player::isAlive()
{
    switch(aliveState)
    {
    case ALIVE:
        return true;
        break;
    case DEAD:
        return false;
        break;
    }
}
bool Player::isImpacted()
{
    return false;
}

void Player::gaugeAttack(std::string attack,b2Vec2 direction)
{
    b2Vec2 p =getPosition();

    b2Vec2 d = b2Vec2(direction.x-p.x,direction.y-p.y);
     d.Normalize();
    impactDirection = d;
    if(attack.compare("drain")==0)
    {
        impactTypeState = PULLED;
    }
}



///LASER ATTACK
void Player::laser()
    {
    if(attackCoolDown<=0)
        {
        if(attackFixture)
        {
            //std::cout<<firing<<std::endl;
            if(attackDuration<=0)
            {

                _physicsBody->body->DestroyFixture(attackFixture);
                firing = false;
                attackDuration = 20;
                attackCoolDown = 60;
                setNoAttack();
                attackFixture = nullptr;

            }
            else
            {
                attackDuration-=1;
            }

        }
        else
        {
            //attackDuration = 20;
            //attackCoolDown = 60;
            firing = true;
            b2PolygonShape laserShape;
            fixtureUserData* f = new fixtureUserData;
            f->data ="laser";
            b2FixtureDef laserFixtureDef;
            laserFixtureDef.isSensor= true;
            laserShape.SetAsBox((500.0f)/30,(20.0f)/30,b2Vec2(18,0),0);
            laserFixtureDef.shape = &laserShape;
            laserFixtureDef.userData= ((void*)f);
            attackFixture = _physicsBody->body->CreateFixture(&laserFixtureDef);
        }
    }
    else
    {
        std::cout<<"Laser is in cooldown"<<std::endl;
        attackDuration = 20;
        setNoAttack();
    }


}
