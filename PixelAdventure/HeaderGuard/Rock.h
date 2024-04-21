
#ifndef ROCK_H_
#define ROCK_H_

#include "CommonF.h"
#include "BaseObject.h"

#define ROCK_GRAVITY_SPEED 0.3
#define ROCK_MAX_FALL_SPEED 14

class RockObject : public BaseObject
{
public:
    RockObject();
    ~RockObject();
    void set_x_val(int xp) {x_val_ = xp;}
    void set_y_val(int yp) {y_val_ = yp;}

    void set_x_pos(const int& xps) {x_pos_ = xps;}
    void set_y_pos(const int& yps) {y_pos_ = yps;}
    int get_x_pos() {return x_pos_;}
    int get_y_pos() {return y_pos_;}

    void Show(SDL_Renderer* des);
    bool LoadImg(std::string path, SDL_Renderer* screen);

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;};
    void CheckToMap(Map& g_map);
    void CenterEntityOnMap(Map& g_map);
    void DoPlayer(Map& g_map);
    void ImpMoveType(SDL_Renderer* screen);

    SDL_Rect GetRectFrame();

private:
    int map_x_;
    int map_y_;
    int on_ground_;
    int x_pos_;
    int y_pos_;
    float x_val_;
    float y_val_;
    int width_frame_;
    int height_frame_;
};



#endif