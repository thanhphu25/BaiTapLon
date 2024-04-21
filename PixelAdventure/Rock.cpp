
#include "HeaderGuard/Rock.h"

RockObject::RockObject()
{
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    map_x_ = 0;
    map_y_ = 0;
}

 RockObject::~RockObject()
 {

 }

SDL_Rect RockObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

bool RockObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        width_frame_ = rect_.w;
        height_frame_ = rect_.h;
    }

    return ret;
}

void RockObject::Show(SDL_Renderer* des)
{
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_- map_y_;

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

        SDL_RenderCopy(des, p_object_, NULL, &renderQuad );
    
}

void RockObject::DoPlayer(Map& g_map)
{
    x_val_ = 0;


        y_val_ += ROCK_GRAVITY_SPEED;

        if (y_val_ >= ROCK_MAX_FALL_SPEED)
            y_val_ = ROCK_MAX_FALL_SPEED;


    if (y_pos_ >= SCREEN_HEIGHT - height_frame_)
    {
        y_pos_ = 0;
    }

    map_x_ = g_map.start_x_;
    map_y_ = g_map.start_y_;

    y_pos_ += y_val_;
}
