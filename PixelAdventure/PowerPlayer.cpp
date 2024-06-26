#include "HeaderGuard/PowerPlayer.h"

PowerPlayer::PowerPlayer()
{
    number_ = 0;
}

PowerPlayer::~PowerPlayer()
{

}

void PowerPlayer::AddPos(const int& xp)
{
    pos_list_.push_back(xp);
}

void PowerPlayer::Init(SDL_Renderer* screen)
{
    LoadImg("img//pw_player.png", screen);
    number_ = 3;
    if(pos_list_.size() > 0)
    {
        pos_list_.clear();
    }
    for(int i = 0; i < number_; i++)
        AddPos(20 + 40*i);
    // AddPos(20);
    // AddPos(60);
    // AddPos(100);
    //AddPos(140);//
}

void PowerPlayer::Show(SDL_Renderer* screen)
{
    for(int i = 0; i < pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 0;
        Render(screen);
    }
}

void PowerPlayer::Decrease()
{
    number_ --;
    pos_list_.pop_back();
}

int PowerPlayer::get_number()
{
    return number_;
}

void PowerPlayer::Increase()
{
    int last_pos = pos_list_.back() + 40;
    
    AddPos(last_pos);

    number_++;
}


//MONEY
PlayerMoney::PlayerMoney()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayerMoney::~PlayerMoney()
{ }

void PlayerMoney::Init(SDL_Renderer* screen)
{
    bool ret = LoadImg("img//money.png", screen);
}

void PlayerMoney::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);
}

//BLOCK
PlayerBlock::PlayerBlock()
{}

PlayerBlock::~PlayerBlock()
{}

void PlayerBlock::Init(SDL_Renderer* screen)
{
    bool ret = LoadImg("img//block.png", screen);
}

void PlayerBlock::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);
}


