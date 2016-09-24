#ifndef STACK_H
#define STACK_H
#include <deque>
#include<stdlib.h>
#include"token.h"
#include"Tree.h"


class TreeStack{

public:
  deque <Tree>  V;
   Tree * top;
   int size;

  TreeStack();
  bool isEmpty();
  Tree  read();
  void push(Tree t);
  Tree lookFwd();
  void remove();
  void testStack();
  int getSize();
  //~TreeStack();
  
};




#endif
