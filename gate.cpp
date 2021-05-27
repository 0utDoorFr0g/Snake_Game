#include <iostream>
#include "gate.h"
using namespace std;

gate::gate()
{
  gateInitialize(0);
}

void gate::gateInitialize(int mapNum)
{
  mapWallData.clear();
  mapDataNum = mapNum;
  SnakeEnteringGate = false;
  wallCount = 0;
  for (int h = 0; h < 21; h++)
  {
    for (int w = 0; w < 21; w++)
    {
      if (map[mapDataNum][h][w] == 1)
      {
        //if (mapDataNum == 0) cout << h << " " << w << endl;
        wallCount++;
        mapWallData.push_back(Position(h,w,4));
      }
    }
  }
}


void gate::gateGenerate()
{
  snakeLength = 0;
  gateExist = true;
  int randomFirstGate;
  int randomSecondGate;

  do {
    srand((unsigned int)time(NULL));
    randomFirstGate = rand();
    randomFirstGate = (int)randomFirstGate%wallCount;
    randomSecondGate = rand();
    randomSecondGate = (int)randomSecondGate%wallCount;
  } while(randomSecondGate == randomFirstGate);

  firstGate = mapWallData[randomFirstGate];
  secondGate = mapWallData[randomSecondGate];
}


void gate::gateDegenerate()
{
  if (SnakeEnteringGate == false)
  {
    gateExist  = false;
  }
}

int gate::gateEntering(int snakeDirection, int py, int px, int snakeLength)
{
  this-> snakeLength = snakeLength;
  SnakeEnteringGate = true;

  int returnResult;
  int otherGateX;
  int otherGateY;
  if (gateExist && (firstGate.getPosX() == px) && (firstGate.getPosY() == py))
  {
    otherGateX = secondGate.getPosX();
    otherGateY = secondGate.getPosY();
  }
  else
  {
    otherGateX = firstGate.getPosX();
    otherGateY = firstGate.getPosY();
  }

  //본격적인 뱀의 게이트 통과후 방향 리턴 시작.
  if (otherGateX == 0)//왼쪽 벽에서 gate 나올때.
  {
    return 1;//중앙으로 이동해야함.
  }
  else if (otherGateX == 21)//오른쪽 벽에서 게이트 나올 때
  {
    return 2;//중앙으로 이동해야함.
  }
  else if (otherGateY == 0)//위쪽벽 gate
  {
    return 3;
  }
  else if (otherGateY == 21)//아래쪽 벽 gate
  {
    return 4;
  }
  else//출구 gate가 맵 경계가 아닐 때... 다른 말로 맵의 가운데 부분에 있을 때...
  {
    returnResult = snakeDirection;

    //출구 gate에서 나오고 바로 마주치는 곳이 벽인 경우를 계산하여 유효성 검사를 해야 함.
    int nextPosX;
    int nextPosY;
    int temp = 0;
    //gate 로직 시작
    if (snakeDirection == 1)//처음
    {
      if ((map[mapDataNum][otherGateY][otherGateX+1] != 1) && (map[mapDataNum][otherGateY][otherGateX+1] != 2))
      {
        nextPosX = otherGateX+1;
        nextPosY = otherGateY;
        returnResult = 1;
      }
      else if ((map[mapDataNum][otherGateY+1][otherGateX] != 1) && (map[mapDataNum][otherGateY+1][otherGateX] != 2))
      {
        nextPosX = otherGateX;
        nextPosY = otherGateY+1;
        returnResult = 3;
      }
      else if ((map[mapDataNum][otherGateY-1][otherGateX] != 1) && (map[mapDataNum][otherGateY-1][otherGateX] != 2))
      {
        nextPosX = otherGateX;
        nextPosY = otherGateY-1;
        returnResult = 4;
      }
      else
      {
        nextPosX = otherGateX-1;
        nextPosY = otherGateY;
        returnResult = 2;
      }
    }
    else if (snakeDirection == 2)
    {
      if ((map[mapDataNum][otherGateY][otherGateX-1] != 1) && (map[mapDataNum][otherGateY][otherGateX-1] != 2))
      {
        nextPosX = otherGateX-1;
        nextPosY = otherGateY;
        returnResult = 2;
      }
      else if ((map[mapDataNum][otherGateY-1][otherGateX] != 1) && (map[mapDataNum][otherGateY-1][otherGateX] != 2))
      {
        nextPosX = otherGateX;
        nextPosY = otherGateY-1;
        returnResult = 4;
      }
      else if ((map[mapDataNum][otherGateY+1][otherGateX] != 1) && (map[mapDataNum][otherGateY+1][otherGateX] != 2))
      {
        nextPosX = otherGateX;
        nextPosY = otherGateY+1;
        returnResult = 3;
      }
      else
      {
        nextPosX = otherGateX+1;
        nextPosY = otherGateY;
        returnResult = 1;
      }
    }
    else if (snakeDirection == 3)
    {
      if ((map[mapDataNum][otherGateY+1][otherGateX] != 1) && (map[mapDataNum][otherGateY+1][otherGateX] != 2))
      {
        nextPosX = otherGateX;
        nextPosY = otherGateY+1;
        returnResult = 3;
      }
      else if ((map[mapDataNum][otherGateY][otherGateX-1] != 1) && (map[mapDataNum][otherGateY][otherGateX-1] != 2))
      {
        nextPosX = otherGateX-1;
        nextPosY = otherGateY;
        returnResult = 2;
      }
      else if ((map[mapDataNum][otherGateY][otherGateX+1] != 1) && (map[mapDataNum][otherGateY][otherGateX+1] != 2))
      {
        nextPosX = otherGateX+1;
        nextPosY = otherGateY;
        returnResult = 1;
      }
      else
      {
        nextPosX = otherGateX;
        nextPosY = otherGateY-1;
        returnResult = 4;
      }
    }
    else if (snakeDirection == 4)
    {
      if ((map[mapDataNum][otherGateY-1][otherGateX] != 1) && (map[mapDataNum][otherGateY-1][otherGateX] != 2))
      {
        nextPosX = otherGateX;
        nextPosY = otherGateY-1;
        returnResult = 4;
      }
      else if ((map[mapDataNum][otherGateY][otherGateX+1] != 1) && (map[mapDataNum][otherGateY][otherGateX+1] != 2))
      {
        nextPosX = otherGateX+1;
        nextPosY = otherGateY;
        returnResult = 1;
      }
      else if ((map[mapDataNum][otherGateY][otherGateX-1] != 1) && (map[mapDataNum][otherGateY][otherGateX-1] != 2))
      {
        nextPosX = otherGateX-1;
        nextPosY = otherGateY;
        returnResult = 2;
      }
      else
      {
        nextPosX = otherGateX;
        nextPosY = otherGateY+1;
        returnResult = 3;
      }
    }

  return returnResult;
  }
}

Position gate::getFirstGate()
{
  return firstGate;
}

Position gate::getSecondGate()
{
  return secondGate;
}

bool gate::isSnakeEnteringGate()
{
  return SnakeEnteringGate;
}

bool gate::isGateExist()
{
  return gateExist;
}

bool gate::gateSnakeEnteringCount()
{
  if (gateExist && SnakeEnteringGate)
  {
    snakeLength--;
    if (snakeLength == -1)
    {
      gateDegenerate();
      SnakeEnteringGate = false;
      return true;
    }
  }
  return false;
}
