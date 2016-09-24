#include <string.h>
#include <deque>
#include <stdio.h>
#include "token.h"
#include "tokenQueue.h"
#include "rp.h"
#include "Tree.h"
#include "TreeStack.h"
#include "parse.h"
//#include "defs.h"

extern tokenQueue LEX_QUEUE;
extern TreeStack P_STACK;


extern deque <Tree> *temp1;




void buildTree(Tree t, int count){
int i;
Tree test;
  if(count ==0)
   {P_STACK.push(t);
     return;
   }  
  if(count > P_STACK.getSize())
  {
   cout<<"ERROR- Buffer Overflow";
   exit(1);
  }
  
  if(t.root.type=="-1111")
      return;

for(i=0; i<count; i++)
  {
    
    temp1->push_front(test=P_STACK.read());
    temp1->push_front(test =P_STACK.read());
    P_STACK.remove();
    t.insertChild(&(temp1->front()));
    
  }

//t.prettyPrint();

//std::cout<<"\n";

P_STACK.push(t);



}

void expect( string value){

token y = LEX_QUEUE.lookAtFirst();

if(y.value== value)
{
  LEX_QUEUE.pop();
  return;

}
else{
 cout<<"Expected token "<<value<<" but got  ";
 y.print();
exit(1);

}

}


void consume(string value){
    
    token m = LEX_QUEUE.lookAtFirst();

if(m.value== value)
    m = LEX_QUEUE.removeHead();
else{
    cout<<"ERROR! Unexpected token read";
    m.print();
    printf("expected %s",value.c_str());
    exit(1);

    }

}


token peek(){

token t = LEX_QUEUE.lookAtFirst();
 token n = LEX_QUEUE.lookAtNext();

 if(n.isEmpty())
     cout<<"Empty token!";

 return n;  
 
}


void parse()
{

//TreeStack P_STACK;

if(LEX_QUEUE.isEmpty())
cout<<"ERROR -Nothing to parse";

else
parseE();

}

//Function declarartions

void parseE();
void parseEw();
void parseD();
void parseDa();
void parseDb();
void parseDr();
void parseR();
void parseRn();
void parseVb();
void parseVl();
void parseT();
void parseTa();
void parseTc();
void parseB();
void parseBt();
void parseBs();
void parseBp();
void parseA();
void parseAt();
void parseAf();
void parseAp();

void parseE()
{
  token t = LEX_QUEUE.lookAtFirst();

  if(t.tokenCompare("KEYWORD","let"))
  {
     consume("let");

     parseD();

     expect("in");

     parseE();

     buildTree(t,2);



  }

  else if(t.tokenCompare("KEYWORD","fn"))
  {
    consume("fn");

    int i = 0;

      do{

          parseVb(); //Note: consume in Vb function.

          i++;

        } while(LEX_QUEUE.lookAtFirst().tokenCompare("<Punc>","(") || LEX_QUEUE.lookAtFirst().tokenCompare("<Punc>",")") );

       consume(".");

       parseE();

       token t1("KEYWORD","lambda");

       buildTree(t1, i+1);

  }

   else{  parseEw();   }





}


void parseD(){
    
    
    parseDa(); //consume in Da
    
    token t = LEX_QUEUE.lookAtFirst();
    
    if(t.tokenCompare("KEYWORD","within")) {
        
        consume("within");
         
         parseD();
         
         Tree t1(t);
         
         buildTree(t1,2);
        
        
        
        }
    
}


void parseDa(){
    
    
      token t = LEX_QUEUE.lookAtFirst();
      
      parseDr();
      
      t = LEX_QUEUE.lookAtFirst();
    
      if(t.value=="and"){
          
          
          int n =0;
          
          Tree t1(t);
          
          
          while(t.value=="and"){
              
              consume("and");
              
              parseDr();

              n++;
              
              t = LEX_QUEUE.lookAtFirst();
              
                          
              }
          
          
          buildTree(t1,n+1);
          
          
          
          
          }
    
    
    
    
    
    }


void parseDr(){
    
    
     token t = LEX_QUEUE.lookAtFirst();
     
     if(t.value=="rec"){
    
     consume("rec");
     
     Tree t1(t);
     
     parseDb();
     
     buildTree(t1,1);
     
     }
    
    else{ parseDb(); }
    
    
    }


void parseDb(){
    
    token t = LEX_QUEUE.lookAtFirst();
    
    if(t.tokenCompare("<Punc","(")){
        
        
        consume("(");
        
        parseD();
        
        consume(")");
        
        return;
        
     }
    
    if(t.type !="ID"){printf("Error in parsing Db, id expected but found"); t.print(); return;}

    t = LEX_QUEUE.lookAtFirst();

    token next = peek();
    
    
    if(next.tokenCompare("<Punc>",",") ||  next.tokenCompare("OP","="))
        
        {
            parseVl();
            
            consume("=");
            
            Tree t1("OP","=");
            
            parseE();
            
            buildTree(t1,2);
                      
            
            
        }
    
    else if(next.type =="ID" || next.tokenCompare("<Punc>","(")){
        
            Tree t2 ("KEYWORD","function_form");
            
            parseVb();
            
            t = LEX_QUEUE.lookAtFirst();
            
            int n =0; 
            
            next = peek();

               do     
            {
                
               parseVb();

               n++;
               
               next = LEX_QUEUE.lookAtFirst();
                
                
            }
            
             while(!next.tokenCompare("OP","="));
        
           consume("=");
           
           parseE();
           
           buildTree(t2,n+2);
        
        
        
        }
    
    else {printf("Error while parsing Db, found "); 
    t.print();}
    
    }



void parseVb(){
    
    token t = LEX_QUEUE.lookAtFirst();
    
    if(t.type=="ID")
     {
         LEX_QUEUE.pop();
         
         Tree t1(t);
         
         P_STACK.push(t1);
         
     }
    
    else if(t.tokenCompare("<Punc>","(")){
        
        consume("(");
        
        t = LEX_QUEUE.lookAtFirst();
        
             if(t.tokenCompare("<Punc>",")")){
        
                  consume(")");
                  
                  Tree t1("<Punc>","()"); //No idea what type it is
        
                  buildTree(t1,0); 
                }
                  
             else{
                 
                   parseVl();
                 
                   consume(")");
                 
                 
                 
                 }
          
          }
        else{printf("Error while parsing Vb, expected identifier or (, got"); t.print();}


}
    
    
void parseVl(){
    
      token t = LEX_QUEUE.lookAtFirst();
      
      if(t.type !="ID"){
          
          printf("Error while parsing Vl, expected identifier, got "); 
          t.print();
          return;
          }
    
    Tree t1(t);

    LEX_QUEUE.pop();
   
    P_STACK.push(t1);

    
    t = LEX_QUEUE.lookAtFirst();
  
   if(t.tokenCompare("<Punc>",",")){    
    
       Tree t2(t);
       
       consume(",");
       
       token first,next = peek();
       
       int n=0;
       
       while(next.tokenCompare("<Punc>",","))
           {
             first = LEX_QUEUE.removeHead();
             
             Tree f(first);
             
             P_STACK.push(f);
             
             consume(",");

             n++;             
           
             next = peek();
           
           }

           first = LEX_QUEUE.removeHead();
             
             Tree f(first);
             
             buildTree(f,0);
             
             n++;
             
             buildTree(t2,n+1);

        
        
        }  
       
    
    }    
    
    


void parseEw(){
    
  parseT(); // consume token in T

  token t = LEX_QUEUE.lookAtFirst();
  
   if(t.tokenCompare("KEYWORD","where"))  
   {   
       //Should T be left child or right?
       
       consume("where");
       
       parseDr();

       Tree t1(t);

       buildTree(t1,2);
       
    }
   



 
    
}


void parseT(){
    
     parseTa();
     
     int n =0;
     
     token t = LEX_QUEUE.lookAtFirst();
     
     if(t.tokenCompare("<Punc>",",")){
         
         Tree ta("KEYWORD","tau");
         
         while(t.tokenCompare("<Punc>",","))
             {
               consume(",");
             
                parseTa();
              
                n++;
             
                t = LEX_QUEUE.lookAtFirst();
             
             }
         
           buildTree(ta,n+1);
         
         
         
         }
    
    
    
    
    
    
    
    }


void parseTa(){
    
 parseTc();

 token t = LEX_QUEUE.lookAtFirst();
 
 while(t.tokenCompare("KEYWORD","aug")){
     
       consume("aug");
       
       parseTc();
       
       Tree au("KEYWORD","aug");

       buildTree(au,2);    
     
       t = LEX_QUEUE.lookAtFirst();
     
     } 
     
}


void parseTc(){
    
    parseB();
    
    token t = LEX_QUEUE.lookAtFirst();
    
    if(t.tokenCompare("OP","->")){
        
        consume("->");
        
        parseTc();
        
        consume("|");               
        
        parseTc();
        
        Tree t1(t);
        
        buildTree(t1,3);
        
        }
    
        
    
    
    }
    

void parseB(){
    

parseBt();

token t = LEX_QUEUE.lookAtFirst();

    while(t.tokenCompare("KEYWORD","or")){
         
          consume("or"); 
         
          parseBt();
          
          Tree t1(t);
          
          buildTree(t1,2);
        
          t = LEX_QUEUE.lookAtFirst();
        
        }
    
    
    
}    


void parseBt(){

 parseBs();    
    
 token t = LEX_QUEUE.lookAtFirst();

    while(t.tokenCompare("OP","&")){
        
        consume("&"); 
        
        parseBs();
        
        Tree t1(t);
        
        buildTree(t1,2);
        
        t = LEX_QUEUE.lookAtFirst();
        
        }  
    

    
}

void parseBs(){
    
     token t = LEX_QUEUE.lookAtFirst();
    
     if(t.tokenCompare("KEYWORD","not")){
         
         consume("not");
         
         parseBp();
         
         Tree t1(t);

         buildTree(t1,1);         
         
         }
    
       else{
           
            parseBp();
           
           }
    
    
    }



void parseBp(){
    
 parseA();
 
 int flag =0;

 token t = LEX_QUEUE.lookAtFirst();

 if(t.tokenCompare("KEYWORD","gr") || t.tokenCompare("OP",">")){
      flag=1;
      
      t.value = "gr";
      t.type ="KEYWORD";
      
      LEX_QUEUE.pop();
     
     
     }
    
 else if(t.tokenCompare("KEYWORD","ge") || t.tokenCompare("OP",">=")){
      flag=1;
     
      t.value = "ge";

      t.type ="KEYWORD";
       
      LEX_QUEUE.pop();
     
     
     }   
    
      
       else if(t.tokenCompare("KEYWORD","ls") || t.tokenCompare("OP","<")){
             flag=1; 
           
             t.value = "ls";

             t.type ="KEYWORD";
       
             LEX_QUEUE.pop();
     
     
             } 

             
             else if(t.tokenCompare("KEYWORD","le") || t.tokenCompare("OP","<=")){
                    flag=1;   
                 
                    t.value = "le";

                    t.type ="KEYWORD";
       
                    LEX_QUEUE.pop();
     
     
                 } 

                    
                   else if(t.tokenCompare("KEYWORD","eq")){
                            flag=1;      
                       
                            t.value = "eq";

                            t.type ="KEYWORD";
       
                            LEX_QUEUE.pop();
     
     
                       }  

                        
                         else if(t.tokenCompare("KEYWORD","ne")){
                             flag=1; 
                             
                             t.value = "ne";

                             t.type ="KEYWORD";
       
                             LEX_QUEUE.pop();
     
     
                              }        

  if(flag == 1)        
  {
      
      Tree t1(t);
      
      parseA();
      
      buildTree(t1,2);
      
      
      
  }
}


void parseA(){
    
token t = LEX_QUEUE.lookAtFirst();
int flag =0;


if(t.tokenCompare("OP","+") || t.tokenCompare("OP","-")){

  if(t.tokenCompare("OP","+"))
    consume("+");

  else if(t.tokenCompare("OP","-")){flag =1; consume("-");}
    
  parseAt();   
    
  if(flag ==1){
     
   Tree t("KEYWORD","neg");

   buildTree(t,1);    
   }   
    
}
    
 else parseAt();
 
 t = LEX_QUEUE.lookAtFirst();
 
 while(t.tokenCompare("OP","+") || t.tokenCompare("OP","-")){
     
         LEX_QUEUE.pop();
         
         parseAt();
         
         Tree t2(t);
         
         buildTree(t2,2);

         t= LEX_QUEUE.lookAtFirst();
     
     }
     
     
 
    
}



void parseAt(){
    
    
  parseAf();

  token t = LEX_QUEUE.lookAtFirst();

  while(t.tokenCompare("OP","*") || t.tokenCompare("OP","/")){
      
         LEX_QUEUE.pop();
         
         parseAf();
         
         Tree t1(t); 

         buildTree(t1,2);
    
         t = LEX_QUEUE.lookAtFirst();
      
      }  
    
    
    
    
}


void parseAf(){
    
  parseAp();

   token t = LEX_QUEUE.lookAtFirst();

   while(t.tokenCompare("OP","**")){
       
         consume("**");
         
         Tree t1(t);

         buildTree(t1,2);       
       
         t = LEX_QUEUE.lookAtFirst();
       
       } 
    
    
    
}


void parseAp(){
    
  
parseR();

token t = LEX_QUEUE.lookAtFirst();
 
while(t.tokenCompare("OP","@")){
    
       consume("@");

       t = LEX_QUEUE.lookAtFirst();
       
       if(t.type!="ID")
        {printf("Expected identifier but got "); 
        t.print();
         return;
        }
      
        token t1 = LEX_QUEUE.removeHead();
        
        Tree t2(t1);
        
        P_STACK.push(t2);
    
        parseR();
        
        buildTree(t,3);
        
        t = LEX_QUEUE.lookAtFirst();

    
    } 
    



    
    
}


void parseR(){
    
    
    parseRn();
    
    token t = LEX_QUEUE.lookAtFirst();
    
    while(t.type=="ID" || t.type=="INT" || t.type=="STR" || t.value=="true" || t.value=="false" 

       || t.value=="nil" || t.value=="dummy" || t.value =="(")
           
    {
        
      parseRn();
        
      Tree tg("KEYWORD","gamma");
      
      t = LEX_QUEUE.lookAtFirst();
      
      token tn = LEX_QUEUE.lookAtNext();

      buildTree(tg,2);

      t = LEX_QUEUE.lookAtFirst(); 

      tn = LEX_QUEUE.lookAtNext(); 
    
        
        
    }     
    
    
    
    
    
    }
    
    
    
    void parseRn()
    {
        std::string tr = "true";
        
        std::string fa = "false";
        
        std::string du = "dummy"; 
        
        std:: string ni = "nil";
        
   
        token t;
        
        t = LEX_QUEUE.lookAtFirst();

        if(t.type =="ID"|| t.type=="INT"|| t.type=="STR" || t.value == tr ||  t.value == fa || t.value == du || t.value == ni)
            {
                token t1 = LEX_QUEUE.removeHead();
                
                token t3 = LEX_QUEUE.lookAtFirst();
                
                token tn = LEX_QUEUE.lookAtNext();
                
                Tree t2(t);
                
                buildTree(t2,0);
                
                
            }
        
            else
             {
                consume("(");
                
                t = LEX_QUEUE.lookAtFirst();

                parseE();

                consume(")");
                
                // t = LEX_QUEUE.lookAtFirst();
                 
                 //token t1 = LEX_QUEUE.lookAtNext();    
             
             };
        
        
        
        
        
    }
    
    
    
    
    
    
    void testParse(){
        
        token t1("", "1");
        token t2("", "2");
        token t3("", "3");
        token t4("","4");
        
        LEX_QUEUE.pushback(t1);
        
        LEX_QUEUE.pushfront(t2);
        
        LEX_QUEUE.pushback(t3);
        
        LEX_QUEUE.pushback(t4);

        token t = LEX_QUEUE.lookAtFirst();
        
        t.print();

        consume("2");    
        
         t = LEX_QUEUE.lookAtFirst();
        
         t.print();
        
         t = peek();
        
         t.print();
        
        }