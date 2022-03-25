#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "quadtree.h"


int getMaxNumberOfColumns()
{
 FILE *fptr= fopen("00014_burma.cha","r");
 Chaines *c =   readStrings(fptr);
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
 Chaines *c =   readStrings(fptr);
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
    printf("Filling with default values\n");
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
 Chaines *c =   readStrings(fptr);
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
{
  struct treeQuat *r = createTreeQuat(25.23,97.24,0,0);
 // printQuatTree(r);
} 
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
  CellNode *head=NULL;
  CellNode *chain=NULL;
  getAllUniqueNodeChainFromQuaTree(root,head,chain);
 
  return root;
}
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
