/*!
 * \file    geometrie.h
 * \brief   Prototypes de geometrie.c
 * \author  Valentin Caillard & Domitille Buttin & Antoine Le Calvez & Thibault Perel
 * \date 18/03/2015
 */

#ifndef GEOMETRIE
#define GEOMETRIE

#include "commun.h"

unsigned long Color(int R, int G, int B);

void PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel);

void drawLine(SDL_Surface *surf,int x1,int y1, int x2,int y2, int R, int G, int B);

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );

#endif


