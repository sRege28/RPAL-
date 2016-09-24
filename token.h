#ifndef TOKEN_H
#define TOKEN_H

//#include <iostream>
//#include <stdio.h>
#include <string>
//#include <fstream>
//#include <stdlib.h>


using namespace std;



/*************************************
/ File: Defines the token class
/ Class : Token
/ Defines basic data structure for storing
/ type and value parameters for lexemes
/
/*************************************/
class token
{

public:

    // Data
    string type;

    string value;

    // Member functions
    token();


    token(string, string);


    void print();


    bool tokenCompare(string, string);

    bool isEmpty();



};

#endif
