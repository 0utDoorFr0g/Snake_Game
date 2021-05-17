#include <iostream>
#include "gameMap.h"

using namespace std;


gameMap::gameMap()
{
  /*
  생성자가 호출되면 기본으로 currentMap을 map[0]으로 바꾼다.
  */
  setCurrentMap(0);
}

int gameMap::getCurrentMapPosition(int x, int y)
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
}
