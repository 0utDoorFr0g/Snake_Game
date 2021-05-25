#include <iostream>
#include <clocale>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "gameMap.h"
#include "kbtick.h"

using namespace std;


int main()
{
  gameMap mapControl;
  WINDOW *gameScreen;
  WINDOW *scoreScreen;
  WINDOW *missionScreen;
  int randomNum;

  //유니코드 사용설정
  setlocale(LC_ALL,"");
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  noecho();
  raw();

  int x = resize_term(21,87);
  border('-','-','-','-','-','-','-','-');


  refresh();
  getch();


  gameScreen = newwin(21,42,0,1);//왜인지는 모르겠으나 가로 길이를 21로 하면 오류 발생.
  wbkgd(gameScreen,COLOR_PAIR(1));
  srand((unsigned int)time(NULL));
  mapControl.setCurrentMap(rand()%4);
  mapControl.snakeInitialize();
  mapControl.itemInitialize();

  //map 표시 시작
  //0은 빈공간(\u2B1C), 1은 wall, 2는 immune wall (\u2B1B), 3은 snake 머리, 4는 몸통 (\u2B1A), 5는 독 아이템, 6은 성장 아이템
  int emptySquare;
  for (int h = 0; h < 21; h++)
  {
    for (int w = 0; w < 21; w++)
    {
      if(mapControl.getCurrentMapPosition(h,w) == 0)
      {
        mvwprintw(gameScreen,h,2*w," ");
      }
      else if(mapControl.getCurrentMapPosition(h,w) == 1 || mapControl.getCurrentMapPosition(h,w) == 2)
      {
        mvwprintw(gameScreen,h,2*w,"\u25A1");
      }
      else if(mapControl.getCurrentMapPosition(h,w) == 3)
      {
        mvwprintw(gameScreen,h,2*w,"\u25CC");
      }
      else if(mapControl.getCurrentMapPosition(h,w) == 4)
      {
        mvwprintw(gameScreen,h,2*w,"\u25CB");
      }
      else if(mapControl.getCurrentMapPosition(h,w) == 5)
      {
        mvwprintw(gameScreen,h,2*w,"\u2B14");
      }
      else if(mapControl.getCurrentMapPosition(h,w) == 6)
      {
        mvwprintw(gameScreen,h,2*w,"\u2B15");
      }
      emptySquare = 2*w - 1;
      mvwprintw(gameScreen,h,emptySquare," ");
    }
  }
  wrefresh(gameScreen);



  //scoreScreen
  scoreScreen = newwin(10,42,0,44);
  wborder(scoreScreen, '+','+','+','+','+','+','+','+');
  mvwprintw(scoreScreen,5,5,"scoreScreen");
  wrefresh(scoreScreen);



  //missionScreen
  missionScreen = newwin(10,42,11,44);
  wborder(missionScreen, '+','+','+','+','+','+','+','+');
  mvwprintw(missionScreen,5,5,"MissionScreen");
  wrefresh(missionScreen);



  //중요!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //시간 틱이 반복문을 통해 수행한다는 가정하에 단지 gameTimeFlow를 실행하는 것으로 map의 데이터를 바꿀 수 있다!!!
  //아이템에 부딪히는 것과 벽과 부딪히는 것은 아직 실패 스크린을 구상하지 않았기에 비어있는 if문으로 처리를 했다.
  halfdelay(10);
  int ch = 0;
  while(ch != KB_X)
  {
    ch = custom_getch_tick();
    if(ch == KB_D)
      mapControl.snakeChangeDirection(1);
    else if(ch == KB_A)
      mapControl.snakeChangeDirection(2);
    else if (ch == KB_S)
      mapControl.snakeChangeDirection(3);
    else if (ch == KB_W)
      mapControl.snakeChangeDirection(4);
    mapControl.gameTimeFlow();
    for (int h = 0; h < 21; h++)
    {
      for (int w = 0; w < 21; w++)
      {
        if(mapControl.getCurrentMapPosition(h,w) == 0)
        {
          mvwprintw(gameScreen,h,2*w," ");
        }
        else if(mapControl.getCurrentMapPosition(h,w) == 1 || mapControl.getCurrentMapPosition(h,w) == 2)
        {
          mvwprintw(gameScreen,h,2*w,"\u25A1");
        }
        else if(mapControl.getCurrentMapPosition(h,w) == 3)
        {
          mvwprintw(gameScreen,h,2*w,"\u25CC");
        }
        else if(mapControl.getCurrentMapPosition(h,w) == 4)
        {
          mvwprintw(gameScreen,h,2*w,"\u25CB");
        }
        else if(mapControl.getCurrentMapPosition(h,w) == 5)
        {
          mvwprintw(gameScreen,h,2*w,"\u2b14");
        }
        else if(mapControl.getCurrentMapPosition(h,w) == 6)
        {
          mvwprintw(gameScreen,h,2*w,"\u2b15");
        }
      }
    }
  wrefresh(gameScreen);
  }

  //윈도우 정리
  getch();
  delwin(gameScreen);
  endwin();
  return 0;
}
