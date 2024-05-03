#ifndef MOUSE_H_
#define MOUSE_H_

#include "BaseObject.h"
#include "CommonFunc.h"

class Mouse : public BaseObject
{
public:
    Mouse();
    ~Mouse();

    bool LoadImg(std:: string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
private:
    SDL_Rect frame_clip_[0];
};

#endif // MOUSE_H_
