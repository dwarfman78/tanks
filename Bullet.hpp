#ifndef Bullet_hpp
#define Bullet_hpp
#include <SimpleEngine/Core/Renderable.hpp>
#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Event.hpp>
#include <SimpleEngine/Core/Entity.hpp>
#include <SimpleEngine/Graphic/AnimationManager.hpp>
#include <SimpleEngine/ToolBox/Utils.hpp>
#include <SimpleEngine/Graphic/GraphicEngine.hpp>
#include <SimpleEngine/Graphic/GeometricalContext.hpp>

class Bullet : public se::Renderable
{

public:
enum Owner{
    ENNEMI,
    PLAYER
};
    Bullet(se::Application& application,float angle, float x, float y, Owner owner);
    virtual ~Bullet();
    void render();
    void renderLogic();
    void interpolate(float interpolation);
    void unregister();
    virtual bool unregister() const;
    std::shared_ptr<se::Entity> myEntity;
    sf::Vector2f speed;
    bool unregistered;
    Owner owner;

private:
    void defRotation();
    bool collision();
    float myInterpolation;
    se::Application& myApplication;
};
#endif // Bullet_hpp
