#ifndef RP_H
#define RP_H

//#include <iostream>
//#include <stdio.h>
//#include <string>
//#include <fstream>
//#include <deque>
//#include <stdlib.h>
//#include "tokenQueue.h"
//#include "token.h"


extern char fchar;
extern char c;
extern char nxt;
extern string inp;
extern FILE *fp;

extern tokenQueue LEX_QUEUE;


char lookFwd();

//bool ifkeyw(string s);

bool isChar(char fchar);

bool isNum(char fchar);

bool isOp(char fchar);

void tokenVerify(char fchar);

token scan_ID();

token scan_Int();

token scan_String();

void scan_Comment();

token scan_Op();

token scan_Punc();

void scan(FILE *fp);


#endif
