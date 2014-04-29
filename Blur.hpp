#ifndef Blur_hpp
#define Blur_hpp
#include <SimpleEngine/Graphic/GraphicEngine.hpp>
#include <SimpleEngine/Core/Renderable.hpp>
class Blur : public se::Renderable
{
public:
    void render();
    void renderLogic();
    void interpolate(const float interpolation);
    bool unregister()  const ;
private:
    const std::string SHADERPATH = "medias/fx/pixelate.frag";
};
#endif // Blur_hpp
