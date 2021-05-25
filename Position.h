#ifndef _POSITION_H_
#define _POSITION_H_
#include <iostream>

using namespace std;

class Position
{
private:
  int x;
  int y;
  int type;

public:
  Position(int py=0, int px=0, int ptype=0);
  int getPosX();
  int getPosY();
  int getType();
  void setPosX(int px);
  void setPosY(int py);
  void setType(int ptype);
};

#endif
