
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

void GameMap::PlaceBlock_RIGHT(int x, int y)
{
    int map_x = x / TILE_SIZE + 2;
    int map_y = y / TILE_SIZE + 1;

    if (map_x >= 0 && map_x < MAX_MAP_X && map_y >= 0 && map_y < MAX_MAP_Y)
    {
        if(game_map_.tile[map_y][map_x] == 0)
        {
            game_map_.tile[map_y][map_x] = BLOCK_TAKE;

            if (map_x > game_map_.max_x_ / TILE_SIZE)  //cap nhat lai max_x _y
                game_map_.max_x_ = (map_x + 1) * TILE_SIZE;
            if (map_y > game_map_.max_y_ / TILE_SIZE)
                game_map_.max_y_ = (map_y + 1) * TILE_SIZE;
        }
    }
}

void GameMap::PlaceBlock_LEFT(int x, int y)
{
    int map_x = x / TILE_SIZE - 1;
    int map_y = y / TILE_SIZE + 1;

    if (map_x >= 0 && map_x < MAX_MAP_X && map_y >= 0 && map_y < MAX_MAP_Y)
    {
        if(game_map_.tile[map_y][map_x] == 0)
        {
            game_map_.tile[map_y][map_x] = BLOCK_TAKE;

            if (map_x > game_map_.max_x_ / TILE_SIZE)
                game_map_.max_x_ = (map_x + 1) * TILE_SIZE;
            if (map_y > game_map_.max_y_ / TILE_SIZE)
                game_map_.max_y_ = (map_y + 1) * TILE_SIZE;
        }
    }
}

bool GameMap::CheckBlockBullet(BulletObject* pt)
{
    for(int kk = 0; kk < MAX_MAP_Y; kk ++)
    {
        for(int ll = 0; ll < MAX_MAP_X; ll ++)
        {	
            SDL_Rect block_tile;
            if(game_map_.tile[kk][ll] == BLOCK_TAKE)
            {
                block_tile.x = ll*TILE_SIZE;
                block_tile.y = kk*TILE_SIZE;
                block_tile.w = 50;
                block_tile.h = 50;
                bool bColblock = SDLCommonFunc::CheckCollision(pt->GetRect(), block_tile);
                if(bColblock)
                    return true;
            }
            //SDL_Rect bullet = pt->GetRect();
            
        }
    }
    return false;
}