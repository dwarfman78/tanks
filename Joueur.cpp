#include <Joueur.hpp>
int cpt=1;
Joueur::Joueur(se::Application& application, Plateau& plateau) : life(30), points(0),
    myApplication(application), myPlateau(plateau)
{
    myEntity = std::make_shared<se::Entity>();
    myEntity->makeDrawable("tanks");

    myEntity->makeAnimable("joueur_stop");

    myEntity->setPosition(100,100);

    myEntity->setOrigin(16,16);

    myEntity->setRotation(0);

    lifeCounter = std::make_shared<se::Entity>();

    lifeCounter->makeWritable(se::Utils::toString(life));

    lifeCounter->setPosition(0,0);

    lifeCounter->setScale(0.5,0.5);

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
    sf::FloatRect rectEntity(myEntity->getPosition().x-16,myEntity->getPosition().y-16,32,32);

    return rectEntity.contains(bullet.myEntity->getPosition().x,bullet.myEntity->getPosition().y);
}
void Joueur::tirer()
{

    std::shared_ptr<Bullet> newBullet = std::make_shared<Bullet>(myApplication,myEntity->getSprite().getRotation(),myEntity->getPosition().x,myEntity->getPosition().y,Bullet::PLAYER);

    myPlateau.getMyBullets().insert(newBullet);

    myApplication.getCurrentScene()->registerRenderable(newBullet->myEntity);
    myApplication.getCurrentScene()->registerRenderable(newBullet);

    myApplication.addTemporaryParticleEntity(myEntity->getPosition().x+speed.x*3,myEntity->getPosition().y+speed.y*3,110,40,myEntity->getSprite().getRotation()+180,900000,"smokes","fire_smoke");

    myApplication.addTemporaryParticleEntity(myEntity->getPosition().x+speed.x*3,myEntity->getPosition().y+speed.y*3,70,40,myEntity->getSprite().getRotation()-90,200000,"muzzles","muzzle");

    myApplication.addTemporarySoundEntity("tirer");

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
        myApplication.getCurrentScene()->registerRenderable(goodbyeMessage);
    }
    else if(life<=10)
    {
        //sf::Color color(255/life,0,0);
        myEntity->setColor(sf::Color::Red);
    }
    else if(life<=20)
    {
        myEntity->setColor(sf::Color(255,128,0));
    }

    lifeCounter->makeWritable("HP: "+se::Utils::toString(life));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Joystick::isButtonPressed(0, joyLeft)) //11
    {
        speed.x = -5;
        speed.y = 0;

        myEntity->makeAnimable("joueur_run");

        myEntity->setRotation(180.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Joystick::isButtonPressed(0, joyUp)) //13
        {
            speed.y = -5;
            myEntity->setRotation(225.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Joystick::isButtonPressed(0, joyDown)) //14
        {
            speed.y = 5;
            myEntity->setRotation(135.f);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Joystick::isButtonPressed(0, joyRight)) //12
    {
        speed.x = 5;
        speed.y = 0;

        myEntity->makeAnimable("joueur_run");

        myEntity->setRotation(0.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Joystick::isButtonPressed(0, joyUp)) //13
        {
            speed.y = -5;
            myEntity->setRotation(315.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Joystick::isButtonPressed(0, joyDown)) //14
        {
            speed.y = 5;
            myEntity->setRotation(45.f);
        }
    }
    else
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Joystick::isButtonPressed(0, joyUp)) //13
        {
            speed.x = 0;
            speed.y = -5;

            myEntity->makeAnimable("joueur_run");
            myEntity->setRotation(270.f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Joystick::isButtonPressed(0, joyDown)) //14
        {
            speed.x = 0;
            speed.y = 5;
            myEntity->setRotation(90.f);
            myEntity->makeAnimable("joueur_run");
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
        myEntity->makeAnimable("joueur_stop");
        speed.x = 0;
        speed.y = 0;
    }

    if(!collision())
    {
        myEntity->setPosition(myEntity->getPosition().x+(speed.x*(myInterpolation)),
                              myEntity->getPosition().y+(speed.y*(myInterpolation)));


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

    se::GraphicEngine* engine = se::GraphicEngine::getInstance();

    sf::RenderWindow& window = engine->getRenderWindow();

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
