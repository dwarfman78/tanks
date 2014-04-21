#ifndef MenuKeyboardEventObserver_hpp
#define MenuKeyboardEventObserver_hpp
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Scene.hpp>
#include <SimpleEngine/Core/Impl/SceneSetImplementation.hpp>
#include <SimpleEngine/Gui/SimpleFunctorOption.hpp>
#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Gui/Menu.hpp>
#include <MenuItem.hpp>
class MenuKeyboardEventObserver : public se::Observer
{
    public:
        MenuKeyboardEventObserver();
        void notify(const se::Event& event);
        void showMenu();
        void hideMenu();
    private:
        std::shared_ptr<se::Scene> myMenuScene;
        se::Menu myMenu;
        bool myMenuIsOpen;
        std::shared_ptr<MenuItem> items [3];
        unsigned int currentSelectedItem;
        bool firstShow;
};
#endif // MenuKeyboardEventObserver_hpp
