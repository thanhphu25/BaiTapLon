// SDL2_GAME.CPP
//
#include "HeaderGuard/CommonF.h"
#include "HeaderGuard/BaseObject.h"
#include "HeaderGuard/game_map.h"
#include "HeaderGuard/MainObject.h"
#include "HeaderGuard/Timer.h"
#include "HeaderGuard/ThreatsObject.h"
#include "HeaderGuard/BulletObject.h"
#include "HeaderGuard/Effect.h"
#include "HeaderGuard/TextObject.h"
#include "HeaderGuard/PowerPlayer.h"
#include "HeaderGuard/Geometric.h"
#include "HeaderGuard/BossObject.h"
#include "HeaderGuard/Rock.h"

BaseObject g_background, g_menu_screen, g_lose, g_win, g_hint;
TTF_Font* font_time = NULL;
int boos_heart = 0, time_time, time_game_ = 300, power_number;
int x_pos, y_pos;
int num_die = 0;

bool InitData() 
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if(ret < 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("PTP Clone Pixel Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(g_window == NULL) {
		success = false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if(g_screen == NULL)
			success = false;
		else 
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}

		if(TTF_Init() == -1)
		{
			success = false;
		}

		font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
		if(font_time == NULL)
		{
			success = false;
		}

		if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			success = false;
		g_sound_bullet[0] = Mix_LoadWAV("audio//laze.wav");
		g_sound_bullet[1] = Mix_LoadWAV("audio//dan1.wav");
		g_sound_exp[0] = Mix_LoadWAV("audio//bomb.wav");
		g_sound_effect[0] = Mix_LoadWAV("audio//jump.wav");
		g_sound_effect[1] = Mix_LoadWAV("audio//collectcoin.wav");

		if(g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL || g_sound_effect[0] == NULL || g_sound_effect[1] == NULL)
			success = false;
	}

	return success;
}

bool LoadBackground() 
{
	bool ret = g_background.LoadImg("img//bg.jpg", g_screen);
	if(ret == false)
		return false;

	return true;
}

void close()
{
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();  
	SDL_Quit();
}

std::vector<RockObject*> MakeRock()
{
	std::vector<RockObject*> rock_s;

	RockObject* rock = new RockObject[10];
	for(int i = 0; i < 10; i++)
	{
		RockObject* p_rock = (rock + i);
		if(p_rock != NULL)
		{
			p_rock->LoadImg("img//rock.png", g_screen);;
			p_rock->set_x_pos(2000 + i*1000);
			p_rock->set_y_pos(35);


			rock_s.push_back(p_rock);
		}
	}

	return rock_s;
}


std::vector<ThreatsObject*> MakeThreatList()
{
	std::vector<ThreatsObject*> list_threats;

	ThreatsObject* dynamic_threats = new ThreatsObject[30];
	for(int i = 0; i < 30; i++)
	{
		ThreatsObject* p_threat = (dynamic_threats + i);
		if(i < 15)
		if(p_threat != NULL)
		{
			p_threat->LoadImg("img//threat_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
			p_threat->set_x_pos(500 + i*500);
			p_threat->set_y_pos(200);

			int pos1 = p_threat->get_x_pos() - 60;
			int pos2 = p_threat->get_x_pos() + 60;
			p_threat->SetAnimationPos(pos1, pos2);
			p_threat->set_input_left(1);

			//BulletObject* p_bullet = new BulletObject();
			//p_threat->InitBullet(p_bullet, g_screen);

			list_threats.push_back(p_threat);
		}
		if(i >= 15)
		if(p_threat != NULL)
		{
			p_threat->LoadImg("img//blade.jpg", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatsObject::BLADE_MOVE);
			p_threat->set_x_pos(500 + i*500);
			p_threat->set_y_pos(200);

			int pos1 = p_threat->get_x_pos() - 60;
			int pos2 = p_threat->get_x_pos() + 60;
			p_threat->SetAnimationPos(pos1, pos2);
			p_threat->set_input_left(1);

			//BulletObject* p_bullet = new BulletObject();
			//p_threat->InitBullet(p_bullet, g_screen);

			list_threats.push_back(p_threat);
		}
	}


	ThreatsObject* threats_objs = new ThreatsObject[30];

	for(int i = 0; i < 15; i++)
	{
		ThreatsObject* p_threat = (threats_objs + i);
		if(p_threat != NULL)
		{
			p_threat->LoadImg("img//threat_level.png", g_screen);
			p_threat->set_clips();
			SDL_Delay(100);
			p_threat->set_x_pos(700 + i*1200); //1200
			p_threat->set_y_pos(250);
			p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
			p_threat->set_input_left(0);

			BulletObject* p_bullet = new BulletObject();
			p_threat->InitBullet(p_bullet, g_screen);

			list_threats.push_back(p_threat);
			
		}
	}

	return list_threats;
}


Mix_Music* g_music = NULL; 

bool InitAudio() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return false;
    }
    return true;
}

bool LoadMusic() {
    g_music = Mix_LoadMUS("audio//nhacnen.mp3"); 
    if (g_music == NULL) {
        return false;
    }
    return true;
}

void PlayMusic() {
    //phat nhac voi so lan lap vo han
    Mix_PlayMusic(g_music, -1);
}

void CleanUpAudio() {
    Mix_FreeMusic(g_music);
    Mix_CloseAudio();
}


int main(int argc, char* args[])
{
	ImpTimer fps_timer;

	if(InitData() == false)
		return -1;

	if (!InitAudio()) 
        return -1;

	if(LoadBackground() == false)
		return -1;

	GameMap game_map;
	 game_map.Load_Map("map/map01.dat");
	 game_map.LoadTiles(g_screen);


	MainObject p_player;
	p_player.LoadImg("img//player_right.png", g_screen);
	p_player.set_clips();

	RockObject p_rock;
	p_rock.LoadImg("img//rock.png", g_screen);

	PowerPlayer player_power;
	player_power.Init(g_screen);

	PlayerMoney player_money;
	player_money.Init(g_screen);
	player_money.SetPos(SCREEN_WIDTH*0.5 - 300, 8);

	PlayerBlock player_block;
	player_block.Init(g_screen);
	player_block.SetPos(SCREEN_WIDTH - 400, 8);


	std::vector<ThreatsObject*> threats_list;// = MakeThreatList();
	std::vector<RockObject*> rock_s;

	//BOSSSSSSSSSSSSSSSSSSSSSss
	BossObject bossObject;
	bossObject.LoadImg("img//boss_object.png", g_screen);
	bossObject.set_clips();
	int xPosBoss = MAX_MAP_X*TILE_SIZE - SCREEN_WIDTH*0.6;
	bossObject.set_xpos(xPosBoss);
	bossObject.set_ypos(10);

	Effect exp_threat;
	bool tRet = exp_threat.LoadImg("img//exp3.png", g_screen);
	if(!tRet) return -1;
	exp_threat.set_clips();

	Effect exp_main;
	bool ret = exp_main.LoadImg("img//exp3.png", g_screen);
    exp_main.set_clips();
    if (!ret) return 0;

	TextObject time_game;
	time_game.SetColor(TextObject::BLACK_TEXT);

	TextObject mark_game;
	mark_game.SetColor(TextObject::BLACK_TEXT);
	UINT mark_value = 0;

	TextObject money_game;
	money_game.SetColor(TextObject::BLACK_TEXT);

	//TextObject mark_game;
	//mark_game.SetColor(TextObject::BLACK_TEXT);
	TextObject count_coin;
	count_coin.SetColor(TextObject::BLACK_TEXT);

	TextObject block_game;
	block_game.SetColor(TextObject::BLACK_TEXT);

	if (!LoadMusic()) {
        return -1;
    }
    PlayMusic();

	bool real_quit = false;

	BaseObject StartButton[2];
	BaseObject ExitButton[2];
	BaseObject ContinueButton[2];
	BaseObject Hint[2];

	Hint[0].LoadImg("img//menu//hint.png",g_screen);
	Hint[1].LoadImg("img//menu//hint2.png",g_screen);
	StartButton[0].LoadImg("img//menu//play.png",g_screen);
	StartButton[1].LoadImg("img//menu//play2.png",g_screen);
	ExitButton[0].LoadImg("img//menu//exit.png",g_screen);
	ExitButton[1].LoadImg("img//menu//exit2.png",g_screen);
	ContinueButton[0].LoadImg("img//menu//continue.png",g_screen);
	ContinueButton[1].LoadImg("img//menu//continue2.png",g_screen);
	
	StartButton[0].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 - 50);
	StartButton[1].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 - 50);
	
	ExitButton[0].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 + 150);
	ExitButton[1].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 + 150);
	
	Hint[0].SetRect(SCREEN_WIDTH/8 ,SCREEN_HEIGHT/2 );
	Hint[1].SetRect(SCREEN_WIDTH/8 ,SCREEN_HEIGHT/2 );

	ContinueButton[0].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 + 50);
	ContinueButton[1].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 + 50);

    int MousePosX = 0;
    int MousePosY = 0;
	g_menu_screen.LoadImg("img//menu//menu_game.png", g_screen);

    bool quit_ = false;
    while(!quit_)
    {
        p_player.set_x_pos(0);
        p_player.set_y_pos(0);
        p_player.set_status_();
        p_player.set_input_right(0);

        std::vector<ThreatsObject*> threats_list = MakeThreatList();
		std::vector<RockObject*> rock_s = MakeRock();
        
        bool menu_quit = false;
        bool is_quit = false;
        int num_die = 1;
        player_power.Init(g_screen);
		bool hint_show = false;

        while(!menu_quit)
        {
            SDL_RenderClear(g_screen);
            g_menu_screen.Render(g_screen, NULL);
            while(SDL_PollEvent(&g_event) != 0)
            {
                if(g_event.type == SDL_MOUSEMOTION)
                {
                    MousePosX = g_event.motion.x;
                    MousePosY = g_event.motion.y;
                }
                if(g_event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (g_event.button.button == SDL_BUTTON_LEFT)
                    {
                        if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,StartButton[0].GetRect()) == true)
                        {
                            menu_quit = true;
							is_quit = false;
							
                            p_player.ResetPlay();
                            for(int i = 0; i < threats_list.size(); i++)
							{
								ThreatsObject* p_threat = threats_list.at(i);
								if(p_threat)
								{
									p_threat->Free();
									p_threat = NULL;
								}
							}
                             threats_list = MakeThreatList();
                             game_map.Load_Map("map//map01.dat");
                             game_map.LoadTiles(g_screen);
							 p_player.set_money(0);
							 p_player.set_block(0);
							 mark_value = 0;
							 time_game_ = 499;
                        }
                        if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,ExitButton[0].GetRect()) == true )
                        {
                            menu_quit = true;
                            is_quit = true;
                            quit_ = true;
                        }
						if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,Hint[0].GetRect()) == true )
                        {
							hint_show = true;
							menu_quit = true;
							is_quit = true;
                        }
                         if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,ContinueButton[0].GetRect()) == true)
                         { 
							int nb = player_power.get_number();
							p_player.set_health(nb);
                         	if(p_player.get_health() > 0)
                         	{
                         		int x, y, heath, money, time_;
                         		SDLCommonFunc::LoadSaveFile(x, y, heath, money, time_);
                         		p_player.set_x_pos(x);
								p_player.set_y_pos(y);
								for(int i = 1; i <= 3-heath; i++) 
								{
									player_power.Decrease();
									num_die++;
								}
								p_player.set_money(money);
								time_game_ = time_;
                         		menu_quit = true;
                         	}
                         }
                    }
                }
            }

            if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,StartButton[0].GetRect()) == true)
            {
                StartButton[1].Render(g_screen);
            }
            else
            {
                StartButton[0].Render(g_screen);
            }
            if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
            {
                ExitButton[1].Render(g_screen);
            }
            else
            {
                ExitButton[0].Render(g_screen);
            }
			if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,ContinueButton[0].GetRect()) == true)
            {
                ContinueButton[1].Render(g_screen);
            }
            else
            {
                ContinueButton[0].Render(g_screen);
            }
			if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,Hint[0].GetRect()) == true)
            {
                Hint[1].Render(g_screen);
            }
            else
            {
                Hint[0].Render(g_screen);
            }
			
            SDL_RenderPresent(g_screen);
            SDL_Delay(100);
        }

	while(hint_show)
	{
		SDL_RenderClear(g_screen);
		g_hint.LoadImg("img//menu//howtoplay.png", g_screen);
		g_hint.Render(g_screen, NULL);
		while(SDL_PollEvent(&g_event) != 0)
		if(g_event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (g_event.button.button == SDL_BUTTON_LEFT)
			{
				hint_show = false;
				g_hint.Free();
				menu_quit = false;
			}
		}
		SDL_RenderPresent(g_screen);

	}
	
	while(!is_quit) 
	{
		fps_timer.start();
		while(SDL_PollEvent(&g_event) != 0)
		{
			if(g_event.type == SDL_QUIT)
			{
				is_quit  = true;
				quit_ = true;
			}

			else if(g_event.type == SDL_KEYDOWN)
            {
                if(g_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    fps_timer.paused();
                    is_quit = SDLCommonFunc::Menu(g_screen);
                    fps_timer.unpaused();
                }
                    
            }
			
			p_player.HandelInputAction(g_event, g_screen, g_sound_bullet, g_sound_effect);

			if(g_event.type == SDL_MOUSEBUTTONDOWN)
			{
				if(g_event.button.button == SDL_BUTTON_RIGHT)  //dat block
				{
					if(p_player.get_status() == MainObject::WALK_RIGHT && p_player.GetBlockCount() > 0)
					{
						game_map.PlaceBlock_RIGHT(p_player.get_x_pos(), p_player.get_y_pos());
						p_player.DrecreaseBlock();
					}
					else if(p_player.get_status() == MainObject::WALK_LEFT  && p_player.GetBlockCount() > 0)
					{
						game_map.PlaceBlock_LEFT(p_player.get_x_pos(), p_player.get_y_pos());
						p_player.DrecreaseBlock();
					}
				}
			}
		}

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		//game_map.DrawMap(g_screen);
		Map map_data = game_map.getMap();

		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data, g_sound_effect);
		p_player.Show(g_screen);

		x_pos = p_player.get_x_pos();
		y_pos = p_player.get_y_pos();

		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		//DRAW GEOMETRIC
		GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
		ColorData color_data(255, 227, 250); //0, 80, 150
		Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

		GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38);
		ColorData color_data2(255, 0, 0);
		Geometric::RenderOutLine(outLineSize, color_data2, g_screen);
	
		player_power.Show(g_screen);
		player_money.Show(g_screen);
		player_block.Show(g_screen);

		if(p_player.GetOnGround() > 0)  //roi xuong vuc = die
		{
			player_power.Decrease();
			player_power.Render(g_screen);
			p_player.SetOnGround(0);
			num_die++;
		}
		
		bool bCol3 = p_player.SpikeTile(map_data);
		if(bCol3)
		{	
			int width_exp_frame = exp_main.get_frame_height();
			int heiht_exp_height = exp_main.get_frame_width();
			for (int ex = 0; ex < 4; ex++)
			{
				int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
				int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

				exp_main.set_frame(ex);
				exp_main.SetRect(x_pos, y_pos);
				exp_main.Show(g_screen);
				SDL_RenderPresent(g_screen);
			}
			Mix_PlayChannel(-1, g_sound_exp[0], 0);
			player_power.Decrease();
			//player_power.Render(g_screen);
			num_die++;
			SDL_Delay(1000);
			continue;
		}
		bCol3 = false;

		bool bCol4 = p_player.CheckHeart(map_data);
		if(bCol4 && num_die > 1)
		{
			player_power.Increase();
			num_die--;
		}

		bool bCol5 = p_player.BOOM(map_data);
		if(bCol5)
		{
			int width_exp_frame = exp_main.get_frame_height();
			int heiht_exp_height = exp_main.get_frame_width();
			for (int ex = 0; ex < 4; ex++)
			{
				int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
				int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

				exp_main.set_frame(ex);
				exp_main.SetRect(x_pos, y_pos);
				exp_main.Show(g_screen);
				SDL_RenderPresent(g_screen);
			}
			Mix_PlayChannel(-1, g_sound_exp[0], 0);
			player_power.Decrease();
			player_power.Decrease();
			player_power.Decrease();
			num_die = 4;
			SDL_Delay(1000);
		}

		if(num_die > 3)
		{
			{
				SDL_RenderClear(g_screen);
				g_lose.LoadImg("img//you_lose.png", g_screen);
				g_lose.Render(g_screen, NULL);

				mark_game.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

				count_coin.SetText("Coin: ");
				count_coin.LoadFromRenderText(font_time, g_screen);
				count_coin.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100);
				money_game.RenderText(g_screen, SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2 + 100);

				SDL_RenderPresent(g_screen);
				SDL_Delay(1000);
				g_lose.Free();
				for(int i = 0; i < threats_list.size(); i++)
				{
					ThreatsObject* p_threat = threats_list.at(i);
					if(p_threat)
					{
						p_threat->Free();
						p_threat = NULL;
					}
				}
				is_quit = SDLCommonFunc::MenuLast(g_screen);
			}
		}

		//ROCK
		for(int i = 0; i < rock_s.size(); i++)
		{
			RockObject* rock = rock_s.at(i);
			if(rock != NULL)
			{
				rock->SetMapXY(map_data.start_x_, map_data.start_y_);
				if(abs(p_player.get_x_pos() - rock->get_x_pos()) < 80)
					rock->DoPlayer(map_data);
				else rock->set_y_pos(35);
				rock->Show(g_screen);
			}

			SDL_Rect rect_rock = rock->GetRectFrame();
			SDL_Rect rect_player = p_player.GetRectFrame();
			bool bCol = SDLCommonFunc::CheckCollision(rect_player, rect_rock);

			if(bCol)
			{
				int width_exp_frame = exp_main.get_frame_height();
				int heiht_exp_height = exp_main.get_frame_width();
				for (int ex = 0; ex < 4; ex++)
				{
					int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
					int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

					exp_main.set_frame(ex);
					exp_main.SetRect(x_pos, y_pos);
					exp_main.Show(g_screen);
					SDL_RenderPresent(g_screen);
				}
				Mix_PlayChannel(-1, g_sound_exp[0], 0);

				num_die++;
				if(num_die <= 3)
				{
					//p_player.SetOnGround(0);
					p_player.SetRect(0, 0);
					p_player.set_comebacktime(60);
					player_power.Decrease();
					player_power.Render(g_screen);
					SDL_Delay(500);
					continue;
				}
				else
				{
					SDL_RenderClear(g_screen);
					g_lose.LoadImg("img//you_lose.png", g_screen);
					g_lose.Render(g_screen, NULL);

					mark_game.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

					count_coin.SetText("Coin: ");
					count_coin.LoadFromRenderText(font_time, g_screen);
					count_coin.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100);
					money_game.RenderText(g_screen, SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2 + 100);

					SDL_RenderPresent(g_screen);
					SDL_Delay(1000);
					g_lose.Free();
					for(int i = 0; i < threats_list.size(); i++)
					{
						ThreatsObject* p_threat = threats_list.at(i);
						if(p_threat)
						{
							p_threat->Free();
							p_threat = NULL;
						}
					}
					for(int i = 0; i < rock_s.size(); i++)
					{
						RockObject* rock = rock_s.at(i);
						if(rock)
						{
							rock->Free();
							rock = NULL;
						}
					}
					is_quit = SDLCommonFunc::MenuLast(g_screen);
					
				}
			}
		}

		
		for(int i = 0; i < threats_list.size(); i++)
		{
			ThreatsObject* p_threat = threats_list.at(i);
			if(p_threat != NULL)
			{
				p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
				p_threat->ImpMoveType(g_screen);
				p_threat->DoPlayer(map_data);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);


				SDL_Rect rect_player = p_player.GetRectFrame();
				bool bCol1 = false;
				std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();

				for(int jj = 0; jj < tBullet_list.size(); ++jj)
				{
					BulletObject* pt_bullet = tBullet_list.at(jj);
					if(pt_bullet)
					{
						if(game_map.CheckBlockBullet(pt_bullet)) //check block vs dan quai
						{
							pt_bullet->set_is_move(false);
							//p_threat->RemoveBullet(jj);
						}

						bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player)&&pt_bullet->get_is_move(); //dan cua quai va nhan vat game
						if(bCol1 == true)
						{
							pt_bullet->set_is_move(false);
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
							//p_threat->RemoveBullet(jj);
							break;
						}

						
					}
				}

				SDL_Rect rect_threat = p_threat->GetRectFrame();
				bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat); //va cham giua nhan vat va quai vat

				if(bCol1 || bCol2)
				{
					int width_exp_frame = exp_main.get_frame_height();
               		int heiht_exp_height = exp_main.get_frame_width();
               		for (int ex = 0; ex < 4; ex++)
               		{
                   		int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                  		int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

                   		exp_main.set_frame(ex);
                   		exp_main.SetRect(x_pos, y_pos);
                   		exp_main.Show(g_screen);
                   		SDL_RenderPresent(g_screen);
               		}
					Mix_PlayChannel(-1, g_sound_exp[0], 0);

					num_die++;
					if(num_die <= 3)
					{
						//p_player.SetOnGround(0);
						p_player.SetRect(0, 0);
						p_player.set_comebacktime(60);
						player_power.Decrease();
						player_power.Render(g_screen);
						SDL_Delay(1000);
						continue;
					}
					else
					{
						SDL_RenderClear(g_screen);
						g_lose.LoadImg("img//you_lose.png", g_screen);
						g_lose.Render(g_screen, NULL);

						mark_game.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

						count_coin.SetText("Coin: ");
						count_coin.LoadFromRenderText(font_time, g_screen);
						count_coin.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100);
						money_game.RenderText(g_screen, SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2 + 100);

						SDL_RenderPresent(g_screen);
						SDL_Delay(1000);
						g_lose.Free();
						for(int i = 0; i < threats_list.size(); i++)
						{
							ThreatsObject* p_threat = threats_list.at(i);
							if(p_threat)
							{
								p_threat->Free();
								p_threat = NULL;
							}
						}
						for(int i = 0; i < rock_s.size(); i++)
						{
							RockObject* rock = rock_s.at(i);
							if(rock)
							{
								rock->Free();
								rock = NULL;
							}
						}
						is_quit = SDLCommonFunc::MenuLast(g_screen);
						
					}
				}

			}
		}

		int frame_exp_width = exp_threat.get_frame_height();
		int frame_exp_height = exp_threat.get_frame_height();
		std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
		for(int r = 0; r < bullet_arr.size(); r++)
		{
			BulletObject* p_bullet = bullet_arr.at(r);
			if(p_bullet != NULL)
			{
				for(int t = 0; t < threats_list.size(); t++)
				{
					ThreatsObject* obj_threat = threats_list.at(t);
					if(obj_threat != NULL)
					{
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_height_frame();

						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect); //va cham dan va quai

						if(bCol && p_bullet->get_bullet_type() == BulletObject::LASER_BULLET)
						{
							num_die++;
							player_power.Decrease();
						}
			

						if(bCol)
						{
							mark_value++;
							for(int ex = 0; ex < NUM_FRAME_EF; ex++)
							{
								int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
								int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
							}
							p_player.RemoveBullet(r);
							Mix_PlayChannel(-1, g_sound_exp[0], 0); //am thanh vu no
							obj_threat->Free();
							threats_list.erase(threats_list.begin() + t);
						}
					}
				}
			}
		}
		power_number = num_die;

		//Show game time
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = time_game_ - time_val;
		time_time = val_time;
		if(val_time <= 0)
		{
			SDL_RenderClear(g_screen);
			g_lose.LoadImg("img//you_lose.png", g_screen);
			g_lose.Render(g_screen, NULL);
			SDL_RenderPresent(g_screen);
			SDL_Delay(1000);
			g_lose.Free();
			for(int i = 0; i < threats_list.size(); i++)
			{
				ThreatsObject* p_threat = threats_list.at(i);
				if(p_threat)
				{
					p_threat->Free();
					p_threat = NULL;
				}
			}
			for(int i = 0; i < rock_s.size(); i++)
			{
				RockObject* rock = rock_s.at(i);
				if(rock)
				{
					rock->Free();
					rock = NULL;
				}
			}
			is_quit = SDLCommonFunc::MenuLast(g_screen);
		}
		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;

			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
		}

		//Erase map
		if(val_time%50 == 0)
		{	
			int xp = p_player.get_x_pos();
			int yp = p_player.get_y_pos();
			game_map.EraseMap(xp, yp);
		}

		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark: ");
		strMark += val_str_mark;
		mark_game.SetText(strMark);
		mark_game.LoadFromRenderText(font_time, g_screen);
		mark_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);

		int money_count = p_player.GetMoneyCount();
		std::string money_str = std::to_string(money_count);
		money_game.SetText(money_str);
		money_game.LoadFromRenderText(font_time, g_screen);
		money_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);

		int block_count = p_player.GetBlockCount();
		std::string block_str = std::to_string(block_count);
		block_game.SetText(block_str);
		block_game.LoadFromRenderText(font_time, g_screen);
		block_game.RenderText(g_screen, SCREEN_WIDTH - 330, 15);


		//Show boss
		
		int val = MAX_MAP_X*TILE_SIZE - (map_data.start_x_ + p_player.GetRect().x);
		if(val <= SCREEN_WIDTH*2)
		{
			SDL_Rect rect_player = p_player.GetRectFrame();
			SDL_Rect r_boss = bossObject.GetRectFrame();
			bossObject.SetMapXY(map_data.start_x_, map_data.start_y_);
			bossObject.DoPlayer(map_data);
			bossObject.MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			bossObject.Show(g_screen);
			

			bool bCol1 = false;
			std::vector<BulletObject*> tBullet_list = bossObject.get_bullet_list();
			for(int jj = 0; jj < tBullet_list.size(); ++jj)
			{
				BulletObject* pt_bullet = tBullet_list.at(jj);
				if(pt_bullet)
				{
					bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player)&&pt_bullet->get_is_move(); //dan cua boss va nhan vat game
					if(bCol1 == true)
					{
						pt_bullet->set_is_move(false);
						Mix_PlayChannel(-1, g_sound_exp[0], 0);
						//p_threat->RemoveBullet(jj);
						break;
					}
				}
			}
			power_number = num_die; //*
			bool bCol = SDLCommonFunc::CheckCollision(rect_player, r_boss); //boss cham nguoi
			if(bCol || bCol1)
			{
				int width_exp_frame = exp_main.get_frame_height();
               		int heiht_exp_height = exp_main.get_frame_width();
               		for (int ex = 0; ex < 4; ex++)
               		{
                   		int x_pos = (p_player.GetRect().x + p_player.get_frame_width()*0.5) - width_exp_frame*0.5;
                  		int y_pos = (p_player.GetRect().y + p_player.get_frame_height()*0.5) - heiht_exp_height*0.5;

                   		exp_main.set_frame(ex);
                   		exp_main.SetRect(x_pos, y_pos);
                   		exp_main.Show(g_screen);
                   		SDL_RenderPresent(g_screen);
               		}
					Mix_PlayChannel(-1, g_sound_exp[0], 0);
					num_die++;
					if(num_die <= 3)
					{
						p_player.SetRect(0, 0);
						p_player.set_comebacktime(60);
						player_power.Decrease();
						player_power.Render(g_screen);
						SDL_Delay(1000);
						continue;
					}
					else
					{
						SDL_RenderClear(g_screen);
						g_lose.LoadImg("img//you_lose.png", g_screen);
						g_lose.Render(g_screen, NULL);

						mark_game.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

						count_coin.SetText("Coin: ");
						count_coin.LoadFromRenderText(font_time, g_screen);
						count_coin.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100);
						money_game.RenderText(g_screen, SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2 + 100);

						SDL_RenderPresent(g_screen);
						SDL_Delay(1000);
						g_lose.Free();
						for(int i = 0; i < threats_list.size(); i++)
						{
							ThreatsObject* p_threat = threats_list.at(i);
							if(p_threat)
							{
								p_threat->Free();
								p_threat = NULL;
							}
						}
						for(int i = 0; i < rock_s.size(); i++)
						{
							RockObject* rock = rock_s.at(i);
							if(rock)
							{
								rock->Free();
								rock = NULL;
							}
						}
						is_quit = SDLCommonFunc::MenuLast(g_screen);
					}
			}
			//nhan vat ban boss

			int frame_exp_width = exp_threat.get_frame_height();
			int frame_exp_height = exp_threat.get_frame_height();
			std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
			for(int r = 0; r < bullet_arr.size(); r++)
			{
			BulletObject* p_bullet = bullet_arr.at(r);
			if(p_bullet != NULL)
			{		

				SDL_Rect bRect = p_bullet->GetRect();

				bool bCol = SDLCommonFunc::CheckCollision(bRect, r_boss); //va cham dan va quai

				if(bCol && p_bullet->get_bullet_type() == BulletObject::LASER_BULLET)
				{
					num_die++;
					player_power.Decrease();
				}
				
				if(bCol)
				{
					boos_heart++;
					for(int ex = 0; ex < NUM_FRAME_EF; ex++)
					{
						int x_pos = p_bullet->GetRect().x - frame_exp_width*0.5;
						int y_pos = p_bullet->GetRect().y - frame_exp_height*0.5;

						exp_threat.set_frame(ex);
						exp_threat.SetRect(x_pos, y_pos);
						exp_threat.Show(g_screen);
					}
					
					p_player.RemoveBullet(r);
					Mix_PlayChannel(-1, g_sound_exp[0], 0); //am thanh vu no

					if(boos_heart >= 40)
					{
						bossObject.Free();
						SDL_RenderClear(g_screen);
						g_win.LoadImg("img//you_win.png", g_screen);
						g_win.Render(g_screen, NULL);

						mark_game.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

						count_coin.SetText("Coin: ");
						count_coin.LoadFromRenderText(font_time, g_screen);
						count_coin.RenderText(g_screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 100);
						money_game.RenderText(g_screen, SCREEN_WIDTH/2 + 80, SCREEN_HEIGHT/2 + 100);

						SDL_RenderPresent(g_screen);
						SDL_Delay(1000);
						g_win.Free();
						for(int i = 0; i < threats_list.size(); i++)
						{
							ThreatsObject* p_threat = threats_list.at(i);
							if(p_threat)
							{
								p_threat->Free();
								p_threat = NULL;
							}
						}
						for(int i = 0; i < rock_s.size(); i++)
						{
							RockObject* rock = rock_s.at(i);
							if(rock)
							{
								rock->Free();
								rock = NULL;
							}
						}
						is_quit = SDLCommonFunc::MenuLast(g_screen);
					}
				}
							
			}
		}
			
		}


		SDL_RenderPresent(g_screen); //update man hinh

		int real_imp_time = fps_timer.get_ticks(); //thoi gian da troi qua
		int time_one_frame = 1000/FRAME_PER_SECOND; //mili giay

		if(real_imp_time < time_one_frame) //tao do tre de can bang thoi gian
		{
			int delay_time = time_one_frame - real_imp_time;
			if(delay_time >= 0)
				SDL_Delay(delay_time);

			//neu delaytime cang lon -> ctrinh chay bi cham dan
			//delaytime lon khi FRAME_PER_SC cang nho
			//fps cang nho -> time_one_frame cang to -> delaytime cang to
			//de ctrinh chay nhnah -> tang fps
		}
		

	}



	for(int i = 0; i < threats_list.size(); i++)
	{
		ThreatsObject* p_threat = threats_list.at(i);
		if(p_threat)
		{
			p_threat->Free();
			p_threat = NULL;
		}
	}

	for(int i = 0; i < rock_s.size(); i++)
	{
		RockObject* rock = rock_s.at(i);
		if(rock)
		{
			rock->Free();
			rock = NULL;
		}
	}

	threats_list.clear();
	rock_s.clear();
	}
	if(power_number < 5)
		SDLCommonFunc::SaveGame(x_pos, y_pos, 4-power_number, p_player.GetMoneyCount(), time_time);
	CleanUpAudio();
	close();
	return 0;
}