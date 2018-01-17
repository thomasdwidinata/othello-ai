#include <iostream>
#include "datamanager.cpp"
using namespace std;
int main()
{
  DataManager dm;
  dm.add(5,5);
  dm.add(10,10);
  dm.add(7,7);
  dm.add(100,100);
  dm.add(543,563);
  dm.add(327,213);
  dm.add(-51,-222);
  dm.add(0,2);
  dm.add(737373,212);
  dm.add(10001011,111);
  printf("HERE IS THE STACK:\n");
  dm.print();
  printf("\n\n\n\nGoing to pop Index 3...\n");
  dm.pop(3);
  printf("Here is the last STACK\n");
  dm.print();
  cout << dm.get(1)->x << endl;
}
