#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 #include "SVGwriter.h"
 #include "hash.c"
#include "Reseau.h"
int array_of_node_keys[12];
int number_of_Nodes=0;
int array_of_neigh_number[10];
int check_repeat_orignal_node[24];
int check_repeat_nei_node[24];
int node_num=0;
#define SIZE 100



//creating Network with tree struture
//5.5
Reseau * reconstitutesNetworkTree (Chaines * c){
 
struct treeQuat *r = createTreeQuat(c->chaines->CellPoint_tail->x,c->chaines->CellPoint_tail->y,0,0);
CellNode *Head=NULL,*chain=NULL;
Reseau *network=(struct Reseau*)malloc(sizeof( Reseau));
network->commodites=Find_Commodaties();  // commodaties chain

network->nodes=getAllUniqueNodeChainFromQuaTree( r, Head,chain); // neighbour list
network->gamma=c->gamma;
network->nbNodes=number_of_Nodes;
return network;
}


//4.5
//******************************* contruct Network with Hash Data Structure***************************
Reseau * reconstituteHashNetwork (struct cellnode* hashArray[],Chaines *C){

Reseau *network=(struct Reseau*)malloc(sizeof( Reseau));
network->commodites=Find_Commodaties();  // commodaties chain
network->nodes= getUniqueChaineFromHashTable(hashArray);  // neighbour list
network->gamma=C->gamma;
network->nbNodes=number_of_Nodes;
return network;
}

//*** Method To find Uniques Node as well as their Neighbours*********************
struct CellNode * getUniqueChaineFromHashTable(struct cellnode* hashArray[])
{
    generateFileWithHashTable();

  CellNode *neighbour_head=NULL;
  CellNode *neighbour_chain=NULL;

  int v = 0;
  for(v = 0; v<SIZE; v++) 
  {
  
  if(hashArray[v] != NULL)
  {
    
      if(neighbour_head==NULL)
                {
                number_of_Nodes++;
                CellNode *mainMainDataHolder = (struct CellNode*)malloc(sizeof( CellNode));
                mainMainDataHolder->next=NULL;

                Noeud * New_Node=(struct Noeud*)malloc(sizeof( Noeud));
                New_Node->x=hashArray[v]->nd->x;
                New_Node->y=hashArray[v]->nd->y;
                New_Node->keyIndex=hashArray[v]->nd->keyIndex;
                New_Node->neighbors=hashArray[v]->nd->neighbors;
                mainMainDataHolder->nd=New_Node;

                neighbour_head=mainMainDataHolder;
                neighbour_chain=mainMainDataHolder;
                
                }
                else
                {

                number_of_Nodes++;
                Noeud * New_temp =(struct Node*)malloc(sizeof(Noeud));
                New_temp->x=hashArray[v]->nd->x;
                New_temp->y=hashArray[v]->nd->y;
                New_temp->keyIndex=hashArray[v]->nd->keyIndex;
                New_temp->neighbors =hashArray[v]->nd->neighbors;

                CellNode *tempMainNeiNode = (struct CellNode*)malloc(sizeof( CellNode));
                tempMainNeiNode->next=NULL;
                tempMainNeiNode->nd=New_temp;
                neighbour_chain->next=tempMainNeiNode;
                neighbour_chain=tempMainNeiNode;  
                   
                }
  
    }
   
   }
 
//display_neighbour_nodes(neighbour_head);   
return neighbour_head;

}


//******************************* contruct Network with List Data structure ****************************

// 2.2
Reseau * reconstitueReseauListe(Chaines * C){
Reseau *network=(struct Reseau*)malloc(sizeof( Reseau));
network->commodites=Find_Commodaties();  // commodaties chain
network->nodes=Create_Node_neighbour_list();  // neighbour list
network->gamma=C->gamma;
network->nbNodes=number_of_Nodes;
return network;
}


// bellow given methods are use to network with list
// *********************************** Method to find commodaties*******************************************
CellCommodite * Find_Commodaties(){
 FILE *fptr= fopen("00014_burma.cha","r");
 Chaines *c =   lectureChaines(fptr);
 fclose(fptr);




CellCommodite *cellCommodite_Head=NULL;
CellCommodite *cellCommodite_chain=NULL;


int i=0,j=0;

double start_node_x=0,start_node_y=0,end_node_x=0,end_node_y=0;
int keyA=0,keyB=0;


while (c->chaines_head!=NULL)
 {  start_node_x=0;
    start_node_y=0;
    keyA=0;
    keyB=0;
   
    if(j>=2)
     {
      
     i=0;
     while(c->chaines_head->CellPoint_tail!=NULL)
     {     end_node_x=0;
           end_node_y=0;
           keyB=0;  
             if(i==0)
             {
              
                 start_node_x=c->chaines_head->CellPoint_tail->x;
                 start_node_y=c->chaines_head->CellPoint_tail->y;
                 keyA=c->chaines_head->CellPoint_tail->keyIndex;
           
             }
             
             end_node_x=c->chaines_head->CellPoint_tail->x;
             end_node_y=c->chaines_head->CellPoint_tail->y;
             keyB=c->chaines_head->CellPoint_tail->keyIndex;
             i++;
             c->chaines_head->CellPoint_tail=c->chaines_head->CellPoint_tail->prev;
     }
      
       
       
      if(cellCommodite_Head==NULL)
      {
      
         CellCommodite * cellCommodite_NODE= (struct CellCommodite*)malloc(sizeof( CellCommodite));
         cellCommodite_NODE->next=NULL;
         cellCommodite_NODE->extrA = (struct  Noeud*)malloc(sizeof(  Noeud));
         cellCommodite_NODE->extrA->x=start_node_x;
         cellCommodite_NODE->extrA->y=start_node_y;
         cellCommodite_NODE->extrB=(struct  Noeud*)malloc(sizeof(  Noeud));
         cellCommodite_NODE->extrB->x=end_node_x;
         cellCommodite_NODE->extrB->y=end_node_y;
         cellCommodite_NODE->extrA->keyIndex=keyA;
         cellCommodite_NODE->extrB->keyIndex=keyB;
         cellCommodite_Head=cellCommodite_NODE;
         cellCommodite_chain =cellCommodite_NODE;
      
     }
     else
     {
       CellCommodite * cellCommodite_temp=(struct CellCommodite*)malloc(sizeof( CellCommodite));
         cellCommodite_temp->next=NULL;
         cellCommodite_temp->extrA = (struct  Noeud*)malloc(sizeof( Noeud));
         cellCommodite_temp->extrA->x=start_node_x;
         cellCommodite_temp->extrA->y=start_node_y;
         cellCommodite_temp->extrB=(struct Noeud*)malloc(sizeof( Noeud));
         cellCommodite_temp->extrB->x=end_node_x;
         cellCommodite_temp->extrB->y=end_node_y;
         cellCommodite_temp->extrA->keyIndex=keyA;
         cellCommodite_temp->extrB->keyIndex=keyB;
         cellCommodite_chain->next=cellCommodite_temp;
         cellCommodite_chain=cellCommodite_temp;
       
     
     }

    
      
     }
     else
     {

     }
       c->chaines_head=c->chaines_head->next;  
     j++;
     
 }


//printf("printing list\n");
//display_Commodities(cellCommodite_Head);
  return cellCommodite_Head;
}


//*************************************************** method to display Commodaties**************************
void display_Commodities(CellCommodite *cl){
  printf("\n");
   while(cl!=NULL){
    printf(" end Point (%f ",cl->extrB->x);
    printf(",  %f)\n ",cl->extrB->y);
    printf(" start Point (%f ",cl->extrA->x);
    printf(",  %f)\n ",cl->extrA->y);
    cl=cl->next;
 }
}

//***************************************** method to create list of neighbours lists *********************************
CellNode * Create_Node_neighbour_list(){
     
 FILE *fptr= fopen("00014_burma.cha","r");
 Chaines *c =   lectureChaines(fptr);
 fclose(fptr);
  
int check_presence; 
int i=0,j=0;
int nb_nodes_count=0;
array_of_node_keys[12]=0;
check_repeat_orignal_node[24]=0;
check_repeat_nei_node[24]=0;
double x,y;

     
 
     CellNode *neighbour_head=NULL;
     CellNode *neighbour_chain=NULL;


  while (c->chaines_head!=NULL)
 { 

if(j<2)
{
        
}
else
{

 while (c->chaines_head->CellPoint_tail!=NULL)
{ 
     
     check_presence=check_Node_repeatation(c->chaines_head->CellPoint_tail,i);
    
     if(check_presence==0)
     {

             }
     else
     {
                if(neighbour_head==NULL)
                {
                
                CellNode *mainMainDataHolder = (struct CellNode*)malloc(sizeof( CellNode));
                mainMainDataHolder->next=NULL;

                Noeud * New_Node=(struct Noeud*)malloc(sizeof( Noeud));
                New_Node->x=c->chaines_head->CellPoint_tail->x;
                New_Node->y=c->chaines_head->CellPoint_tail->y;
                New_Node->keyIndex=c->chaines_head->CellPoint_tail->keyIndex;
                New_Node->neighbors=Neighbour_node_create(c->chaines_head->CellPoint_tail->x,c->chaines_head->CellPoint_tail->y);
                
                mainMainDataHolder->nd=New_Node;

                neighbour_head=mainMainDataHolder;
                neighbour_chain=mainMainDataHolder;

                 }
                else
                {

               
                Noeud * New_temp =(struct Node*)malloc(sizeof( Noeud));
                New_temp->x=c->chaines_head->CellPoint_tail->x;
                New_temp->y=c->chaines_head->CellPoint_tail->y;
                New_temp->keyIndex=c->chaines_head->CellPoint_tail->keyIndex;
                New_temp->neighbors = Neighbour_node_create(c->chaines_head->CellPoint_tail->x,c->chaines_head->CellPoint_tail->y);
                
                CellNode *tempMainNeiNode = (struct CellNode*)malloc(sizeof( CellNode));
                tempMainNeiNode->next=NULL;
                tempMainNeiNode->nd=New_temp;
                neighbour_chain->next=tempMainNeiNode;
                neighbour_chain=tempMainNeiNode;  
                

                }
                nb_nodes_count++;
            
     }

	 c->chaines_head->CellPoint_tail=c->chaines_head->CellPoint_tail->prev;
  i++;
   }

   }
    
    c->chaines_head=c->chaines_head->next;
    j++;
 }

number_of_Nodes=nb_nodes_count;
//display_neighbour_nodes(neighbour_head);

return neighbour_head;

} 


//****************************** method to check for repeatation***************************************
int check_Node_repeatation(CellPoint *p,int i){
    int j=0;
    bool isFound =true;
    
     if(i==0)
     {
             array_of_node_keys[i]=p->keyIndex;
             return 1;
                
     }
     else{
           for(int k=0;k<12;k++){
               if(array_of_node_keys[k]==p->keyIndex){
                isFound=false;
                
              }
               if(array_of_node_keys[k]==0){
                   j=k;
                   break;
               }
            
                
           }
           if(isFound){
               array_of_node_keys[j]=p->keyIndex;
               return 1;
           }
           else{
               return 0;
           }
     }

}


//************************** method to display neighbour list chain*****************************

void display_neighbour_nodes(CellNode *head)
{
    while (head!=NULL)
    {  
         printf(" Node - (%f ",head->nd->x);
          printf(",  %f)\n ",head->nd->y);
      
      while (head->nd->neighbors!=NULL)
      { 
          printf(" Neighbour (%f ",head->nd->neighbors->nd->x);
          printf(",  %f)\n ",head->nd->neighbors->nd->y);
        head->nd->neighbors=head->nd->neighbors->next;
      }
      
    
      head=head->next;
    }
    
}



//********************************* neighbour nodes***********************************************

CellPoint * right_neighbour(CellPoint *p){
  
     if(p->next!=NULL){

           return  p->next;     
       }else{
         return NULL;
       }

}
CellPoint * left_neighbour(CellPoint *p){
              if(p->prev!=NULL){

                 return p->prev;
                 }
                else {
                  return NULL;
                }

}

//******************************* Check repeatation in neighbour Nodes******************
int check_neighbour_repeatation(int orignal_node_key,int neighbour_node_key,int i){
int j=0;
    bool isFound =true;
    
     if(i==0)
     {
             array_of_neigh_number[i]=neighbour_node_key;
             check_repeat_orignal_node[node_num]=orignal_node_key;
             check_repeat_nei_node[node_num]=neighbour_node_key;
             node_num++;
             return 1;
             
                
     }
     else{
           for(int k=0;k<10;k++){
               if(array_of_neigh_number[k]==neighbour_node_key){
                isFound=false;
                
              }
               if(array_of_neigh_number[k]==0){
                   j=k;
                   break;
               }
            
                
           }
           if(isFound){
               array_of_neigh_number[j]=neighbour_node_key;
               check_repeat_orignal_node[node_num]=orignal_node_key;
               check_repeat_nei_node[node_num]=neighbour_node_key;
               node_num++;
               return 1;
           }
           else{
               return 0;
           }
     }

}







//************************************************* check each node Neighbour ***************************************************

CellNode * Neighbour_node_create(double x, double y){


 FILE *fptr= fopen("00014_burma.cha","r");
 Chaines *c =  lectureChaines(fptr);
 fclose(fptr);

array_of_neigh_number[10]=0;
CellNode *neighbour = (struct CellNode*)malloc(sizeof( CellNode));
neighbour->next=NULL;
 
CellNode *neighbour_head=neighbour;
CellNode *neighbour_chain=neighbour;
 
CellPoint *prev_p;
CellPoint *next_p;

int i=0;
int orignal_node_key=0, neighbour_node_key=0,N=0;
while (c->chaines_head!=NULL)
 { 
  
   while (c->chaines_head->CellPoint_tail!=NULL)
   {  
       if(c->chaines_head->CellPoint_tail->x==x&&c->chaines_head->CellPoint_tail->y==y){
          
          
           
           prev_p=left_neighbour(c->chaines_head->CellPoint_tail);
           next_p=right_neighbour(c->chaines_head->CellPoint_tail);
           orignal_node_key=c->chaines_head->CellPoint_tail->keyIndex;
           
           if(prev_p==NULL){}
           else
           {
           
            neighbour_node_key=prev_p->keyIndex;

           int check_val= check_neighbour_repeatation(orignal_node_key,neighbour_node_key,N);
           N++;

        
           if(check_val==0){

           }else{
            Noeud * node_data_holder = (struct Noeud*)malloc(sizeof( Noeud));     
              
           if(i==0)
           {
         
              node_data_holder->x = prev_p->x;
              node_data_holder->y = prev_p->y;
              node_data_holder->keyIndex= prev_p->keyIndex;
              neighbour_head->nd = node_data_holder;
              neighbour_chain->nd = node_data_holder;
              
              neighbour_head->next=NULL;
              neighbour_chain->next=NULL;

              i++;
           }
           else
           {
          
              node_data_holder->x = prev_p->x;
              node_data_holder->y = prev_p->y;
              node_data_holder->keyIndex= prev_p->keyIndex;
              CellNode *tempNei = (struct CellNode*)malloc(sizeof( CellNode));
              tempNei->next=NULL;

              tempNei->nd=node_data_holder;
              neighbour_chain->next=tempNei;
              neighbour_chain=tempNei;  

           } 
           

           }
                  }

           if(next_p==NULL){}
           else
           {
           neighbour_node_key=next_p->keyIndex;

           int check_val= check_neighbour_repeatation(orignal_node_key,neighbour_node_key,N);
           N++;

      
           if(check_val==0){

           }else {
           Noeud * node_data_holder = (struct Noeud*)malloc(sizeof( Noeud));               
              
             
           if(i==0)
           {
        
              node_data_holder->x = next_p->x;
              node_data_holder->y = next_p->y;
              node_data_holder->keyIndex=next_p->keyIndex;
              neighbour_head->nd = node_data_holder;
              neighbour_chain->nd = node_data_holder;
              
              neighbour_head->next=NULL;
              neighbour_chain->next=NULL;

              i++;
           }
           else
           {
              node_data_holder->x = next_p->x;
              node_data_holder->y = next_p->y;
              node_data_holder->keyIndex=next_p->keyIndex;
              CellNode *tempNei = (struct CellNode*)malloc(sizeof( CellNode));
              tempNei->next=NULL;

              tempNei->nd=node_data_holder;
              neighbour_chain->next=tempNei;
              neighbour_chain=tempNei;  

           }


           }

           
                }
          
         
       }
     c->chaines_head->CellPoint_tail=c->chaines_head->CellPoint_tail->prev;
   }
  
    c->chaines_head=c->chaines_head->next;
 }


   
 

 return neighbour_head;

 }
 



//******************************************** creating Method that are in header file task*********************************


// method to write Network connection**************************
//3.1
int nbLiaisons(Reseau *R){
   
 // here  i m not using R because we have already create array from it so for for that we are using
 // existing array to calculate number of nodes 
    int k=0;
    int new_check_repeat_orignal_node[24];
    int new_check_repeat_nei_node[24];
    int count=0;
    bool isFound=true;
  
for(int m=0;m<24;m++){
 
         for(int n=m;n<24;n++){
         
         if(check_repeat_orignal_node[m]==check_repeat_nei_node[n]&&check_repeat_nei_node[m]==check_repeat_orignal_node[n]){
         
           isFound=false;
           break;
         }
         else{
           isFound=true;
         }
      

       }

       if(isFound){
          new_check_repeat_orignal_node[k]=check_repeat_orignal_node[m];
           new_check_repeat_nei_node[k]=check_repeat_nei_node[m];
           count++;
           k++;
       }

}


    return count;

}


// method to count Number of commodaties
//3.1
int nbCommodites(Reseau *R){
    int count=0;
   
   CellCommodite *cl= R->commodites;
   while(cl!=NULL){
    cl=cl->next;
    count++;
 }
 return count;
}


//********************************** Search and add Node Method **************************************

//  2.1
Noeud * rechercheCreeNoeudListe(Reseau *R, double x, double y){

bool isFound=false; 
    while (R->nodes!=NULL)
    {  
    
      if(R->nodes->nd->x==x&&R->nodes->nd->y==y){
          isFound=true;
         
      } 
      else if(R->nodes->next==NULL&&R->nodes->nd->x!=x&&R->nodes->nd->y!=y){
           number_of_Nodes++;
           printf("Not Found : now creating new Node \n");
           Noeud * New_temp =(struct Noeud*)malloc(sizeof( Noeud));
           New_temp->x=x;
           New_temp->y=y;
           New_temp->neighbors=NULL;
           R->nodes->next=New_temp;
           printf("number of nodes: %d\n",number_of_Nodes);
           return R->nodes->next;
          }
          R->nodes=R->nodes->next;
      }
      
      if(isFound){
        printf("Found");
        return R->nodes->nd;
      }
      
      
    }



//****************************************** Writing to File***********************************
// 3.2
void ecrireReseau(Reseau *R, FILE *f){
     int k=0;
    int new_check_repeat_orignal_node[24];
    int new_check_repeat_nei_node[24];
  
    bool isFound=true;


 CellNode *hNode= R->nodes;
 CellNode* h1Node= R->nodes;
 CellCommodite * h2Node= R->commodites;
 Reseau * R1=R;

 //******************************* printing basic details***********************************
   fprintf(f, "NbNoeuds: %d\n",number_of_Nodes);
   fprintf(f, "NbLiaisons: %d\n",nbLiaisons (R));
   fprintf(f, "NbCommodites: %d\n",nbCommodites(R1));
   fprintf(f, "gamma: %d\n",R->gamma);
  
   
   while(hNode!=NULL){
      printf("in loop outer for printing nodes\n");
      
      fprintf(f, "v %d %f %f\n",hNode->nd->keyIndex,hNode->nd->x,hNode->nd->y);
   
   hNode=hNode->next;
   }
fprintf(f, "\n\n\n");
// printing connections*********************************************

for(int m=0;m<24;m++){
 
         for(int n=m;n<24;n++){
         
         if(check_repeat_orignal_node[m]==check_repeat_nei_node[n]&&check_repeat_nei_node[m]==check_repeat_orignal_node[n]){
         
           isFound=false;
           break;
         }
         else{
           isFound=true;
         }
      

       }

       if(isFound){
          new_check_repeat_orignal_node[k]=check_repeat_orignal_node[m];
           new_check_repeat_nei_node[k]=check_repeat_nei_node[m];
           k++;
       }

}
for(int i=0;i<k;i++){
   fprintf(f,"l %d ",new_check_repeat_orignal_node[i]);
         fprintf(f,"%d\n",new_check_repeat_nei_node[i]);
 
}

// printing Commodaties**************************************
fprintf(f, "\n\n\n");
     while(h2Node!=NULL){
      printf("in loop outer for commodaties nodes\n");
      
         fprintf(f,"k %d ",h2Node->extrA->keyIndex);
         fprintf(f,"%d\n",h2Node->extrB->keyIndex);
   
   h2Node=h2Node->next;
   }


}


//3.3
void afficheReseauSVG(Reseau *R, char* nomInstance){
 CellNode *courN,*courv,*courN1;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    
    courN=R->nodes;
    courN1=courN;
    while (courN!=NULL){
       printf("outer loop1\n");
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->next;
    }
    SVGinit(&svg,nomInstance,500,500);
    
    while (courN1!=NULL){
      printf("outer loop\n");
        SVGpoint(&svg,500*(courN1->nd->x-minx)/(maxx-minx),500*(courN1->nd->y-miny)/(maxy-miny));
        courv=courN1->nd->neighbors;
        while (courv!=NULL){
           printf("inner loop\n");
            if (courv->nd->num<courN1->nd->num)
                {SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN1->nd->x-minx)/(maxx-minx),500*(courN1->nd->y-miny)/(maxy-miny));
                }
            courv=courv->next;
        }
        courN1=courN1->next;
    }
    SVGfinalize(&svg);

}


// 4.4
// search method by using Hash
struct Noeud * searchCreeNodeHash (Reseau * R, struct cellnode* hashArray[], double x, double y){
   
bool isFound=false; 
    while (R->nodes!=NULL)
    {  
    
      if(R->nodes->nd->x==x&&R->nodes->nd->y==y){
          isFound=true;
         
      } 
      else if(R->nodes->next==NULL&&R->nodes->nd->x!=x&&R->nodes->nd->y!=y){
           number_of_Nodes++;
           printf("Not Found : now creating new Node \n");
           Noeud * New_temp =(struct Noeud*)malloc(sizeof( Noeud));
           New_temp->x=x;
           New_temp->y=y;
           New_temp->neighbors=NULL;
           R->nodes->next=New_temp;
           printf("number of nodes: %d\n",number_of_Nodes);
           return R->nodes->next;
          }
          R->nodes=R->nodes->next;
      }
      
      if(isFound){
        printf("Found");
        return R->nodes->nd;
      }

}








//****************************** bellow are the method that are used for the creation of tree structure***********
int getMaxNumberOfColumns()
{
 FILE *fptr= fopen("00014_burma.cha","r");
 Chaines *c =   lectureChaines(fptr);
 fclose(fptr);


 int i=0,j=0;
 int noOfCol=0;


while (c->chaines_head!=NULL)
 {  
   if(j<2)
   {
        c->chaines_head=c->chaines_head->next;
   }
   else
   {
    
   int temp=0;     
   while (c->chaines_head->CellPoint_tail!=NULL)
   {  
     temp++;  
     c->chaines_head->CellPoint_tail=c->chaines_head->CellPoint_tail->prev;
   }
   if(temp>noOfCol)
   {
       noOfCol=temp;
   } 
    c->chaines_head=c->chaines_head->next  ;
    i++;
   }
   
    j++;
 }

return noOfCol;
} 
int  getMaxNoOfRows()
{
 
 FILE *fptr= fopen("00014_burma.cha","r");
 Chaines *c =   lectureChaines(fptr);
 fclose(fptr);


 int i=0,j=0;
 int noOfCol=0;

while (c->chaines_head!=NULL)
 {  
   if(j<2)
   {
        c->chaines_head=c->chaines_head->next;
   }
   else
   {
    
    
    c->chaines_head=c->chaines_head->next  ;
    i++;
   }
   
    j++;
 }

return i;
}

void fillWithDefaultValue(double array[maxRow][maxCol])
{
   // printf("Filling with default values\n");
    for(int i=0;i<maxRow;i++)
    {
        for(int j=0;j<maxCol;j++)
        {
            array[i][j]=(-1.00);
            
        }
    }
}
void fillingWithFileValues(double array[maxRow][maxCol])
{
    FILE *fptr= fopen("00014_burma.cha","r");
 Chaines *c =   lectureChaines(fptr);
 fclose(fptr);


 int i=0,j=0;
 int noOfCol=0;

while (c->chaines_head!=NULL)
 {  
   if(j<2)
   {
        c->chaines_head=c->chaines_head->next;
   }
   else
   {
   int  col=0; 
   while (c->chaines_head->CellPoint_tail!=NULL)
   {  

     array[i][col]=c->chaines_head->CellPoint_tail->x;
     col++;
     array[i][col]=c->chaines_head->CellPoint_tail->y;
     col++;
     
     c->chaines_head->CellPoint_tail=c->chaines_head->CellPoint_tail->prev;
   }
    
    c->chaines_head=c->chaines_head->next  ;
    i++;
   }
   
    j++;
 }

}

//5.3
struct treeQuat *insertTreeNode(int callNo,struct treeQuat *treeNode,double xc,double yc,double allNodes[maxRow][maxCol],double traveredNodes[maxRow][maxCol])
{

	if(xc==-1 || yc==-1)
		return NULL;
	
    
	
 	// treeNode->xc=xc;
    // treeNode->yc=yc;
	

// Node we will traverse the array and will check according to give condtion for each child.
// struct treeQuat * so; / * Southwest subtree, for x <xc and y <yc * /-4
//  struct treeQuat * se; / * Southeast subtree, for x> = xc and y <yc * /-3
//  structQuat tree * no; / * Northwest subtree, for x <xc and y> = yc * /-1
//  struct treeQuat * ne; / * Northeast subtree, for x> = xc and y> = yc * /-2

//FOR NO - 1
   double x1,y1;
    int flag1=0;
    for(int i=0;i<maxRow;i++)
    {
        for(int j=0;j<maxCol;j++)
        {
            if(allNodes[i][j]<xc && allNodes[i][j+1]>=yc)
            {
                x1=allNodes[i][j];
                y1=allNodes[i][j+1];


                int v = 0;
                for(int k=0;k<maxRow;k++)
                {
                    for(int l=0;l<maxCol;l++)
                    {
                        if(traveredNodes[k][l]==x1 && traveredNodes[k][l+1]==y1)
                        {
                            v=1;
                            break;
                        }
                        l++;
                    }
                    if(v==1)
                    {
                        break;
                    }
                }

                if(v==0)
                {
                flag1=1;
                break;
                }
            }
            j++;
           
        }
         if(flag1==1)
            {
                break;
            }
    }
  
    if(flag1==0)
    {
        treeNode->no=NULL;
    }
    else
    {
        int v1=0;
     

        if(v1==0)
        {
            //Not travered ...
            //Storing in traversed
            int b=0;
            for(int i=0;i<maxRow;i++)
            {

                for(int j=0;j<maxCol;j++)
                {
                    if(traveredNodes[i][j]==-1)
                    {
                        traveredNodes[i][j]=x1;
                        traveredNodes[i][j+1]=y1;
                        b=1;
                        break;
                    }
                }
                if(b==1)
                {
                    break;
                }
            }
            struct treeQuat *noNode = (struct treeQuat*)malloc(sizeof(struct treeQuat));
            noNode->xc=x1;
            noNode->yc=y1;
            treeNode->no =noNode;

            insertTreeNode(++callNo,treeNode->no,x1,y1,allNodes,traveredNodes);     
        }
        else
        {
         treeNode->no=NULL;   
        }
        //Call next recur
       
    }



//FOR NE - 2
    double x2,y2;
    int flag2=0;
    for(int i=0;i<maxRow;i++)
    {
        for(int j=0;j<maxCol;j++)
        {
            if(allNodes[i][j]>=xc && allNodes[i][j+1]>=yc)
            {
                x2=allNodes[i][j];
                y2=allNodes[i][j+1];
                
                int v = 0;
                for(int k=0;k<maxRow;k++)
                {
                    for(int l=0;l<maxCol;l++)
                    {
                        if(traveredNodes[k][l]==x2 && traveredNodes[k][l+1]==y2)
                        {
                            v=1;
                            break;
                        }
                        l++;
                    }
                    if(v==1)
                    {
                        break;
                    }
                }

                if(v==0)
                {
                flag2=1;
                break;
                }
            }
            j++;
           
        }
         if(flag2==1)
            {
                break;
            }
    }
  
    if(flag2==0)
    {
       
        //NO is null
        treeNode->ne=NULL;
    }
    else
    {
        int v1=0;
    
        if(v1==0)
        {
            //Not travered ...
            //Storing in traversed
            int b=0;
            for(int i=0;i<maxRow;i++)
            {

                for(int j=0;j<maxCol;j++)
                {
                    if(traveredNodes[i][j]==-1)
                    {
                        traveredNodes[i][j]=x2;
                        traveredNodes[i][j+1]=y2;
                        b=1;
                        break;
                    }
                }
                if(b==1)
                {
                    break;
                }
            }
            struct treeQuat *neNode = (struct treeQuat*)malloc(sizeof(struct treeQuat));
            neNode->xc=x2;
            neNode->yc=y2;
            treeNode->ne =neNode;

            insertTreeNode(++callNo,treeNode->ne,x2,y2,allNodes,traveredNodes);     
        }
        else
        {
         treeNode->ne=NULL;   
        }

        //Call next recur
       
    }


//FOR SE - 3


    double x3,y3;
    int flag3=0;
    for(int i=0;i<maxRow;i++)
    {
        for(int j=0;j<maxCol;j++)
        {
            if(allNodes[i][j]>=xc && allNodes[i][j+1]<yc)
            {
                  x3=allNodes[i][j];
                y3=allNodes[i][j+1];
                
                int v = 0;
                for(int k=0;k<maxRow;k++)
                {
                    for(int l=0;l<maxCol;l++)
                    {
                        if(traveredNodes[k][l]==x3 && traveredNodes[k][l+1]==y3)
                        {
                            v=1;
                            break;
                        }
                        l++;
                    }
                    if(v==1)
                    {
                        break;
                    }
                }

                if(v==0)
                {
                flag3=1;
                break;
                }
            }
            j++;
           
        }
         if(flag3==1)
            {
                break;
            }
    }
  
    if(flag3==0)
    {
        treeNode->se=NULL;
    }
    else
    {
        int v1=0;
    

        if(v1==0)
        {
            //Not travered ...
            //Storing in traversed
            int b=0;
            for(int i=0;i<maxRow;i++)
            {

                for(int j=0;j<maxCol;j++)
                {
                    if(traveredNodes[i][j]==-1)
                    {
                        traveredNodes[i][j]=x3;
                        traveredNodes[i][j+1]=y3;
                        b=1;
                        break;
                    }
                }
                if(b==1)
                {
                    break;
                }
            }
            struct treeQuat *seNode = (struct treeQuat*)malloc(sizeof(struct treeQuat));
            seNode->xc=x3;
            seNode->yc=y3;
            treeNode->se =seNode;

             insertTreeNode(++callNo,treeNode->se,x3,y3,allNodes,traveredNodes);     
        }
        else
        {
         treeNode->se=NULL;   
        }

        //Call next recur
       
    }


//FOR SO - 4


    double x4,y4;
    int flag4=0;
    for(int i=0;i<maxRow;i++)
    {
        for(int j=0;j<maxCol;j++)
        {
            if(allNodes[i][j]<xc && allNodes[i][j+1]<yc)
            {
                 x4=allNodes[i][j];
                y4=allNodes[i][j+1];

              
                int v = 0;
                for(int k=0;k<maxRow;k++)
                {
                    for(int l=0;l<maxCol;l++)
                    {
                        if(traveredNodes[k][l]==x4 && traveredNodes[k][l+1]==y4)
                        {
                            v=1;
                            break;
                        }
                        l++;
                    }
                    if(v==1)
                    {
                        break;
                    }
                }

                if(v==0)
                {
                flag4=1;
                break;
                }
            }
            j++;
           
        }
         if(flag4==1)
            {
                break;
            }
    }
  
    if(flag4==0)
    {
        treeNode->so=NULL;
    }
    else
    {
        int v1=0;
        if(v1==0)
        {
            //Not travered ...
            //Storing in traversed
            int b=0;
            for(int i=0;i<maxRow;i++)
            {

                for(int j=0;j<maxCol;j++)
                {
                    if(traveredNodes[i][j]==-1)
                    {
                        traveredNodes[i][j]=x4;
                        traveredNodes[i][j+1]=y4;
                        b=1;
                        break;
                    }
                }
                if(b==1)
                {
                    break;
                }
            }
            struct treeQuat *soNode = (struct treeQuat*)malloc(sizeof(struct treeQuat));
            soNode->xc=x4;
            soNode->yc=y4;
            treeNode->so =soNode;

            insertTreeNode(++callNo,treeNode->so,x4,y4,allNodes,traveredNodes);     
        }
        else
        {
         treeNode->so=NULL;   
        }

        //Call next recur
       
    }




  	
    return treeNode;
}
//to print tree nodes
void printQuatTree(struct  treeQuat *node)
{
    if(node==NULL)
    return;

    printf("V XC %f and YC%f \n",node->xc,node->yc);
    printQuatTree(node->no);
    printQuatTree(node->ne);
    printQuatTree(node->se);
    printQuatTree(node->so);
    
}
void createQuadTree()
{   // can pass any node to create the chain
    FILE *fptr= fopen("00014_burma.cha","r");
    Chaines *c =   lectureChaines(fptr);
    fclose(fptr);
    
   struct treeQuat *r = createTreeQuat(c->chaines->CellPoint_tail->x,c->chaines->CellPoint_tail->y,0,0);
 
} 


//5.2
struct treeQuat *createTreeQuat (double xc, double yc, double dimensionX, double dimensionY)
{
    int noOfCol = getMaxNumberOfColumns()*2;
    int noOfRows = getMaxNoOfRows();
    maxCol=noOfCol;
    maxRow=noOfRows;

    double MainChainArray[noOfRows][noOfCol];
    double TraversedNodes[noOfRows][noOfCol];
    
    fillWithDefaultValue(MainChainArray);
    fillWithDefaultValue(TraversedNodes);
    
    fillingWithFileValues(MainChainArray);

  struct treeQuat *root = (struct treeQuat*)malloc(sizeof(struct treeQuat));
  root->xc=xc;
  root->yc=yc;
  TraversedNodes[0][0]=xc;
  TraversedNodes[0][1]=yc;
  
  root->ne=NULL;
  root->no=NULL;
  root->se=NULL;
  root->so=NULL;
  
  insertTreeNode(1,root,xc,yc,MainChainArray,TraversedNodes);


  return root;
}






// 5.1 
void stringCoordMinMax(Chaines * c, double * xmin, double * ymin, double * xmax, double * ymax){
         int i=0,j=0;

double start_node_x=0,start_node_y=0,end_node_x=0,end_node_y=0;
int keyA=0,keyB=0;

int Num=0;

while (c->chaines_head!=NULL)
 {  start_node_x=0;
    start_node_y=0;
    keyA=0;
    keyB=0;
   
    if(j>=2)
     {
      
     i=0;
     while(c->chaines_head->CellPoint_tail!=NULL)
     {     end_node_x=0;
           end_node_y=0;
           keyB=0;  
             if(i==0)
             {
                 
                 start_node_x=c->chaines_head->CellPoint_tail->x;
                 start_node_y=c->chaines_head->CellPoint_tail->y;
                 xmin[Num]=start_node_x;
                 ymin[Num]=start_node_y;
              
             }
             
             end_node_x=c->chaines_head->CellPoint_tail->x;
             end_node_y=c->chaines_head->CellPoint_tail->y;
         
             i++;
             c->chaines_head->CellPoint_tail=c->chaines_head->CellPoint_tail->prev;
     }
      
      xmax[Num]=end_node_x;
      ymax[Num]=end_node_y;
      Num++;
     }
     else
     {

     }
       c->chaines_head=c->chaines_head->next;  
     j++;
     
 }


 for (int i = 0; i < Num; i++)
 {
    printf("MinX %f\n", xmin[i]);
     printf("MinY %f\n", ymin[i]);
      printf("MaxX %f\n", xmax[i]);
       printf("MaxY %f\n", ymax[i]);
 }
 


}




// creating chaine of cellnode from tree
struct CellNode *getAllUniqueNodeChainFromQuaTree( struct treeQuat *node, CellNode *Head,CellNode *chain)
{
   
   if(node==NULL)
    return Head;

    if(Head==NULL)
    {     number_of_Nodes++;
           CellNode *mainMainDataHolder = (struct CellNode*)malloc(sizeof( CellNode));
         mainMainDataHolder->next=NULL;
         Noeud * New_Node=(struct Noeud*)malloc(sizeof( Noeud));
         New_Node->x=node->xc;
         New_Node->y=node->yc;
         New_Node->neighbors=Neighbour_node_create(node->xc,node->yc);
         mainMainDataHolder->nd=New_Node;
         Head=mainMainDataHolder;
         chain=mainMainDataHolder;
  
    getAllUniqueNodeChainFromQuaTree(node->no,Head,chain);
    getAllUniqueNodeChainFromQuaTree(node->ne,Head,chain);
    getAllUniqueNodeChainFromQuaTree(node->se,Head,chain);
    getAllUniqueNodeChainFromQuaTree(node->so,Head,chain); 
    }
    else
    {
         number_of_Nodes++;
         CellNode *mainMainDataHolder = (struct CellNode*)malloc(sizeof( CellNode));
         mainMainDataHolder->next=NULL;
         Noeud * New_Node=(struct Noeud*)malloc(sizeof( Noeud));
         New_Node->x=node->xc;
         New_Node->y=node->yc;
         New_Node->neighbors=Neighbour_node_create(node->xc,node->yc);
         mainMainDataHolder->nd=New_Node;
         chain->next=mainMainDataHolder;
         chain=mainMainDataHolder;
    getAllUniqueNodeChainFromQuaTree(node->no,Head,chain);
    getAllUniqueNodeChainFromQuaTree(node->ne,Head,chain);
    getAllUniqueNodeChainFromQuaTree(node->se,Head,chain);
    getAllUniqueNodeChainFromQuaTree(node->so,Head,chain);   
    }
//display_neighbour_nodes(Head); 
  return Head;
      
} 

// 5.4
Noeud * searchCreeNodeTree (Reseau * R, TreeQuat *parent, double x, double y){
    bool isFound=false; 
    while (R->nodes!=NULL)
    {  
    
      if(R->nodes->nd->x==x&&R->nodes->nd->y==y){
          isFound=true;
         
      } 
      else if(R->nodes->next==NULL&&R->nodes->nd->x!=x&&R->nodes->nd->y!=y){
           number_of_Nodes++;
           printf("Not Found : now creating new Node \n");
           Noeud * New_temp =(struct Noeud*)malloc(sizeof( Noeud));
           New_temp->x=x;
           New_temp->y=y;
           New_temp->neighbors=NULL;
           R->nodes->next=New_temp;
           printf("number of nodes: %d\n",number_of_Nodes);
          // return R->nodes->next;
          }
          R->nodes=R->nodes->next;
      }
      
      if(isFound){
        printf("Found");
       // return R->nodes->nd;
      }

      //
    
      

}
//5.4 continue
void insertionAfterSearchingInTreeCaller(TreeQuat *parent, double x, double y)
{
     int resp =  checkPresencceInTree(parent,x, y);
     if(resp==1)
     {
         printf("FOUND IN TREE");
     }
     else
     {
         printf(" NOT FOUND IN TREE\n");
         
         printf("Tree---------------------- before --------------------insertion of new node\n");

         printQuatTree(parent); 
         lock=0;
         insertAgainInTreeAfterSearch(parent,x,y,NULL,0);
         printf("Tree------------------------- after --------------------insertion of new node\n");
         printQuatTree(parent); 
     }
}
void insertAgainInTreeAfterSearch(TreeQuat *parent, double x, double y,TreeQuat *prev,int type)
{
    if(parent==NULL)
    { 
        // printf("Inserting in tree \n");
        if(lock==0)
        {
        struct treeQuat *noNode = (struct treeQuat*)malloc(sizeof(struct treeQuat));
            noNode->xc=x;
            noNode->yc=y;
            printf("TRAGE XC %f YC%f \n",prev->xc,prev->yc);
            if(type==1)
            {
                prev->no=noNode;
            }
            else if(type==2)
            {
                prev->ne=noNode;
            }
            else if(type==3)
            {
                prev->se=noNode;
            }
            else if(type==4)
            {
                prev->so=noNode;
            }
            lock=1;
            // parent=noNode;
        }
        return NULL;
    }

//    printf("SEARCHING FOR INSERTION \n");

    insertAgainInTreeAfterSearch(parent->no,x,y,parent,1);
    insertAgainInTreeAfterSearch(parent->ne,x,y,parent,2);
    insertAgainInTreeAfterSearch(parent->se,x,y,parent,3);
    insertAgainInTreeAfterSearch(parent->so,x,y,parent,4);
    
}
int * checkPresencceInTree(TreeQuat *parent, double x, double y)
{
    // printf("SEarhing in tree \n");
    if(parent==NULL)
    {
       
        return 0;
    }

    if(parent->xc==x && parent->yc==y)
    {
        return 1;
    }
    checkPresencceInTree(parent->ne,x,y);
    
    checkPresencceInTree(parent->no,x,y);
    
    checkPresencceInTree(parent->se,x,y);
    
    checkPresencceInTree(parent->so,x,y);
    
    return 0;
}
 