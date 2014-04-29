#include <Plateau.hpp>
#include <Joueur.hpp>
#include <Ennemi.hpp>
bool one = false;

Plateau::Plateau(se::Application& application) : myApplication(application),myPopTime(4000000),MAX_ENNEMI(10), myZikIndex(3)
{

    application.loadMusic(MUSIC[myZikIndex++%3]);
    application.playMusic();
    myClock.restart();
    myJoueur = std::make_shared<Joueur>(application,*this);
    myApplication.getCurrentScene()->registerRenderable(myJoueur->myEntity);
    myApplication.getCurrentScene()->registerRenderable(myJoueur);

}

void Plateau::render()
{

}

std::unordered_set<std::shared_ptr<Bullet> >& Plateau::getMyBullets()
{
    return myBullets;
}

void Plateau::renderLogic()
{
    float bulletPosX , bulletPosY = 0.f;

    float enemyPosX , enemyPosY = 0.f;

    for(std::unordered_set<std::shared_ptr<Bullet> >::iterator i = myBullets.begin(); i!=myBullets.end();)
    {

        std::shared_ptr<Bullet> bullet = *i;

        bulletPosX = bullet->myEntity->getPosition().x;
        bulletPosY = bullet->myEntity->getPosition().y;

        if(bullet->unregistered)
        {
            myBullets.erase(*(i++));
        }
        else
        {
            for(std::unordered_set<std::shared_ptr<Ennemi> >::iterator e = myEnnemis.begin(); e!=myEnnemis.end();)
            {
                std::shared_ptr<Ennemi> ennemi = *e;
                enemyPosX = ennemi->myEntity->getPosition().x;
                enemyPosY = ennemi->myEntity->getPosition().y;

                if(ennemi->unregistered)
                {
                    myEnnemis.erase(*(e++));
                }
                else
                {
                    if(bullet->owner == Bullet::PLAYER&&ennemi->collision(*bullet))
                    {
                        bullet->unregister();
                        ennemi->unregister();
                        myJoueur->points++;
                        if(myJoueur->points%10==0)
                        {
                            myPopTime = myPopTime/1.5;
                            if(!myApplication.getCurrentMusic().getStatus() == sf::Music::Paused)
                            {
                                myApplication.pauseMusic();
                                myApplication.loadMusic(MUSIC[myZikIndex++%3]);
                                myApplication.playMusic();
                            }
                        }

                        myApplication.addTemporaryParticleEntity(enemyPosX,enemyPosY,30,30,0,700000,EXPLOSIONS,EXPLOSION);
                        myApplication.addTemporarySoundEntity(EXPLOSION);
                    }
                    ++e;
                }
            }
            if(bullet->owner == Bullet::ENNEMI&&myJoueur->collision(*bullet))
            {
                bullet->unregister();
                myJoueur->life--;
                myApplication.addTemporaryParticleEntity(bulletPosX,bulletPosY,64,64,0,50000,HITS,HIT);
                myApplication.addTemporarySoundEntity(IMPACT);

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

        auto scene = myApplication.getCurrentScene();
        scene->registerRenderable(newEnnemi->myEntity);
        scene->registerRenderable(newEnnemi);
        myEnnemis.insert(newEnnemi);
    }
}

void Plateau::interpolate(float interpolation)
{
    //myInterpolation = interpolation;
}

bool Plateau::unregister() const
{
    return false;
}
