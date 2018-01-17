#pragma once

#include <iostream>
#include "dataclass.cpp"

using namespace std;

class DataManager{
private:
  DataClass *head;
  DataClass *tail;
  int dataSize = 0; // For caching purpose

public:
  DataManager()
  {
    head = tail = NULL;
  }

  void add(DataClass* dc)
  {
    if(head == NULL)
    {
        head = tail = dc;
        head->next = head->prev = NULL;
    }
    else
    {
        tail->next = dc;
        dc->next=NULL;
        dc->prev = tail;
        tail = dc;
    }
    ++dataSize;
  }

  void add(int x, int y)
  {
    DataClass *d = new DataClass();
    d->set(x,y);
    this->add(d);
  }

  DataClass* pop(int index)
  {
    DataClass *temp = head;
    DataClass *toBeDeleted = NULL;
    if(index < dataSize)
    {
      // |5| -> |4| -> |7| -> |1| -> |9|
      for(int i = 0; i < index; ++i)
        temp = temp->next;
      toBeDeleted = temp;
      toBeDeleted->next->prev = toBeDeleted->prev;
      toBeDeleted->prev->next = toBeDeleted->next;
      --dataSize;
    }
    return toBeDeleted;
  }

  DataClass* pop(DataClass *dc)
  {
    int zzz = 0;
    DataClass *temp = head;
    int index = 0;
    while(temp != NULL)
    {
        if(temp == dc)
          return this->pop(index);
        ++index;
    }
  }

  void print()
  {
    DataClass *temp = head;
    while(temp != NULL)
    {
        cout << "[";
        if(temp->next == NULL)
            cout << "X : " << temp->x << "| Y : " << temp->y << "]";
        else
            cout << "X : " << temp->x << "| Y : " << temp->y << "] -> ";
        temp = temp->next;
    }
  }

  DataClass* get(int index)
  {
    DataClass *temp = head;
    if(index < dataSize)
    {
      for(int i = 0; i < index; ++i)
        temp = temp->next;
    }
    return temp;
  }

  /*~DataManager()
  {
    DataClass *temp = head;
    if(head != NULL)
    {
      do{
        delete head;
      }
      while(temp->next != NULL);
    }
  }*/

  //DataManager operator+(DataManager& one) const;
};

/*DataManager DataManager::operator+ (DataManager& one) const
{
  this->add();
  return d;
};*/
