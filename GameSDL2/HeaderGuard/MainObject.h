
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonF.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10 //toc do roi max
#define PLAYER_SPEED 8 //toc do nhan vat
#define PLAYER_JUMP_VAL 20

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips(); //hieu ung animation

    void DoPlayer(Map& map_data);  //
    void CheckToMap(Map& map_data);  //check va cham
    //void CheckGround(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) { //ban do di chuyen theo nhan vat
        map_x_ = map_x; map_y_ = map_y;
    }
    void CenterEntityOnMap(Map& map_data); //thong so map khi di chuyen
    void UpdateImagePlayer(SDL_Renderer* des);

    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list_;}
    void HandleBullet(SDL_Renderer* des);

    SDL_Rect GetRectFrame();

    void RemoveBullet(const int& idx);
    void IncreaseMoney();
    void ChangeBullet();
    int get_frame_width() const {return width_frame_;}
    int get_frame_height() const {return height_frame_;}
    void set_comebacktime(const int& cb_time) {come_back_time_ = cb_time;}
    int GetMoneyCount() const {return money_count;}
private:

    BulletObject::BulletType bullet_type_;
    int money_count;
    std::vector<BulletObject*> p_bullet_list_;
    float x_val_;
    float y_val_;

    float x_pos_; // vi tri nha vat
    float y_pos_;

    int width_frame_; //kich thuoc frame
    int height_frame_;

    SDL_Rect frame_clip_[12]; //so anh hanh dong cua nhan vat
    Input input_type_; //bien luu trang thai
    int frame_;
    int status_; //luu trang thai left right
    bool on_ground_;

    int map_x_;
    int map_y_;

    int come_back_time_;
};

#endif