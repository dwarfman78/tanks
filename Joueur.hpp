#ifndef Joueur_hpp
#define Joueur_hpp
#include <SimpleEngine/Core/Renderable.hpp>
#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Event.hpp>
#include <SimpleEngine/Core/Entity.hpp>
#include <SimpleEngine/Graphic/AnimationManager.hpp>
#include <SimpleEngine/ToolBox/Utils.hpp>
#include <SimpleEngine/Graphic/GraphicEngine.hpp>
#include <SimpleEngine/ToolBox/Config.hpp>
#include <SFML/Graphics.hpp>
#include <Bullet.hpp>
#include <Plateau.hpp>
class Joueur : public se::Renderable
{
public:
    Joueur(se::Application& application, Plateau& myPlateau);
    void render();
    void renderLogic();
    void interpolate(float interpolation);
    void unregister(Bullet& bullet);
    bool collision(Bullet& bullet);
    std::shared_ptr<se::Entity> myEntity;
    int life;
    int points;
    bool unregister() const;
private:
    void tirer();
    bool collision();
    float myInterpolation;
    sf::Vector2f speed;
    se::Application& myApplication;
    sf::Clock rateOfFireClock;
    std::shared_ptr<se::Entity> goodbyeMessage;
    std::shared_ptr<se::Entity> lifeCounter;
    Plateau& myPlateau;
    unsigned int joyLeft, joyRight, joyUp, joyDown, joyFire;
};
#endif // Joueur_hpp
