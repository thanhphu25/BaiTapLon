
#include "HeaderGuard/game_map.h"

void GameMap::Load_Map(const std::string& path)
{
    FILE* fp = NULL;
    fopen_s(&fp, path.c_str(), "rb"); //doc file
    if(fp == NULL)
    {
        return; 
    }
    /*std::ifstream file(name, std::ios::binary);
    if(!file.is_open()){
        std::cout << "Not open file" <<std::endl;
        return;
    }*/

    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;
    for(int i = 0; i < MAX_MAP_Y; i++)
    {
        for(int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf_s(fp, "%d", &game_map_.tile[i][j]); //doc du lieu
            //file >> game_map_.tile[i][j];
            int val = game_map_.tile[i][j];
            if(val > 0)
            {
                if(j > game_map_.max_x_)
                {
                    game_map_.max_x_ = j;
                }

                if(i > game_map_.max_y_)
                {
                    game_map_.max_y_ = i;
                }
            }
        }
    }

    game_map_.max_x_ = (game_map_.max_x_ + 1)*TILE_SIZE; //gia tri toi da cua ban do
    game_map_.max_y_ = (game_map_.max_y_ + 1)*TILE_SIZE;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;

    game_map_.file_name_ = path; //luu lai de phong
    fclose(fp);
    //file.close();

}

void GameMap::LoadTiles(SDL_Renderer* screen) //load img cho anh tuong ung
{
    char file_img[30];
    FILE* fp = NULL;

    for(int i = 0; i < MAX_TILE; i++)
    {
        sprintf_s(file_img, "map/%d.png", i);

        fopen_s(&fp, file_img, "rb");
        if(fp == NULL)
        {
            continue;
        }

        fclose(fp);

        tile_mat[i].LoadImg(file_img, screen); //load tam anh len
    }
}

void GameMap::DrawMap(SDL_Renderer* screen)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x_/TILE_SIZE;

    x1 = (game_map_.start_x_%TILE_SIZE)*-1; //lui ve 1 ti de khong khuyet anh
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map_.start_y_/TILE_SIZE;

    y1 = (game_map_.start_y_%TILE_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    for(int i = y1; i < y2; i+=TILE_SIZE)
    {
        map_x = game_map_.start_x_/TILE_SIZE;
        for(int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];
            if(val > 0)
            {
                tile_mat[val].SetRect(j, i);
                tile_mat[val].Render(screen);//man hinh
            }
            map_x++;
        }
        map_y++;
    }
}
 
/*void GameMap::AddMap(const Map& map) {

    for (int i = 0; i < 20; ++i) {
        Map newMap;

        newMap.start_x_ = 0;
        newMap.start_y_ = 0;
        newMap.max_x_ = 20 * TILE_SIZE; 
        newMap.max_y_ = 10 * TILE_SIZE;

        map_list_.push_back(newMap);
    }
}*/