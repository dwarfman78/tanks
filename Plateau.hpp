#ifndef Plateau_hpp
#define Plateau_hpp
#include <SimpleEngine/Core/Renderable.hpp>
#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Event.hpp>
#include <SimpleEngine/Core/Entity.hpp>
#include <SimpleEngine/Graphic/AnimationManager.hpp>
#include <SimpleEngine/ToolBox/Utils.hpp>
#include <SimpleEngine/Core/Impl/SceneSetImplementation.hpp>
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
    std::unordered_set<std::shared_ptr<Bullet> >& getMyBullets();
    std::shared_ptr<Joueur> myJoueur;
    unsigned int renderingPosition() const;
    void makeExplosion(const b2Vec2& center);
private:
    float myInterpolation;
    sf::Clock myClock;
    std::unordered_set<std::shared_ptr<Ennemi> > myEnnemis;
    std::unordered_set<std::shared_ptr<Bullet> > myBullets;

    se::Application& myApplication;
    int myPopTime;
    const unsigned int MAX_ENNEMI;
    const std::string MUSIC1 = "medias/snd/music1.ogg";
    const std::string MUSIC2 = "medias/snd/music2.ogg";
    const std::string MUSIC3 = "medias/snd/music3.ogg";
    const std::string MUSIC [3] = {MUSIC1,MUSIC2,MUSIC3};

    const std::string EXPLOSIONS = "explosions";
    const std::string EXPLOSION = "explosion";
    const std::string BLAST1 = "blast1";
    const std::string BLAST2 = "blast2";
    const std::string BLAST3 = "blast3";
    const std::string BLAST [3] = {BLAST1,BLAST2,BLAST3};
    const std::string HITS = "hits";
    const std::string HIT = "hit";
    const std::string IMPACT = "impact";

    unsigned int myZikIndex;
    unsigned int myBlastIndex;

};
#endif
