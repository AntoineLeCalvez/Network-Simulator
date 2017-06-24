/*!
 * \file    commun.h
 * \brief   Contient les constantes de taille/positions et les prototypes de commun.c
 * \author  Valentin Caillard & Domitille Buttin & Antoine Le Calvez & Thibault Perel
 * \date 18/03/2015
 */

#ifndef COMMUN
#define COMMUN

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_image.h>
#include "geometrie.h"

//Les paramètres de l'écran
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 840
#define SCREEN_BPP 32
//Les paramètres de la feuille de sprite Ouvrir/Sauvegarder
#define OUVRIR_SAUVEGARDER_WIDTH_SPRITE 128
#define OUVRIR_SAUVEGARDER_HEIGHT_SPRITE 128
//Les paramètres de la feuille de sprite Run/Cancel
#define RUN_CANCEL_WIDTH_SPRITE 220
#define RUN_CANCEL_HEIGHT_SPRITE 110
//Les paramètres de la feuille de sprite Débit
#define DEBIT_WIDTH_SPRITE 200
#define DEBIT_HEIGHT_SPRITE 300
////Les paramètres de la feuille de sprite Taille
#define TAILLE_WIDTH_SPRITE 200
#define TAILLE_HEIGHT_SPRITE 300
//Les paramètres de la feuille de sprite Plus/Moins
#define PLUS_MOINS_WIDTH_SPRITE 200
#define PLUS_MOINS_HEIGHT_SPRITE 184
//Les paramètres de la feuille de sprite Reboot
#define REBOOT_WIDTH_SPRITE 200
#define REBOOT_HEIGHT_SPRITE 80
//Les paramètres du bouton ouvrir/sauvegarder
#define OUVRIR_X 30
#define OUVRIR_Y 15
#define SAUVEGARDER_X 150
#define SAUVEGARDER_Y 15
#define OUVRIR_SAUVEGARDER_WIDTH 64
#define OUVRIR_SAUVEGARDER_HEIGHT 64
//Les paramètres du bouton run/cancel
#define RUN_CANCEL_X 15
#define RUN_CANCEL_Y 700
#define RUN_CANCEL_WIDTH 110
#define RUN_CANCEL_HEIGHT 110
//Les paramètres du bouton reboot
#define REBOOT_X 140
#define REBOOT_Y 715
#define REBOOT_WIDTH 100
#define REBOOT_HEIGHT 80
//Les paramètres du bouton plus/moins
#define PLUS_MOINS_WIDTH 100
#define PLUS_MOINS_HEIGHT 92
#define PLUS_X 130
#define PLUS_Y 600
#define MOINS_X 20
#define MOINS_Y 600
//Les paramètres des boutons de débit
#define DEBIT_WIDTH 100
#define DEBIT_HEIGHT 100
#define DEBIT_10_X 20
#define DEBIT_10_Y 200
#define DEBIT_100_X 20
#define DEBIT_100_Y 310
#define DEBIT_1000_X 20
#define DEBIT_1000_Y 420
//Les paramètres des boutons de taille
#define TAILLE_WIDTH 100
#define TAILLE_HEIGHT 100
#define TAILLE_10_X 130
#define TAILLE_10_Y 200
#define TAILLE_100_X 130
#define TAILLE_100_Y 310
#define TAILLE_1000_X 130
#define TAILLE_1000_Y 420
//Définition des positions du PC de départ du hub1
#define PC_DEPART_HUB1_X (HUB1_X+28)
#define PC_DEPART_HUB1_Y 700
//Définition des positions du PC de départ du hub2
#define PC_DEPART_HUB2_X (HUB2_X+28)
#define PC_DEPART_HUB2_Y PC_DEPART_HUB1_Y
//Définition des positions du PC de départ du hub3
#define PC_DEPART_HUB3_X (HUB3_X+28)
#define PC_DEPART_HUB3_Y 30
//Définition des positions du hub1
#define HUB1_X 530
#define HUB1_Y 450
//Définition des positions du hub2
#define HUB2_X (HUB1_X+600)
#define HUB2_Y HUB1_Y
//Définition des positions du hub3
#define HUB3_X ((HUB2_X+HUB1_X)/2)
#define HUB3_Y 300
//Définition des positions des messages
#define MESSAGE_RECEPTION_X 275
#define MESSAGE_RECEPTION_Y 300
#define MESSAGE_OK_X 275
#define MESSAGE_OK_Y 380
#define MESSAGE_TEMPS_X 275
#define MESSAGE_TEMPS_Y 340
void init_position(SDL_Rect* positionFond,SDL_Rect* positionInfo,SDL_Rect* positionInfoOk,SDL_Rect* positionTemps,SDL_Rect* positionPC_hub1,SDL_Rect* positionPC_hub2,
              SDL_Rect* positionPC_hub3,SDL_Rect* positionHub1,SDL_Rect* positionHub2,SDL_Rect* positionHub3,SDL_Rect* positionRunCancel);

void init_sprite(SDL_Rect* ouvrir_sauvegarder_sprite,SDL_Rect* run_cancel_sprite,SDL_Rect* debit_sprite,SDL_Rect* taille_sprite,SDL_Rect* reboot_sprite,SDL_Rect* plus_moins_sprite);

void init_charger_images(SDL_Surface **imageDeFond, SDL_Surface **PC, SDL_Surface **hub, SDL_Surface **run,SDL_Surface **debit ,SDL_Surface **taille, SDL_Surface **plus_moins,
                    SDL_Surface **effacer_PC, SDL_Surface **ouvrir_sauvegarder,SDL_Surface **PC_source,SDL_Surface **PC_destination, SDL_Surface **reboot,
                    SDL_Surface **image_sauvegarde, SDL_Surface **message);

void init_blitter_images(SDL_Surface **ecran,SDL_Surface **imageDeFond, SDL_Surface **PC, SDL_Surface **hub, SDL_Rect *positionFond, SDL_Rect *positionPC_hub1,
                    SDL_Rect *positionPC_hub2, SDL_Rect *positionPC_hub3, SDL_Rect *positionHub1, SDL_Rect *positionHub2, SDL_Rect *positionHub3);

void init_tracer_lignes(SDL_Surface **ecran,SDL_Rect* positionPC_hub1,SDL_Rect* positionPC_hub2,SDL_Rect* positionPC_hub3,SDL_Rect positionHub1,
                        SDL_Rect positionHub2,SDL_Rect positionHub3, SDL_Surface** PC, SDL_Surface** hub);

void init_blitter_boutons(SDL_Surface **ecran,SDL_Surface **run,SDL_Rect *run_cancel_sprite,SDL_Surface **debit,SDL_Rect *debit_sprite,SDL_Surface **taille,SDL_Rect *taille_sprite,
                SDL_Surface **plus_moins,SDL_Rect *plus_moins_sprite,SDL_Surface **ouvrir_sauvegarder,SDL_Rect *ouvrir_sauvegarder_sprite,SDL_Surface **reboot,SDL_Rect *reboot_sprite);

void sauvReseau(SDL_Rect *positionPC_hub1,
                SDL_Rect *positionPC_hub2,
                SDL_Rect *positionPC_hub3,
                int nombre_PC_hub1,
                int nombre_PC_hub2,
                int nombre_PC_hub3,
                int nombre_PC_selec,
                int PC_hub1_selec_source,
                int PC_hub2_selec_source,
                int PC_hub3_selec_source,
                int PC_hub1_selec_destination,
                int PC_hub2_selec_destination,
                int PC_hub3_selec_destination,
                int indice_PC_hub1_selec_source,
                int indice_PC_hub2_selec_source,
                int indice_PC_hub3_selec_source,
                int indice_PC_hub1_selec_destination,
                int indice_PC_hub2_selec_destination,
                int indice_PC_hub3_selec_destination);

void ouvrirReseau(SDL_Rect *positionPC_hub1,
                SDL_Rect *positionPC_hub2,
                SDL_Rect *positionPC_hub3,
                int *nombre_PC_hub1,
                int *nombre_PC_hub2,
                int *nombre_PC_hub3,
                int *nombre_PC_selec,
                int *PC_hub1_selec_source,
                int *PC_hub2_selec_source,
                int *PC_hub3_selec_source,
                int *PC_hub1_selec_destination,
                int *PC_hub2_selec_destination,
                int *PC_hub3_selec_destination,
                int *indice_PC_hub1_selec_source,
                int *indice_PC_hub2_selec_source,
                int *indice_PC_hub3_selec_source,
                int *indice_PC_hub1_selec_destination,
                int *indice_PC_hub2_selec_destination,
                int *indice_PC_hub3_selec_destination);

#endif
