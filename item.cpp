
#include "item.h"

// itemPosition 변수 접근자, 받은 주소를 이용하여 관련 함수를 호출하여 값 제어 가능.
Position * item::getItemPosition()
{
  return &(this->itemPosition);
}

// item 객체의 생성자.
item::item(int y, int x, int type)
{
  this->itemPosition = Position(y,x,type);
  this->age = 0;
}

item::item()
{
  this->itemPosition = Position();
  this->age = 0;
}

// age 변수 접근자
int item::getAge()
{
  return this->age;
}

void item::setAge(int a)
{
  this->age = a;
}
