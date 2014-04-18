#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Core/Entity.hpp>
#include <SimpleEngine/ToolBox/Logger.hpp>
#include <SimpleEngine/myImports.hpp>

#include <StopObserver.hpp>
#include <KeyboardObserver.hpp>
#include <Plateau.hpp>
#if defined(SYSTEM_WINDOWS)
#include <windows.h>
#endif // defined

using namespace std;
using namespace se;

#if defined(SYSTEM_WINDOWS)
int WINAPI WinMain ( HINSTANCE, HINSTANCE, LPSTR, int )
#else
int main()
#endif // defined
{
    //Logger log("Main::Main");

    Application* a = Application::getInstance();

    a->setBackground("medias/img/background.bmp");

    sf::Image imageIcon;

    sf::RenderWindow& window = GraphicEngine::getInstance()->getRenderWindow();

    if(imageIcon.loadFromFile("medias/icon.bmp"))
    {
        window.setIcon(32,32,imageIcon.getPixelsPtr());
    }
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();

    window.setPosition(sf::Vector2i(mode.width/4, mode.height/4));

    Plateau p(*a);

    StopObserver so;

    a->registerObserver(std::shared_ptr<Observer>(&so));

    KeyboardObserver ko;

    a->registerObserver(std::shared_ptr<Observer>(&ko));

    a->start();

    //log.append();

    return 0;
}
