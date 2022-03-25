#include<stdio.h>
#include<math.h>
#include<time.h>
#include "SVGwriter.h"
#include "SVGwriter.c"
#include "Chaine.h"

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
// main method
int main(){

char FileName[50];
FILE *fptr;

// Creating Chain by reading file 00014_burma.cha
fptr= fopen("00014_burma.cha","r");
Chaines *c =   lectureChaines(fptr);
fclose(fptr);

// writing to File
printf("veuillez entrer le nom du fichier à écrire:: \n");
scanf("%s", &FileName);
strcat(FileName,".txt");
FILE *fWrite= fopen(FileName,"w");
ecrireChaines(c,fWrite);
fclose(fWrite);




printf("Afficher les chaînes en SVG:\n");
printf("Entrez le nom du fichier pour la création SVG:\n");
scanf("%s", &FileName);

// Creating Chain by reading file 00014_burma.cha
fptr= fopen("00014_burma.cha","r");
Chaines *c1 =   lectureChaines(fptr);
fclose(fptr);
afficheChainesSVG(c1,FileName);



printf("Calculer Calculer la longueur de la chaîne et la longueur totale entre les chaînes\n");
fptr= fopen("00014_burma.cha","r");
Chaines *c2=   lectureChaines(fptr);
fclose(fptr);
printf("Longueur totale: %.4f\n", longueurTotale(c2));



printf("Points totaux \n");
fptr= fopen("00014_burma.cha","r");
Chaines *c3 =   lectureChaines(fptr);
fclose(fptr);
printf("Nombre total de points: %d\n",comptePointsTotal(c3));







return 0;
}


