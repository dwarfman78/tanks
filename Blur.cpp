#include <Blur.hpp>
/** @brief render
  *
  * @todo: document this function
  */
void Blur::render()
{
    se::GraphicEngine::getInstance()->applyShader(SHADERPATH);
}

/** @brief renderLogic
  *
  * @todo: document this function
  */
void Blur::renderLogic()
{

}

/** @brief interpolate
  *
  * @todo: document this function
  */
void Blur::interpolate(const float interpolation)
{

}

/** @brief unregister
  *
  * @todo: document this function
  */
bool Blur::unregister() const
{
return false;
}
unsigned int Blur::renderingPosition() const
{
    return 1;
}

