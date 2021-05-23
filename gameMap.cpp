#include "gameMap.h"


gameMap::gameMap(int num) : currentNum(num)
{
  setCurrentMap(num);
}

void gameMap::setCurrentMap(int num)
{
  for(int i=0; i < MAP_HEIGHT; i++)
  {
    for(int j=0; j < MAP_WIDTH; j++)
    {
      currentMap[i][j] = init_map[num][i][j];
    }
  }
}

int gameMap::getCurrentMapPosition(int x, int y)
{
  return currentMap[x][y];
}
