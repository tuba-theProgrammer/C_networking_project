# ifndef __ARBRE_QUAT_H__
#define __ARBRE_QUAT_H__

#include "Reseau.c"

int maxRow;
int maxCol;

 typedef struct treeQuat {
 double xc, yc; 
 double dimensionX; 
 double dimensionY;
 struct node * knot; 
 struct treeQuat * so;
 struct treeQuat * se; 
 struct treeQuat * no;
 struct treeQuat * ne;
} TreeQuat;


//5.2
struct treeQuat *insertTreeNode(int callNo,struct treeQuat *treeNode,double xc,double yc,double allNodes[maxRow][maxCol],double traveredNodes[maxRow][maxCol]);
void printQuatTree(struct  treeQuat *nvode);
void createQuadTree();

//5.3
struct treeQuat *createTreeQuat (double xc, double yc, double dimensionX, double dimensionY);
struct CellNode *getAllUniqueNodeChainFromQuaTree( struct treeQuat *node,struct CellNode *Head,struct CellNode *chain);

TreeQuat * inserIfNotFound(TreeQuat *parent, double x, double y);
 # endif
