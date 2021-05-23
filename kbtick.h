#include <ncurses.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <chrono>

// 키보드 상하좌우 입력 값
#define KB_UP 259
#define KB_DOWN 258
#define KB_RIGHT 261
#define KB_LEFT 260

// 키보드 WSDA 입력 값
#define KB_W 119
#define KB_S 115
#define KB_D 100
#define KB_A 97

//X는 프로그램을 종료하기 위한 키.
#define KB_X 120

// TIME_TICK = 1 second
#define TIME_TICK 1000

int custom_getch();
int custom_getch_tick();
