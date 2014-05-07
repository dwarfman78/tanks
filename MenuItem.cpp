#include <MenuItem.hpp>
#include <SimpleEngine/Gui/SimpleFunctorOption.hpp>

MenuItem::MenuItem(const std::string& label) : selected(false), myLabel(label), redIndex(5), sens(5)
{
    myEntity = std::make_shared<se::Entity>();

    myEntity->makeWritable(myLabel);

    unselect();
}

MenuItem::~MenuItem()
{

}

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

void MenuItem::interpolate(const float interpolation)
{

}

bool MenuItem::unregister() const
{
    return false;
}
