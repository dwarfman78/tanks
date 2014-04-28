#ifndef MenuKeyboardEventObserver_hpp
#define MenuKeyboardEventObserver_hpp
#include <SimpleEngine/Core/Observer.hpp>
#include <SimpleEngine/Core/Scene.hpp>
#include <SimpleEngine/Core/Impl/SceneVectorImplementation.hpp>
#include <SimpleEngine/Gui/SimpleFunctorOption.hpp>
#include <SimpleEngine/Core/Application.hpp>
#include <SimpleEngine/Gui/Menu.hpp>
#include <MenuItem.hpp>
#include <Blur.hpp>
#include <SFML/Graphics.hpp>
#include <Plateau.hpp>
class MenuKeyboardEventObserver : public se::Observer
{
    public:
        MenuKeyboardEventObserver();
        void notify(const se::Event& event);
        void showMenu();
        void hideMenu();
        void init();
    private:

        void addGoMenuItem();
        void addRestartMenuItem();
        void addEffectMenuItem();
        void addBackground();
        void addMenuTitle();
        void addQuitMenuItem();

        std::shared_ptr<se::Scene> myMenuScene;
        se::Menu myMenu;
        bool myMenuIsOpen;
        std::vector<std::shared_ptr<MenuItem> > items;
        std::vector<std::shared_ptr<MenuItem> >::iterator currentItem;
        bool firstShow;
        sf::Texture bgTexture;
};
#endif // MenuKeyboardEventObserver_hpp
