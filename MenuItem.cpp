#include <MenuItem.hpp>
#include <SimpleEngine/Gui/SimpleFunctorOption.hpp>
/** @brief MenuItem
  *
  * @todo: document this function
  */
MenuItem::MenuItem(const std::string& label) : selected(false), myLabel(label), redIndex(5), sens(5)
{
    myEntity = std::make_shared<se::Entity>();

    myEntity->makeWritable(myLabel);

    unselect();

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
void MenuItem::select()
{
    //myEntity->makeWritable(">" + myLabel);
    selected = true;
    redIndex = 5;
}
void MenuItem::unselect()
{
    //myEntity->makeWritable(" " + myLabel);
    selected = false;
}

/** @brief renderLogic
  *
  * @todo: document this function
  */
void MenuItem::renderLogic()
{
    if(selected)
    {
        myEntity->setColor(sf::Color(redIndex,0,0));

        if(redIndex == 255 || redIndex == 0)
        {
            sens *= -1;
        }
        redIndex = ( redIndex + sens );
    }
    else
    {
        myEntity->setColor(sf::Color::Black);
    }
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



