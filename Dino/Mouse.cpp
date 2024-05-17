#include "Mouse.h"
#include "stdafx.h"
Mouse::Mouse()
{

}

Mouse::~Mouse()
{

}
bool Mouse::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    return ret;
}
void Mouse::Show(SDL_Renderer* des)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    LoadImg("asset//mouse.png", des);
    rect_.x = mouse_x;
    rect_.y = mouse_y;

    frame_clip_[0].x = 0;
    frame_clip_[0].y = 0;
    frame_clip_[0].w = rect_.w;
    frame_clip_[0].h = rect_.h;
    SDL_Rect* current_clip = &frame_clip_[0];
    SDL_Rect renderQuad = {mouse_x, mouse_y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}
