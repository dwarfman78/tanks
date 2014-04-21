#ifndef MenuItem_hpp
#define MenuItem_hpp
#include <SimpleEngine/Core/Renderable.hpp>
#include <SimpleEngine/Gui/Option.hpp>
#include <SimpleEngine/Core/Entity.hpp>
class MenuItem : public se::Renderable
{
    public:
        MenuItem(const std::string& label);
        virtual ~MenuItem();
        void render();
        void renderLogic();
        void interpolate(const float interpolation);
        bool unregister()  const ;
        bool selected;
        std::shared_ptr<se::Entity> myEntity;
        std::shared_ptr<se::Option> myOption;
};
#endif // MenuItem_hpp
