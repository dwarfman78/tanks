#ifndef Ennemi_hpp
#define Ennemi_hpp
#include <SimpleEngine/Core/Renderable.hpp>
#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Event.hpp>
#include <SimpleEngine/Core/Entity.hpp>
#include <SimpleEngine/Graphic/AnimationManager.hpp>
#include <SimpleEngine/ToolBox/Utils.hpp>
#include <SimpleEngine/Graphic/GraphicEngine.hpp>
#include <SimpleEngine/ToolBox/Utils.hpp>
#include <SimpleEngine/Core/Scene.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include <SimpleEngine/ToolBox/Config.hpp>
#include <Bullet.hpp>
#include <Plateau.hpp>
#include <Joueur.hpp>
class Ennemi : public se::Renderable
{
public:
    Ennemi(se::Application& application, Plateau& plateau);
    virtual ~Ennemi();
    void render();
    void renderLogic();
    void interpolate(float interpolation);
    bool collision(Bullet& bullet);
    void unregister();
    bool unregister() const;
    bool unregistered;
    unsigned int renderingPosition() const;
    std::shared_ptr<se::Entity> myEntity;
    std::shared_ptr<se::Entity> myShadow;
private:
    /////////////////////////////
    /// Private methods.
    /////////////////////////////
    bool collision();
    void initEntity(se::Application& application);
    void initGraphics();
    void initCaracteristics();
    void defVectVitesse();
    void defRotation();
    void tirer();

    ////////////////////////////
    /// private data
    ////////////////////////////
    float myInterpolation;

    sf::Vector2f speed;
    double nspeed;
    Plateau& myPlateau;
    se::Application& myApplication;
    sf::Clock myBrainTick;

    /////////////////////////////
    /// Constants
    /////////////////////////////
    const std::string MEDIA = "tanks";
    const std::string RUN = "ennemi_run"; /// Animation "run"
    const std::string STOP = "ennemi_stop"; /// Animation "stop"
    const std::string TIRER = "tirer";
    const std::string SMOKES = "smokes";
    const std::string FIRESMOKE = "fire_smoke";
    const std::string MUZZLES = "muzzles";
    const std::string MUZZLE = "muzzle";
    const std::string SHADOW = "shadow";
    const std::string MAX_SPEED = "ennemi_maxspeed";
    const std::string MIN_SPEED = "ennemi_minspeed";
    const std::string SHELL = "shell";
    const int SIZE = 16;


    std::mt19937 gen;

    std::uniform_int_distribution<> dis;

};
#endif // Ennemi_hpp

