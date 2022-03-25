#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Hash.h"

//Q 4.2 The value to be stored is given by the coordinates (x, y) of a point.
// You can use the key function f (x, y) = y + (x + y) (x + y + 1) / 2.
// Test the keys generated for points (x, y) with x integer ranging from 1 to 10 
//and y integer ranging from 1 to 10. Does the key function seem appropriate to you?

// in this way function is generating too large value for each key that is not appropiate
void Check_key_generation(){
   
   int key_generated=0;
   
   for(int i=1;i<=10;i++){
   int x = (rand() %
           (10 - 1 + 1)) + 1;
        printf("x--%d ", x);
        
  int y = (rand() %
           (10 - 1 + 1)) + 1;
        printf("y--%d\n", y);
     
key_generated= (y+(x+y)*(x+y+1))/2;
 printf("output--%d\n", key_generated);
   }
}






// 4.3 for Hash Table with M cells******************************
//bellow  given function are part of 4.3 exercise
int hashCode(int key) {
   return key % SIZE;
}


//******************* search for repeatation value in generated nodes********
struct cellnode *search(int key) {
   //get the hash 
   int hashIndex = hashCode(key);  
	
   //move in array until an empty 
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
			
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}



// insert in Hash Table
void insert(int key,Noeud *ndr) {

   struct cellnode *item = (struct cellnode*) malloc(sizeof(struct cellnode));
   item->nd = ndr;  
   item->key = key;

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}

struct cellnode* delete(struct cellnode* item) {
   int key = item->key;

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key) 
      {
         struct cellnode* temp = hashArray[hashIndex]; 
		   //assign a dummy item at deleted position
         hashArray[hashIndex] = dummyItem; 
         return temp;
      }
		
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }      
	
   return NULL;        
}





//******************************** Print Hash Table ******************** Nodes with its neughbours=======
void printHashTable() {
   int i = 0;
	
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i] != NULL){
          printf(" ( KEY : %d, X  %f Y %f) \n",hashArray[i]->key,hashArray[i]->nd->x,hashArray[i]->nd->y);
   while (hashArray[i]->nd->neighbors->next!=NULL)
    {
    printf("----------NODE----key %d-----Neighbours-------Nei X %f and Y %f-------------\n",hashArray[i]->nd->neighbors->nd->num,hashArray[i]->nd->neighbors->nd->x,hashArray[i]->nd->neighbors->nd->y);
        /* code */
        hashArray[i]->nd->neighbors=hashArray[i]->nd->neighbors->next;
    }
      }
   }
	
   // printf("\n");
}



// generating Hash Table
void generateFileWithHashTable()
{


CellNode *node_pointer;
  FILE *f3= fopen("00014_burma.cha","r");
  Chaines *c =  lectureChaines(f3);
 while (c->chaines_head!=NULL)
 { 
   while (c->chaines_head->CellPoint_tail!=NULL)
   { 
  
	  struct noeud *n =  (struct noeud*)malloc(sizeof( noeud));
     n->x=c->chaines_head->CellPoint_tail->x;
	  n->y=c->chaines_head->CellPoint_tail->y;
     
     struct cellnode *tempRes =  search(c->chaines_head->CellPoint_tail->keyIndex);
     if(tempRes!=NULL)
     {

     }
     else
     { 
        n->num=c->chaines_head->CellPoint_tail->keyIndex;

        n->neighbors = Neighbour_node_create(c->chaines_head->CellPoint_tail->x,c->chaines_head->CellPoint_tail->y);
        insert(c->chaines_head->CellPoint_tail->keyIndex,n); 
     }

	   c->chaines_head->CellPoint_tail=c->chaines_head->CellPoint_tail->prev;
   }

    c->chaines_head=c->chaines_head->next;
 }

 

}






