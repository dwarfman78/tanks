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
    unsigned int renderingPosition() const;
    std::shared_ptr<se::Entity> myEntity;
    std::shared_ptr<se::Entity> myShadow;
    int life;
    int points;
    bool unregister() const;
        sf::Vector2f speed;
private:
    void tirer();
    bool collision();
    float myInterpolation;
    se::Application& myApplication;
    sf::Clock rateOfFireClock;
    std::shared_ptr<se::Entity> goodbyeMessage;
    std::shared_ptr<se::Entity> lifeCounter;
    Plateau& myPlateau;
    unsigned int joyLeft, joyRight, joyUp, joyDown, joyFire;

    const std::string MEDIA = "tanks";
    const std::string RUN = "joueur_run"; /// Animation "run"
    const std::string STOP = "joueur_stop"; /// Animation "stop"
    const std::string TIRER = "tirer";
    const std::string SMOKES = "smokes";
    const std::string FIRESMOKE = "fire_smoke";
    const std::string MUZZLES = "muzzles";
    const std::string MUZZLE = "muzzle";
    const std::string SHADOW = "shadow";
    const std::string HP = "HP : ";

    const sf::RenderWindow& window;

};
#endif // Joueur_hpp
