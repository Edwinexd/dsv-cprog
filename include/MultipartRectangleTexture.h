#ifndef MULTIPARTRECTANGLETEXTURE_H
#define MULTIPARTRECTANGLETEXTURE_H
#include <Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <memory>
#include <Color.h>
#include <Session.h>

class MultipartRectangleTexture : public MultipartTexture
{
public:
    static std::shared_ptr<MultipartRectangleTexture> create_instance(std::shared_ptr<Session> session, int width, int height, Color color) {
        return std::shared_ptr<MultipartRectangleTexture>(new MultipartRectangleTexture(session, width, height, color));
    }
protected:
    MultipartRectangleTexture(std::shared_ptr<Session> session, int width, int height, Color color);
};



#endif