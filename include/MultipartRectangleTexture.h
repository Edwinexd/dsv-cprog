#ifndef MULTIPARTRECTANGLETEXTURE_H
#define MULTIPARTRECTANGLETEXTURE_H
#include <Component.h>
#include <MultipartTexture.h>
#include <SDL2/SDL.h>
#include <memory>
#include <Color.h>
#include <Session.h>

// Spelmotorklass - En rektangulär textur med en viss färg för MultipartComponent
class MultipartRectangleTexture : public MultipartTexture
{
public:
    static std::shared_ptr<MultipartRectangleTexture> create_instance(std::shared_ptr<Session> session, int width, int height, Color color);
protected:
    MultipartRectangleTexture(std::shared_ptr<Session> session, int width, int height, Color color);
};



#endif