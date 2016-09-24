#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <stdlib.h>


#include "token.h"

using namespace std;



/*********************************************
Function:Token constructor
Input: None
Description: Initializes token to empty values
Output: None
**********************************************/
    token::token()
    {
       type = "-1111";
        value ="-1111";


    }
/*********************************************
Function:Token constructor
Input: string type , string value
Description: Initializes token to values given by
  input parameters
Output: None
**********************************************/
    token::token(string ty, string val)
    {
        type = ty;
        value =val;

    }

  /*********************************************
Function: print();
Input: None
Description: Prints the value of the given token
Output: None
**********************************************/


    void token::print()
    {
        if(type != "-1111")
           if(type == "OP" || type =="KEYWORD")
             cout<<value<<"\n";
             else
                cout<<"<"<<type<<":"<<value<<">\n";
    }



    bool token::tokenCompare(string type, string value)
{
    if(this->type==type && this->value==value)
        return true;
    else return false;
}



  bool token::isEmpty()
  {
     if(type=="-1111"&& value=="-1111")
        return true;
    else return false;
  }




