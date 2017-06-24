/*!
 * \file    geometrie.c
 * \brief   Fonctions géométriques (dessiner une ligne, appliquer une surface à partir d'une feuille de sprite)
 * \author  Valentin Caillard & Domitille Buttin & Antoine Le Calvez & Thibault Perel
 * \date 18/03/2015
 */

#include "geometrie.h"


/*!
 * \fn unsigned long Color(int R, int G, int B)
 * \brief Convertit RGB en long
 * \param[in] R Rouge
 * \param[in] G Vert
 * \param[in] B Bleu
 * \return entier long correspondant à la couleur
 */
unsigned long Color(int R, int G, int B)
{
	return 65536*R + 256*G + B;
}

/*!
 * \fn void PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel)
 * \brief Affiche un pixel
 * \param[in] surface sur laquelle mettre le pixel
 * \param[in] x abscisse
 * \param[in] y ordonnée
 * \param[in] pixel à afficher
 */
void PutPixel(SDL_Surface *surface, int x, int y, unsigned long pixel)
{
	int bpp = (surface)->format->BytesPerPixel;
	unsigned char *p = (unsigned char *)(surface)->pixels + y * (surface)->pitch + x * bpp;
	if (bpp==4) *(unsigned long*)p = pixel;
}

/*!
 * \fn void drawLine(SDL_Surface *surf,int x1,int y1, int x2,int y2, int R, int G, int B)  // Algorithme de Bresenham
 * \brief Dessine une ligne
 * \param[in] surface sur laquelle on dessine la ligne
 * \param[in] x1 abscisse du 1er point
 * \param[in] y1 ordonnée du 1er point
 * \param[in] x2 abscisse du 2eme point
 * \param[in] y2 ordonnée du 2eme point
 * \param[in] R Rouge
 * \param[in] G Vert
 * \param[in] B Bleu
 */
void drawLine(SDL_Surface *surf,int x1,int y1, int x2,int y2, int R, int G, int B)
{
	unsigned long couleur = Color(R, G, B);
	int x,y;
	int Dx,Dy;
	int xincr,yincr;
	int erreur;
	int i;

	Dx = abs(x2-x1);
	Dy = abs(y2-y1);
	if(x1<x2)
		xincr = 1;
	else
		xincr = -1;
	if(y1<y2)
		yincr = 1;
	else
		yincr = -1;

	x = x1;
	y = y1;
	if(Dx>Dy)
	{
		erreur = Dx/2;
		for(i=0;i<Dx;i++)
		{
			x += xincr;
			erreur += Dy;
			if(erreur>Dx)
			{
				erreur -= Dx;
				y += yincr;
			}
			PutPixel(surf,x, y,couleur);
		}
	}
	else
	{
		erreur = Dy/2;
		for(i=0;i<Dy;i++)
		{
			y += yincr;
			erreur += Dx;

			if(erreur>Dy)
			{
				erreur -= Dy;
				x += xincr;
			}
			PutPixel(surf,x, y,couleur);
		}
	}
}

/*!
 * \fn void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
 * \brief afficher une partie d'une feuille de la feuille de sprite source sur la destination
 * \param[in] x abscisse
 * \param[in] y ordonnée
 * \param[in] source
 * \param[in] destination
 * \param[in] clip coordonnées de la source à considérer
 */
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
