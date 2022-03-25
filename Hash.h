#define __HASH_H__
#include <stdio.h>
#include "Reseau.h"

//Q 4.1 Give a TableHash structure that allows you to implement
// a hash table with management of collisions by chaining. Define it in a file named Hash.h.
#define SIZE 100
struct cellnode* hashArray[SIZE]; 
struct cellnode* dummyItem;
struct cellnode* item;



void printHashTable();
void insert(int key,Noeud *ndr);
struct cellnode *search(int key);
int hashCode(int key);
void generateFileWithHashTable();
struct CellNode * getUniqueChaineFromHashTable(struct cellnode* hashArray[]);