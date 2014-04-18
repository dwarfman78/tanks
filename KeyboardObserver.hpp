#ifndef KeyboardObserver_hpp
#define KeyboardObserver_hpp

#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Event.hpp>

class KeyboardObserver : public se::Observer
{
public:
    KeyboardObserver() : paused(false){;}
    void notify(const se::Event& event)
    {
        if(event.getSfEvent().type == sf::Event::KeyPressed && event.getSfEvent().key.code == sf::Keyboard::M)
        {
            if(!paused)
            {
                se::Application::getInstance()->pauseMusic();
            }
            else
            {
                se::Application::getInstance()->playMusic();
            }
            paused = ! paused;

        }

    }
private:
bool paused;
};
#endif // KeyboardObserver_hpp
