#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Baseobject.h"
#include "CommonFunc.h"

#define GRAVITY_SPEED 0.8
#define GRAVITY 1
#define MAX_FALL_SPEED 100
//#define PLAYER_SPEED 10
#define PLAYER_JUMP_SPEED 20
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
    void Show(SDL_Renderer* des, Map& map_data);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen,
                            Mix_Chunk* g_sound_character[10]);
    void set_clips();

    void DoPlayer(Map& map_data,Mix_Chunk* g_sound_character[10]);
    void CheckToMap(Map & map_data);

    void CheckVerticalUp(Map& map_data);
    void CheckVerticalDown(Map& map_data);

    void CheckHorizontalLeft(Map& map_data);
    void CheckHorizontalRight(Map& map_data);

    void SetMapXY(const int map_x, const  int map_y){map_x_ = map_x; map_y_ = map_y;}
    void MoveMap(Map& map_data);

    void MoveLeft();
    void MoveRight();
    void JumpLeft();
    void JumpRight();
    void SlideLeft();
    void SlideRight();
    void Star_Game(Map& map_data);
    bool CheckLose();
    bool CheckWin();
    void waitUntilKeyPressed();
    void Set_Default(Map& map_data);

    bool star_;
    bool tnt;
    bool ps;
    bool die;
    bool win_;
    Input input_type_;
    int MAP_STEP;
    int PLAYER_SPEED;
 private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;
    float velocity;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[10];
    //SDL_Rect frame_j_clip_[2];

    //Input input_type_;
    int frame_;
    int status_;

    bool on_ground_;
    int map_x_;
    int map_y_;

};

#endif // MAIN_OBJECT_H_
