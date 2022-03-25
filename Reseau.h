#ifndef __RESEAU_H__
#define __RESEAU_H__
#include <stdio.h>
 #include "Chaine.h"

typedef struct noeud Noeud;


int maxRow;
int maxCol;
int lock;

/* Chain list of nodes (for the list of network nodes AND the lists of neighbors of each node) */
typedef struct cellnode {
    Noeud * nd; /* Pointer to the stock node */
    int key;
    struct cellnode * next; /* Next cell in the list */
} CellNode;

/* Network node */
struct noeud {
   int num; /* Node number */
   double x, y; /* Coordinates of the node */
   int keyIndex;
   CellNode * neighbors; /* List of neighbors of the node */
   struct CellNode * cellnode_head;
}noeud;

/* Chain list of commodities */
typedef struct cellCommodite {
    Noeud * extrA, * extrB; /* Knots at the ends of the convenience */
    struct cellCommodite * next; /* Next cell in the list */
} CellCommodite;

/* A network */
typedef struct {
    int nbNodes; /* Number of network nodes */
    int gamma; /* Maximum number of fibers per cable */
    CellNode * nodes; /* List of network nodes */
    CellCommodite * commodites; /* List of commodities to link */
} Reseau;



// tree structure Part
 typedef struct treeQuat {
 double xc, yc; 
 int key;
 double dimensionX; 
 double dimensionY;
 struct noeud * knot; 
 struct treeQuat * so;
 struct treeQuat * se; 
 struct treeQuat * no;
 struct treeQuat * ne;
} TreeQuat;


//5.3
struct treeQuat *insertTreeNode(int callNo,struct treeQuat *treeNode,double xc,double yc,double allNodes[maxRow][maxCol],double traveredNodes[maxRow][maxCol]);
void printQuatTree(struct  treeQuat *nvode);
void createQuadTree();
//5.2
struct treeQuat *createTreeQuat (double xc, double yc, double dimensionX, double dimensionY);
// creating cellnode list from tree structure
struct CellNode *getAllUniqueNodeChainFromQuaTree( struct treeQuat *node, CellNode *Head, CellNode *chain);
int * checkPresencceInTree(TreeQuat *parent, double x, double y);

void insertAgainInTreeAfterSearch(TreeQuat *parent, double x, double y,TreeQuat *prev,int type);
void insertionAfterSearchingInTreeCaller(TreeQuat *parent, double x, double y);

// Methods That are used in reconstruction of network
int check_Node_repeatation(CellPoint *p,int i);
int check_neighbour_repeatation(int orignal_node_key,int neighbour_node_key,int i);
void display_neighbour_nodes(CellNode *nd);
CellNode * Create_Node_neighbour_list();
CellPoint * right_neighbour(CellPoint *p);
CellPoint * left_neighbour(CellPoint *p);
CellNode * Neighbour_node_create(double x, double y);
CellCommodite * Find_Commodaties();
void display_Commodities(CellCommodite *cl);






// Methods for Task
//2.1
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);// search method 
//2.2 
Reseau* reconstitueReseauListe(Chaines *C);
//3.2
void ecrireReseau(Reseau *R, FILE *f);// write to fle method
//3.1
int nbLiaisons(Reseau *R);
//3.1
int nbCommodites(Reseau *R);// commodaties
//3.3
void afficheReseauSVG(Reseau *R, char* nomInstance);

//4.4
 struct Noeud * searchCreeNodeHash (Reseau * R, struct cellnode* hashArray[], double x, double y);
//4.5
Reseau * reconstituteHashNetwork  (struct cellnode* hashArray[],Chaines *c);


//5.4
Noeud * searchCreeNodeTree (Reseau * R, TreeQuat *parent, double x, double y);
//5.5
Reseau * reconstitutesNetworkTree (Chaines * c);
#endif