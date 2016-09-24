#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <deque>
#include <stdlib.h>

#include "token.h"
#include "tokenQueue.h"
#include "rp.h"
#include "Tree.h"
#include "TreeStack.h"
#include "parse.h"
//#include "defs.h"
using namespace std;

extern tokenQueue LEX_QUEUE;

extern TreeStack  P_STACK;


deque<Tree> *temp1 = new deque<Tree>;


//string inp;
FILE *fp;
char fchar;
char nxt;
char c;
string inp;

int main(int argc, char ** argv)
{
  inp =argv[1];

    fp =fopen(argv[2],"r");


  Tree AST;

  if(inp=="-test"){

    AST.testTree();
  
  }


    if((inp=="-lex"))
    {

        //tokenQueue LEX_QUEUE = new tokenQueue();
        scan(fp);
        LEX_QUEUE.emptyQueue();

    }


    else if (inp=="-ast")
    {

        scan(fp);
        parse();
        //cout<<"THE AST IS:-\n";
        AST = P_STACK.read();
        
        AST.prettyPrint();

    }

    else if (inp =="-st")
    {
       
        scan(fp);
        parse();
        //cout<<"THE AST IS:-\n";
        AST = P_STACK.read();

        AST.stdize();
        AST.prettyPrint();
    }


    delete temp1;
    fclose(fp);
    return 0;
}

