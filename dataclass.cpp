#pragma once

#include <iostream>

using namespace std;

class DataClass{
public:
  int x;
  int y;
  DataClass *next;
  DataClass *prev;
  DataClass()
  {
    x = y = 0;
  }

  void set(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

  void print()
  {
    printf("This object value is X: %d, Y: %d\n", x,y);
  }

  DataClass operator+(DataClass& one) const;
  bool operator==(DataClass& one) const;
};

DataClass DataClass::operator+ (DataClass& one) const
{
  DataClass d;
  d.set(this->x + one.x, this->y + one.y);
  return d;
};

bool DataClass::operator== (DataClass & one) const
{
  if(this->x == one.x && this->y == one.y)
    return true;
  else
    return false;
}
