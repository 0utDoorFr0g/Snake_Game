#include "GameWindow.h"
#include "gameMap.h"
#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <locale.h>

using namespace std;

int main(int argc, char * argv[])
{
  WINDOW * game_screen;
  WINDOW * score_screen;
  WINDOW * mission_screen;

  // 유니코드 사용설정 생략.
  setlocale(LC_ALL,"");
  noecho();
  raw();


  initscr(); // Curses 모드 시작
  resize_term(MAP_HEIGHT, MAP_WIDTH * 2); // terminal 크기 조정

  refresh(); // 스크린에 출력


  // game screen 설정 및 출력
  game_screen = newwin(MAP_HEIGHT,MAP_WIDTH*2,0,0);
  srand((unsigned int)time(NULL));
  gameMap gm = gameMap(rand()%4);

  for(int i=0; i <MAP_HEIGHT; i++)
  {
    for(int j=0; j < MAP_WIDTH; j++)
    {
      switch (gm.getCurrentMapPosition(i,j))
      {
        case 1:
          mvwprintw(game_screen,i,j,"1");
          break;
        case 2:
          mvwprintw(game_screen,i,j,"2");
          break;
        case 3:
          mvwprintw(game_screen,i,j,"3");
          break;
        case 4:
          mvwprintw(game_screen,i,j,"4");
          break;
      }
    }

  }

  wrefresh(game_screen); // 실제 스크린에 출력

  // score_screen 출력 설정

  score_screen = newwin(10,21,0,21);
  wborder(score_screen,'|','|','-','-','*','*','*','*'); // box에 표기할 문자 설정
  mvwprintw(score_screen,5,5,"ScoreScreen");
  wrefresh(score_screen);

  // mission screen 출력 설정

  mission_screen = newwin(10,21,11,21);
  wborder(mission_screen,'|','|','-','-','*','*','*','*'); // box에 표기할 문자 설정
  mvwprintw(mission_screen,5,5,"MissionScreen");
  wrefresh(mission_screen);


  getch(); // 프로그램 종료를 막기 위한 입력 대기.
  delwin(game_screen);
  delwin(score_screen);
  delwin(mission_screen);
  endwin(); // Curses 모드 종료

  return 0;
}
