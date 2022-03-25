#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"
#include "SVGwriter.h"



//===================Reading, storing and displaying data============================================================
// method to read file file and create the chain 
// here we are reading file also assigning it index which will use on next steps
// 1.1
Chaines* lectureChaines(FILE *f){

// Counting the number of nodes (x and y)
char line1[128];
int l=0,sizeOfFlagArray=0;

while(fgets(line1, sizeof(line1), f)){
 
  int j=0;
  char * token = strtok(line1, " ");
  
   while( token != NULL ) {
        if(l==0&&j==1)
         { 
            
         }
         else if(l==1&&j==1)
         {
          
         }
         else if(l>=2&&j==1){
          
          
         }
         else if(j>1)
         { token = strtok(NULL, " ");
           sizeOfFlagArray = sizeOfFlagArray+1;
       
         }
      token = strtok(NULL, " ");
      j++;
   }
    l++; 
  }

// printf("DONE\n");
double keys[sizeOfFlagArray][3];



//storing null on each index

for(int i=0;i<sizeOfFlagArray;i++)
{
  for(int j=0;j<3;j++)
  {
    keys[i][j]=-1;
   
  }
}

int indexKey=1,indexforKeysRow=0;

fclose(f);

FILE *f1= fopen("00014_burma.cha","r");


while(fgets(line1, sizeof(line1),f1)){
 
  int j=0;
  char * token = strtok(line1, " ");
 
   while( token != NULL ) {
        if(l==0&&j==1)
         { 
            
         }
         else if(l==1&&j==1)
         {
          
         }
         else if(l>=2&&j==1){
          
          
         }
         else if(j>1)
         {  
           double x = strtod(token, NULL);
           token = strtok(NULL, " ");
           double y = strtod(token, NULL);
           
           
           keys[indexforKeysRow][0]=x;
           keys[indexforKeysRow][1]=y;
           keys[indexforKeysRow][2]=0;
             indexforKeysRow=indexforKeysRow+1;
         }
          
         
      token = strtok(NULL, " ");
      j++;
   }
   
    l++; 
  }

//storing null on each index
double filterdKeyValues[sizeOfFlagArray][3];


for(int i=0;i<sizeOfFlagArray;i++)
{
  for(int j=0;j<3;j++)
  {
    filterdKeyValues[i][j]=-1;
    // printf("EPM %f VAL \n",keys[i][j]) ;
  }
}


//Just printing for testing



for(int i=0;i<sizeOfFlagArray;i++)
{
  if(i==0)
  {
    filterdKeyValues[i][0]=keys[i][0];
    filterdKeyValues[i][1]=keys[i][1];
    filterdKeyValues[i][2]=indexKey;
    indexKey++;
  } 
  else
  {
      double target_x = keys[i][0];
      double target_y = keys[i][1];
      bool isDup=false;
      for(int j=0;j<sizeOfFlagArray;j++)
      {
          //checking back word
          if(filterdKeyValues[j][0]==(-1.000000))
          {
            break;
          }
          else if(filterdKeyValues[j][0]==target_x && filterdKeyValues[j][1]==target_y)
          {

            isDup=true;
            break;
          }
      }
      if(!isDup)
      {
        filterdKeyValues[i][0]=target_x;
        filterdKeyValues[i][1]=target_y;
        filterdKeyValues[i][2]=indexKey;
        indexKey++;
      }
  }
}



//STARTED CREATING REAL CHAIN.
fclose(f1);

FILE *f2= fopen("00014_burma.cha","r");

char line[128];
int i=0;
double num_of_chains=0,gamma_val=0,number_of_points=0;

//Creating object of Main chain Head ..

struct Chaines *mainChainHead = NULL;
struct CellChaine *tempCellHead = NULL;
struct CellPoint *tempPoint = NULL;


while(fgets(line, sizeof(line), f2)){

  int j=0;
  char * token = strtok(line, " ");
  
  if(mainChainHead==NULL)
  {
  
        mainChainHead = (struct Chaines*)malloc(sizeof( Chaines));

        struct CellChaine *chain =  (struct CellChaine*)malloc(sizeof( CellChaine));
        chain->next=NULL;
        chain->CellPoint_head=NULL;
        chain->points=NULL;
        mainChainHead->chaines_head=chain;
        mainChainHead->chaines=chain;
  }
  else
  {
        struct CellChaine *chain =  (struct CellChaine*)malloc(sizeof( CellChaine));
        chain->next=NULL;
        chain->CellPoint_head=NULL;
        chain->points=NULL;
        mainChainHead->chaines->next=chain;
        mainChainHead->chaines=chain;
  }
  


   while( token != NULL ) {
   
        if(i==0&&j==1)
         { 
            num_of_chains=strtod(token, NULL);
            mainChainHead->nbChaines=num_of_chains;
         }
         else if(i==1&&j==1)
         {
            gamma_val=strtod(token, NULL);
            mainChainHead->gamma=gamma_val;
         }
         else if(i>=2&&j==1){
          number_of_points=strtod(token, NULL);
        
        
          mainChainHead->chaines->number=strtod(token, NULL);
          
        
          
         }
         else if(j>1)
         {
           double x = strtod(token, NULL);
           token = strtok(NULL, " ");
           double y = strtod(token, NULL);
            
          int indexKey = -1;

          
           for(int g=0;g<sizeOfFlagArray;g++)
           {
           
             if(filterdKeyValues[g][0]==x && filterdKeyValues[g][1]==y)
             {
               indexKey=filterdKeyValues[g][2];
          
             }
           }
     
 
        if(mainChainHead->chaines->CellPoint_head==NULL)
          {
             struct CellPoint *point = (struct CellPoint*)malloc(sizeof( CellPoint));
             point->next=NULL;
             point->prev=NULL;
             point->x=x;
             point->y=y;
             point->keyIndex=indexKey;
             mainChainHead->chaines->CellPoint_tail=point;
             mainChainHead->chaines->CellPoint_head=point;
             mainChainHead->chaines->points=point;  //adding data
           }
           else{
            struct CellPoint *point = (struct CellPoint*)malloc(sizeof( CellPoint));
             point->next=NULL;
             point->prev=NULL;
             point->x=x;
             point->y=y;
            point->keyIndex=indexKey;
            mainChainHead->chaines->CellPoint_head->prev=point;
            point->next=mainChainHead->chaines->CellPoint_head;
            mainChainHead->chaines->CellPoint_head=point;
           }

           
         }
      token = strtok(NULL, " ");
      j++;
   }
    i++; 
  } 

  fclose(f2);

  
  
  return mainChainHead;
}








// Writing to file funtion
// 1.2
void ecrireChaines(Chaines *c, FILE *f){
 
  int i=0,j=0;
 
   fprintf(f, "NbChain: %.0f\n",c->nbChaines);
   fprintf(f, "Gamma: %.0f\n",c->gamma);
  
 
  
  while (c->chaines_head!=NULL)
 {  
   if(j<2){
   c->chaines_head=c->chaines_head->next;
    }else{
    
   fprintf(f,"%d %.0f ",i,c->chaines_head->number);
   
   while (c->chaines_head->CellPoint_tail!=NULL)
   {  
   
     fprintf(f,"%.2f ",c->chaines_head->CellPoint_tail->x);
     fprintf(f,"%.2f ",c->chaines_head->CellPoint_tail->y);

     c->chaines_head->CellPoint_tail=c->chaines_head->CellPoint_tail->prev;
   }
    fprintf(f,"\n");
    c->chaines_head=c->chaines_head->next;
    i++;
   }
   
  
    j++;
 }
   
}



//1.3
// display SVG 
void afficheChainesSVG(Chaines *C, char* nomInstance){
  
  // creating chain again for next steps use
  FILE *fptr= fopen("00014_burma.cha","r");
  Chaines *V =   lectureChaines(fptr);
  fclose(fptr);



    int i;
    double maxx = 0, maxy = 0, minx = 1e6, miny = 1e6;
    CellChaine * ccour;
    CellPoint * pcour;
    double precx, precy;
    SVGwriter svg;
    ccour = C->chaines;
    Chaines *c= C;
    Chaines *v= V;  

//here
while (c->chaines_head!=NULL)
 { 
   while (c->chaines_head->CellPoint_head!=NULL)
   {  
     if (maxx <c->chaines_head->CellPoint_head->x) maxx = c->chaines_head->CellPoint_head->x;
            if (maxy <c->chaines_head->CellPoint_head->y) maxy = c->chaines_head->CellPoint_head->y;
            if (minx> c->chaines_head->CellPoint_head->x) minx = c->chaines_head->CellPoint_head->x;
            if (miny> c->chaines_head->CellPoint_head->y) miny = c->chaines_head->CellPoint_head->y;
     c->chaines_head->CellPoint_head=c->chaines_head->CellPoint_head->next;
   }
 
    c->chaines_head=c->chaines_head->next;
 }
 //end


SVGinit (& svg, nomInstance, 500,500);


while (v->chaines_head!=NULL)
 { 
 
   
     
  int l=0;
  while (v->chaines_head->CellPoint_head!=NULL)
   { 
     if(l==0)
     {
        double t = 500 * (v->chaines_head->CellPoint_head->x-minx) / (maxx-minx);
        double z = 500 * (v->chaines_head->CellPoint_head->y-miny) / (maxy-miny);
         SVGlineRandColor (& svg);
         SVGpoint (& svg,t,z);

         precx = v->chaines_head->CellPoint_head->x;
         precy = v->chaines_head->CellPoint_head->y;
         l++;
     }
     else
     {
            SVGline (& svg, 500 * (precx-minx) / (maxx-minx), 500 * (precy-miny) / (maxy-miny), 500 * (v->chaines_head->CellPoint_head-> x-minx) / (maxx-minx), 500 * (v->chaines_head->CellPoint_head-> y-miny) / (maxy-miny));
            SVGpoint (& svg, 500 * (v->chaines_head->CellPoint_head-> x-minx) / (maxx-minx), 500 * (v->chaines_head->CellPoint_head->y-miny) / (maxy-miny));
            precx = v->chaines_head->CellPoint_head->x;
            precy = v->chaines_head->CellPoint_head->y; 
     }

     v->chaines_head->CellPoint_head=v->chaines_head->CellPoint_head->next;
   }

    v->chaines_head=v->chaines_head->next;
 }


    SVGfinalize (& svg);
}



//1.4
// containing part1 and part2
double longueurTotale(Chaines *c)
{   
    int j=0;
    double sum_chain=0, dist_between_points=0, Total_distance=0;
    double x1=0,y1=0,x2=0,y2=0, gdistance=0;
 while (c->chaines_head!=NULL)
 { 
   sum_chain=0;  
  //  printf(" for %d\n",j);
   while (c->chaines_head->CellPoint_head!=NULL)
   {    
        x1=c->chaines_head->CellPoint_head->x;
        y1=c->chaines_head->CellPoint_head->y;
       
     c->chaines_head->CellPoint_head=c->chaines_head->CellPoint_head->next;
        
        x2=c->chaines_head->CellPoint_head->x;
        y2=c->chaines_head->CellPoint_head->y;
       
         gdistance = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
         dist_between_points=sqrt(gdistance);
        // printf("Distance between the said points: %.4f\n", dist_between_points);
         sum_chain= sum_chain+ dist_between_points;
         if(c->chaines_head->CellPoint_head->next==NULL){
    break;
        }
       
   }
    if(j<2){

    }else{
printf("Total distance of each chain: %.4f\n", sum_chain);
    }
    
    Total_distance=Total_distance+sum_chain;
   j++;
    c->chaines_head=c->chaines_head->next;
   
 }
  return Total_distance;

}



// Count Total number of Points
//1.5
int comptePointsTotal(Chaines *c){
  int i=1,j=0;
  while (c->chaines_head!=NULL)
 {  
   if(j<2){
   c->chaines_head=c->chaines_head->next;
  }
  else{
   while (c->chaines_head->CellPoint_head!=NULL)
   { i++; 
     c->chaines_head->CellPoint_head=c->chaines_head->CellPoint_head->next;
     
   }
   
    c->chaines_head=c->chaines_head->next  ;
    
   }
   
  
    j++;
 }
 return i;
}



//6.2
// creation of chaine again

Chaines * generationAleatory (int nbStrings, int nbPointsString, int xmax, int ymax){
struct Chaines *mainChainHead = NULL;
struct CellChaine *tempCellHead = NULL;
struct CellPoint *tempPoint = NULL;
double num_of_chaines=0;
double point_val_x=0,point_val_y=0;
   if(mainChainHead==NULL)
  {
  
        mainChainHead = (struct Chaines*)malloc(sizeof( Chaines));

        struct CellChaine *chain =  (struct CellChaine*)malloc(sizeof( CellChaine));
        chain->next=NULL;
        chain->CellPoint_head=NULL;
        chain->points=NULL;
        mainChainHead->chaines_head=chain;
        mainChainHead->chaines=chain;
  }
  else
  {
        struct CellChaine *chain =  (struct CellChaine*)malloc(sizeof( CellChaine));
        chain->next=NULL;
        chain->CellPoint_head=NULL;
        chain->points=NULL;
        mainChainHead->chaines->next=chain;
        mainChainHead->chaines=chain;
  }

  for(int i=0;i<nbStrings;i++){
    point_val_x=0;
    point_val_y=0;
    mainChainHead->chaines->number=num_of_chaines;
    double Num_of_points = (rand() %
           ( nbPointsString - 500 + 1)) + 500;

           Num_of_points=Num_of_points+500;
        printf("x--%f ", Num_of_points);
   

    printf("Enter Point Values for Chaine Number: %d\n",i);
    for(int j=0;j<Num_of_points;j++)
    {  
          printf("\ncreate random X %d:",j);
          double x = (rand() %
           (ymax - 0 + 1)) + 0;
        printf("x--%f ", x);

        printf("\nCreate Random y %d:",j); 
         double y = (rand() %
           (ymax - 0 + 1)) + 0;
          printf("y--%f\n", y);
         
         
        if((point_val_x>=0&&point_val_x<=xmax)||(point_val_y>=0&&point_val_y<=ymax)){
          printf("here\n");
         if(mainChainHead->chaines->CellPoint_head==NULL)
          {
             struct CellPoint *point = (struct CellPoint*)malloc(sizeof( CellPoint));
             point->next=NULL;
             point->prev=NULL;
             point->x=x;
             point->y=y;
             mainChainHead->chaines->CellPoint_tail=point;
             mainChainHead->chaines->CellPoint_head=point;
             mainChainHead->chaines->points=point;  //adding data
           }
           else{
            struct CellPoint *point = (struct CellPoint*)malloc(sizeof( CellPoint));
             point->next=NULL;
             point->prev=NULL;
             point->x=x;
             point->y=y;
           
            mainChainHead->chaines->CellPoint_head->prev=point;
            point->next=mainChainHead->chaines->CellPoint_head;
            mainChainHead->chaines->CellPoint_head=point;
           }

        }
        else{
          
          printf("\nEntered value is more than max val\n");
         j--;
        }


        
    }

    num_of_chaines++;
  }
  
return mainChainHead;
}


