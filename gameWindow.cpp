#include <iostream>
#include <locale.h>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "gameMap.h"

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
  noecho();
  raw();

  int x = resize_term(21,84);
  border('-','-','-','-','-','-','-','-');


  refresh();
  getch();

  
  gameScreen = newwin(21,42,0,0);//왜인지는 모르겠으나 가로 길이를 21로 하면 오류 발생.
  srand((unsigned int)time(NULL));
  mapControl.setCurrentMap(rand()%4);

  //map 표시 시작
  for (int i = 0; i < 21; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      if(mapControl.getCurrentMapPosition(i,j) == 0)
      {
        mvwprintw(gameScreen,j,i,"\u2B1C");
      }
      else if(mapControl.getCurrentMapPosition(i,j) == 1 || mapControl.getCurrentMapPosition(i,j) == 2)
      {
        mvwprintw(gameScreen,j,i,"\u2B1B");
      }
    }
  }
  wrefresh(gameScreen);


  //scoreScreen
  scoreScreen = newwin(10,42,0,42);
  wborder(scoreScreen, '+','+','+','+','+','+','+','+');
  mvwprintw(scoreScreen,5,5,"scoreScreen");
  wrefresh(scoreScreen);


  //missionScreen
  missionScreen = newwin(10,42,11,42);
  wborder(missionScreen, '+','+','+','+','+','+','+','+');
  mvwprintw(missionScreen,5,5,"MissionScreen");
  wrefresh(missionScreen);



  //윈도우 정리
  getch();
  delwin(gameScreen);
  endwin();
  return 0;
}
