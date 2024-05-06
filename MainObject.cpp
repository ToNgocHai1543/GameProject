#include "stdafx.h"
#include "MainObject.h"
#include <iostream>
using namespace std;
MainObject::MainObject()
{
    frame_ = 0;
    x_pos_ = 128;
    y_pos_ = 320;

    width_frame_ = 0;
    height_frame_ = 0;

    status_ = -1;
    input_type_.left_  = 0;
    input_type_.right_ = 0;
    input_type_.jump_left_ = 0;
    input_type_.jump_right_ = 0;
    input_type_.slide_right_ = 0;
    input_type_.slide_left_ = 0;

    on_ground_ = false;

    velocity = 0;
    tnt = false;
    ps = false;
    star_ = false;
    die = false;
 }

MainObject::~MainObject()
{

}
bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w / 10;
        height_frame_ = rect_.h;
    }
    return ret;
}
void MainObject::set_clips()
{
    if (width_frame_ > 0 and height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = 2 * width_frame_;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;

        frame_clip_[3].x = 3 * width_frame_;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame_;
        frame_clip_[3].h = height_frame_;

        frame_clip_[4].x = 4 * width_frame_;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = width_frame_;
        frame_clip_[4].h = height_frame_;

        frame_clip_[5].x = 5 * width_frame_;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = width_frame_;
        frame_clip_[5].h = height_frame_;

        frame_clip_[6].x = 6 * width_frame_;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = width_frame_;
        frame_clip_[6].h = height_frame_;

        frame_clip_[7].x = 7 * width_frame_;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = width_frame_;
        frame_clip_[7].h = height_frame_;

        frame_clip_[8].x = 8 * width_frame_;
        frame_clip_[8].y = 0;
        frame_clip_[8].w = width_frame_;
        frame_clip_[8].h = height_frame_;

        frame_clip_[9].x = 9 * width_frame_;
        frame_clip_[9].y = 0;
        frame_clip_[9].w = width_frame_;
        frame_clip_[9].h = height_frame_;
    }
}

void MainObject::Show(SDL_Renderer* des)
{
    if (on_ground_ == true)
    {
        if (status_ == WALK_LEFT)
        {
            LoadImg("Ninja//Run__l.png", des);
        }
        else if (status_ == WALK_RIGHT)
        {
            LoadImg("Ninja//Run__r.png", des);
        }
        else if (status_ == SLIDE_LEFT)
        {
            LoadImg("Ninja//Slide_l.png", des);
        }
        else if (status_ == SLIDE_RIGHT)
        {
            LoadImg("Ninja//Slide_r.png", des);
        }
    }
    if (status_ == JUMP_LEFT )
    {
        LoadImg("Ninja//Jump_l.png", des);
    }
    else if (status_ == JUMP_RIGHT)
    {
        LoadImg("Ninja//Jump_r.png", des);
    }
    if (input_type_.left_ == 1 or input_type_.right_ == 1
        or input_type_.jump_left_ == 1 or input_type_.jump_right_ == 1
        or input_type_.slide_left_ == 1 or input_type_.slide_right_ == 1)
    {
        frame_++;
    }
    else {
        frame_ = 0;
    }
    if (frame_ >= 10 ) frame_ = 0;

    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void MainObject:: HandelInputAction(SDL_Event events, SDL_Renderer* screen,
                                    Mix_Chunk* g_sound_character[10])
{
    if (events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = WALK_RIGHT;
                input_type_.right_ = 1;
                if (on_ground_ == true)
                {

                  LoadImg("Ninja//Run__r.png", screen);

                }
                else {
                    LoadImg("Ninja//Jump_r.png", screen);
                }
                Mix_PlayChannel(-1, g_sound_character[0], 0);
            }
            break;
        case SDLK_LEFT:
            {
                status_ = WALK_LEFT;
                input_type_.left_ = 1;
                if (on_ground_ == true)
                {
                  LoadImg ("Ninja//Run__l.png", screen);
                }
                else {
                    LoadImg("Ninja//Jump_l.png", screen);
                }
                Mix_PlayChannel(-1, g_sound_character[0], 0);
            }
            break;
        case SDLK_UP:
            {
                if (on_ground_)
                {
                    if (status_ == WALK_LEFT or status_ == JUMP_LEFT)
                    {
                        status_ = JUMP_LEFT;
                        input_type_.jump_left_ = 1;
                    }
                    if (status_ == WALK_RIGHT or status_ == JUMP_RIGHT)
                    {
                        status_ = JUMP_RIGHT;
                        input_type_.jump_right_ = 1;
                    }
                    Mix_PlayChannel(-1, g_sound_character[1], 0);
                }
            }
            break;
        case SDLK_DOWN:
            {

                if (status_ == WALK_LEFT or status_ == JUMP_LEFT or status_ == SLIDE_LEFT)
                {
                    status_ = SLIDE_LEFT;
                    input_type_.slide_left_ = 1;

                }
                if (status_ == WALK_RIGHT or status_ == JUMP_RIGHT or status_ == SLIDE_RIGHT)
                {
                    status_ = SLIDE_RIGHT;
                    input_type_.slide_right_ = 1;
                }
                Mix_PlayChannel(-1, g_sound_character[0], 0);
            }
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type_.right_ = 0;
            }
            break;
        case SDLK_LEFT:
            {
                input_type_.left_ = 0;
            }
            break;
        case SDLK_UP:
            {
                input_type_.jump_left_ = 0;
                input_type_.jump_right_ = 0;
            }
            break;
        case SDLK_DOWN:
            {
                input_type_.slide_left_ = 0;
                input_type_.slide_right_ = 0;
            }
            break;
        }
    }
}

bool MainObject::CheckLose()
{
    return die;
}

void MainObject::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
void MainObject::MoveLeft()
{
    x_pos_ = x_pos_ - PLAYER_SPEED + MAP_STEP;
}
void MainObject::MoveRight()
{
    x_pos_ += PLAYER_SPEED;
}
void MainObject::JumpLeft()
{
    if (on_ground_ == true)
    {
        velocity = 0 - PLAYER_JUMP_SPEED;
        x_pos_ = x_pos_ - PLAYER_SPEED + MAP_STEP;
    }
}
void MainObject::JumpRight()
{
    if (on_ground_ == true)
    {
        velocity = 0 - PLAYER_JUMP_SPEED;
        x_pos_ += PLAYER_SPEED;
    }
}
void MainObject::SlideLeft()
{
    x_pos_ = x_pos_ - PLAYER_SPEED + MAP_STEP;
}
void MainObject::SlideRight()
{
     x_pos_ += PLAYER_SPEED;
}
void MainObject::DoPlayer(Map& map_data, Mix_Chunk* g_sound_character[10])
{
    die = false;
    if (input_type_.left_ == 1)
    {
        MoveLeft();
    }
    else if (input_type_.right_ == 1)
    {
        MoveRight();
    }
    else if (input_type_.jump_left_ == 1 )
    {
        JumpLeft();
    }
    else if (input_type_.jump_right_ == 1 )
    {

        JumpRight();
    }
    else if (input_type_.slide_left_ == 1)
    {
        SlideLeft();
    }
    else if (input_type_.slide_right_ == 1)
    {
        SlideRight();
    }


    // Kiểm tra va chạm với bản đồ và di chuyển nhân vật
    CheckVerticalDown(map_data);
    CheckVerticalUp(map_data);
    CheckHorizontalRight(map_data);
    CheckHorizontalLeft(map_data);
    if (tnt == true)
    {
        Mix_PlayChannel(-1, g_sound_character[2], 0);
        die = true;
    }
    if (ps == true)
    {
        Mix_PlayChannel(-1, g_sound_character[3], 0);
        die = true;
    }
    if (star_ == true)
    {
        Mix_PlayChannel(-1, g_sound_character[4], 0);
    }
    if (rect_.x >= SCREEN_WIDTH or rect_.x <= -5)
    {
       Mix_PlayChannel(-1, g_sound_character[5], 0);
       die = true;
    }
    if (rect_.y >= SCREEN_HEIGHT)
    {
        Mix_PlayChannel(-1, g_sound_character[5], 0);
        die = true;
    }
    MoveMap(map_data);
}

void MainObject::CheckVerticalDown(Map& map_data)
{
    int y = 0;
    int x = 0;
    int y_next = y_pos_ + velocity;
    x = (x_pos_ - width_frame_ /2 - 10) / TILE_SIZE + 1;
    y = (y_next + height_frame_) / TILE_SIZE;
    if (map_data.tile[y][x] == BLANK_TILE)
    {
        y_pos_ = y_pos_ + velocity;
        velocity = velocity + GRAVITY;
        on_ground_ = false;
    }
    else
    {
        if (map_data.tile[y][x] == STAR)
        {
            star_ = true;
            map_data.tile[y][x] = BLANK_TILE;
        }
        if (map_data.tile[y][x] == TNT )
        {
        tnt = true;
        }
        if ( map_data.tile[y][x] == POISION)
        {
        ps = true;
        }
        on_ground_ = true;
        y_pos_ = y * TILE_SIZE - height_frame_;

    }

}
void MainObject::CheckVerticalUp(Map& map_data)
{
    int x = 0, y = 0;
    int y_next = y_pos_ + velocity;
    x = (x_pos_ + width_frame_ / 2 ) / TILE_SIZE;
    y = y_next / TILE_SIZE;
    if (map_data.tile[y][x] != BLANK_TILE && velocity < 0)
    {
        y_pos_ = (y + 1) * TILE_SIZE ;
        velocity += GRAVITY;
        if (map_data.tile[y][x] == TNT)
        {
            tnt = true;
        }
        if ( map_data.tile[y][x] == POISION)
        {
        ps = true;
        }
    }
    if (map_data.tile[y][x] == STAR)
    {
        star_ = true;
        map_data.tile[y][x] = BLANK_TILE;
    }
    //else star_ = false;

}
void MainObject::CheckHorizontalRight(Map& map_data)
{
    int x = 0, y = 0;
    int y_next = y_pos_ + velocity;
    x = (x_pos_ + width_frame_  + 1 ) / TILE_SIZE;
    y = (y_pos_ + 1) / TILE_SIZE;
    if (height_frame_ > TILE_SIZE)
    {
        if (map_data.tile[y][x] != BLANK_TILE or map_data.tile[y + 1][x] != BLANK_TILE)
        {
            //x_pos_ = x * TILE_SIZE - width_frame_;
            x_pos_ = x_pos_ - PLAYER_SPEED;
        }
        if (map_data.tile[y][x] == TNT or map_data.tile[y + 1][x] == TNT)
        {
            tnt = true;
        }
        if (map_data.tile[y][x] == POISION  or map_data.tile[y + 1][x] == POISION)
        {
        ps = true;
        }
        if (map_data.tile[y][x] == STAR )
        {
            star_ = true;
            map_data.tile[y][x] = BLANK_TILE;
        }
        if (map_data.tile[y + 1][x] == STAR )
        {
            star_ = true;
            map_data.tile[y + 1][x] = BLANK_TILE;
        }
    }
    else if(map_data.tile[y][x] != BLANK_TILE)
    {
        if (map_data.tile[y][x] == STAR)
        {
            star_ = true;
            map_data.tile[y][x] = BLANK_TILE;
        }
        if (map_data.tile[y][x] == TNT)
        {
            tnt = true;
        }
        if ( map_data.tile[y][x] == POISION)
        {
        ps = true;
        }
        x_pos_ = x_pos_ - PLAYER_SPEED;

    }
}
void MainObject::CheckHorizontalLeft(Map& map_data)
{
    int x = 0, y = 0;
    int y_next = y_pos_ + velocity;
    x = (x_pos_ + 1 ) / TILE_SIZE;
    y = (y_pos_ + 1) / TILE_SIZE;
    if (height_frame_ > TILE_SIZE)
    {
        if (map_data.tile[y][x] != BLANK_TILE or map_data.tile[y + 1][x] != BLANK_TILE)
        {
            x_pos_ = x_pos_ + PLAYER_SPEED;
        }
        if (map_data.tile[y][x] == TNT or map_data.tile[y + 1][x] == TNT)
        {
            tnt = true;
        }
        if (map_data.tile[y][x] == POISION
             or map_data.tile[y + 1][x] == POISION)
        {
        ps = true;
        }
        if (map_data.tile[y][x] == STAR )
        {
            star_ = true;
            map_data.tile[y][x] = BLANK_TILE;
        }
        if (map_data.tile[y + 1][x] == STAR )
        {
            star_ = true;
            map_data.tile[y + 1][x] = BLANK_TILE;
        }
    }
    else if(map_data.tile[y][x] != BLANK_TILE)
    {
        x_pos_ = x_pos_ + PLAYER_SPEED;
        if (map_data.tile[y][x] == STAR)
        {
            star_ = true;
            map_data.tile[y][x] = BLANK_TILE;
        }
        if (map_data.tile[y][x] == TNT)
        {
            tnt = true;
        }
        if ( map_data.tile[y][x] == POISION)
        {
        ps = true;
        }
    }
}

void MainObject:: MoveMap(Map& map_data)
{
    //cerr << "map_x_ " <<  map_x_ << endl;
    //cerr << "map_y_ " << map_y_ << endl;
    if (map_data.start_x_ >= MAX_MAP_X * TILE_SIZE)
    {
        map_data.start_x_ = 0;
    }
    else
    {
        map_data.start_x_ = (map_data.start_x_ + MAP_STEP) % (MAX_MAP_X * TILE_SIZE);

    }

    if (rect_.x >= SCREEN_WIDTH or rect_.x <= 0)
    {
       // waitUntilKeyPressed();
        map_data.start_x_ = MAP_STEP;
        x_pos_ = 128; y_pos_ = 320;
        status_ = -1;
        input_type_.left_  = 0;
        input_type_.right_ = 0;
        input_type_.jump_left_ = 0;
        input_type_.jump_right_ = 0;
        input_type_.slide_right_ = 0;
        input_type_.slide_left_ = 0;
    }
    if (rect_.y >= SCREEN_HEIGHT)
    {
       // waitUntilKeyPressed();
        map_data.start_x_ = MAP_STEP;
        x_pos_ = 128; y_pos_ = 320;
        status_ = -1;
        input_type_.left_  = 0;
        input_type_.right_ = 0;
        input_type_.jump_left_ = 0;
        input_type_.jump_right_ = 0;
        input_type_.slide_right_ = 0;
        input_type_.slide_left_ = 0;
    }
    if (ps == true)
    {
       // waitUntilKeyPressed();
        map_data.start_x_ = MAP_STEP;
        x_pos_ = 128; y_pos_ = 320;
        status_ = -1;
        ps = false;
        input_type_.left_  = 0;
        input_type_.right_ = 0;
        input_type_.jump_left_ = 0;
        input_type_.jump_right_ = 0;
        input_type_.slide_right_ = 0;
        input_type_.slide_left_ = 0;
    }
    if (tnt == true)
    {
       // waitUntilKeyPressed();
        map_data.start_x_ = MAP_STEP;
        x_pos_ = 128; y_pos_ = 320;
        tnt = false;
        status_ = -1;
        input_type_.left_  = 0;
        input_type_.right_ = 0;
        input_type_.jump_left_ = 0;
        input_type_.jump_right_ = 0;
        input_type_.slide_right_ = 0;
        input_type_.slide_left_ = 0;
    }
}







