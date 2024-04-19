
#include "HeaderGuard/Effect.h"


Effect::Effect()
{
    frame_ = 0;
    frame_width_ = 0;
    frame_height_ = 0;
}


Effect::~Effect()
{

}


bool Effect::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  if (ret == true)
  {
    frame_width_ = rect_.w/NUM_FRAME_EF;
    frame_height_ = rect_.h;
  }

  return ret;
}

void Effect::set_clips()
{
  //Clip the sprites
  if (frame_width_ > 0 && frame_height_ > 0)
  {
    frame_clip_[ 0 ].x = 0;
    frame_clip_[ 0 ].y = 0;
    frame_clip_[ 0 ].w = frame_width_;
    frame_clip_[ 0 ].h = frame_height_;

    frame_clip_[ 1 ].x = frame_width_;
    frame_clip_[ 1 ].y = 0;
    frame_clip_[ 1 ].w = frame_width_;
    frame_clip_[ 1 ].h = frame_height_;

    frame_clip_[ 2 ].x = frame_width_ * 2;
    frame_clip_[ 2 ].y = 0;
    frame_clip_[ 2 ].w = frame_width_;
    frame_clip_[ 2 ].h = frame_height_;

    frame_clip_[ 3 ].x = frame_width_ * 3;
    frame_clip_[ 3 ].y = 0;
    frame_clip_[ 3 ].w = frame_width_;
    frame_clip_[ 3 ].h = frame_height_;

    frame_clip_[ 4 ].x = frame_width_ * 4;
    frame_clip_[ 4 ].y = 0;
    frame_clip_[ 4 ].w = frame_width_;
    frame_clip_[ 4 ].h = frame_height_;

    frame_clip_[ 5 ].x = frame_width_ * 5;
    frame_clip_[ 5 ].y = 0;
    frame_clip_[ 5 ].w = frame_width_;
    frame_clip_[ 5 ].h = frame_height_;

    frame_clip_[ 6 ].x = frame_width_ * 6;
    frame_clip_[ 6 ].y = 0;
    frame_clip_[ 6 ].w = frame_width_;
    frame_clip_[ 6 ].h = frame_height_;

    frame_clip_[ 7 ].x = frame_width_ * 7;
    frame_clip_[ 7 ].y = 0;
    frame_clip_[ 7 ].w = frame_width_;
    frame_clip_[ 7 ].h = frame_height_;
  }
}


void Effect::Show(SDL_Renderer* screen)
{
    SDL_Rect* currentClip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, frame_width_, frame_height_};
    if (currentClip != NULL)
    {
      renderQuad.w = currentClip->w;
      renderQuad.h = currentClip->h;
    }

    SDL_RenderCopy(screen, p_object_, currentClip, &renderQuad );
}
