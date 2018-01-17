#pragma once

#include <iostream>
#include "unnamed-library.cpp"

#define OTHELLO_SIZE 8
#define OTHELLO_WHITE 1
#define OTHELLO_BLACK 2

using namespace std;

/*

  Othello Indexing and Printing System

  X  A  B  C  D  E  F  G  H
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
    set(1, 3, 4);
    set(2, 5, 1);
               X, Y

  *1 is for `o`*
  *2 is for `x`*

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
    printf("     A  B  C  D  E  F  G  H\n");
    printf("  o--------------------------o\n");
    for(int i = 0; i < OTHELLO_SIZE; ++i){
      printf("%d |  ", i);
      for(int j = 0; j < OTHELLO_SIZE; ++j)
      {
        char c;
        switch(othello[i][j])
        {
          case 0:
            c = '-'; break;
          case 1:
            c = 'w'; break;
          case 2:
            c = 'b'; break;
        }
        printf("%c  ", c);
      }
      printf("|\n");
    }
    printf("  o--------------------------o\n");
  }

  void set(unsigned int X, char Y_char, int othello_colour)
  {
    unsigned int Y = 0;
    switch(Y_char)
    {
      case 'A':
        Y = 0; break;
      case 'B':
        Y = 1; break;
      case 'C':
        Y = 2; break;
      case 'D':
        Y = 3; break;
      case 'E':
        Y = 4; break;
      case 'F':
        Y = 5; break;
      case 'G':
        Y = 6; break;
      case 'H':
        Y = 7; break;
    }
    switch(othello_colour)
    {
      case OTHELLO_WHITE:
        othello[Y][X] = OTHELLO_WHITE;
        break;
      case OTHELLO_BLACK:
        othello[Y][X] = OTHELLO_BLACK;
        break;
    }
    game();
  }

  void reset()
  {
    for(int i = 0; i < OTHELLO_SIZE; ++i){
      for(int j = 0; j < OTHELLO_SIZE; ++j)
        othello[i][j] = 0;
    }

    // Default Othello starting point. If you want to make your own othello, modify this
    othello[3][3] = othello[4][4] = OTHELLO_BLACK;
    othello[3][4] = othello[4][3] = OTHELLO_WHITE;
  }

  void game(unsigned int init_X, unsigned int init_Y)
  {
    /*
      X  A  B  C  D  E  F  G  H
      o--------------------------o  Y
      |  -  -  -  -  -  -  -  -  |  0
      |                          |
      |  -  -  -  -  -  -  -  -  |  1
      |                          |
      |  -  -  -  -  -  -  -  -  |  2
      |                \^/       |
      |  -  -  -  b  w<<b>>-  -  |  3
      |                /v\       |
      |  -  -  -  w  b  -  -  -  |  4
      |                          |
      |  -  -  -  -  -  -  -  -  |  5
      |                          |
      |  -  -  -  -  -  -  -  -  |  6
      |                          |
      |  -  -  -  -  -  -  -  -  |  7
      o--------------------------o
    */
    for(int i = (init_y-1) ; i < (init_y+1) ; ++i)
    {
      for(int j = (init_x-1); j < (init_y+1) ; ++i)
      {

      }
    }
    othello[][] = new Fenbert();

    return;
  }
};
