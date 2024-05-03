#include "Menu.h"
#include "iostream"

//Menu
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
int Menu::ShowMenu(std:: string t_play, std::string t_exit,std::string t_difficult, std::string t_how, SDL_Renderer* screen )
{
    TTF_Font* font_menu = TTF_OpenFont("FFF_Tusj.ttf", 27);
    bool ret = BaseObject::LoadImg("asset//menu//Menu.jpg", screen);
    Show_Button(screen,"asset//menu//Menu.jpg", 0 ,0);
    Show_Button(screen,"asset//Button//Button_1.png", 300, 200);
    Show_Button(screen,"asset//Button//Button_1.png", 300, 350);
    Show_Button(screen,"asset//Button//Button_1.png", 555, 200);
    Show_Button(screen,"asset//Button//Button_1.png", 555, 350);
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
        //int mouse_x, mouse_y;
        //SDL_GetMouseState(&mouse_x, &mouse_y);
        //Show_Button(screen,"asset//mouse.png", mouse_x ,mouse_y);
        play_game.RenderText(screen, 320, 230);
        exit_.RenderText(screen, 350, 380);
        difficult_.RenderText(screen, 580, 230);
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
                std::cerr<< "x " << x << std::endl;
                std::cerr<< "y " << y << std::endl;
                if(x>=300 && x<=505 && y >= 200 && y<= 300){
                    play_game.SetColor(255, 255, 0);
                    Show_Button(screen,"asset//Button//Button_1_2.png", 300, 200);
                }
                else if(x>= 300 && x <= 505 && y >= 350 && y <= 450){
                    exit_.SetColor(255, 255, 0);
                    Show_Button(screen,"asset//Button//Button_1_2.png", 300, 350);
                }
                else if(x>= 555 && x <= 755 && y >= 350 && y <= 450){
                    how_.SetColor(255, 255, 0);
                    Show_Button(screen,"asset//Button//Button_1_2.png", 555, 350);
                }
                else if(x>= 555 && x <= 755 && y >= 200 && y <= 300){
                    difficult_.SetColor(255, 255, 0);
                    Show_Button(screen,"asset//Button//Button_1_2.png", 555, 200);
                }
                else{
                    play_game.SetColor(TextObject::RED_TEXT);
                    Show_Button(screen,"asset//Button//Button_1.png", 300, 200);
                    exit_.SetColor(255, 0 ,0);
                    Show_Button(screen,"asset//Button//Button_1.png", 300, 350);
                    difficult_.SetColor(255, 0 ,0);
                    Show_Button(screen,"asset//Button//Button_1.png", 555, 200);
                    how_.SetColor(255, 0 ,0);
                    Show_Button(screen,"asset//Button//Button_1.png", 555, 350);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = g_event.button.x;
                y = g_event.button.y;

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

                }
                break;

            }
        }
        SDL_RenderPresent(screen);
    }
}
