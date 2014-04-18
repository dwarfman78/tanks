#ifndef StopObserver_hpp
#define StopObserver_hpp

#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Event.hpp>

class StopObserver : public se::Observer
{
public:
    void notify(const se::Event& event)
    {
        if(event.getSfEvent().type == sf::Event::Closed)
            se::Application::getInstance()->stop();
    }
};
#endif // StopObserver_hpp
