#include <iostream>
#include "Position.h"

using namespace std;

Position::Position() : x(0), y(0), type(0){}
Position::Position(int py, int px, int ptype): x(px), y(py), type(ptype){}


int Position::getPosX()
{
  return this->x;
}
int Position::getPosY()
{
  return this->y;
}
int Position::getType()
{
  return type;
}

void Position::setPosX(int px)
{
  this->x = px;
}
void Position::setPosY(int py)
{
  this->y = py;
}
void Position::setType(int ptype)
{
  this->type = ptype;
}
