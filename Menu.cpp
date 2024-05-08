#include "Menu.h"
#include "iostream"

Menu::Menu()
{

}
bool Menu::Load_Button(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    return ret;
}
void Menu::Show_Button(SDL_Renderer* des, std::string path, int button_x, int button_y)
{
    LoadImg(path, des);
    rect_.x = button_x;
    rect_.y = button_y;

    frame_clip_[0].x = 0;
    frame_clip_[0].y = 0;
    frame_clip_[0].w = rect_.w;
    frame_clip_[0].h = rect_.h;
    SDL_Rect* current_clip = &frame_clip_[0];
    SDL_Rect renderQuad = {button_x, button_y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}
int Menu::Show_Difficult (SDL_Renderer* screen, std:: string easy, std::string normal,
                           std:: string hard, Mix_Chunk* g_sound_character[10])
{
    TTF_Font* font_menu = TTF_OpenFont("FFF_Tusj.ttf", 27);
    Show_Button(screen,"asset//menu//Menu_game.jpg", 0, 0);
    //Show_Button(screen,"asset//menu//menu_how.png", 340, 80);
    Show_Button(screen,"asset//Button//Button_1.png", 555, 100);
    Show_Button(screen,"asset//Button//Button_1.png", 555, 250);
    Show_Button(screen,"asset//Button//Button_1.png", 555, 400);
    easy_.SetText(easy);
    easy_.LoadFromRenderText(font_menu, screen);
    normal_.SetText(normal);
    normal_.LoadFromRenderText(font_menu, screen);
    hard_.SetText(hard);
    hard_.LoadFromRenderText(font_menu, screen);
    int x = 0;
    int y = 0;
    while(1)
    {
        easy_.RenderText(screen, 610, 130);
        normal_.RenderText(screen, 595, 280);
        hard_.RenderText(screen, 610, 430);
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEMOTION:
                x = g_event.motion.x;
                y = g_event.motion.y;
                if(x >= 555 && x <= 760 && y >= 100 && y<= 200){
                    Show_Button(screen,"asset//Button//Button_1_2.png", 555, 100);
                }
                else if(x >= 555 && x <= 760 && y >= 250 && y<= 350){
                    Show_Button(screen,"asset//Button//Button_1_2.png", 555, 250);
                }
                else if(x >= 555 && x <= 760 && y >= 400 && y<= 500){
                    Show_Button(screen,"asset//Button//Button_1_2.png", 555, 400);
                }
                else{
                    Show_Button(screen,"asset//Button//Button_1.png", 555, 100);
                    Show_Button(screen,"asset//Button//Button_1.png", 555, 250);
                    Show_Button(screen,"asset//Button//Button_1.png", 555, 400);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = g_event.button.x;
                y = g_event.button.y;
                Mix_PlayChannel(-1, g_sound_character[6], 0);
                if(x >= 555 && x <= 760 && y >= 100 && y<= 200){
                    BaseObject::Free();
                    return 0;
                }
                if(x >= 555 && x <= 760 && y >= 250 && y<= 350){
                    BaseObject::Free();
                    return 0;
                }
                 if(x >= 555 && x <= 760 && y >= 400 && y<= 500){
                    BaseObject::Free();
                    return 0;
                }
                break;
            }
        }
        SDL_RenderPresent(screen);
    }
}
int Menu::Show_How(SDL_Renderer* screen, std:: string t_how_, Mix_Chunk* g_sound_character[10])
{
    TTF_Font* font_menu = TTF_OpenFont("FFF_Tusj.ttf", 27);
    Show_Button(screen,"asset//menu//Menu_game_1.jpg", 0, 0);
    Show_Button(screen,"asset//Button//Button_1.png", 555, 505);
    _how_.SetText(t_how_);
    _how_.LoadFromRenderText(font_menu, screen);
    int x = 0;
    int y = 0;
    while(1)
    {
        _how_.RenderText(screen, 610, 535);
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEMOTION:
                x = g_event.motion.x;
                y = g_event.motion.y;
                if(x >= 555 && x <= 760 && y >= 505 && y<= 605){
                    Show_Button(screen,"asset//Button//Button_1_2.png", 555, 505);
                }
                else{
                    Show_Button(screen,"asset//Button//Button_1.png", 555, 505);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = g_event.button.x;
                y = g_event.button.y;
                Mix_PlayChannel(-1, g_sound_character[6], 0);
                if(x >= 555 && x <= 760 && y >= 505 && y<= 605){
                    BaseObject::Free();
                    return 0;
                }
                break;
            }
        }
        SDL_RenderPresent(screen);
    }
}

int Menu::ShowMenu(std:: string t_play, std::string t_exit,std::string t_difficult, std::string t_how,
                    SDL_Renderer* screen, Mix_Chunk* g_sound_character[10])
{
    TTF_Font* font_menu = TTF_OpenFont("FFF_Tusj.ttf", 27);
    //bool ret = BaseObject::LoadImg("asset//menu//Menu_game.jpg", screen);
    Show_Button(screen,"asset//menu//Main_menu.png", 0 ,0);
    Show_Button(screen,"asset//Button//Button_1.png", 300, 200);
    Show_Button(screen,"asset//Button//Button_1.png", 300, 350);
    Show_Button(screen,"asset//Button//Button_1.png", 555, 200);
    Show_Button(screen,"asset//Button//Button_1.png", 555, 350);
    Show_Button(screen,"asset//Button//Button_7.png", 1200, 550);
    play_game.SetText(t_play);
    play_game.LoadFromRenderText(font_menu, screen);
    exit_.SetText(t_exit);
    exit_.LoadFromRenderText(font_menu, screen);
    difficult_.SetText(t_difficult);
    difficult_.LoadFromRenderText(font_menu, screen);
    how_.SetText(t_how);
    how_.LoadFromRenderText(font_menu, screen);
    BaseObject::Render(screen, NULL);
    int x=0;
    int y=0;
    while(1)
    {
        play_game.RenderText(screen, 320, 230);
        exit_.RenderText(screen, 350, 380);
        difficult_.RenderText(screen, 610, 230);
        how_.RenderText(screen, 615, 380);
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEMOTION:
                x = g_event.motion.x;
                y = g_event.motion.y;
                //std::cerr<< "x " << x << std::endl;
                //std::cerr<< "y " << y << std::endl;
                if(x>=300 && x<=505 && y >= 200 && y<= 300){
                    //play_game.SetColor(255, 255, 0);
                    Show_Button(screen,"asset//Button//Button_1_2.png", 300, 200);
                }
                else if(x>= 300 && x <= 505 && y >= 350 && y <= 450){
                    //exit_.SetColor(255, 255, 0);
                    Show_Button(screen,"asset//Button//Button_1_2.png", 300, 350);
                }
                else if(x>= 555 && x <= 755 && y >= 350 && y <= 450){
                    //how_.SetColor(255, 255, 0);
                    Show_Button(screen,"asset//Button//Button_1_2.png", 555, 350);
                }
                else if(x>= 555 && x <= 755 && y >= 200 && y <= 300){
                    //difficult_.SetColor(255, 255, 0);
                    Show_Button(screen,"asset//Button//Button_1_2.png", 555, 200);
                }
                else{
                    //play_game.SetColor(TextObject::RED_TEXT);
                    Show_Button(screen,"asset//Button//Button_1.png", 300, 200);
                    //exit_.SetColor(255, 0 ,0);
                    Show_Button(screen,"asset//Button//Button_1.png", 300, 350);
                    //difficult_.SetColor(255, 0 ,0);
                    Show_Button(screen,"asset//Button//Button_1.png", 555, 200);
                    //how_.SetColor(255, 0 ,0);
                    Show_Button(screen,"asset//Button//Button_1.png", 555, 350);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = g_event.button.x;
                y = g_event.button.y;
                Mix_PlayChannel(-1, g_sound_character[6], 0);
                if(x>= 300 && x <= 505 && y >= 350 && y <= 450){
                    BaseObject::Free();
                    //exit
                    return -1;
                }
                if(x>=300 && x<=505 && y >= 200 && y <= 300){
                    BaseObject::Free();
                    //play_game
                    return 1;
                }
                if(x>= 555 && x <= 755 && y >= 200 && y <= 300){
                    //difficult
                    return 3;
                    BaseObject::Free();
                }
                if (x>= 555 && x <= 755 && y >= 350 && y <= 450)
                {
                    // how
                    return 2;
                    BaseObject::Free();
                }
                if(x >= 1200 && x <= 1275 && y >= 550 && y <= 625){
                    //mute
                    mute = !mute;
                    if(mute == false)
                    {
                        Show_Button(screen,"asset//Button//Button_7.png", 1200, 550);
                        Mix_Resume(-1);
                        Mix_ResumeMusic();
                    }
                    else if (mute == true)
                    {
                        Show_Button(screen,"asset//Button//Button_7_2.png", 1200, 550);
                        Mix_Pause(-1);
                        Mix_PauseMusic();//Mix_HaltMusic();
                    }
                    BaseObject::Free();
                }
                break;
            }
        }
        SDL_RenderPresent(screen);
    }
}

int Menu::Show_Option(SDL_Renderer* screen, std:: string t_play_again, std::string t_exit, Mix_Chunk* g_sound_character[10])
{
    TTF_Font* font_menu = TTF_OpenFont("FFF_Tusj.ttf", 27);
    Show_Button(screen,"asset//menu//play_again.png", 492, 120);
    Show_Button(screen,"asset//Button//Button_1.png", 540, 220);
    Show_Button(screen,"asset//Button//Button_1.png", 540, 350);
    BaseObject::Render(screen, NULL);
    play_agian.SetText(t_play_again);
    play_agian.LoadFromRenderText(font_menu, screen);
    quit.SetText(t_exit);
    quit.LoadFromRenderText(font_menu, screen);
    int x = 0;
    int y = 0;
    while(1)
    {
        play_agian.RenderText(screen, 570, 250);
        quit.RenderText(screen, 600, 380);
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEMOTION:
                x = g_event.motion.x;
                y = g_event.motion.y;
                if(x >= 540 && x <= 715 && y >= 220 && y<= 320){
                    Show_Button(screen,"asset//Button//Button_1_2.png", 540, 220);
                }
                else if(x>= 540 && x <= 715 && y >= 350 && y <= 450) {
                    Show_Button(screen,"asset//Button//Button_1_2.png", 540, 350);
                }
                else{
                    Show_Button(screen,"asset//Button//Button_1.png", 540, 220);
                    Show_Button(screen,"asset//Button//Button_1.png", 540, 350);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = g_event.button.x;
                y = g_event.button.y;
                Mix_PlayChannel(-1, g_sound_character[6], 0);
                if(x >= 540 && x <= 715 && y >= 220 && y<= 320){
                    BaseObject::Free();
                    //play_again
                    return 1;
                }
                if(x>= 540 && x <= 715 && y >= 350 && y <= 450) {
                    BaseObject::Free();
                    //exit
                    return -1;
                }
                break;
            }
        }
        SDL_RenderPresent(screen);
    }
}
int Menu::Show_Pause(SDL_Renderer* screen, std:: string t_resume, std::string t_quit, Mix_Chunk* g_sound_character[10])
{
    TTF_Font* font_menu = TTF_OpenFont("FFF_Tusj.ttf", 27);
    Show_Button(screen,"asset//menu//play_again.png", 492, 120);
    Show_Button(screen,"asset//Button//Button_1.png", 540, 220);
    Show_Button(screen,"asset//Button//Button_1.png", 540, 350);
    BaseObject::Render(screen, NULL);
    resume_.SetText(t_resume);
    resume_.LoadFromRenderText(font_menu, screen);
    pau_quit.SetText(t_quit);
    pau_quit.LoadFromRenderText(font_menu, screen);
    int x = 0;
    int y = 0;
    while(1)
    {
        resume_.RenderText(screen, 570, 250);
        pau_quit.RenderText(screen, 600, 380);
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
            case SDL_QUIT:
                return -1;
                break;
            case SDL_MOUSEMOTION:
                x = g_event.motion.x;
                y = g_event.motion.y;
                if(x >= 540 && x <= 715 && y >= 220 && y<= 320){
                    Show_Button(screen,"asset//Button//Button_1_2.png", 540, 220);
                }
                else if(x>= 540 && x <= 715 && y >= 350 && y <= 450) {
                    Show_Button(screen,"asset//Button//Button_1_2.png", 540, 350);
                }
                else{
                    Show_Button(screen,"asset//Button//Button_1.png", 540, 220);
                    Show_Button(screen,"asset//Button//Button_1.png", 540, 350);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = g_event.button.x;
                y = g_event.button.y;
                Mix_PlayChannel(-1, g_sound_character[6], 0);
                if(x >= 540 && x <= 715 && y >= 220 && y<= 320){
                    BaseObject::Free();
                    //resume
                    return 1;
                }
                if(x>= 540 && x <= 715 && y >= 350 && y <= 450) {
                    BaseObject::Free();
                    //exit
                    return -1;
                }
                break;
            }
        }
        SDL_RenderPresent(screen);
    }
}

