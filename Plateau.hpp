#ifndef Plateau_hpp
#define Plateau_hpp
#include <SimpleEngine/Core/Renderable.hpp>
#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Event.hpp>
#include <SimpleEngine/Core/Entity.hpp>
#include <SimpleEngine/Graphic/AnimationManager.hpp>
#include <SimpleEngine/ToolBox/Utils.hpp>
#include <SFML/Graphics.hpp>
#include <Bullet.hpp>
class Joueur;
class Ennemi;
class Plateau : public se::Renderable
{
public:
    Plateau(se::Application& application);
    void render();
    void renderLogic();
    void interpolate(float interpolation);
    bool unregister() const;
    std::set<std::shared_ptr<Bullet> >& getMyBullets();
    std::shared_ptr<Joueur> myJoueur;
private:
    float myInterpolation;
    sf::Clock myClock;
    std::set<std::shared_ptr<Ennemi> > myEnnemis;
    std::set<std::shared_ptr<Bullet> > myBullets;

    se::Application& myApplication;
    int myPopTime;
    const unsigned int MAX_ENNEMI;
    const std::string MUSIC1 = "medias/snd/music1.ogg";
    const std::string MUSIC2 = "medias/snd/music2.ogg";
    const std::string MUSIC3 = "medias/snd/music3.ogg";
    const std::string MUSIC [3] = {MUSIC1,MUSIC2,MUSIC3};
    int myZikIndex;

};
#endif
