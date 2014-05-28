#include <Plateau.hpp>
#include <Joueur.hpp>
#include <Ennemi.hpp>
bool one = false;
int test = 0;
Plateau::Plateau(se::Application& application) : myApplication(application),myPopTime(4000000),MAX_ENNEMI(15), myZikIndex(3)
{
    auto scene = application.getCurrentScene();

    scene->loadMusic(MUSIC[myZikIndex++%3]);
    scene->playMusic();
    myClock.restart();
    myJoueur = std::make_shared<Joueur>(application,*this);

    myApplication.getCurrentScene()->registerRenderable(myJoueur->myEntity);
    myApplication.getCurrentScene()->registerRenderable(myJoueur->myShadow);
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
    if(test == 4)
    {
        test = 0;
        float bulletPosX , bulletPosY = 0.f;

        float enemyPosX , enemyPosY = 0.f;

        auto scene = myApplication.getCurrentScene();
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

                                if(scene->getCurrentMusic().getStatus() != sf::Music::Stopped)
                                {
                                    scene->loadMusic(MUSIC[myZikIndex++%3]);
                                    scene->playMusic();
                                }
                            }

                            scene->addTemporaryParticleEntity(enemyPosX,enemyPosY,30,30,0,700000,EXPLOSIONS,EXPLOSION);
                            scene->addTemporarySoundEntity(EXPLOSION);
                            makeExplosion(b2Vec2(se::Utils::pixelsToMeters(ennemi->myEntity->getPosition().x),se::Utils::pixelsToMeters(ennemi->myEntity->getPosition().y)));
                        }
                        ++e;
                    }
                }
                if(bullet->owner == Bullet::ENNEMI&&myJoueur->collision(*bullet))
                {
                    bullet->unregister();
                    myJoueur->lowerHealth();

                    scene->addTemporaryParticleEntity(bulletPosX,bulletPosY,64,64,0,50000,HITS,HIT);
                    scene->addTemporarySoundEntity(IMPACT);

                }
                ++i;
            }

        }

        if(myClock.getElapsedTime().asMicroseconds()>=myPopTime&&myEnnemis.size()<MAX_ENNEMI)
            //if(!one)
        {
            one=true;
            myClock.restart();
            std::shared_ptr<Ennemi> newEnnemi = std::make_shared<Ennemi>(myApplication,*this);

            auto scene = myApplication.getCurrentScene();
            scene->registerRenderable(newEnnemi->myEntity);
            scene->registerRenderable(newEnnemi->myShadow);

            scene->registerRenderable(newEnnemi);
            myEnnemis.insert(newEnnemi);
        }
    }

    test++;
}
void Plateau::makeExplosion(const b2Vec2& center)
{
    for (int i = 0; i < 512; i++)
    {
        float angle = (i / 512.f) * 360 * 0.0174532925199432957f;
        b2Vec2 rayDir( sinf(angle), cosf(angle) );
        b2Vec2 rayEnd = center + 55.f * rayDir;

        //check what this ray hits
        se::RaycastNearestCallback callback;//basic callback to record body and hit point
        myApplication.getCurrentScene()->getPhysicWorld().RayCast(&callback, center, rayEnd);
        if ( callback.myBody != nullptr)
            se::Utils::applyBlastImpulse(callback.myBody, center, callback.myPoint, (0.05f / 512.f));
    }
}


void Plateau::interpolate(float interpolation)
{

}

bool Plateau::unregister() const
{
    return false;
}
unsigned int Plateau::renderingPosition() const
{
    return 0;
}
