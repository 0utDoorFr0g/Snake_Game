#include <iostream>
#include <ncurses.h>
#include <vector>
#include "snake.h"
using namespace std;

snake::snake()
{
  snakePosition.push_back(Position(3,6,3));//head random head
  snakePosition.push_back(Position(3,5,4));//body random body
  snakePosition.push_back(Position(3,4,4));//body random body
  direction = 1;
  snakeLength = snakePosition.size();
}

//방향을 바꾸는 메소드, 동서남북을 각각 1234로 표시하며, 이동한 맵의 좌표에 대한 정보가 mapType으로 주어진다.
void snake::changeDirection(int dir)
{
  this->direction = dir;
}

void snake::snakeGo()
{
  //머리를 제외한 몸통 부분 한칸씩 움직이기.
  for (int i = snakePosition.size(); i >= 1; i--)
  {
    snakePosition[i] = snakePosition[i-1];
    if (i == 1)
    {
      snakePosition[i].setType(4);
    }
  }
  //머리 방향대로 움직이기.
  if (direction == 1)//동
  {
    snakePosition[0].setPosX(snakePosition[0].getPosX() + 1);
  }
  else if (direction == 2)//서
  {
    snakePosition[0].setPosX(snakePosition[0].getPosX() - 1);
  }
  else if (direction == 3)//남
  {
    snakePosition[0].setPosY(snakePosition[0].getPosY() + 1);
  }
  else if (direction == 4)//북
  {
    snakePosition[0].setPosY(snakePosition[0].getPosY() - 1);
  }

}

void snake::snakeGrow(int py, int px)
{
  snakePosition.push_back(Position(py, px, 4));
  snakeLength = snakePosition.size();
}

void snake::snakePoison()
{
  snakePosition.erase(snakePosition.end()-1);
  snakeLength = snakePosition.size();
}

int snake::getSnakePosX(int index)
{
  return snakePosition[index].getPosX();
}

int snake::getSnakePosY(int index)
{
  return snakePosition[index].getPosY();
}

int snake::getLength()
{
  return snakePosition.size();
}

void snake::setLength(int n)
{
  snakeLength = n;
}

int snake::getDirection()
{
  return direction;
}


void snake::setSnakeHeadX(int px)
{
  snakePosition[0].setPosX(px);
}

void snake::setSnakeHeadY(int py)
{
  snakePosition[0].setPosY(py);
}

void snake::snakePosition_pop_back()
{
  snakePosition.pop_back();
}

Position snake::snakePosition_back()
{
  return snakePosition.back();
}
