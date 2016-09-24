#ifndef TREE_H
#define TREE_H


#include <iostream>
//#include <stdio.h>
#include "token.h"

class Tree
{
  public:

      token root;
      Tree *left;
      Tree *right;

      Tree();
      Tree(token n);
      Tree(string a, string b);
      void printRoot();
      void insertChild(Tree* n);
      void prettyPrint();
      void testTree();
      void stdize();

     void levelPrint(int lvl);

};



#endif
