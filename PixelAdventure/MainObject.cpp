
#include "HeaderGuard/MainObject.h"

MainObject::MainObject()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = WALK_NONE;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
    on_ground_ = false;
    map_x_ = 0;
    map_y_ = 0;
    come_back_time_ = 0;
    money_count = 0;
    block_count = 0;
    bullet_type_ = BulletObject::SPHERE_BULLET;
    underground = 0;
    jump_step = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen); //Dung lai cua baseobject

    if(ret == true)
    {
        width_frame_ = rect_.w/12; //chia so luong frame
        height_frame_ = rect_.h;
    }
    return ret;
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

void MainObject::set_clips()
{
    if(width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = 2*width_frame_;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;

        frame_clip_[3].x = 3*width_frame_;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame_;
        frame_clip_[3].h = height_frame_;

        frame_clip_[4].x = 4*width_frame_;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = width_frame_;
        frame_clip_[4].h = height_frame_;

        frame_clip_[5].x = 5*width_frame_;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = width_frame_;
        frame_clip_[5].h = height_frame_;

        frame_clip_[6].x = 6*width_frame_;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = width_frame_;
        frame_clip_[6].h = height_frame_;

        frame_clip_[7].x = 7*width_frame_;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = width_frame_;
        frame_clip_[7].h = height_frame_;

        frame_clip_[8].x = 8*width_frame_;
        frame_clip_[8].y = 0;
        frame_clip_[8].w = width_frame_;
        frame_clip_[8].h = height_frame_;

        frame_clip_[9].x = 9*width_frame_;
        frame_clip_[9].y = 0;
        frame_clip_[9].w = width_frame_;
        frame_clip_[9].h = height_frame_;

        frame_clip_[10].x = 10*width_frame_;
        frame_clip_[10].y = 0;
        frame_clip_[10].w = width_frame_;
        frame_clip_[10].h = height_frame_;

        frame_clip_[11].x = 11*width_frame_;
        frame_clip_[11].y = 0;
        frame_clip_[11].w = width_frame_;
        frame_clip_[11].h = height_frame_;

        frame_clip_[12].x = 12*width_frame_;
        frame_clip_[12].y = 0;
        frame_clip_[12].w = width_frame_;
        frame_clip_[12].h = height_frame_;
    }
}

void MainObject::Show(SDL_Renderer* des)
{
    UpdateImagePlayer(des);

    if(input_type_.left_ == 1 ||
       input_type_.right_ == 1) 
    {
        frame_++;
    }
    else frame_ = 0;

    if(frame_ >= 12) frame_ = 0;

    if(come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_; //tru di do ban do da bi cuon khi nhan vat di chuyen
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip = &frame_clip_[frame_];

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad); // copy hinh anh tu texture vao 1 vung renderquad
    }

}


void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet_sound[2], Mix_Chunk* jump[1])
{
    if(events.type == SDL_KEYDOWN) 
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_d:
            {
                status_ = WALK_RIGHT;
                input_type_.right_ = 1;
                input_type_.left_ = 0; 
                UpdateImagePlayer(screen);
            }
            break;
            case SDLK_a:
            {
                status_ = WALK_LEFT;
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                UpdateImagePlayer(screen);
            }
            break;
            case SDLK_w:
            {
                if (on_ground_ || jump_step < 2) {
                    input_type_.jump_ = 1; 
                    Mix_PlayChannel(-1, jump[0], 0); 
                }
            }
            break;
        }
    } 
    else if(events.type == SDL_KEYUP)
    {
        switch( events.key.keysym.sym )
        {
            case SDLK_d: 
                {input_type_.right_ = 0;}
            break;
            case SDLK_a: 
                {input_type_.left_ = 0; }
            break;
        }
    }
    //BulletObject::BulletType bullet_type_ = BulletObject::LASER_BULLET;

    if(events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
         case SDLK_s:
             ChangeBullet();
            break;
                
        default:
            break;
        }
    }
    if(events.type == SDL_MOUSEBUTTONDOWN)
    {

        if(events.button.button == SDL_BUTTON_LEFT)
        {

            BulletObject* p_bullet = new BulletObject();
            //p_bullet->set_bullet_type_(BulletObject::SPHERE_BULLET);
            p_bullet->set_bullet_type(bullet_type_);
            p_bullet->LoadImgBullet(screen);
            if(bullet_type_ == BulletObject::LASER_BULLET)
            {
                Mix_PlayChannel(-1, bullet_sound[0], 0);
            }
            else Mix_PlayChannel(-1, bullet_sound[1], 0);

            if(status_ == WALK_LEFT)
            {
                p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                p_bullet->SetRect(this->rect_.x, rect_.y + height_frame_*0.25);
            }
            else 
            {
                p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                p_bullet->SetRect(this->rect_.x + width_frame_ -20, rect_.y + height_frame_*0.25);

            }
            
            p_bullet->set_x_val(15); //20
            p_bullet->set_is_move(true);

            p_bullet_list_.push_back(p_bullet);
        }
    }


}

void MainObject::HandleBullet(SDL_Renderer* des) 
{
    for(int i = 0; i < p_bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move() == true)
            {
                p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                p_bullet->Render(des);
            }
            else{
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
                if(p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void MainObject::RemoveBullet(const int& idx)
{
    int size = p_bullet_list_.size();
    if(size > 0 && idx < size)
    {
        BulletObject* p_bullet = p_bullet_list_.at(idx);
        p_bullet_list_.erase(p_bullet_list_.begin() + idx);
        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void MainObject::DoPlayer(Map& map_data, Mix_Chunk* coin[1])
{
    if(come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += 0.8; //do roi cua nhan vat

        if(y_val_ >= MAX_FALL_SPEED)
            y_val_ = MAX_FALL_SPEED;

        if(input_type_.left_ == 1) {
            x_val_ -= PLAYER_SPEED;
        }
        else if (input_type_.right_ == 1) {
            x_val_ += PLAYER_SPEED;
        }

        if(input_type_.jump_ == 1 && (on_ground_ || jump_step < 2))
        {   
            y_val_ = - PLAYER_JUMP_VAL;
            on_ground_ = false; 
            jump_step++; 

            input_type_.jump_ = 0;
        }

        if (on_ground_ && jump_step == 2) 
        {
            jump_step = 0;
        }

        CheckToMap(map_data, coin);
        CenterEntityOnMap(map_data);
    }

    if(come_back_time_ > 0)
    {
        come_back_time_ --;
        if(come_back_time_ == 0) //reset again
        {
            on_ground_ = false;
            if(x_pos_ > 256) // lui 4 o tile map
            {
                x_pos_ -= 256;
                
            }
            else {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            x_val_ = 0;
            y_val_ = 0;
        }
    }
}

void MainObject::CenterEntityOnMap(Map& map_data)//map di chuyen theo nv
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/3); //map di chuyen khi nhan vat di duoc 1/3
    
    if(map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = y_pos_ -(SCREEN_HEIGHT/2);
    if(map_data.start_y_ < 0)
    {
        map_data.start_y_ = 0;
    }
    else if(map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}

void MainObject::CheckToMap(Map& map_data, Mix_Chunk* collect_coin[1]) //check va cham
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;
    //check theo chieu ngang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE; //chia ra so o
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;
    bool kt = false;

    //x1,y1             x2,y1


   //x1,y2              x2,y2

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0) //main object moving to right
        {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if(val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                Mix_PlayChannel(-1, collect_coin[1], 0);
                IncreaseMoney();
            }
            else if(val1 == HEART_TILE || val2 == HEART_TILE)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
            }
            else if(val1 == BlOCK_TILE || val2 == BlOCK_TILE)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                UpBlock();
            }
            else{
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos_ = x2*TILE_SIZE;
                    x_pos_ -= width_frame_ + 1;
                    x_val_ = 0;
                }
            }

        }
        else if(x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if(val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                Mix_PlayChannel(-1, collect_coin[1], 0);
                IncreaseMoney();
            }
            else if(val1 == HEART_TILE || val2 == HEART_TILE)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
            }
            else if(val1 == BlOCK_TILE || val2 == BlOCK_TILE)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                UpBlock();
            }
            else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos_ = (x1 + 1)*TILE_SIZE;
                    x_val_ = 0;
                }
            }
        }
    } 

    //check vertical(chieu doc)
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val_ > 0) //roi tu do
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if(val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                Mix_PlayChannel(-1, collect_coin[1], 0);
                IncreaseMoney();
            }
            else if(val1 == HEART_TILE || val2 == HEART_TILE)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
            }
            else if(val1 == BlOCK_TILE || val2 == BlOCK_TILE)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                UpBlock();
            }
            else
            {
                if(val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos_ = y2*TILE_SIZE;
                    y_pos_ -= (height_frame_ + 1);
                    y_val_ = 0;
                    on_ground_ = true;

                    if(status_ == WALK_NONE)
                    {
                        status_ = WALK_RIGHT;
                    }
                }
            }
        }
        else if(y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseMoney();
                Mix_PlayChannel(-1, collect_coin[1], 0);
            }
            else if(val1 == HEART_TILE || val2 == HEART_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
            }
            else if(val1 == BlOCK_TILE || val2 == BlOCK_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                UpBlock();
            }
            else
            {
                if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
                {
                    y_pos_ = (y1 + 1)*TILE_SIZE;
                    y_val_ = 0;
                    on_ground_ = false;
                }
            }
        }
    } //else on_ground_ = false;

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(x_pos_ < 0) { //cham ban do
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ > map_data.max_x_) //qua gioi han ban do
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;

    }

    if(y_pos_ > map_data.max_y_) // roi xuong vuc
    {
        underground++;
        come_back_time_ = 60;
    }

}


bool MainObject::SpikeTile(Map& map_data) //check va cham
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;
    //check theo chieu ngang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE; //
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;
    bool kt = false;

    //x1,y1             x2,y1


   //x1,y2              x2,y2

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0) //main object moving to right
        {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

             if(val1 == SPIKE_TILE || val2 == SPIKE_TILE)
            {
                return true;
            }

        }
        else if(x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if(val1 == SPIKE_TILE || val2 == SPIKE_TILE)
            {
                return true;
            }
        }
    } 

    //check vertical(chieu doc)
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val_ > 0) //roi tu do
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if(val1 == SPIKE_TILE || val2 == SPIKE_TILE)
            {
                return true;
            }
        }
        else if(y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 == SPIKE_TILE || val2 == SPIKE_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
            }
        }
    } 

    return false;
}

bool MainObject::BOOM(Map& map_data) //check va cham
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;
    //check theo chieu ngang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE; //
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;
    bool kt = false;

    //x1,y1             x2,y1


   //x1,y2              x2,y2

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0) //main object moving to right
        {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

             if(val1 == BOOM_TILE || val2 == BOOM_TILE)
            {
                return true;
            }

        }
        else if(x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if(val1 == BOOM_TILE || val2 == BOOM_TILE)
            {
                return true;
            }
        }
    } 

    //check vertical(chieu doc)
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val_ > 0) //roi tu do
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if(val1 == BOOM_TILE || val2 == BOOM_TILE)
            {
                return true;
            }
        }
        else if(y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 == BOOM_TILE || val2 == BOOM_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
            }
        }
    } 

    return false;
}

bool MainObject::CheckHeart(Map& map_data) //check va cham
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;
    //check theo chieu ngang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE; //
    x2 = (x_pos_ + x_val_ + width_frame_ - 1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;
    bool kt = false;

    //x1,y1             x2,y1


   //x1,y2              x2,y2

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0) //main object moving to right
        {

            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

             if(val1 == HEART_TILE || val2 == HEART_TILE)
            {
                return true;
            }

        }
        else if(x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if(val1 == HEART_TILE || val2 == HEART_TILE)
            {
                return true;
            }
        }
    } 

    //check vertical(chieu doc)
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val_ > 0) //roi tu do
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if(val1 == HEART_TILE || val2 == HEART_TILE)
            {
                return true;
            }
        }
        else if(y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if(val1 == HEART_TILE || val2 == HEART_TILE)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
            }
        }
    } 

    return false;
}

void MainObject::IncreaseMoney()
{
    money_count++;
}

void MainObject::UpBlock()
{
    block_count++;
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
    if(on_ground_ == true)
    {   
        if(status_ == WALK_LEFT)
        {
            LoadImg("img//player_left.png", des);
        }
        else 
        {
            LoadImg("img//player_right.png", des);
        }
    }
    else
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("img//jum_left.png", des);
        }
        else
        {
            LoadImg("img//jum_right.png", des);
        }
    }
}

void MainObject::ChangeBullet()
{
    bullet_type_ = (bullet_type_ == BulletObject::LASER_BULLET) ? BulletObject::SPHERE_BULLET : BulletObject::LASER_BULLET;
}

void MainObject::ResetPlay()
{
    //set_comebacktime(60);
    set_x_pos(0);
    set_y_pos(0);
}