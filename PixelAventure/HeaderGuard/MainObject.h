
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonF.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "PowerPlayer.h"

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
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen,  Mix_Chunk* bullet_sound[2]);
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

    void set_status_() {status_ = WALK_NONE;}
    void set_input_right(int ip) {input_type_.right_ = ip;}

    SDL_Rect GetRectFrame();

    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void set_x_pos(float px) { x_pos_ = px;}
    void set_y_pos(float py) { y_pos_ = py;}
    void set_y_val(float py) { y_val_ = py;}

    void set_int_xpos(int px) { pospos_x = px;}
    void set_int_ypos(int py) { pospos_x = py;}
    int get_int_xpos() const {return pospos_x;}
    int get_int_ypos() const {return pospos_y;}

    void RemoveBullet(const int& idx);
    void IncreaseMoney();
    void ZeroMoney();
    void ChangeBullet();
    int get_frame_width() const {return width_frame_;}
    int get_frame_height() const {return height_frame_;}
    void set_comebacktime(const int& cb_time) {come_back_time_ = cb_time;}
    int GetMoneyCount() const {return money_count;}
    int GetOnGround() const {return underground;}
    void SetOnGround(const int& ud) {underground = ud;} 
    bool SpikeTile(Map& map_data);
    bool CheckHeart(Map& map_data);
    bool BOOM(Map& map_data);
    void set_health(int nb) {health = nb;}
    int get_health() const {return health;}
    void set_money(int nmey) {money_count = nmey;}
private:

    BulletObject::BulletType bullet_type_;
    int money_count;
    std::vector<BulletObject*> p_bullet_list_;
    float x_val_;
    float y_val_;

    float x_pos_; // vi tri nha vat
    float y_pos_;

    int pospos_x;
    int pospos_y;

    int health;

    int width_frame_; //kich thuoc frame
    int height_frame_;

    SDL_Rect frame_clip_[12]; //so anh hanh dong cua nhan vat
    Input input_type_; //bien luu trang thai
    int frame_;
    int status_; //luu trang thai left right
    bool on_ground_;
    int underground;

    int map_x_;
    int map_y_;

    int come_back_time_;
};

#endif