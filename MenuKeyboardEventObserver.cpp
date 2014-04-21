#include <MenuKeyboardEventObserver.hpp>
MenuKeyboardEventObserver::MenuKeyboardEventObserver() : currentSelectedItem(1), firstShow(true)
{
    myMenuScene = std::make_shared<se::SceneSetImplementation>();

    sf::RenderWindow& window = se::GraphicEngine::getInstance()->getRenderWindow();

    std::shared_ptr<se::Entity> menuBg = std::make_shared<se::Entity>();
    menuBg->setOrigin(59,48);
    menuBg->setPosition(window.getSize().x/2, (window.getSize().y/2)-100);
    menuBg->makeDrawable("menubg");
    myMenuScene->registerRenderable(menuBg);

    items[0] = std::make_shared<MenuItem>("Tanks !");
    myMenuScene->registerRenderable(items[0]);
    myMenuScene->registerRenderable(items[0]->myEntity);
    items[0]->myEntity->setColor(sf::Color::Black);

    items[1] = std::make_shared<MenuItem>("Go");

    myMenuScene->registerRenderable(items[1]);
    myMenuScene->registerRenderable(items[1]->myEntity);

    items[1]->select();

    items[2] = std::make_shared<MenuItem>("Quit");

    myMenuScene->registerRenderable(items[2]);
    myMenuScene->registerRenderable(items[2]->myEntity);

    items[1]->myEntity->setOrigin(50,50);
    items[1]->myEntity->setPosition(window.getSize().x/2, window.getSize().y/2);

    items[2]->myEntity->setOrigin(50,50);
    items[2]->myEntity->setPosition(window.getSize().x/2, (window.getSize().y/2)+30);

    items[2]->myOption = std::make_shared<se::SimpleFunctorOption<std::function<void()> > >([]()
    {
        se::Application::getInstance()->stop();
    });
    items[1]->myOption = std::make_shared<se::SimpleFunctorOption<std::function<void()> > >([this]()
    {
        hideMenu();
    });

    myMenu.addOption(items[1]->myOption);
    myMenu.addOption(items[2]->myOption);
}
void MenuKeyboardEventObserver::showMenu()
{
    if(!myMenuIsOpen)
    {
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
            myMenu.scrollUp();
            items[currentSelectedItem]->unselect();

            currentSelectedItem = (currentSelectedItem+1)%3;

            if(currentSelectedItem == 0) currentSelectedItem++;

            items[currentSelectedItem]->select();
        }
    }
}
