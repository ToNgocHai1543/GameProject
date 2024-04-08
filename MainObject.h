#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Baseobject.h"
#include "CommonFunc.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 10

class MainObject : public BaseObject
{
public :
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
        JUMP_RIGHT = 2,
        JUMP_LEFT = 3,
        SLIDE_LEFT = 4,
        SLIDE_RIGHT = 5,
    };
    bool LoadImg(std:: string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();

    void DoPlayer(Map& map_data);
    void CheckToMap(Map & map_data);
private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[10];
    //SDL_Rect frame_j_clip_[2];

    Input input_type_;
    int frame_;
    int status_;

    bool on_ground_;

};

#endif // MAIN_OBJECT_H_
