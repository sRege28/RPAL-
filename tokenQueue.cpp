
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <deque>
#include <stdlib.h>

#include "token.h"
#include "tokenQueue.h"



tokenQueue LEX_QUEUE;

bool tokenQueue::isEmpty(){

if(s.empty())
    return true;
else return false;

}

/*********************************************
Function: pushfront();
Input: token t
Description: Pushes the token t to the front
of the queue
Output: None
**********************************************/


void tokenQueue::pushfront(token t)
    {
        tp = t;
        s.push_front(tp);
    }


/*********************************************
Function: pushback();
Input: token t
Description: Pushes the token t to the back
of the queue
Output: None
**********************************************/


void tokenQueue::pushback(token t)
    {
        tp = t;
        s.push_back(tp);
    }



/*********************************************
Function: lookAtFirst();
Input: None
Description: Return the first token at the head
of the queue, without popping it out
Output: Head token t
**********************************************/

token tokenQueue::lookAtFirst()

{   
    token EOS("-1111","-1111");
    
    if(s.size()==0)
        return EOS;
    else
    return s[0];
    
}


/*********************************************
Function: removeHead();
Input: None
Description: Return the first token at the head
of the queue, after popping it out
Output: Head token t
**********************************************/

token tokenQueue::removeHead()
    {
        if(s.size()==0)
        {
        cout<<"No element to remove";
         return token("","");

        }
        t=s.front();
        s.pop_front();
        return t;
    }

/*********************************************
Function: pop();
Input: None
Description: Remove the first token at the head
Output: None
**********************************************/


void tokenQueue::pop()
    {
        s.pop_front();
    }


/*********************************************
Function: emptyQueue();
Input: None
Description: Remove all elements from the queue
Output: None
**********************************************/

void tokenQueue::emptyQueue() // Maybe not needed?
    {

        while(s.size()!=0)
        {
            s.front().print();
            pop();
        }

    }

/*********************************************
Function: lookAtNext();
Input: None
Description: Return the second token at the head
of the queue, without popping it out
Output: Second token t
**********************************************/

token tokenQueue::lookAtNext()
    {
      if(s.size()>=2){
        tp = removeHead();
        t = removeHead();
        s.push_front(t);
        s.push_front(tp);
        return t;
      }

      else return token("","");
    }





