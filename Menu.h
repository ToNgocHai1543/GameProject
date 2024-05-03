#ifndef Menu_H_
#define Menu_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Menu_object.h"
#include "Mouse.h"

class Menu : BaseObject
{
private:
    TextObject play_game;
    TextObject exit_;
    TextObject difficult_;
    TextObject how_;

    SDL_Rect frame_clip_[0];
    //Mouse m_;
public:
    Menu();
    int ShowMenu(std:: string t_play, std::string t_exit,std::string t_difficult, std::string t_how, SDL_Renderer* screen );
    bool Load_Button(std:: string path, SDL_Renderer* screen);
    void Show_Button(SDL_Renderer* des,std:: string path, int button_x ,int button_y);
};

#endif // Menu_H_
