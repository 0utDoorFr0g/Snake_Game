#include <iostream>
#include "gate.h"
using namespace std;

gate::gate()
{
  gateInitialize(0);
}

void gate::gateInitialize(int mapNum)
{
  mapDataNum = mapNum;
  isSnakeEnteringGateVar = false;
  wallCount = 0;
  for (int h = 0; h < 21; h++)
  {
    for (int w = 0; w < 21; w++)
    {

      if (map[mapNum][h][w] == 1)
      {
        wallCount++;
        mapWallData.push_back(Position(h,w,4));
      }
    }
  }
}


void gate::gateGenerate()
{
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
  if (isSnakeEnteringGateVar == false)
  {
    gateExist  = false;
  }
}

int gate::gateEntering(int dir)
{
  return 0;
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
  return isSnakeEnteringGateVar;
}

bool gate::isGateExist()
{
  return gateExist;
}
