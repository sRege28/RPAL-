

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <deque>
#include <stdlib.h>

#include "token.h"
#include "tokenQueue.h"
#include "rp.h"

using namespace std;
/*
bool ifkeyw(s)                                              
{      if(                                                         
      s=="let" || s=="fn" || s=="aug" || s=="not" || s=="ge" || s=="le"  
      s=="ne" || s=="false" || s=="dummy" || s=="and" || s=="rec" || s=="in"
      s=="where" || s=="or" || s=="gr" || s=="ls" || s=="eq" || s=="true" 
      s=="nil" || s=="within" || s=="rec"   
         )
     return true;
       else return false;                   
}
*/
char lookFwd( )
{
    nxt = getc(fp);
    return (nxt == EOF) ? EOF : ungetc(nxt,fp);


}


bool isChar( char fchar )

{
    if((fchar>=65&&fchar<=90)||(fchar>=97&&fchar<=122))
        return true;
    else return false;

}

bool isNum(char fchar)
{
    if((fchar>=48 && fchar<=57))
        return true;

    else return false;
}
bool isOp(char fchar)
{
    if(fchar == '+'|| fchar == '-' || fchar =='*' || fchar =='<' || fchar =='>'|| fchar =='&' || fchar =='.' || fchar =='@' || fchar =='/' || fchar ==':' || fchar =='=' ||fchar == '|' || fchar =='$' || fchar =='!' || fchar =='#'
            ||fchar =='%' || fchar =='^' || fchar =='_' || fchar =='[' || fchar ==']' || fchar =='{' || fchar=='}' || fchar =='"'|| fchar =='`' || fchar =='?')
        return true;

    else return false;
}


void tokenVerify(token t, string type, string value)

{
  if(!(t.type==type && t.value==value))
   {cout<<"ERROR!Unexepected value";
   exit(1);
   }
   else return;
}


//Identifies the identifier token
token scan_ID()
{

    token token_id;

    token_id.type = "ID";

    token_id.value = fchar;

    lookFwd();

    while( isChar(nxt) || isNum(nxt) || (nxt=='_'))
    {
        fchar = fgetc(fp);
        token_id.value += fchar;
        lookFwd();

    }
    
    string s = token_id.value;
    
    if(s=="let" || s=="fn" || s=="aug" || s=="not" || s=="ge" || s=="le" || s=="ne" || s=="false" || s=="in" || s=="rec" || s=="and" || s=="dummy"||s=="where" || s=="or" || s=="gr" || s=="ls"||s=="eq" || s=="true" || s=="nil" || s=="within"
      )
          
    token_id.type = "KEYWORD";

    return token_id;


}

//Identifies the integer token
token scan_Int()
{

    token token_int;

    token_int.type ="INT";

    token_int.value = fchar;

    lookFwd();

    while(isNum(nxt))
    {
        fchar =fgetc(fp);
        token_int.value += fchar;
        lookFwd();
    }

    return token_int;



}

//Identifies the STR token
token scan_string()
{

    token token_str;

    token_str.type ="STR";
    
    token_str.value="";

    do
    {

        fchar =fgetc(fp);
//lookFwd();
        if (fchar == '"' || fchar == '\'') break;
//else
        token_str.value += fchar;

    }
    while(fchar!= '"' || fchar == '\'') ;

    //fchar = fgetc(fp);

    return token_str;
}

//Identifies and parses comments
void scan_Comment()
{

    while((fchar = fgetc(fp))!= '\n')
        continue;




}
//Identifies the operator token
token scan_Op()
{

    token token_op;

    token_op.type ="OP";
    
    token_op.value = fchar;

    lookFwd();
    while(isOp(nxt))
    {
        fchar =fgetc(fp);
        token_op.value += fchar;
        lookFwd();
    }

    return token_op;
}

//Identifies the punctuation token
token scan_Punc()
{

    token token_punc;

    token_punc.type="<Punc>";

    token_punc.value = fchar;

    return token_punc;

}



//Scans the given file character by character, creating tokens
void scan(FILE *fp)
{
    char tm;
    token lexeme;
    
    

    while( (fchar =fgetc(fp))!= EOF )
    { 
        int fc = (int)fchar; 

        if(isChar(fchar)) //character
        {
            lexeme=scan_ID();

        }
        else if(isNum(fchar))

            lexeme=scan_Int();

        else if(fchar =='"' || fchar == '\'')

            lexeme=scan_string();

        else if(fchar=='/')
        {
            lookFwd();
            if(nxt == '/')
            {
                scan_Comment();
                continue;
            }
            else scan_Op();


        }
        else if(isOp(fchar))
            //cout<<fchar<<"is operator     ";

            lexeme=scan_Op();

        else if( fchar=='('  || fchar==')' ||  fchar==';'  ||  fchar==',' )

            lexeme=scan_Punc();

        else if( fchar==' ' || fchar =='\n' || fchar=='\t' || fchar =='\r' )
            continue;

        else {cout<<"ERROR! TOKEN NOT RECOGNIZED!" << "Start "<<fchar<<"\n";return;}

        LEX_QUEUE.pushback(lexeme);



    }


    return;
}

/*
void parseD(){

cout<<"in D";

 Read("ID","a");

 token t = token("","D");

 buildTree(t,0);


}

void parseE()
{

    token t, t1,t2,t3;

    t = LEX_QUEUE.lookAtFirst();

    cout<<"Element in Lex";t.print();

  if(tokenCompare(t,"ID","let"))

   {

    cout<<"True";

     Read("ID","let");


    buildTree(t,0);


    parseD();


    Read("ID","in");



    buildTree(t,1);


   }

    /*else if(tokenCompare(t,"ID","fn"))

        {

         t2 = token("","lambda");

         //t2.print();

         do
            {
                 ParseVb;
                 t3 =LEX_QUEUE.removeHead();
                 t3.print();

            }


         while ( tokenCompare((LEX_QUEUE.lookAtFirst()),"<Punc>","(" ) || (LEX_QUEUE.lookAtFirst().type == "ID"));

         t1 = LEX_QUEUE.removeHead();

          //t1.print();

         tokenVerify(t1,"OP",".");



         //parseE();

        }

        else parseEw();

      //  else

*/
       // }










