#include<stdio.h>
#include<math.h>
#include<time.h>
#include "SVGwriter.h"
#include "SVGwriter.c"
#include "Reseau.c"

int main(){

// ReconstitueReseau.c program that uses the command line to take a .cha file as a parameter and an integer indicating which method one wishes to use (list, hash table, or tree)
//2.3
    
    double xmin[12],ymin[12],xmax[12],ymax[12]; // use for seach min max method in exe 5.1
    int Number;
    FILE *fptr;
    // Creating Chain by reading file 00014_burma.cha
    fptr= fopen("00014_burma.cha","r");
    Chaines *c =   lectureChaines(fptr);
    fclose(fptr);
    printf("Sélectionnez le type de structure de données que vous souhaitez utiliser pour créer le réseau:\n\n");
    printf("Select 1 for List Structure: \n Select 2 for Hash Structure: \n Select 3 for Tree Structure: \n\n");
    scanf("%d", &Number);

    if(Number==1){
        printf("Working on List Structure :\n");
        Reseau * R= reconstitueReseauListe(c);
        //afficheReseauSVG(R,"CreateSVGFrom_network");
        // search method
        // Noeud * nd= rechercheCreeNoeudListe(R,3.6, 7.8);
        // printf("x:%f\n",nd->x);
        // printf("x:%f\n",nd->y);
        //writting method
        // FILE *f1;
        // f1= fopen("Write_Network_data_withList.txt","w");
        // ecrireReseau(R, f1);
        //  fclose(f1);
        

    }else if(Number==2){
        printf("Working on Hash Structure:\n");
         Reseau *R = reconstituteHashNetwork(hashArray,c);
         
    }
    else if(Number==3){
      printf("Working on Tree Structure:\n");
     Reseau *R= reconstitutesNetworkTree (c);
     searchCreeNodeTree (R,NULL, 16.47 ,100.44);
     
     struct treeQuat *parent = createTreeQuat(c->chaines->CellPoint_tail->x,c->chaines->CellPoint_tail->y,0,0);
     insertionAfterSearchingInTreeCaller(parent,16.47,100.44);


     
    } 

printf("\n\n");

// Exercise 6
// - Comparison of the three structures 

//6.1

FILE *f= fopen("Output_Computation.txt","w");
 //printf("calculates their computation time\n");
    double time_taken=0;
   
    clock_t ts1,te1;
    ts1 = clock();
    for(int i=0; i< 10000000; i++) {
   }
    generateFileWithHashTable();
    te1 = clock();
    time_taken = (double)(te1 - ts1) / CLOCKS_PER_SEC; // in seconds
  
    fprintf(f,"Time finding unique node with Hash %f\n", time_taken);
   
   
 
    ts1 = clock();
        for(int i=0; i< 10000000; i++) {
   }

    Create_Node_neighbour_list();
    te1 = clock();
   time_taken = (double)(te1 - ts1) / CLOCKS_PER_SEC;
   fprintf(f,"Time finding unique node with List %f\n", time_taken);
   
   

  
    ts1 = clock();   
        for(int i=0; i< 10000000; i++) {
   }

    createQuadTree();
    te1 = clock();
    time_taken = (double)(te1 - ts1) / CLOCKS_PER_SEC; // in seconds
  
    fprintf(f,"Time finding unique node with Tree %f\n", time_taken);

    fclose(f);

    return 0;
}
