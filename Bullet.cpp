#include <Bullet.hpp>

Bullet::Bullet(se::Application& application, float angle, float x, float y,Owner owner) :
    speed(se::Utils::createFromPolar(se::Utils::degToRads(angle),7)),
    unregistered(false),
    owner(owner),
    myApplication(application),
    window(se::GraphicEngine::getInstance()->getRenderWindow())

{
    myEntity = std::make_shared<se::Entity>();

    myEntity->makeDrawable(BULLETS);
    myEntity->makeAnimable(FIRE);

    myEntity->setPosition(x+speed.x*3,y+speed.y*3);
    myEntity->setScale(0.3f,0.3f);
    myEntity->setOrigin(12,12);

    //defRotation();
}

Bullet::~Bullet()
{
}

void Bullet::render()
{

}
void Bullet::unregister()
{
    unregistered = true;
    myEntity->getContext().unregister();

}

bool Bullet::unregister() const
{
    return unregistered;
}

void Bullet::renderLogic()
{
    if(!collision())
    {
        myEntity->setPosition(myEntity->getPosition().x+(speed.x*(myInterpolation)),
                             myEntity->getPosition().y+(speed.y*(myInterpolation)));
    }
    else
    {
        unregister();
    }

}

void Bullet::interpolate(float interpolation)
{
    myInterpolation = interpolation;
}

bool Bullet::collision()
{
    sf::Vector3f position = sf::Vector3f(myEntity->getPosition());

    position.x += speed.x*myInterpolation;
    position.y += speed.y*myInterpolation;

    return !(window.getViewport(window.getView()).contains(position.x,position.y));
}
unsigned int Bullet::renderingPosition() const
{
    return 1;
}
