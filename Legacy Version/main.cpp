#pragma once
#include <iostream>
#include "unnamed-library.cpp"
#include "Othello.cpp"
using namespace std;

Othello *o;

int main()
{
  string a = "A1";
  char b = *a.c_str();
  int c = ((int) *a.c_str()) - 64;
  cout << "char b : " << b << endl;
  cout << "int c : " << c << endl;
  cout << "System testing completed!" << endl;
  system_pause();
  int x;
  int y;
  int choice;
  int turn = OTHELLO_WHITE;
  string name = "\n";
  o = new Othello();

  printf( BOLDGREEN "Othello AI\n" RESETCOLOUR "Made by : \n" CYAN "Andre Valentino\nFenbert\nThomas Dwi Dinata\n\n" RESETCOLOUR);
  printf("Hello, please enter youe name : ");
  getline(std::cin, name);
  while(strcmp(name.c_str(), "\n") == -10)
  {
    printf("Please enter a name: ");
    getline(std::cin, name);
  }
  std::cin.clear();
  printf("Hi, %s! Let's play othello! You are the white and I am the black one (AI).\n\n", name.c_str());
  o->print();
  printf("Tip: To enter a move, you just need to type the letter followed by the number.\nFor example: " BOLDCYAN "D2" RESETCOLOUR ", " BOLDCYAN "F7" RESETCOLOUR "\n");
  system_pause();
  string move;
  unsigned int X = 0;
  char Y = 'A';
  while(true)
  {
    if(turn == OTHELLO_WHITE)
    {
      printf(BOLDCYAN"%s" RESETCOLOUR "'s' Turn : ", name.c_str());
      getline(std::cin, move);
      Y = *move.c_str();
      X = ((int) *move.c_str()) - 64;
      o->set(X, Y, OTHELLO_WHITE);
      //char a = move.c_str();
      //o->set(OTHELLO_WHITE);
    }

    else
    {
      printf(BOLDRED "AI" RESETCOLOUR "'s Turn. Thinking...");
    }

    system_pause();
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
