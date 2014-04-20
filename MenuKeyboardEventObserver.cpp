#include <MenuKeyboardEventObserver.hpp>
MenuKeyboardEventObserver::MenuKeyboardEventObserver() : currentSelectedItem(0)
{
    myMenuScene = std::make_shared<se::SceneSetImplementation>();

    items[0] = std::make_shared<MenuItem>("Start");

    myMenuScene->registerRenderable(items[0]);
    myMenuScene->registerRenderable(items[0]->myEntity);

    myMenu.addOption(items[0]->myOption);
    items[0]->selected=true;

    items[1] = std::make_shared<MenuItem>("Quit");

    items[1]->myEntity->setPosition(0,50);
    myMenuScene->registerRenderable(items[1]);
    myMenuScene->registerRenderable(items[1]->myEntity);

    myMenu.addOption(items[1]->myOption);


}
/** @brief notify
  *
  * @todo: document this function
  */
void MenuKeyboardEventObserver::notify(const se::Event& event)
{
    if(event.getSfEvent().type == sf::Event::KeyPressed)
    {
        if(event.getSfEvent().key.code == sf::Keyboard::Escape)
        {

            se::Application* app = se::Application::getInstance();
            if(myMenuIsOpen)
            {
                myMenuIsOpen = false;
                app->popScene();
            }
            else
            {
                myMenuIsOpen = true;
                app->pushScene(myMenuScene);
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
            items[currentSelectedItem]->selected = false;

            currentSelectedItem = (currentSelectedItem+1)%2;

            items[currentSelectedItem]->selected = true;
        }
    }
}
