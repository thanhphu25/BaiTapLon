#ifndef EFFECT_H_
#define EFFETC_H_

#include "CommonF.h"
#include "BaseObject.h"

#define NUM_FRAME_EF 8

class Effect : public BaseObject
{

public:
    Effect();
    ~Effect();
public:
    void set_clips();
    void set_frame(const int& fr) {frame_ = fr;}
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const {return frame_width_;}
    int get_frame_height() const {return frame_height_;}

private:
    int frame_width_;
    int frame_height_;

    unsigned int frame_;
    SDL_Rect frame_clip_[NUM_FRAME_EF];
};


#endif