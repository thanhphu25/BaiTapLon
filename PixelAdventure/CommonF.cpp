
#include "HeaderGuard/CommonF.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2) 
{
  int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;
 
  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;
 
  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }
 
  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }
 
  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }
 
  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }
  
  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }
 
  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }
 
  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }
 
  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }
 
   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }
 
  return false;
}

bool SDLCommonFunc::CheckMouseWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
  if(x >= rect.x && x <= rect.x + rect.w &&
     y >= rect.y && y <= rect.y + rect.h)
     {
      return true;
     }
     return false;
}

bool SDLCommonFunc::Menu(SDL_Renderer* g_screen)
{
  BaseObject StartButton[2];
	BaseObject ExitButton[2];
  BaseObject PauseMenu;
  PauseMenu.LoadImg("img//menu//menu_game.png",g_screen);
  StartButton[0].LoadImg("img//menu//play.png",g_screen);
	StartButton[1].LoadImg("img//menu//play2.png",g_screen);
	ExitButton[0].LoadImg("img//menu//exit.png",g_screen);
	ExitButton[1].LoadImg("img//menu//exit2.png",g_screen);

	SDL_Rect Button;
	StartButton[0].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 - 50);
	StartButton[1].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 - 50);
	
	ExitButton[0].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 + 70);
	ExitButton[1].SetRect(SCREEN_WIDTH/3 + 100, SCREEN_HEIGHT/2 + 70);


  Button = PauseMenu.GetRect();
  // int wMenu = Button.w;
  // int hMenu = Button.h;
  int x_pos = SCREEN_WIDTH/2 - Button.w/2;
  int y_pos = SCREEN_HEIGHT/2 - Button.h/2;
  PauseMenu.SetRect(x_pos,y_pos); 
  SDL_Event g_event;


  int MousePosX = 0;
  int MousePosY = 0;
  bool menu_quit = false;
  while(!menu_quit)
  {
      while(SDL_PollEvent(&g_event) != 0)
      {
          if(g_event.type == SDL_KEYDOWN)
          {
            if(g_event.key.keysym.sym == SDLK_ESCAPE)
            {
              menu_quit = true;
            }
          }
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
                  }
                  if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,ExitButton[0].GetRect()) == true )
                  {
                      menu_quit = true;
                      return true;
                  }
              }
          }
      }
      PauseMenu.Render(g_screen);
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

      SDL_RenderPresent(g_screen);
      SDL_Delay(100);
  }
  return false;
}

bool SDLCommonFunc::MenuLast(SDL_Renderer* g_screen)
{
	BaseObject ExitButton[2];
	ExitButton[0].LoadImg("img//menu//exit.png",g_screen);
	ExitButton[1].LoadImg("img//menu//exit2.png",g_screen);

	
	ExitButton[0].SetRect(SCREEN_WIDTH/5, SCREEN_HEIGHT/2 + 70);
	ExitButton[1].SetRect(SCREEN_WIDTH/5, SCREEN_HEIGHT/2 + 70);

  SDL_Event g_event;

  int MousePosX = 0;
  int MousePosY = 0;
  bool menu_quit = false;
  while(!menu_quit)
  {
      while(SDL_PollEvent(&g_event) != 0)
      {
          if(g_event.type == SDL_KEYDOWN)
          {
            if(g_event.key.keysym.sym == SDLK_ESCAPE)
            {
              menu_quit = true;
            }
          }
          if(g_event.type == SDL_MOUSEMOTION)
          {
              MousePosX = g_event.motion.x;
              MousePosY = g_event.motion.y;
          }
          if(g_event.type == SDL_MOUSEBUTTONDOWN)
          {
              if (g_event.button.button == SDL_BUTTON_LEFT)
              {
                  if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,ExitButton[0].GetRect()) == true )
                  {
                      menu_quit = true;
                      return true;
                  }
              }
          }
      }
      if(SDLCommonFunc::CheckMouseWithRect(MousePosX,MousePosY,ExitButton[0].GetRect()) == true)
      {
          ExitButton[1].Render(g_screen);
      }
      else
      {
          ExitButton[0].Render(g_screen);
      }

      SDL_RenderPresent(g_screen);
      SDL_Delay(100);
  }
  return false;
}

bool SDLCommonFunc::LoadSaveFile(int& px_pos, int& py_pos, int& p_heath, int& p_money, int& time_)//doc file gan gia tri
{
	std::ifstream inputFile("save.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file for reading\n";
        return false;
    }
    int count = 0;
    if (inputFile >> px_pos) count++;
    if (inputFile >> py_pos) count++;
    if (inputFile >> p_heath) count++;
    if (inputFile >> p_money) count++;
	  if (inputFile >> time_) count++;
    inputFile.close();

    if (count == 5) {
        return true;
    } else {
        std::cerr << "File does not contain enough values\n";
        return false;
    }
	return true;
}

bool SDLCommonFunc::SaveGame(const int& px_pos, const int& py_pos, const int& p_heath, const int& p_money, const int& time_)//save vao file
{
	std::ofstream outputFile("save.txt");
    if(!outputFile.is_open()) {
        std::cerr << "Failed to open file for writing\n";
        return false;
    }
	  outputFile << px_pos << " "
			   << py_pos << " "
			   << p_heath << " "
			   << p_money << " "
			   << time_ << " ";
	  outputFile.close();
	return true;
}