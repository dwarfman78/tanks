#include <MenuKeyboardEventObserver.hpp>
MenuKeyboardEventObserver::MenuKeyboardEventObserver() : firstShow(true)
{
    init();
    myMenu.addOption(items[0]->myOption);
    myMenu.addOption(items[1]->myOption);
}
void MenuKeyboardEventObserver::init()
{
    items.clear();
    myMenuScene = std::make_shared<se::SceneVectorImplementation>();

    if(!firstShow)
    {
        addBackground();
    }
    addEffectMenuItem();
    addMenuTitle();
    addGoMenuItem();

    if(se::Application::getInstance()->isPaused())
    {
        addRestartMenuItem();
    }

    addQuitMenuItem();

    currentItem = items.begin();
}
/** @brief addBackground
  *
  * @todo: document this function
  */
void MenuKeyboardEventObserver::addBackground()
{
    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();
    std::shared_ptr<se::Entity> mainBg = std::make_shared<se::Entity>();
    mainBg->makeDrawable("menubg");
    bgTexture.create(window.getSize().x,window.getSize().y);
    bgTexture.update(window);
    mainBg->getContext().getDrawingContext().getSprite().setTexture(bgTexture,true);
    myMenuScene->registerRenderable(mainBg);
}

/** @brief addMenuTitle
  *
  * @todo: document this function
  */
void MenuKeyboardEventObserver::addMenuTitle()
{
    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();
    std::shared_ptr<se::Entity> menuBg = std::make_shared<se::Entity>();
    menuBg->setOrigin(59,48);
    menuBg->setPosition(window.getSize().x/2, (window.getSize().y/2)-100);
    menuBg->makeDrawable("menubg");
    myMenuScene->registerRenderable(menuBg);
}

/** @brief addGoMenuItem
  *
  * @todo: document this function
  */
void MenuKeyboardEventObserver::addGoMenuItem()
{
    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();
    items.push_back(std::make_shared<MenuItem>("Go"));

    myMenuScene->registerRenderable(items[0]);
    myMenuScene->registerRenderable(items[0]->myEntity);

    items[0]->myEntity->setOrigin(50,50);
    items[0]->myEntity->setPosition(window.getSize().x/2, window.getSize().y/2);
    items[0]->select();

    items[0]->myOption = std::make_shared<se::SimpleFunctorOption<std::function<void()> > >([this]()
    {
        hideMenu();
    });
}

/** @brief addRestartMenuItem
  *
  * @todo: document this function
  */
void MenuKeyboardEventObserver::addRestartMenuItem()
{

}

/** @brief addEffectMenuItem
  *
  * @todo: document this function
  */
void MenuKeyboardEventObserver::addEffectMenuItem()
{
    myMenuScene->registerRenderable(std::make_shared<Blur>());
}

/** @brief addQuitMenuItem
  *
  * @todo: document this function
  */
void MenuKeyboardEventObserver::addQuitMenuItem()
{
    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();
    items.push_back(std::make_shared<MenuItem>("Quit"));

    myMenuScene->registerRenderable(items[1]);
    myMenuScene->registerRenderable(items[1]->myEntity);

    items[1]->myEntity->setOrigin(50,50);
    items[1]->myEntity->setPosition(window.getSize().x/2, (window.getSize().y/2)+30);

    items[1]->myOption = std::make_shared<se::SimpleFunctorOption<std::function<void()> > >([]()
    {
        se::Application::getInstance()->stop();
    });
}

void MenuKeyboardEventObserver::showMenu()
{
    if(!myMenuIsOpen)
    {
        init();
        myMenuIsOpen = true;

        se::Application::getInstance()->pushScene(myMenuScene);
    }

}
void MenuKeyboardEventObserver::hideMenu()
{
    if(myMenuIsOpen)
    {
        firstShow = false;
        myMenuIsOpen = false;
        se::Application::getInstance()->popScene();
    }

}
/** @brief notify
  *
  * @todo: document this function
  */
void MenuKeyboardEventObserver::notify(const se::Event& event)
{
    if(event.getSfEvent().type == sf::Event::KeyPressed)
    {
        if(event.getSfEvent().key.code == sf::Keyboard::Escape && !firstShow)
        {
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
