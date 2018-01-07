#pragma once
#include <iostream>
#include "unnamed-library.cpp"
#include "Othello.cpp"
using namespace std;

Othello *o;

int main()
{
  printf( BOLDGREEN "Othello AI\n" RESETCOLOUR "Made by : \n" CYAN "Andre Valentino\nThomas Dwi Dinata\n\n" RESETCOLOUR);
  printf("Initial state:\n");
  o = new Othello();
  o->print();
  int x;
  int y;
  int choice;
  while(true)
  {
    printf("1) set 'o'\n2) set 'x'\n3) reset\n4) exit\nchoice: ");
    choice = scanNumber();
    switch(choice)
    {
      case 1:
        printf("Which coordinate? (X) = ");
        x = scanNumber();
        printf("Which coordinate? (Y) = ");
        y = scanNumber();
        o->set(x,y,true);
        break;
      case 2:
        printf("Which coordinate? (X) = ");
        x = scanNumber();
        printf("Which coordinate? (Y) = ");
        y = scanNumber();
        o->set(x,y,false);
        break;
      case 3:
        o->reset(); break;
      case 4:
        exit(0);
    }
    o->print();
  }
  return 0;
}
