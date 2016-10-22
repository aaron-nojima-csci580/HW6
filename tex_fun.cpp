/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"

#define ARRAY(x,y)  (x + (y * xs))

GzColor	*image=NULL;
int xs, ys;
int reset = 1;

/* Image texture function */
int tex_fun(float u, float v, GzColor color)
{
  unsigned char		pixel[3];
  unsigned char     dummy;
  char  		foo[8];
  int   		i, j;
  FILE			*fd;

  if (reset) {          /* open and load texture file */
    fd = fopen ("texture", "rb");
    if (fd == NULL) {
      fprintf (stderr, "texture file not found\n");
      exit(-1);
    }
    fscanf (fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
    image = (GzColor*)malloc(sizeof(GzColor)*(xs+1)*(ys+1));
    if (image == NULL) {
      fprintf (stderr, "malloc for texture image failed\n");
      exit(-1);
    }

    for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
      fread(pixel, sizeof(pixel), 1, fd);
      image[i][RED] = (float)((int)pixel[RED]) * (1.0 / 255.0);
      image[i][GREEN] = (float)((int)pixel[GREEN]) * (1.0 / 255.0);
      image[i][BLUE] = (float)((int)pixel[BLUE]) * (1.0 / 255.0);
      }

    reset = 0;          /* init is done */
	fclose(fd);
  }

/* bounds-test u,v to make sure nothing will overflow image array bounds */
/* determine texture cell corner values and perform bilinear interpolation */
/* set color to interpolated GzColor value and return */
  
  // bounds-test u,v to make sure nothing will overflow image array bounds
  u = fmaxf(0, fminf(1, u));
  v = fmaxf(0, fminf(1, v));

  // determine texture cell corner values (after scale)
  u = u * (xs - 1);
  v = v * (ys - 1);
  int minU, maxU, minV, maxV;
  float s, t;
  minU = floor(u);
  maxU = ceil(u);
  minV = floor(v);
  maxV = ceil(v);
  s = u - minU;
  t = v - minV;

  // perform bilinear interpolation, set color to interpolated GzColor value and return
  color[RED] =
	  ((s * t * image[ARRAY(maxU, maxV)][RED]) +
	  ((1 - s) * t * image[ARRAY(minU, maxV)][RED]) +
	  (s * (1 - t) * image[ARRAY(maxU, minV)][RED]) +
	  ((1 - s) * (1 - t) * image[ARRAY(minU, minV)][RED]));

  color[GREEN] =
	  ((s * t * image[ARRAY(maxU, maxV)][GREEN]) +
	  ((1 - s) * t * image[ARRAY(minU, maxV)][GREEN]) +
	  (s * (1 - t) * image[ARRAY(maxU, minV)][GREEN]) +
	  ((1 - s) * (1 - t) * image[ARRAY(minU, minV)][GREEN]));

  color[BLUE] = 
	  ((s * t * image[ARRAY(maxU, maxV)][BLUE]) +
	  ((1 - s) * t * image[ARRAY(minU, maxV)][BLUE]) +
	  (s * (1 - t) * image[ARRAY(maxU, minV)][BLUE]) +
	  ((1 - s) * (1 - t) * image[ARRAY(minU, minV)][BLUE]));

  return GZ_SUCCESS;
}

/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{
	// bounds-test u,v to make sure nothing will overflow image array bounds
	u = fmaxf(0, fminf(1, u));
	v = fmaxf(0, fminf(1, v));

	// TODO: IMPLEMENT (Be Creative!)
	GzColor black = { 0.0f, 0.0f, 0.0f };
	GzColor red = { 1.0f, 0.0f, 0.0f };

	int gridCount = 8;
	int uGrid = floor(u * gridCount);
	int vGrid = floor(v * gridCount);
	if (uGrid % 2 == vGrid % 2)
	{
		color[RED] = black[RED];
		color[GREEN] = black[GREEN];
		color[BLUE] = black[BLUE];
	}
	else
	{
		color[RED] = red[RED];
		color[GREEN] = red[GREEN];
		color[BLUE] = red[BLUE];
	}

	return GZ_SUCCESS;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}

