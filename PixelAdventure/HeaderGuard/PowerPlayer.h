
#ifndef POWER_PLAYER_H_
#define POWER_PLAYER_H_

#include "CommonF.h"
#include "BaseObject.h"

class PowerPlayer : public BaseObject
{
public:
    PowerPlayer();
    ~PowerPlayer();

    void SetNum(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void InitCrease();
    void Decrease();
    void Increase();
    int get_number();

private:
    int number_;
    std::vector<int> pos_list_;

};


class PlayerMoney : public BaseObject
{
public:
    PlayerMoney();
    ~PlayerMoney();

    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& xp, const int& yp) {x_pos_ = xp; y_pos_ = yp;}
private:
    int x_pos_;
    int y_pos_;
};

class PlayerBlock : public BaseObject
{
public: 
    PlayerBlock();
    ~PlayerBlock();

    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& xp, const int& yp) {x_pos_ = xp; y_pos_ = yp;}

private:
    int x_pos_;
    int y_pos_;
};

#endif