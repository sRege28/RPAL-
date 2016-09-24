#include<iostream>
#include<stdlib.h>
#include<string.h>
#include "Tree.h"
#include "token.h"
#include "TreeStack.h"
#include <deque>


void TreeStack::push(Tree t)
{
  V.push_front(t);
    top = &(V.front());

}


TreeStack::TreeStack(){
  
  //deque <Tree > * V = new deque<Tree>();  
    
  Tree EOS("EOS","EOS");
  push(EOS);
  top = &V.front();
  
}

bool TreeStack::isEmpty(){

  if(top->root.type=="EOS" && top->root.value=="EOS")
        return true;
     return false;
}


 Tree TreeStack::read(){

       Tree tmp = V[0];
       
       return tmp;


}


void TreeStack::remove(){

  if(!isEmpty()){


      V.pop_front();
     top = &V.front();

        }


}

Tree TreeStack::lookFwd(){

 Tree temp = V.front();
  remove();
  Tree t = read();
    push(temp);

  if(t.root.type=="EOS" && t.root.type=="EOS")
     cout<<"From lookfwd: Stack empty";

  return t;

}


int TreeStack::getSize(){

    int size = (V.size()-1);
    
    return size;

}


void TreeStack::testStack(){


cout<<"Testing Stack \n";

Tree t1("ABC","6");
Tree t2("ABC","7");
push(t1);

Tree t3 =  read();
t2.insertChild(&t3);

t2.prettyPrint();

push(t2);

Tree t4 = read();

t4.prettyPrint();


}


//TreeStack::~TreeStack(){ delete V; }

TreeStack P_STACK;
