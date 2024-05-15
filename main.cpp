#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.foundation.h>
#include "stdafx.h"
#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Game_map.h"
#include "Menu_object.h"
#include "Mouse.h"
#include "Menu.h"
#include <fstream>
using namespace std;

BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow ("Game NINJA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (g_window == NULL)
    {
        success = false;
    }
    else {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL) success = false;
        else {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR , RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) and imgFlags))
                success = false;
        }
        if (TTF_Init() == -1)
        {
            success = false;
        }
    }

    //Music
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        success = false;
    }
    g_sound_character[0] = Mix_LoadWAV("sound//character//run1.wav");
    g_sound_character[1] = Mix_LoadWAV("sound//character//jump.ogg");
    g_sound_character[2] = Mix_LoadWAV("sound//character//cannon_attack.wav");
    g_sound_character[3] = Mix_LoadWAV("sound//character//hero_death_1.ogg");
    g_sound_character[4] = Mix_LoadWAV("sound//character//star.wav");
    g_sound_character[5] = Mix_LoadWAV("sound//character//gameover.mp3");
    g_sound_character[6] = Mix_LoadWAV("sound//click//click.mp3");
    g_sound_character[7] = Mix_LoadWAV("sound//win.mp3");
    m_ingame = Mix_LoadMUS("sound//click//Ingame.MP3");
    font_time = TTF_OpenFont("FFF_Tusj.ttf", 15);
    if (font_time == NULL)
    {
        success = false;
    }
    return success;
}
bool LoadBackground()
{
    bool ret = g_background.LoadImg("bkgr//back_ground_3.jpg", g_screen);
    if (ret == false) return false;
    else return true;

}
void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    //Mix_FreeChunk(g_sound_character);
    //Mix_FreeMusic(m_ingame);
    Mix_CloseAudio();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}
int main(int argc, char *argv[])
{

    if (InitData() == false)
    {
        return -1;
    }
    SDL_Surface* mouse = IMG_Load("asset//mouse.png");
    SDL_Cursor* cursor = SDL_CreateColorCursor(mouse, 0, 0);
    SDL_SetCursor(cursor);
    Mix_PlayMusic(m_ingame, -1);
    Menu menu_game;
    int ret_menu = 0;

    if (LoadBackground() == false) return -1;

    MainObject p_player;
    p_player.LoadImg("Ninja//Run__r.png", g_screen);
    p_player.set_clips();

    GameMap game_map;
    game_map.LoadMap("map//map02.txt");
    game_map.LoadTiles(g_screen);

    TextObject author;
    author.SetColor(TextObject:: RED_TEXT);
    std::string au = "To Ngoc Hai";
    author.SetText(au);
    author.LoadFromRenderText (font_time, g_screen);


//Time text
    TextObject time_game;
    time_game.SetColor(TextObject:: RED_TEXT);
// Start text
    TextObject star;
    star.SetColor(TextObject:: RED_TEXT);
//Hight Star
    TextObject th_star;
    th_star.SetColor(TextObject:: RED_TEXT);




    bool is_quit = false;
    Uint32 star_val = 0;
    mute = false;
    menu_game.win = false;


    while(!is_quit)
    {
        p_player.MAP_STEP = 5;
        p_player.PLAYER_SPEED = 10;
        while(ret_menu == 0)
        {
            ret_menu = menu_game.ShowMenu("PLAY GAME", "EXIT", "LEVEL", "HOW", g_screen,g_sound_character);
            if(ret_menu == -1) return 0;
            if (ret_menu == 2)
            {
                while(ret_menu == 2)
                {
                    ret_menu = menu_game.Show_How(g_screen, "OKAY", g_sound_character);
                    if(ret_menu == -1) return 0;
                }
            }
            if (ret_menu == 3)
            {
                while (ret_menu == 3)
                {
                    int level = menu_game.Show_Difficult(g_screen, "EASY", "NORMAL", "HARD", "OKAY", g_sound_character);
                    if (level == 1)
                    {
                        p_player.MAP_STEP = 5;
                        p_player.PLAYER_SPEED = 10;
                    }
                    if (level == 2)
                    {
                        p_player.MAP_STEP = 7;
                        p_player.PLAYER_SPEED = 12;
                    }
                    if (level == 3)
                    {
                        p_player.MAP_STEP = 9;
                        p_player.PLAYER_SPEED = 15;
                    }
                    if (level == 0) ret_menu = level;
                    if (ret_menu == -1) return 0;
                }
            }
        }

        ret_menu = 0;
        while (!is_quit)
        {
            std::ifstream input_hightstar("asset//hight_star.txt");
            Uint32 hight_star;
            input_hightstar >> hight_star;
            std::string hs = std::to_string(hight_star);
            hs = "Hight Star: " + hs;
            th_star.SetText(hs);
            th_star.LoadFromRenderText (font_time, g_screen);
            input_hightstar.close();

            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                }
                p_player.HandelInputAction(g_event, g_screen, g_sound_character);
            }

            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR,RENDER_DRAW_COLOR, RENDER_DRAW_COLOR );
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);
            Map map_data = game_map.getMap();
            p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
            p_player.DoPlayer(map_data, g_sound_character);
            p_player.Show(g_screen, map_data);

            game_map.SetMap(map_data);
            game_map.DrawMap(g_screen);

            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_ESCAPE]) {
                int pau = 0;
                while (pau == 0)
                {
                    pau = menu_game.Show_Pause(g_screen, "RESUME", "QUIT", g_sound_character);
                    if (pau == -1) {
                            return 0;
                            break;
                    }
                }
                if (pau == -1) {
                    p_player.Set_Default(map_data);
                    break;
                }
                p_player.input_type_.left_  = 0;
                p_player.input_type_.right_ = 0;
                p_player.input_type_.jump_left_ = 0;
                p_player.input_type_.jump_right_ = 0;
                p_player.input_type_.slide_right_ = 0;
                p_player.input_type_.slide_left_ = 0;
            }
// Render Text
            author.RenderText(g_screen, 100 , 15);
            th_star.RenderText(g_screen, SCREEN_WIDTH - 200, 15);

            std::string star_add = "Stars: ";

            if(p_player.star_== true)
            {
                star_val = star_val + 1;
                p_player.star_ = false;
            }
            std::string star_val_ = std::to_string(star_val);
            star_add += star_val_;
            star.SetText(star_add);
            star.LoadFromRenderText(font_time, g_screen);
            star.RenderText(g_screen, SCREEN_WIDTH / 2 , 15);
            if(star_val > hight_star)
            {
                std::ofstream output_hightstar("asset//hight_star.txt", std::ofstream::out | std::ofstream::trunc);
                output_hightstar << star_val;
                output_hightstar.close();
            }
             if (p_player.CheckLose())
            {
                int option_menu = menu_game.Show_Option(g_screen,"Play Again", "Quit",star_add, g_sound_character);
                if(option_menu == -1)
                {
                    game_map.LoadMap("map//map02.txt");
                    star_val = 0;
                    option_menu = 0;
                    break;
                }
                if (option_menu == 1)
                {
                    game_map.LoadMap("map//map02.txt");
                    star_val = 0;
                    option_menu = 0;
                }
            }
            if (p_player.CheckWin() == true)
            {
                menu_game.win = true;
                int option_menu = menu_game.Show_Option(g_screen,"Play Again", "Quit",star_add, g_sound_character);
                if(option_menu == -1)
                {
                    game_map.LoadMap("map//map02.txt");
                    star_val = 0;
                    option_menu = 0;
                    break;
                }
                if (option_menu == 1)
                {
                    game_map.LoadMap("map//map02.txt");
                    star_val = 0;
                    option_menu = 0;
                }
            }

            menu_game.win = false;

            SDL_RenderPresent(g_screen);
            SDL_Delay(50);
            }
        }
    close();
    return 0;
}
