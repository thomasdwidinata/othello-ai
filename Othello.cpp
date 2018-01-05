#pragma once

#include <iostream>
#include "unnamed-library.cpp"

#define OTHELLO_SIZE 8

using namespace std;

/*

  Othello Indexing and Printing System

  X  0  1  2  3  4  5  6  7
  o--------------------------o  Y
  |  -  -  -  -  -  -  -  -  |  0
  |  -  -  -  -  -  x  -  -  |  1
  |  -  -  -  -  -  -  -  -  |  2
  |  -  -  -  -  -  -  -  -  |  3
  |  -  -  -  o  -  -  -  -  |  4
  |  -  -  -  -  -  -  -  -  |  5
  |  -  -  -  -  -  -  -  -  |  6
  |  -  -  -  -  -  -  -  -  |  7
  o--------------------------o

                       Y  X
  The first `o` is on [4][3],
  The first `x` is on [1][5].
  But in this Library, you can call it like this:
    set(true, 3, 4);
    set(false, 5, 1);
               X, Y

  *true is for `o`*
  *false is for `x`*

*/

class Othello{
private:
  unsigned int othello[OTHELLO_SIZE][OTHELLO_SIZE];
public:
  Othello()
  {
    reset();
  }
  void print()
  {
    printf("o--------------------------o\n");
    for(int i = 0; i < OTHELLO_SIZE; ++i){
      printf("|  ");
      for(int j = 0; j < OTHELLO_SIZE; ++j)
      {
        char c;
        switch(othello[i][j])
        {
          case 0:
            c = '-'; break;
          case 1:
            c = 'o'; break;
          case 2:
            c = 'x'; break;
        }
        printf("%c  ", c);
      }
      printf("|\n");
    }
    printf("o--------------------------o\n");
  }
  void set(unsigned int X, unsigned int Y, bool isO)
  {
    if(isO)
      othello[Y][X] = 1;
    else
      othello[Y][X] = 2;
  }
  void reset()
  {
    for(int i = 0; i < OTHELLO_SIZE; ++i)
      for(int j = 0; j < OTHELLO_SIZE; ++j)
        othello[i][j] = 0;
  }
};
