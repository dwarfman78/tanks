#include <Ennemi.hpp>
//int cpt2=1;
Ennemi::Ennemi(se::Application& application, Plateau& p) :
    unregistered(false),
    myPlateau(p),
    myApplication(application),
    gen(time(NULL)),
    dis(10,30)
{
    initEntity(application);
}
Ennemi::~Ennemi()
{

}
void Ennemi::initGraphics()
{
    myEntity->makeDrawable(MEDIA);

    myShadow->makeDrawable(SHADOW);

    myEntity->makeAnimable(STOP);

}
void Ennemi::initCaracteristics()
{

    se::Config* conf = se::Config::getInstance();

    int vitesseMin, vitesseMax = 1;

    if(conf->get(MIN_SPEED,vitesseMin)&&conf->get(MAX_SPEED,vitesseMax))
    {
        std::uniform_int_distribution<> dis(vitesseMin,vitesseMax);

        speed.x = static_cast<float>(dis(gen));
        speed.y = static_cast<float>(dis(gen));
    }
    else
    {
        speed.x = static_cast<float>(dis(gen));
        speed.y = static_cast<float>(dis(gen));
    }

    nspeed = se::Utils::norm(speed);

    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();

    std::uniform_int_distribution<> disMod(0,3);
    std::uniform_int_distribution<> varMod(0,100);

    float startX = 0;
    float startY = 0;
    int varPart = varMod(gen);

    switch(disMod(gen))
    {
    case 0 :
        startX = varPart;
        startY = -varPart;
        break;
    case 1 :
        startX = window.getSize().x + varPart;
        startY = varPart;
        break;
    case 2 :
        startX = window.getSize().x + varPart;
        startY = window.getSize().y + varPart;
        break;
    case 3 :
        startX = -varPart;
        startY = window.getSize().y +varPart;
        break;
    default :
        ;
        break;
    }

    myEntity->setPosition(startX,startY);

    myEntity->setOrigin(SIZE,SIZE);

    myShadow->setOrigin(SIZE,SIZE);


}
void Ennemi::initEntity(se::Application& application)
{
    myEntity = std::make_shared<se::Entity>();
    myEntity->setRenderingPosition(1);
    myShadow = std::make_shared<se::Entity>();
    initGraphics();
    initCaracteristics();

}

void Ennemi::render()
{

}
void Ennemi::defVectVitesse()
{
    sf::Vector3f pos3f = myEntity->getPosition();

    sf::Vector2f pos;
    pos.x = pos3f.x;
    pos.y = pos3f.y;

    sf::Vector3f pos3fJoueur = myPlateau.myJoueur->myEntity->getPosition();
    sf::Vector2f jPos;
    jPos.x = pos3fJoueur.x;
    jPos.y = pos3fJoueur.y;

    jPos += sf::Vector2f(myPlateau.myJoueur->speed.x*4,myPlateau.myJoueur->speed.y*4);

    sf::Vector2f diffPos = jPos-pos;

    float norm = se::Utils::norm(diffPos);
    speed.x = ((diffPos.x * nspeed ) / norm);
    speed.y = ((diffPos.y * nspeed ) / norm);
}
void Ennemi::defRotation()
{
    sf::Vector2f abscisse(1,0);
    float rotationDeg = se::Utils::radsToDeg(se::Utils::getOrientedAngle(speed,abscisse));

    if(se::Utils::det(speed,abscisse)>0)
        rotationDeg*=-1;

    myEntity->setRotation(rotationDeg);
    myShadow->setRotation(rotationDeg);
}
bool Ennemi::collision(Bullet& bullet)
{
    float entityPosX = myEntity->getPosition().x;
    float entityPosY = myEntity->getPosition().y;

    float bulletPosX = bullet.myEntity->getPosition().x;
    float bulletPosY = bullet.myEntity->getPosition().y;

    return sf::FloatRect(entityPosX-16,entityPosY-16,32,32).contains(bulletPosX,bulletPosY);

}
void Ennemi::unregister()
{
    unregistered = true;
    myEntity->getContext().unregister();
    myShadow->getContext().unregister();
}
void Ennemi::tirer()
{
    std::shared_ptr<Bullet> newBullet = std::make_shared<Bullet>(myApplication,myEntity->getSprite().getRotation(),myEntity->getPosition().x,myEntity->getPosition().y,Bullet::ENNEMI);

    myPlateau.getMyBullets().insert(newBullet);

    std::shared_ptr<se::Scene> scene = myApplication.getCurrentScene();

    scene->registerRenderable(newBullet->myEntity);
    scene->registerRenderable(newBullet);

    scene->addTemporaryParticleEntity(myEntity->getPosition().x+speed.x*3,myEntity->getPosition().y+speed.y*3,110,40,myEntity->getSprite().getRotation()+180,900000,SMOKES,FIRESMOKE);
    scene->addTemporaryParticleEntity(myEntity->getPosition().x+speed.x*3,myEntity->getPosition().y+speed.y*3,70,40,myEntity->getSprite().getRotation()-90,200000,MUZZLES,MUZZLE);

    auto shellEntity = scene->addTemporaryPhysicParticle(myEntity->getPosition().x,myEntity->getPosition().y,7.5,1.5,0,5000000,SHELL,SHELL);

    auto body = shellEntity->getContext().getPhysicContext().getBody();

    b2FrictionJointDef jd;

    jd.bodyA = body;
    jd.bodyB = myApplication.getCurrentScene()->getGround();
    jd.maxForce = 0.005;
    jd.maxTorque = 0.00001f;

    myApplication.getCurrentScene()->getPhysicWorld().CreateJoint(&jd);

    body->ApplyForceToCenter(b2Vec2(-speed.x/20,0.0),true);

    float tork = dis(gen)/10000.f;

    body->ApplyTorque(tork,true);

    scene->addTemporarySoundEntity(TIRER);
}
bool Ennemi::unregister() const
{
    return unregistered;
}
void Ennemi::renderLogic()
{
    if(myBrainTick.getElapsedTime().asMilliseconds()>200)
    {
        myBrainTick.restart();

        tirer();

        if(speed.x!=0||speed.y!=0)
            myApplication.getCurrentScene()->addTemporaryParticleEntity(myEntity->getPosition().x+speed.x*-3,myEntity->getPosition().y+speed.y*-3,16,16,myEntity->getSprite().getRotation()-90,5000000,"trails","trail");
    }
    if(!collision())
    {
        defVectVitesse();

        myEntity->makeAnimable(RUN);
        myEntity->setPosition(myEntity->getPosition().x+(speed.x*(myInterpolation)),
                              myEntity->getPosition().y+(speed.y*(myInterpolation)));

        myShadow->setPosition(myEntity->getPosition().x, myEntity->getPosition().y);

        defRotation();
    }
    else
    {
        speed.x = speed.y = 0;
        myEntity->makeAnimable(STOP);
    }
}

void Ennemi::interpolate(float interpolation)
{
    myInterpolation = interpolation;
}

bool Ennemi::collision()
{
    //collision avec les bords de l'écran.
    sf::Vector3f position = sf::Vector3f(myEntity->getPosition());

    position.x += speed.x*myInterpolation;
    position.y += speed.y*myInterpolation;

    sf::Vector2f joueurPos = myPlateau.myJoueur->myEntity->getSprite().getPosition();

    sf::FloatRect recJoueur = sf::FloatRect(joueurPos.x-32,joueurPos.y-32,64,64);

    return recJoueur.contains(position.x,position.y);
}
unsigned int Ennemi::renderingPosition() const
{
    return 1;
}
