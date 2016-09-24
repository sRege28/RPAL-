#include "Tree.h"
#include<cstddef>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "TreeStack.h"
#include "defs.h"
//extern deque<Tree> *temp1;




Tree::Tree(){

 left =NULL;
 right = NULL;


}


Tree:: Tree(token n){

    root = n;
    left = NULL;
    right = NULL;
}



Tree:: Tree(string a, string b){

    token t1(a,b);
    root = t1;
    left = NULL;
    right = NULL;
}



void Tree::insertChild(Tree * n){

//std::cout<<"Entering  func";

//if(n->root = -1111)
  //return;


if(root.isEmpty()){
//std::cout<<"Root is empty";
    root = n->root;
    left = n->left;
    right = n->right;

      }

 else{
    //std::cout<<"Root is empty";
    int i=0;
    Tree *temp = left;

    if(temp==NULL)
      left = n;
    //std::cout<<"Hello!";
 else{
         left = n;
         n->right = temp;
     

      }
     }

}


void Tree::printRoot()
{
    
    root.print();

}


void Tree::prettyPrint(){

    levelPrint(0);


}

void Tree::levelPrint(int lvl){

int count = lvl;

while(count != 0)

{
  std::cout<<".";
  count--;
}

printRoot();

if(left!=NULL){

    //left->printRoot();
    left->levelPrint(lvl+1);

              }

if(right!=NULL){


          right->levelPrint(lvl);
          //temp = temp->right;

}



}




void Tree::stdize(){
    
    Tree* p;
    Tree* x;
    Tree* e;
    Tree * x1;
    Tree * x2;
    Tree * e1;
    Tree * e2;
    
    if(left!= NULL)
      left->stdize();
    if(right!=NULL)  
      right->stdize();

        
   if(root.tokenCompare("KEYWORD","let"))
      {
         root.type = root.value = "gamma";
          
         left->root.type = left->root.value = "lambda"; 
          
         p = left->right;

         x = left->left;
         
         e = x->right;

         left-> right = e;
          
         x->right = p;  

    }

       
else if(root.tokenCompare("KEYWORD","where"))
     {
         
         root.type = root.value = "gamma";
         
         p = left;
         
         x = p->right->left;
         
         e = x->right;
         
         p->right = NULL;
         
         Tree n("lambda","lambda");
         
         n.left = x;
         
         n.right = p;
         
         n.left->right = e;

         temp1->push_front(n); 

         left =&(temp1->front());
         
    
         


     }
    
          
else if(root.tokenCompare("KEYWORD","within"))
     {
         
         x1 = left->left;
         e1 = x1->right;
         x2 = left->right->left;
         e2 = x2->right;
         root.type = "KEYWORD";
         root.value = "eq";
         x1->right =NULL;
         x2->right = NULL;
         left = x2;             
         Tree n("lambda","lambda");
         n.left = x1;
         n.left->right = e2;
       
         
         temp1->push_front(n); 
         
         Tree n1("gamma","gamma");
         n1.left = &(temp1->front());
         n1.right =e1;
         
         temp1->push_front(n1); 
          left->right = &(temp1->front()); 
         
         
     }
               
else if(root.tokenCompare("KEYWORD","function_form"))
     {
         root.value = "eq";
         root.type = "KEYWORD";
         p= left;
         
         while(p->right->right!=NULL)
              {
                
               Tree *m = new Tree("lambda","lambda");
               m-> left = p->right;
               
               temp1->push_front(*m); 
               p->right = &(temp1->front());
               p = p->right->left;        
               delete m;
                  
              }   
         
         
         
    }
    
else if(root.tokenCompare("KEYWORD","and"))  
     {
           root.value = "eq";
           root.type = "KEYWORD";
           Tree c("comma","comma");
           Tree tu("tau","tau");
           Tree *co = &c;
           Tree *ta = &tu;
           co->right = ta;
           x = left;
           co->left = x->left;
           ta->left=x->left->right;
           x1 = co->left;
           x2 = ta->left;
           
           
          while(x->right!=NULL){
              
               x = x->right;
               x1->right = x->left;
               x2->right = x->left->right;
               x1=x1->right;
               x2=x2->right;
                
          }
            
            
            
            x1->right =NULL;
            x2->right =NULL;
            
            temp1->push_front(*ta); 
            co->right = &(temp1->front());
            temp1->push_front(*co);
            left = &(temp1->front());
    
     }
                       

else if(root.tokenCompare("OP","@")){
    
    
          root.type = root.value = "gamma";
          e1 = left;
          x =e1->right;
          e2 = x->right;
          Tree g("gamma","gamma");  
          e1->right = NULL;
          g.left = x;
          x->right = e1;
          g.right = e2;        
          temp1->push_front(g);
          left = &(temp1->front());  
    
    
    
    
    }
                           
                           
                           
else if(root.tokenCompare("KEYWORD","lambda") ||  root.tokenCompare("lambda","lambda") ){
    
         x = left;
          
         while(x->right->right!= NULL) 
          {
              p = x->right;
              
              Tree *l = new Tree("lambda","lambda");
              
              l->left = p;   

               temp1->push_front(*l);
               x->right =&(temp1->front());            
             
               delete l;
              
              
              
              
              
          }
    
    
    
    
    
    
    
    
    
    }
                               
                               
                
                
else if(root.tokenCompare("KEYWORD","rec")){
    
        x= left->left;
        e = x->right;
        x->right = NULL;
        left = x;
        
        
        Tree g("gamma","gamma");
        Tree y("","Ystar");
        Tree l("lambda","lambda");
        Tree x1(x->root.type,x->root.value);
        
        x1.right = e;
        
        temp1->push_front(x1);
        l.left =&(temp1->front());  
    
        
        temp1->push_front(l);
        y.right =&(temp1->front());  
    
    
        temp1->push_front(y);
         g.left =&(temp1->front());
    
        temp1->push_front(g);
        x->right =&(temp1->front());
    
    }
        
            
                        



}
    
    
    
    
    
    
    
    
    
    







void Tree::testTree(){


Tree t("KEYWORD","lambda");
 
Tree t1("","V");

Tree t2("","=");

Tree t3("","V2");

Tree t4("","E");

Tree t5("","E2");


Tree t6("","X2");


Tree t7("","=");

Tree t8("","X3");

Tree t9("","E3");

temp1->push_back(t);
temp1->push_back(t1);
temp1->push_back(t2);
temp1->push_back(t3);
temp1->push_back(t4);
temp1->push_back(t5);
temp1->push_back(t6);
temp1->push_back(t7);
temp1->push_back(t8);
temp1->push_back(t9);

t.left = &t1;

t1.right = &t3;

t3.right = &t4;



t.prettyPrint();

t.stdize();




t.prettyPrint();
}








