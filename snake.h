#ifndef _SNAKE_H_
#define _SNAKE_H_
#include <iostream>
#include <vector>
#include "Position.h"

using namespace std;

class snake
{
private:
  vector<Position> snakePosition;
  int snakeLength;
  int direction;//1은 오른쪽, 2는 오른쪽, 3은 위, 4는 아래.
public:
  snake();
  void changeDirection(int dir);//방향을 바꿈.
  void snakeGo();//1틱이 지나 전진할 때, snake 구성 Position의 위치를 전부 바꿈.
  void snakeGrow(int py, int px);//아이템 먹었을 때 snake의 길이를 늘림.
  void snakePoison();
  int getSnakePosX(int index);//snake의 특정 인덱스의 위치를 리턴.
  int getSnakePosY(int index);//snake의 특정 인덱스의 위치를 리턴
  void setSnakeHeadX(int px);//gate에 들어갔을 때 snake head의 위치를 바꾼다.
  void setSnakeHeadY(int py);//gate에 들어갔을 때 snake head의 위치를 바꾼다.
  int getLength();
  void setLength(int n);
  int getDirection();
  void snakePosition_pop_back();
  Position snakePosition_back();
};

#endif
