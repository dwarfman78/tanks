#include <Joueur.hpp>
int cpt=1;
Joueur::Joueur(se::Application& application, Plateau& plateau) : life(30), points(0),
    myApplication(application), myPlateau(plateau),window(se::GraphicEngine::getInstance()->getRenderWindow()),
    gen(time(NULL)),
    dis(10,30)
{
    myShadow = std::make_shared<se::Entity>();
    myShadow->makeDrawable(SHADOW);
    myShadow->setPosition(100,100);

    myShadow->setOrigin(16,16);

    myShadow->setRotation(0);

    myEntity = std::make_shared<se::Entity>();
    myEntity->makeDrawable(MEDIA);

    myEntity->makeAnimable(STOP);

    myEntity->setPosition(100,100);

    myEntity->setOrigin(16,16);

    myEntity->setRotation(0);

    myEntity->setRenderingPosition(1);

    lifeCounter = std::make_shared<se::Entity>();

    lifeCounter->makeWritable(se::Utils::toString(life));

    lifeCounter->setPosition(0,0);

    lifeCounter->setScale(0.5,0.5);

    lifeCounter->setRenderingPosition(3);

    myApplication.getCurrentScene()->registerRenderable(lifeCounter);

    goodbyeMessage = std::make_shared<se::Entity>();

    se::Config* conf = se::Config::getInstance();

    conf->get("leftJoyButton",joyLeft);
    conf->get("rightJoyButton",joyRight);
    conf->get("upJoyButton",joyUp);
    conf->get("downJoyButton",joyDown);
    conf->get("fireJoyButton",joyFire);

}
void Joueur::render()
{

}
bool Joueur::collision(Bullet& bullet)
{
    float entityPosX = myEntity->getPosition().x;
    float entityPosY = myEntity->getPosition().y;

    float bulletPosX = bullet.myEntity->getPosition().x;
    float bulletPosY = bullet.myEntity->getPosition().y;

    return sf::FloatRect(entityPosX-16,entityPosY-16,32,32).contains(bulletPosX,bulletPosY);
}
void Joueur::tirer()
{

    std::shared_ptr<Bullet> newBullet = std::make_shared<Bullet>(myApplication,myEntity->getSprite().getRotation(),myEntity->getPosition().x,myEntity->getPosition().y,Bullet::PLAYER);

    myPlateau.getMyBullets().insert(newBullet);

    auto scene = myApplication.getCurrentScene();

    scene->registerRenderable(newBullet->myEntity);
    scene->registerRenderable(newBullet);

    scene->addTemporaryParticleEntity(myEntity->getPosition().x+speed.x*3,myEntity->getPosition().y+speed.y*3,110,40,myEntity->getSprite().getRotation()+180,900000,SMOKES,FIRESMOKE);

    scene->addTemporaryParticleEntity(myEntity->getPosition().x+speed.x*3,myEntity->getPosition().y+speed.y*3,70,40,myEntity->getSprite().getRotation()-90,200000,MUZZLES,MUZZLE);

    auto shellEntity = scene->addTemporaryPhysicParticle(myEntity->getPosition().x,myEntity->getPosition().y,0,0,0,5000000,SHELL,SHELL);

    auto body = shellEntity->getContext().getPhysicContext().getBody();

    b2FrictionJointDef jd;

    jd.bodyA = body;
    jd.bodyB = myApplication.getCurrentScene()->getGround();
    jd.maxForce = 0.005;
    jd.maxTorque = 0.00001f;

    myApplication.getCurrentScene()->getPhysicWorld().CreateJoint(&jd);

    body->ApplyForceToCenter(ejection,true);

    float tork = dis(gen)/10000.f;

    body->ApplyTorque(tork,true);

    scene->addTemporarySoundEntity(TIRER);

}

void Joueur::renderLogic()
{
    if(life<=0)
    {
        myApplication.pause();
        sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();
        goodbyeMessage->makeWritable("Game OVER : " + se::Utils::toString(points) + " points.");
        goodbyeMessage->setOrigin(100,100);
        goodbyeMessage->setPosition(window.getSize().x/2,window.getSize().y/2);
        goodbyeMessage->setScale(0.5,0.5);
        goodbyeMessage->setRotation(0);
        goodbyeMessage->setRenderingPosition(3);
        myApplication.getCurrentScene()->registerRenderable(goodbyeMessage);
    }
    else if(life<=10)
    {
        myEntity->setColor(sf::Color::Red);
    }
    else if(life<=20)
    {
        myEntity->setColor(sf::Color(255,128,0));
    }

    lifeCounter->makeWritable(HP+se::Utils::toString(life));

    float ejectionForce = 0.250;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Joystick::isButtonPressed(0, joyLeft)) //11
    {
        speed.x = -5;
        speed.y = 0;

        myEntity->makeAnimable(RUN);

        myEntity->setRotation(180.f);
        myShadow->setRotation(180.f);

        ejection.x = 0.0;
        ejection.y = ejectionForce;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Joystick::isButtonPressed(0, joyUp)) //13
        {
            speed.y = -5;
            myEntity->setRotation(225.f);
            myShadow->setRotation(225.f);

            ejection.x = -ejectionForce;

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Joystick::isButtonPressed(0, joyDown)) //14
        {
            speed.y = 5;
            myEntity->setRotation(135.f);
            myShadow->setRotation(135.f);

            ejection.x = ejectionForce;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Joystick::isButtonPressed(0, joyRight)) //12
    {
        speed.x = 5;
        speed.y = 0;

        myEntity->makeAnimable(RUN);

        myEntity->setRotation(0.f);
        myShadow->setRotation(0.f);

        ejection.x = 0.0;
        ejection.y = ejectionForce;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Joystick::isButtonPressed(0, joyUp)) //13
        {
            speed.y = -5;
            myEntity->setRotation(315.f);
            myShadow->setRotation(315.f);

            ejection.x = ejectionForce;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Joystick::isButtonPressed(0, joyDown)) //14
        {
            speed.y = 5;
            myEntity->setRotation(45.f);
            myShadow->setRotation(45.f);

            ejection.x = -ejectionForce;
        }
    }
    else
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Joystick::isButtonPressed(0, joyUp)) //13
        {
            speed.x = 0;
            speed.y = -5;

            myEntity->makeAnimable(RUN);
            myEntity->setRotation(270.f);
            myShadow->setRotation(270.f);

            ejection.x = ejectionForce;
            ejection.y = 0.0;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Joystick::isButtonPressed(0, joyDown)) //14
        {
            speed.x = 0;
            speed.y = 5;
            myEntity->setRotation(90.f);
            myShadow->setRotation(90.f);
            myEntity->makeAnimable(RUN);

            ejection.x = ejectionForce;
            ejection.y = 0.0;
        }

    }

    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&
            !sf::Joystick::isButtonPressed(0, joyLeft)&&
            !sf::Joystick::isButtonPressed(0, joyRight)&&
            !sf::Joystick::isButtonPressed(0, joyUp)&&
            !sf::Joystick::isButtonPressed(0, joyDown))
    {
        myEntity->makeAnimable(STOP);
        speed.x = 0;
        speed.y = 0;
    }

    if(!collision())
    {
        myEntity->setPosition(myEntity->getPosition().x+(speed.x*(myInterpolation)),
                              myEntity->getPosition().y+(speed.y*(myInterpolation)));


        myShadow->setPosition(myEntity->getPosition().x,
                              myEntity->getPosition().y);


    }

    if(rateOfFireClock.getElapsedTime().asMilliseconds()>=100&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Joystick::isButtonPressed(0, joyFire)))
    {
        rateOfFireClock.restart();
        tirer();
    }

}

bool Joueur::collision()
{
    //collision avec les bords de l'écran.
    sf::Vector3f position = sf::Vector3f(myEntity->getPosition());

    position.x += speed.x*myInterpolation;
    position.y += speed.y*myInterpolation;

    return !(window.getViewport(window.getView()).contains(position.x,position.y));

}
bool Joueur::unregister() const
{
    return false;
}
void Joueur::interpolate(float interpolation)
{
    myInterpolation=interpolation;
}
unsigned int Joueur::renderingPosition() const
{
    return 1;
}
