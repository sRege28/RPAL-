#ifndef TOKENQUEUE_H
#define TOKENQUEUE_H

//#include <iostream>
//#include <stdio.h>
//#include <string>
//#include <fstream>
#include <deque>
//#include <stdlib.h>

//#include "token.h"


using namespace std;
/****************************************
/File: Defines the tokenQueue class
/Class: Defines a queue structure for storing
 lexeme tokens. Uses the std::deque template.

*****************************************/
class tokenQueue
{

public:
    deque<token> s;
    
    token tp,ts;
    token t;

    bool isEmpty();

    void pushfront(token);

    void pushback(token);

    token lookAtFirst();

    token removeHead();

    void pop();

    void emptyQueue();

    token lookAtNext();


};

#endif
