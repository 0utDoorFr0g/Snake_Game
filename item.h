#include "Position.h"

// 아이템 속성에 대응하는 상수값 정의
#define POISION_ITEM 5
#define GROW_ITEM    6

//아이템을 표기할 유니코드값 정의
#define POISION_CHAR     0x2b14
#define GROW_CHAR        0x2b15

class item
{
private:
  Position itemPosition; // 아이템이 위치한 위치, 아이템의 종류
  int age; // 아이템이 맵에 출현한 후 지난 시간
public:
  int getAge();
  void setAge(int a);
  Position * getItemPosition();
  item(int y, int x, int type);
  item();
};
