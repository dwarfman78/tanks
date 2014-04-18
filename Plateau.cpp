#include <Plateau.hpp>
#include <Joueur.hpp>
#include <Ennemi.hpp>
bool one = false;

Plateau::Plateau(se::Application& application) : myApplication(application),myPopTime(4000000),MAX_ENNEMI(10), myZikIndex(3)
{
    application.registerRenderable(std::shared_ptr<Renderable>(this));

    application.loadMusic(MUSIC[myZikIndex++%3]);
    application.playMusic();
    myClock.restart();
    myJoueur = std::make_shared<Joueur>(application,*this);
    application.registerRenderable(myJoueur->myEntity);
    application.registerRenderable(myJoueur);

}

void Plateau::render()
{

}

std::set<std::shared_ptr<Bullet> >& Plateau::getMyBullets()
{
    return myBullets;
}

void Plateau::renderLogic()
{

    for(std::set<std::shared_ptr<Bullet> >::iterator i = myBullets.begin(); i!=myBullets.end();)
    {
        std::shared_ptr<Bullet> bullet = *i;
        if(bullet->unregistered)
        {
            myBullets.erase(*(i++));
        }
        else
        {

            for(std::set<std::shared_ptr<Ennemi> >::iterator e = myEnnemis.begin(); e!=myEnnemis.end();)
            {
                std::shared_ptr<Ennemi> ennemi = *e;

                if(ennemi->unregistered)
                {
                    myEnnemis.erase(*(e++));
                }
                else
                {
                    if(ennemi->collision(*bullet)&&bullet->owner == Bullet::PLAYER)
                    {
                        bullet->unregister();
                        ennemi->unregister();
                        myJoueur->points++;
                        if(myJoueur->points%10==0)
                        {
                            myPopTime = myPopTime/1.5;
                            myApplication.pauseMusic();
                            myApplication.loadMusic(MUSIC[myZikIndex++%3]);
                            myApplication.playMusic();
                        }

                        myApplication.addTemporaryParticleEntity(ennemi->myEntity->getPosition().x,ennemi->myEntity->getPosition().y,30,30,0,700000,"explosions","explosion");
                        myApplication.addTemporarySoundEntity("explosion");
                    }
                    ++e;
                }
            }
            if(myJoueur->collision(*bullet)&&bullet->owner == Bullet::ENNEMI)
            {
                bullet->unregister();
                myJoueur->life--;
                myApplication.addTemporaryParticleEntity(bullet->myEntity->getPosition().x,bullet->myEntity->getPosition().y,64,64,0,50000,"hits","hit");
                myApplication.addTemporarySoundEntity("impact");

            }
            ++i;
        }

    }

    //std::cout << myPopTime << " " << myClock.getElapsedTime().asMicroseconds() << std::endl;
    if(myClock.getElapsedTime().asMicroseconds()>=myPopTime&&myEnnemis.size()<MAX_ENNEMI)
    //if(!one)
    {
        one=true;
        myClock.restart();
        std::shared_ptr<Ennemi> newEnnemi = std::make_shared<Ennemi>(myApplication,*this);
        myApplication.registerRenderable(newEnnemi->myEntity);
        myApplication.registerRenderable(newEnnemi);
        myEnnemis.insert(newEnnemi);
    }
}

void Plateau::interpolate(float interpolation)
{
    myInterpolation = interpolation;
}

bool Plateau::unregister() const
{
    return false;
}
