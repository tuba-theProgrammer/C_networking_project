#ifndef __CHAIN_H__
#define __CHAINE_H__
#include <stdio.h>

/* Chain list of points */
typedef struct CellPoint {
  double x;
  double y; /* Point coordinates */
  int keyIndex;
  struct CellPoint * next; /* Next cell in the list */
  struct CellPoint * prev; /* prev cell in the list */

} CellPoint;

/* Cell in a list (string) of strings */
typedef struct CellChaine {
  double number; /* Chaine number */
   
  CellPoint * points; /* List of chaine points */
  struct CellChaine * next; /* Next cell in the list */
  struct CellPoint * CellPoint_head; 
  struct CellPoint * CellPoint_tail;
} CellChaine;

/* All strings */
typedef struct Chaines{
  double gamma; /* Maximum number of fibers per cable */
  double nbChaines; /* Number of Chaines */
  CellChaine * chaines; /* The Chaine list of Chaines */
  struct CellChaine *chaines_head;
} Chaines;


//1.1
Chaines* lectureChaines(FILE *f);
//1.2
void ecrireChaines(Chaines *C, FILE *f);
//1.3
void afficheChainesSVG(Chaines *C, char* nomInstance);
//1.4
double longueurTotale(Chaines *C);
//1.5
int comptePointsTotal(Chaines *C);
#endif
