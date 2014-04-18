#include <Bullet.hpp>

Bullet::Bullet(se::Application& application, float angle, float x, float y,Owner owner) :
    speed(se::Utils::createFromPolar(se::Utils::degToRads(angle),7)),
    unregistered(false),
    owner(owner),
    myApplication(application)

{
    myEntity = std::shared_ptr<se::Entity>(new se::Entity());

    myEntity->makeDrawable("bullets");
    myEntity->makeAnimable("bullet_fire");

    myEntity->setPosition(x+speed.x*3,y+speed.y*3);
    myEntity->setScale(0.3f,0.3f);
    myEntity->setOrigin(12,12);

    defRotation();


    //application.registerRenderable(std::shared_ptr<se::Renderable>(&myEntity));
    //application.registerRenderable(std::shared_ptr<se::Renderable>(this));
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
    myEntity->unregistered = true;

}
void Bullet::defRotation()
{
    sf::Vector2f abscisse(1,0);
    double nspeed = se::Utils::norm(speed);

    float rotationRad = (acos((speed.x*abscisse.x)/nspeed));

    float rotationDeg = se::Utils::radsToDeg(rotationRad);

    if(se::Utils::det(speed,abscisse)>0)
        rotationDeg*=-1;

    myEntity->setRotation(rotationDeg);
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

    se::GraphicEngine* engine = se::GraphicEngine::getInstance();

    sf::RenderWindow& window = engine->getRenderWindow();

    return !(window.getViewport(window.getView()).contains(position.x,position.y));
}
