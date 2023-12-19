#ifndef MULTIPARTRECTANGLETEXTURE_H
#define MULTIPARTRECTANGLETEXTURE_H
#include <Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <memory>
#include <Color.h>

class MultipartRectangleTexture : public MultipartTexture
{
public:
    static std::shared_ptr<MultipartRectangleTexture> createInstance(int width, int height, Color color) {
        return std::shared_ptr<MultipartRectangleTexture>(new MultipartRectangleTexture(width, height, color));
    }
protected:
    MultipartRectangleTexture(int width, int height, Color color);
};



#endif