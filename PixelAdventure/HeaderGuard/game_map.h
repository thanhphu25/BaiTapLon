
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonF.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "MainObject.h"

#define MAX_TILE 20

class TileMat : public BaseObject
{
public:
    TileMat() {;}
    ~TileMat() {;}
};

class GameMap
{
public: 
    GameMap() {;}
    ~GameMap() {;}

    void Load_Map(const std::string& path); //doc thong tin trong file tile map
    void LoadTiles(SDL_Renderer* screen);  //load
    void DrawMap(SDL_Renderer* screen); //xay dung map
    Map getMap() const {return game_map_;};
    void SetMap(Map& map_data) {game_map_ = map_data;};
    void PlaceBlock_RIGHT(int x, int y);
    void PlaceBlock_LEFT(int x, int y);
    bool CheckBlockBullet(BulletObject* pt);
    void EraseMap(const int& x_pos, const int& y_pos);
private:
    Map game_map_;
    TileMat tile_mat[MAX_TILE];
};

#endif