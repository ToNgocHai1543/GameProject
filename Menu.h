#ifndef Menu_H_
#define Menu_H_
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Menu_object.h"

class Menu : BaseObject
{
private:
    TextObject play_game;
    TextObject exit_;
    TextObject difficult_;
    TextObject how_;

    TextObject _how_;

    TextObject easy_;
    TextObject normal_;
    TextObject hard_;

    TextObject play_agian;
    TextObject quit;

    TextObject resume_;
    TextObject pau_quit;
    SDL_Rect frame_clip_[0];

public:
    Menu();
    int ShowMenu(std:: string t_play, std::string t_exit,std::string t_difficult, std::string t_how,
                  SDL_Renderer* screen, Mix_Chunk* g_sound_character[10] );
    bool Load_Button(std:: string path, SDL_Renderer* screen);
    void Show_Button(SDL_Renderer* des,std:: string path, int button_x ,int button_y);
    int Show_Option(SDL_Renderer* screen, std:: string t_play_again, std::string t_exit, Mix_Chunk* g_sound_character[10]);
    int Show_Pause(SDL_Renderer* screen, std:: string t_resume, std::string t_quit, Mix_Chunk* g_sound_character[10]);
    int Show_How (SDL_Renderer* screen, std:: string t_how_, Mix_Chunk* g_sound_character[10]);
    int Show_Difficult (SDL_Renderer* screen, std:: string easy, std::string normal, std:: string hard, Mix_Chunk* g_sound_character[10]);
    //bool mute;
};

#endif // Menu_H_
