#include <iostream>
#include <clocale>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include "gameMap.h"
#include "kbtick.h"

using namespace std;


int main()
{
    gameMap mapControl;
    WINDOW* gameScreen;
    WINDOW* scoreScreen;
    WINDOW* missionScreen;
    WINDOW* failScreen;
    int randomNum;


    //유니코드 사용설정
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    noecho();
    raw();

    int x = resize_term(21, 87);
    border('-', '-', '-', '-', '-', '-', '-', '-');


    refresh();
    getch();


    gameScreen = newwin(21, 42, 0, 1);//왜인지는 모르겠으나 가로 길이를 21로 하면 오류 발생.
    wbkgd(gameScreen, COLOR_PAIR(1));
    srand((unsigned int)time(NULL));
    mapControl.setCurrentMap(rand() % 4);
    mapControl.snakeInitialize();

    //map 표시 시작
    //0은 빈공간(\u2B1C), 1은 wall, 2는 immune wall (\u2B1B), 3은 snake 머리, 4는 몸통 (\u2B1A), 5는 Poison Item, 6은 growthItem, 7은 gate
    int emptySquare;
    for (int h = 0; h < 21; h++)
    {
        for (int w = 0; w < 21; w++)
        {
            if (mapControl.getCurrentMapPosition(h, w) == 0)
            {
                mvwprintw(gameScreen, h, 2 * w, " ");
            }
            else if (mapControl.getCurrentMapPosition(h, w) == 1 || mapControl.getCurrentMapPosition(h, w) == 2)
            {
                mvwprintw(gameScreen, h, 2 * w, "\u25A1");
            }
            else if (mapControl.getCurrentMapPosition(h, w) == 3)
            {
                mvwprintw(gameScreen, h, 2 * w, "\u25CC");
            }
            else if (mapControl.getCurrentMapPosition(h, w) == 4)
            {
                mvwprintw(gameScreen, h, 2 * w, "\u25CB");
            }
            else if (mapControl.getCurrentMapPosition(h, w) == 5)
            {
                mvwprintw(gameScreen, h, 2 * w, "\u25B2");
            }
            else if (mapControl.getCurrentMapPosition(h, w) == 6)
            {
                mvwprintw(gameScreen, h, 2 * w, "\u25B3");
            }
            else if (mapControl.getCurrentMapPosition(h, w) == 7)
            {
                mvwprintw(gameScreen, h, 2 * w, "\u25A6");
            }
            emptySquare = 2 * w - 1;
            mvwprintw(gameScreen, h, emptySquare, " ");
        }
    }
    wrefresh(gameScreen);



    //scoreScreen
    scoreScreen = newwin(10, 42, 0, 44);
    wborder(scoreScreen, '+', '+', '+', '+', '+', '+', '+', '+');
    mvwprintw(scoreScreen, 2, 5, "scoreScreen");
    wrefresh(scoreScreen);



    //missionScreen
    missionScreen = newwin(10, 42, 11, 44);
    wborder(missionScreen, '+', '+', '+', '+', '+', '+', '+', '+');
    mvwprintw(missionScreen, 2, 5, "MissionScreen");
    wrefresh(missionScreen);


    //failScreen
    //실패할 경우 이 화면이 window를 덮으며 게임이 종료된다.
    failScreen = newwin(21, 42, 0, 1);
    wborder(failScreen, '+', '+', '+', '+', '+', '+', '+', '+');
    mvwprintw(failScreen, 10, 13, "You Failed!!!!!!!");

    //중요!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //시간 틱이 반복문을 통해 수행한다는 가정하에 단지 gameTimeFlow를 실행하는 것으로 map의 데이터를 바꿀 수 있다!!!
    //아이템에 부딪히는 것과 벽과 부딪히는 것은 아직 실패 스크린을 구상하지 않았기에 비어있는 if문으로 처리를 했다.
    halfdelay(10);

    int state = 0;//정상 0, 벽 만나면 1, poison Item 이면 2, growthItem 3, gate는 4, Mission Clear는 5
    while ((state == 0) || (state == 5))
    {
        if (state == 5)
        {
            state = 0;
            for (int h = 0; h < 21; h++)
                for (int w = 0; w < 21; w++)
                  mvwprintw(gameScreen, h, 2 * w, " ");

            mvwprintw(gameScreen, 10, 5, "Game Clear!");
            wrefresh(gameScreen);

            getchar();

            srand((unsigned int)time(NULL));
            mapControl.setCurrentMap(rand() % 4);
            mapControl.snakeReset();
            mapControl.snakeInitialize();

            mapControl.gameMission.setGrowItemMissionClear(0);
            mapControl.gameMission.setPoisionItemMissionClear(0);
            mapControl.gameMission.setGateUseMissionClear(0);
            mapControl.gameMission.setSnakeLengthMissionClear(3);

            mapControl.gameScore.setGottenGrowItem(0);
            mapControl.gameScore.setGottenPoisionItem(0);
            mapControl.gameScore.setUseGate(0);
            mapControl.gameScore.setLengthScore(3);

            int emptySquare;
            for (int h = 0; h < 21; h++)
            {
                for (int w = 0; w < 21; w++)
                {
                    if (mapControl.getCurrentMapPosition(h, w) == 0)
                    {
                        mvwprintw(gameScreen, h, 2 * w, " ");
                    }
                    else if (mapControl.getCurrentMapPosition(h, w) == 1 || mapControl.getCurrentMapPosition(h, w) == 2)
                    {
                        mvwprintw(gameScreen, h, 2 * w, "\u25A1");
                    }
                    else if (mapControl.getCurrentMapPosition(h, w) == 3)
                    {
                        mvwprintw(gameScreen, h, 2 * w, "\u25CC");
                    }
                    else if (mapControl.getCurrentMapPosition(h, w) == 4)
                    {
                        mvwprintw(gameScreen, h, 2 * w, "\u25CB");
                    }
                    else if (mapControl.getCurrentMapPosition(h, w) == 5)
                    {
                        mvwprintw(gameScreen, h, 2 * w, "\u25B2");
                    }
                    else if (mapControl.getCurrentMapPosition(h, w) == 6)
                    {
                        mvwprintw(gameScreen, h, 2 * w, "\u25B3");
                    }
                    else if (mapControl.getCurrentMapPosition(h, w) == 7)
                    {
                        mvwprintw(gameScreen, h, 2 * w, "\u25A6");
                    }
                    emptySquare = 2 * w - 1;
                    mvwprintw(gameScreen, h, emptySquare, " ");
                }
            }
            wrefresh(gameScreen);

            wborder(scoreScreen, '+', '+', '+', '+', '+', '+', '+', '+');
            mvwprintw(scoreScreen, 2, 5, "scoreScreen");
            wrefresh(scoreScreen);

            wborder(missionScreen, '+', '+', '+', '+', '+', '+', '+', '+');
            mvwprintw(missionScreen, 2, 5, "MissionScreen");
            wrefresh(missionScreen);
        }
        else
        {
            int ch = 0;
            int keyBoardState = 0;
            int timeCount = 0;
            while (ch != KB_X && state != 5)
            {
                if (timeCount % 20 == 0)
                {
                    if (mapControl.isGateOnMap() == true)
                    {
                        mapControl.gateDegenerateOnMap();
                    }
                    else
                    {
                        mapControl.gateGenerateOnMap();
                    }
                }
                ch = custom_getch_tick();
                if (ch == KB_D)
                {
                    if (mapControl.getSnakeDirection() == 2)
                    {
                        keyBoardState = 1;//마치 벽을 만난 것처럼 오류 return
                    }
                    else
                        mapControl.snakeChangeDirection(1);
                }
                else if (ch == KB_A)
                {
                    if (mapControl.getSnakeDirection() == 1)
                    {
                        keyBoardState = 1;//마치 벽을 만난 것처럼 오류 return
                    }
                    else
                        mapControl.snakeChangeDirection(2);
                }
                else if (ch == KB_S)
                {
                    if (mapControl.getSnakeDirection() == 4)
                    {
                        keyBoardState = 1;//마치 벽을 만난 것처럼 오류 return
                    }
                    else
                        mapControl.snakeChangeDirection(3);
                }
                else if (ch == KB_W)
                {
                    if (mapControl.getSnakeDirection() == 3)
                    {
                        keyBoardState = 1;//마치 벽을 만난 것처럼 오류 return
                    }
                    else
                        mapControl.snakeChangeDirection(4);
                }

                state = mapControl.gameTimeFlow();

                for (int h = 0; h < 21; h++)
                {
                    for (int w = 0; w < 21; w++)
                    {
                        if (mapControl.getCurrentMapPosition(h, w) == 0)
                        {
                            mvwprintw(gameScreen, h, 2 * w, " ");
                        }
                        else if (mapControl.getCurrentMapPosition(h, w) == 1 || mapControl.getCurrentMapPosition(h, w) == 2)
                        {
                            mvwprintw(gameScreen, h, 2 * w, "\u25A1");
                        }
                        else if (mapControl.getCurrentMapPosition(h, w) == 3)
                        {
                            mvwprintw(gameScreen, h, 2 * w, "\u25CC");
                        }
                        else if (mapControl.getCurrentMapPosition(h, w) == 4)
                        {
                            mvwprintw(gameScreen, h, 2 * w, "\u25CB");
                        }
                        else if (mapControl.getCurrentMapPosition(h, w) == 5)
                        {
                            mvwprintw(gameScreen, h, 2 * w, "\u25B2");
                        }
                        else if (mapControl.getCurrentMapPosition(h, w) == 6)
                        {
                            mvwprintw(gameScreen, h, 2 * w, "\u25B3");
                        }
                        else if (mapControl.getCurrentMapPosition(h, w) == 7)
                        {
                            mvwprintw(gameScreen, h, 2 * w, "\u25A6");
                        }
                        emptySquare = 2 * w - 1;
                        mvwprintw(gameScreen, h, emptySquare, " ");
                    }
                }

                //keyboard 입력이 현재 뱀 방향의 반대라면
                if (keyBoardState == 1)
                {
                    state = 1;
                }
                //failScreen을 띄워야 할 때만 작동. 나머지는 전부 else문.
                if (state == 1)
                {
                    wrefresh(failScreen);
                    getch();
                    break;
                }
                else if ((state == 2) && (mapControl.getSnakeLength() < 3))
                {
                    wrefresh(failScreen);
                    break;
                }
                else
                {
                    mvwprintw(scoreScreen, 2, 5, "Score Board");
                    string s1 = "B: " + to_string(mapControl.getSnakeLength()) + " / 5";
                    mvwprintw(scoreScreen, 3, 5, s1.c_str());
                    string s2 = "+: " + to_string(mapControl.gameScore.getGottenGrowItem());
                    mvwprintw(scoreScreen, 4, 5, s2.c_str());
                    string s3 = "-: " + to_string(mapControl.gameScore.getGottenPoisionItem());
                    mvwprintw(scoreScreen, 5, 5, s3.c_str());
                    string s4 = "G: " + to_string(mapControl.gameScore.getUseGate());
                    mvwprintw(scoreScreen, 6, 5, s4.c_str());


                    mvwprintw(missionScreen, 2, 5, "Mission");
                    string m1 = "B: ";
                    m1 += "5 ";
                    m1 += '(';
                    m1 += (mapControl.gameMission.isSnakeLengthMissionClear() ? 'V' : ' ');
                    m1 += ')';
                    mvwprintw(missionScreen, 3, 5, m1.c_str());
                    string m2 = "+: ";
                    m2 += "4 ";
                    m2 += '(';
                    m2 += (mapControl.gameMission.isGrowItemMissionClear() ? 'V' : ' ');
                    m2 += ')';
                    mvwprintw(missionScreen, 4, 5, m2.c_str());
                    string m3 = "-: ";
                    m3 += "2 ";
                    m3 += '(';
                    m3 += (mapControl.gameMission.isPoisionItemMissionClear() ? 'V' : ' ');
                    m3 += ')';
                    mvwprintw(missionScreen, 5, 5, m3.c_str());
                    string m4 = "G: ";
                    m4 += "1 ";
                    m4 += '(';
                    m4 += (mapControl.gameMission.isGateUseMissionClear() ? 'V' : ' ');
                    m4 += ')';
                    mvwprintw(missionScreen, 6, 5, m4.c_str());

                    wrefresh(scoreScreen);
                    wrefresh(missionScreen);
                    wrefresh(gameScreen);
                }
                timeCount++;

                bool isClear = mapControl.gameMission.isSnakeLengthMissionClear() & mapControl.gameMission.isGateUseMissionClear() & mapControl.gameMission.isPoisionItemMissionClear() & mapControl.gameMission.isGrowItemMissionClear();

                if(isClear == true)
                  state = 5;
            }
        }
    }


    //윈도우 정리
    getch();
    delwin(gameScreen);
    endwin();
    return 0;
}
