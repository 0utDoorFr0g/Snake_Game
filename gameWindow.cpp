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

  //map 표시 시작
  //0은 빈공간(\u2B1C), 1은 wall, 2는 immune wall (\u2B1B), 3은 snake 머리, 4는 몸통 (\u2B1A)
  for (int i = 0; i < 21; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      if(mapControl.getCurrentMapPosition(i,j) == 0)
      {
        mvwprintw(gameScreen,j,2*i," ");
      }
      else if(mapControl.getCurrentMapPosition(i,j) == 1 || mapControl.getCurrentMapPosition(i,j) == 2)
      {
        mvwprintw(gameScreen,j,2*i,"\u25A1");
      }
      else if(mapControl.getCurrentMapPosition(i,j) == 3)
      {
        mvwprintw(gameScreen,j,2*i,"\u25CC");
      }
      else if(mapControl.getCurrentMapPosition(i,j) == 4)
      {
        mvwprintw(gameScreen,j,2*i,"\u25CB");
      }
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
    for (int i = 0; i < 21; i++)
    {
      for (int j = 0; j < 21; j++)
      {
        if(mapControl.getCurrentMapPosition(i,j) == 0)
        {
          mvwprintw(gameScreen,j,2*i," ");
        }
        else if(mapControl.getCurrentMapPosition(i,j) == 1 || mapControl.getCurrentMapPosition(i,j) == 2)
        {
          mvwprintw(gameScreen,j,2*i,"\u25A1");
        }
        else if(mapControl.getCurrentMapPosition(i,j) == 3)
        {
          mvwprintw(gameScreen,j,2*i,"\u25CC");
        }
        else if(mapControl.getCurrentMapPosition(i,j) == 4)
        {
          mvwprintw(gameScreen,j,2*i,"\u25CB");
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
