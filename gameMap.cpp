#include <iostream>
#include <vector>
#include "gameMap.h"


using namespace std;


gameMap::gameMap()
{
  /*
  생성자가 호출되면 기본으로 currentMap을 map[0]으로 바꾼다.
  */
  setCurrentMap(0);
  snakeInitialize();
  gateOnMap.gateInitialize(mapNum);
}

int gameMap::getCurrentMapPosition(int y, int x)
{
  return currentMap[y][x];
}

void gameMap::setCurrentMap(int num)
{
  if((num < 0) || (num > 4))
  {
    //에러발생
    return;
  }
  for (int i = 0; i < MAP_HEIGHT; i++)
  {
    for (int j = 0; j < MAP_WIDTH; j++)
    {
      currentMap[i][j] = map[num][i][j];
    }
  }
  mapNum = num;
}

void gameMap::snakeInitialize()
{
  currentMap[snakeOnMap.getSnakePosY(0)][snakeOnMap.getSnakePosX(0)] = 3;
  for (int i = 1; i < snakeOnMap.getLength(); i++)
  {
    currentMap[snakeOnMap.getSnakePosY(i)][snakeOnMap.getSnakePosX(i)] = 4;
  }
}

int gameMap::gameTimeFlow()
{
  int state;//정상 0, 벽 만나면 1, poison Item 이면 2, growthItem 3, gate는 4
  //tempX와 tempY는 snake의 마지막 꼬리의 좌표로 만약 아이템 획득 없이 snake가 전진한다면 이 좌표에 해당하는 currentMap을 0으로 바꿔줘야 한다.
  int tempX = snakeOnMap.getSnakePosX(snakeOnMap.getLength()-1);
  int tempY = snakeOnMap.getSnakePosY(snakeOnMap.getLength()-1);
  //snake 전진
  snakeOnMap.snakeGo();

  if (currentMap[snakeOnMap.getSnakePosY(0)][snakeOnMap.getSnakePosX(0)] == 1)
  {
    state = 1;
    return state;
  }
  else
  { //머리 부분 currentMap 반영
    currentMap[snakeOnMap.getSnakePosY(0)][snakeOnMap.getSnakePosX(0)] = 3;
    //몸통과 꼬리 currentMap 반영
    for (int i = 1; i < snakeOnMap.getLength(); i++)
    {
      currentMap[snakeOnMap.getSnakePosY(i)][snakeOnMap.getSnakePosX(i)] = 4;
    }
    //꼬리부분 0으로 바꾸기
    currentMap[tempY][tempX] = 0;
    state = 0;
  }
  return state;
}

void gameMap::snakeChangeDirection(int dir)
{
  snakeOnMap.changeDirection(dir);
}

int gameMap::getSnakeLength()
{
  return snakeOnMap.getLength();
}

int gameMap::getSnakeDirection()
{
  return snakeOnMap.getDirection();
}

void gameMap::gateInitialize(int mapNum)
{
  gateOnMap.gateInitialize(mapNum);
}

void gameMap::gateGenerateOnMap()
{
  gateOnMap.gateGenerate();
  currentMap[gateOnMap.getFirstGate().getPosY()][gateOnMap.getFirstGate().getPosX()] = 7;
  currentMap[gateOnMap.getSecondGate().getPosY()][gateOnMap.getSecondGate().getPosX()] = 7;
}

void gameMap::gateDegenerateOnMap()
{
  if (gateOnMap.isSnakeEnteringGate() == false)
  {
  currentMap[gateOnMap.getFirstGate().getPosY()][gateOnMap.getFirstGate().getPosX()] = 1;
  currentMap[gateOnMap.getSecondGate().getPosY()][gateOnMap.getSecondGate().getPosX()] = 1;
  }
  gateOnMap.gateDegenerate();
}

bool gameMap::isGateOnMap()
{
  return gateOnMap.isGateExist();
}
