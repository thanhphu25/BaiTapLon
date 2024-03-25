
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonF.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}  //Set kich thuoc cho rect_
    SDL_Rect GetRect() const {return rect_;}  //lay ra rect
    SDL_Texture* GetObject() const {return p_object_;}

    virtual bool LoadImg(std::string path, SDL_Renderer* screen); //vitural: ham ao, de mainObject co the dung
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
protected:
    SDL_Texture* p_object_; //Luu tru hinh anh
    SDL_Rect rect_; //Luu kich thuoc anh
};

#endif