#include <MenuKeyboardEventObserver.hpp>
MenuKeyboardEventObserver::MenuKeyboardEventObserver() : firstShow(true)
{
    init();
}
void MenuKeyboardEventObserver::init()
{
    items.clear();

    myMenu.clearOptions();

    myMenuScene = std::make_shared<se::SceneSetImplementation>();

    se::Application* app = se::Application::getInstance();


    if(!firstShow)
    {
        addBackground();
    }
    addEffectMenuItem();
    addMenuTitle();

    if(app->isPaused())
    {
        firstShow = true;
        addRestartMenuItem();
        app->unpause();
    }
    else
    {
        addGoMenuItem();
    }
    addQuitMenuItem();
    currentItem = items.begin();
}

void MenuKeyboardEventObserver::addBackground()
{
    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();
    std::shared_ptr<se::Entity> mainBg = std::make_shared<se::Entity>();
    mainBg->makeDrawable("menubg");
    bgTexture.create(window.getSize().x,window.getSize().y);
    bgTexture.update(window);
    mainBg->getContext().getDrawingContext().getSprite().setTexture(bgTexture,true);
    mainBg->setRenderingPosition(0);
    myMenuScene->registerRenderable(mainBg);
}

void MenuKeyboardEventObserver::addMenuTitle()
{
    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();
    std::shared_ptr<se::Entity> menuBg = std::make_shared<se::Entity>();
    menuBg->setOrigin(59,48);
    menuBg->setPosition(window.getSize().x/2, (window.getSize().y/2)-100);
    menuBg->makeDrawable("menubg");
    menuBg->setRenderingPosition(2);
    myMenuScene->registerRenderable(menuBg);
}

void MenuKeyboardEventObserver::addGoMenuItem()
{
    sf::Vector2u windowSize = se::GraphicEngine::getInstance()->getRenderWindow().getSize();

    insertMenuItem(true,
                   "Play",
                   3,
                   30,
                   30,
                   windowSize.x/2,
                   windowSize.y/2,
                   std::make_shared<se::SimpleFunctorOption<std::function<void()> > >([this]()
    {
        hideMenu();
    })
                  );
}

void MenuKeyboardEventObserver::insertMenuItem(bool select, const std::string& content, unsigned int renderingPos, float oriX, float oriY, float posX, float posY, std::shared_ptr<se::Option> action)
{
    auto menuItem = std::make_shared<MenuItem>(content);

    menuItem->myEntity->setRenderingPosition(3);

    myMenuScene->registerRenderable(menuItem);
    myMenuScene->registerRenderable(menuItem->myEntity);

    menuItem->myEntity->setOrigin(oriX,oriY);
    menuItem->myEntity->setPosition(posX, posY);

    if(select)
        menuItem->select();

    menuItem->myOption = action;

    items.push_back(menuItem);
    myMenu.addOption(menuItem->myOption);
}

void MenuKeyboardEventObserver::addRestartMenuItem()
{
    sf::Vector2u windowSize = se::GraphicEngine::getInstance()->getRenderWindow().getSize();

    insertMenuItem(true,
                   "Restart",
                   3,
                   50,
                   30,
                   windowSize.x/2,
                   windowSize.y/2,
                   std::make_shared<se::SimpleFunctorOption<std::function<void()> > >([this]()
    {
        hideMenu();
        se::Application* a = se::Application::getInstance();
        a->reset();
        std::shared_ptr<Plateau> p = std::make_shared<Plateau>(*a);
        a->getCurrentScene()->registerRenderable(p);
    }));


}

void MenuKeyboardEventObserver::addEffectMenuItem()
{
    myMenuScene->registerRenderable(std::make_shared<Blur>());
}

void MenuKeyboardEventObserver::addQuitMenuItem()
{
    sf::Vector2u windowSize = se::GraphicEngine::getInstance()->getRenderWindow().getSize();

    insertMenuItem(false,
                   "Quit",
                   3,
                   30,
                   30,
                   windowSize.x/2,
                   windowSize.y/2+30,
                   std::make_shared<se::SimpleFunctorOption<std::function<void()> > >([this]()
    {
        se::Application::getInstance()->stop();
    }));
}

void MenuKeyboardEventObserver::showMenu()
{
    if(!myMenuIsOpen)
    {
        se::Application* app = se::Application::getInstance();
        init();
        myMenuIsOpen = true;

        app->getCurrentScene()->pauseMusic();

        myMenuScene->loadMusic("medias/snd/menu.ogg");
        myMenuScene->playMusic();
        app->pushScene(myMenuScene);
    }

}
void MenuKeyboardEventObserver::hideMenu()
{
    if(myMenuIsOpen)
    {
        se::Application* app = se::Application::getInstance();
        firstShow = false;
        myMenuIsOpen = false;
        myMenuScene->pauseMusic();
        app->popScene();
        app->getCurrentScene()->playMusic();
    }

}

void MenuKeyboardEventObserver::notify(const se::Event& event)
{
    if(event.getSfEvent().type == sf::Event::KeyPressed)
    {
        if(event.getSfEvent().key.code == sf::Keyboard::Escape && !firstShow)
        {
            se::Application* app = se::Application::getInstance();
            if(app->isPaused())
            {
                app->reset();
            }
            if(myMenuIsOpen)
            {
                hideMenu();

            }
            else
            {
                showMenu();
            }

        }
        else if(event.getSfEvent().key.code == sf::Keyboard::Return)
        {
            if(myMenuIsOpen)
            {
                myMenu.getCurrentOption()->execute();
            }

        }
        else if(event.getSfEvent().key.code == sf::Keyboard::Down)
        {

            (*currentItem)->unselect();

            if(currentItem+1 != items.end())
            {
                currentItem++;
                myMenu.scrollUp();
            }

            (*currentItem)->select();

        }
        else if(event.getSfEvent().key.code == sf::Keyboard::Up)
        {

            (*currentItem)->unselect();

            if(currentItem!=items.begin())
            {
                myMenu.scrollDown();
                currentItem--;
            }

            (*currentItem)->select();
        }
    }
}
