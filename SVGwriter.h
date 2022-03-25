#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include<math.h>
#ifndef _SVGWRITER_H_
#define _SVGWRITER_H_

/* In this library, the colors are used in their form
   hexadecimal as shown in the following examples) */

#define Black "#000000"
#define Cyan "#00FFFF"
#define Fuchsia "#FF00FF"
#define Lime "#00FF00"
#define Orange "#FFA800"
#define Red "#FF0000"
#define RoyalBlue "#486CE8"



typedef struct SVGwriter_struct {
  
  char lineColor[10];  /* Default color value */
  char pointColor[10]; /* Default color value */
  int sizeX, sizeY;    /* Picture size */
   
  FILE *file; /* File stream */

  /* Technical value for random color generation */
  char gencol[16];

} SVGwriter;


  
/* Initialize the struct SVGwriter passed as a parameter
      nomfic: name of the html file to create
      sizeX, sizeY: size in pixel of the image to be created */

void SVGinit(SVGwriter *svg,char *nomfic, int sizeX, int sizeY);

/* Set the line color for the rest */
void SVGlineColor(SVGwriter *svg, char *col);

/* Set a random color for the lines for the rest */
void SVGlineRandColor(SVGwriter *svg);

/* Fix the color of the points for the continuation */
void SVGpointColor(SVGwriter *svg, char *col);

/* Write a dot in the file */
void SVGpoint(SVGwriter *svg, double x, double y);

/* Write a segment to the file */
void SVGline(SVGwriter *svg, double xa, double ya, double xb, double yb);

/* Close the file */
void SVGfinalize(SVGwriter *svg);

#endif
