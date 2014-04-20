#include <MenuItem.hpp>
#include <SimpleEngine/Gui/SimpleFunctorOption.hpp>
/** @brief MenuItem
  *
  * @todo: document this function
  */
MenuItem::MenuItem(const std::string& label) : selected(false)
{
    myEntity = std::make_shared<se::Entity>();

    myEntity->makeWritable(label);

    myOption = std::make_shared<se::SimpleFunctorOption<std::function<void()> > >([label](){std::cout<<label<<std::endl;});

}

/** @brief ~MenuItem
  *
  * @todo: document this function
  */
MenuItem::~MenuItem()
{

}

/** @brief render
  *
  * @todo: document this function
  */
void MenuItem::render()
{
}

/** @brief renderLogic
  *
  * @todo: document this function
  */
void MenuItem::renderLogic()
{
    if(selected)
        myEntity->setColor(sf::Color::Red);
    else
        myEntity->setColor(sf::Color::White);
}

/** @brief interpolate
  *
  * @todo: document this function
  */
void MenuItem::interpolate(const float interpolation)
{

}

/** @brief unregister
  *
  * @todo: document this function
  */
bool MenuItem::unregister() const
{
    return false;
}



