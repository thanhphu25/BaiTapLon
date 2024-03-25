#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int FRAME_PER_SECOND = 40; //fps: so frame/giay
const int SCREEN_WIDTH = 1280;  //1280
const int SCREEN_HEIGHT = 640; //640
const int SCREEN_BPP = 32;   //pixel

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 0
#define TILE_SIZE 64

#define MAX_MAP_X 400 //400
#define MAX_MAP_Y 10

#define STATE_MONEY 6

struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

struct Map
{
    int start_x_;
    int start_y_;

    int max_x_; //chi so
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    std::string file_name_;
    //int index;
};


//XU LY VA CHAM
namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}
#endif