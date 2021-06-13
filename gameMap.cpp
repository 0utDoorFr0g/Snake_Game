#include "gameMap.h"


using namespace std;


gameMap::gameMap()
{
  /*
  생성자가 호출되면 기본으로 currentMap을 map[0]으로 바꾼다.
  */
  setCurrentMap(0);
  snakeInitialize();
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
}

void gameMap::snakeInitialize()
{
  currentMap[snakeOnMap.getSnakePosY(0)][snakeOnMap.getSnakePosX(0)] = 3;
  for (int i = 1; i < snakeOnMap.getSnakeLength(); i++)
  {
    currentMap[snakeOnMap.getSnakePosY(i)][snakeOnMap.getSnakePosX(i)] = 4;
  }
}

// snake가 위치한 주변에 아이템을 만듬.
// 참고로 POISION ITEM은 5 GROW ITEM은 6으로 정했음.
void gameMap::itemInitialize()
{
  int i = 0;

  while(i < 3)
  {
    // 좌표 생성
    int Y = rand() % 21;
    int X = rand() % 21;

    int data = getCurrentMapPosition(Y, X); // 맵의 데이터를 가져온다.

    if(data != 0) // 가져온 데이터가 비어있지 않다면
      continue; // 다시 좌표를 생성한다.

    itemOnMap[i] = item(Y,X,((i%2 == 1) ? POISION_ITEM : GROW_ITEM)); // grow item 또는 poision item을 생성한다.
    currentMap[Y][X] = ((i%2 == 1) ? POISION_ITEM : GROW_ITEM);
    i++; // 다음 아이템 생성
  }
}

void gameMap::gameTimeFlow()
{
  // item이 Map에 남아있었던 시간을 갱신하고 5 tick 이상 남아있었다면 새로운 위치에 item을 생성한다.
  for(int i=0; i < 3; i++)
  {
    if(itemOnMap[i].getAge() < 4)
      itemOnMap[i].setAge(itemOnMap[i].getAge()+1);
    else
    {
        bool flag = false;
        int Y;
        int X;
        while(flag == false) // 반복하여 랜덤하게 좌표를 생성 및 빈 공간인지 확인
        {
          Y = rand() % 21;
          X = rand() % 21;

          int data = getCurrentMapPosition(Y, X);

          if(data != 0)
            continue;

          flag = true;
        }
        currentMap[itemOnMap[i].getItemPosition()->getPosY()][itemOnMap[i].getItemPosition()->getPosX()] = 0; // 기존의 아이템 삭제하고 빈공간 대체.
        itemOnMap[i] = item(Y,X,((i%2 == 1) ? POISION_ITEM : GROW_ITEM)); // 새로운 좌표에 새로운 아이템 생성
        currentMap[itemOnMap[i].getItemPosition()->getPosY()][itemOnMap[i].getItemPosition()->getPosX()] = ((i%2 == 1) ? POISION_ITEM : GROW_ITEM); // 아이템 생성을 맵에 적용
    }

  }
  //tempX와 tempY는 snake의 마지막 꼬리의 좌표로 만약 아이템 획득 없이 snake가 전진한다면 이 좌표에 해당하는 currentMap을 0으로 바꿔줘야 한다.
  int tempX = snakeOnMap.getSnakePosX(snakeOnMap.getSnakeLength()-1);
  int tempY = snakeOnMap.getSnakePosY(snakeOnMap.getSnakeLength()-1);
  //snake 전진
  snakeOnMap.snakeGo();

  if (currentMap[snakeOnMap.getSnakePosY(0)][snakeOnMap.getSnakePosX(0)] != 0)
  {
    //아이템 획득 or 벽 부딪힘.
  }
  else
  { //머리 부분 currentMap 반영
    currentMap[snakeOnMap.getSnakePosY(0)][snakeOnMap.getSnakePosX(0)] = 3;
    //몸통과 꼬리 currentMap 반영
    for (int i = 1; i < snakeOnMap.getSnakeLength(); i++)
    {
      currentMap[snakeOnMap.getSnakePosY(i)][snakeOnMap.getSnakePosX(i)] = 4;
    }
    //꼬리부분 0으로 바꾸기
    currentMap[tempY][tempX] = 0;
  }
}

void gameMap::snakeChangeDirection(int dir)
{
  snakeOnMap.changeDirection(dir);
}
