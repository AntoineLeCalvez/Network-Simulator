/*!
 * \file    commun.c
 * \brief   Fonctions d'initialisation des positions, fils, chargement des images, sauvegarde et ouverture de réseau
 * \author  Valentin Caillard & Domitille Buttin & Antoine Le Calvez & Thibault Perel
 * \date 18/03/2015
 */

#include "commun.h"

//Initialisation des positions du Fond, des hubs, des PC initiaux, et des messages d'information
void init_position(SDL_Rect* positionFond,SDL_Rect* positionInfo,SDL_Rect* positionInfoOk,SDL_Rect* positionTemps,SDL_Rect* positionPC_hub1,SDL_Rect* positionPC_hub2,
              SDL_Rect* positionPC_hub3,SDL_Rect* positionHub1,SDL_Rect* positionHub2,SDL_Rect* positionHub3,SDL_Rect* positionRunCancel)
{
    //DEFINITION DES POSITIONS
    //Définition des positions du fond
    (*positionFond).x = 0;
    (*positionFond).y = 0;
    //Définition de la position de l'info
    (*positionInfo).x = MESSAGE_RECEPTION_X;
    (*positionInfo).y = MESSAGE_RECEPTION_Y;
    //Définition de la position de l'infoOk
    (*positionInfoOk).x = MESSAGE_OK_X;
    (*positionInfoOk).y = MESSAGE_OK_Y;
    //Définition de la position du temps
    (*positionTemps).x = MESSAGE_TEMPS_X;
    (*positionTemps).y = MESSAGE_TEMPS_Y;
    //Définition de la position du PC de départ du hub1
    positionPC_hub1[0].x = PC_DEPART_HUB1_X;
    positionPC_hub1[0].y = PC_DEPART_HUB1_Y;
    //Définition de la position du PC de départ du hub2
    positionPC_hub2[0].x = PC_DEPART_HUB2_X;
    positionPC_hub2[0].y = PC_DEPART_HUB2_Y;
    //Définition de la position du PC de départ du hub3
    positionPC_hub3[0].x = PC_DEPART_HUB3_X;
    positionPC_hub3[0].y = PC_DEPART_HUB3_Y;
    //Définition des positions du hub1
    (*positionHub1).x = HUB1_X;
    (*positionHub1).y = HUB1_Y;
    //Définition des positions du hub2
    (*positionHub2).x = HUB2_X;
    (*positionHub2).y = HUB2_Y;
    //Définition des positions du hub3
    (*positionHub3).x = HUB3_X;
    (*positionHub3).y = HUB3_Y;
    //Définition des positions du bouton run/cancel
    (*positionRunCancel).x = RUN_CANCEL_X;
    (*positionRunCancel).y = RUN_CANCEL_Y;
    (*positionRunCancel).h = RUN_CANCEL_HEIGHT;
    (*positionRunCancel).w = RUN_CANCEL_WIDTH;
//FIN DEFINITION DES POSITIONS
}

//Initialisation des sprites
void init_sprite(SDL_Rect* ouvrir_sauvegarder_sprite,SDL_Rect* run_cancel_sprite,SDL_Rect* debit_sprite,SDL_Rect* taille_sprite,SDL_Rect* reboot_sprite,SDL_Rect* plus_moins_sprite)
{
    // ouvrir_sauvegarder_sprite : On coupe la partie en haut à gauche (premier sprite = ouvrir non brillant)
    ouvrir_sauvegarder_sprite[ 0 ].x = 0;
    ouvrir_sauvegarder_sprite[ 0 ].y = 0;
    ouvrir_sauvegarder_sprite[ 0 ].w = OUVRIR_SAUVEGARDER_WIDTH_SPRITE/2;
    ouvrir_sauvegarder_sprite[ 0 ].h = OUVRIR_SAUVEGARDER_HEIGHT_SPRITE/2;
    // ouvrir_sauvegarder_sprite : On coupe la partie en haut à droite (deuxième sprite = sauvegarder non brillant)
    ouvrir_sauvegarder_sprite[ 1 ].x = OUVRIR_SAUVEGARDER_WIDTH_SPRITE/2;
    ouvrir_sauvegarder_sprite[ 1 ].y = 0;
    ouvrir_sauvegarder_sprite[ 1 ].w = OUVRIR_SAUVEGARDER_WIDTH_SPRITE/2;
    ouvrir_sauvegarder_sprite[ 1 ].h = OUVRIR_SAUVEGARDER_HEIGHT_SPRITE/2;
    // ouvrir_sauvegarder_sprite : On coupe la partie en bas à gauche (troisième sprite = ouvrir brillant)
    ouvrir_sauvegarder_sprite[ 2 ].x = 0;
    ouvrir_sauvegarder_sprite[ 2 ].y = OUVRIR_SAUVEGARDER_HEIGHT_SPRITE/2;
    ouvrir_sauvegarder_sprite[ 2 ].w = OUVRIR_SAUVEGARDER_WIDTH_SPRITE/2;
    ouvrir_sauvegarder_sprite[ 2 ].h = OUVRIR_SAUVEGARDER_HEIGHT_SPRITE/2;
    // ouvrir_sauvegarder_sprite : On coupe la partie en bas à droite (quatrième sprite = sauvegarder brillant)
    ouvrir_sauvegarder_sprite[ 3 ].x = OUVRIR_SAUVEGARDER_WIDTH_SPRITE/2;
    ouvrir_sauvegarder_sprite[ 3 ].y = OUVRIR_SAUVEGARDER_HEIGHT_SPRITE/2;
    ouvrir_sauvegarder_sprite[ 3 ].w = OUVRIR_SAUVEGARDER_WIDTH_SPRITE/2;
    ouvrir_sauvegarder_sprite[ 3 ].h = OUVRIR_SAUVEGARDER_HEIGHT_SPRITE/2;
    // run_cancel_sprite : On coupe la partie en haut à gauche (bouton run)
    run_cancel_sprite[ 0 ].x = 0;
    run_cancel_sprite[ 0 ].y = 0;
    run_cancel_sprite[ 0 ].w = RUN_CANCEL_WIDTH_SPRITE/2;
    run_cancel_sprite[ 0 ].h = RUN_CANCEL_HEIGHT_SPRITE;
    //run_cancel_sprite : On coupe la partie en haut à droite (bouton cancel)
    run_cancel_sprite[ 1 ].x = RUN_CANCEL_WIDTH_SPRITE/2;
    run_cancel_sprite[ 1 ].y = 0;
    run_cancel_sprite[ 1 ].w = RUN_CANCEL_WIDTH_SPRITE/2;
    run_cancel_sprite[ 1 ].h = RUN_CANCEL_HEIGHT_SPRITE;
    //debit_sprite : On coupe la partie en haut à gauche (premier sprite = 10 vert)
    debit_sprite[ 0 ].x = 0;
    debit_sprite[ 0 ].y = 0;
    debit_sprite[ 0 ].w = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 0 ].h = DEBIT_HEIGHT_SPRITE/3;
    //debit_sprite : On coupe la partie en haut à droite (deuxième sprite = 10 rouge)
    debit_sprite[ 1 ].x = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 1 ].y = 0;
    debit_sprite[ 1 ].w = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 1 ].h = DEBIT_HEIGHT_SPRITE/3;
    //debit_sprite : On coupe la partie au milieu à gauche (troisième sprite = 100 vert)
    debit_sprite[ 2 ].x = 0;
    debit_sprite[ 2 ].y = DEBIT_HEIGHT_SPRITE/3;
    debit_sprite[ 2 ].w = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 2 ].h = DEBIT_HEIGHT_SPRITE/3;
    //debit_sprite : On coupe la partie au milieu à droite (quatrième sprite = 100 rouge)
    debit_sprite[ 3 ].x = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 3 ].y = DEBIT_HEIGHT_SPRITE/3;
    debit_sprite[ 3 ].w = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 3 ].h = DEBIT_HEIGHT_SPRITE/3;
    //debit_sprite : On coupe la partie en bas à gauche (cinquième sprite = 1000 vert)
    debit_sprite[ 4 ].x = 0;
    debit_sprite[ 4 ].y = 2*DEBIT_HEIGHT_SPRITE/3;
    debit_sprite[ 4 ].w = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 4 ].h = DEBIT_HEIGHT_SPRITE/3;
    //debit_sprite : On coupe la partie en bas à droite (sixième sprite = 1000 rouge)
    debit_sprite[ 5 ].x = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 5 ].y = 2*DEBIT_HEIGHT_SPRITE/3;
    debit_sprite[ 5 ].w = DEBIT_WIDTH_SPRITE/2;
    debit_sprite[ 5 ].h = DEBIT_HEIGHT_SPRITE/3;
    //taille_sprite : On coupe la partie en haut à gauche (premier sprite = 10 vert)
    taille_sprite[ 0 ].x = 0;
    taille_sprite[ 0 ].y = 0;
    taille_sprite[ 0 ].w = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 0 ].h = TAILLE_HEIGHT_SPRITE/3;
    //taille_sprite : On coupe la partie en haut à droite (deuxième sprite = 10 rouge)
    taille_sprite[ 1 ].x = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 1 ].y = 0;
    taille_sprite[ 1 ].w = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 1 ].h = TAILLE_HEIGHT_SPRITE/3;
    //taille_sprite : On coupe la partie au milieu à gauche (troisième sprite = 100 vert)
    taille_sprite[ 2 ].x = 0;
    taille_sprite[ 2 ].y = TAILLE_HEIGHT_SPRITE/3;
    taille_sprite[ 2 ].w = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 2 ].h = TAILLE_HEIGHT_SPRITE/3;
    //taille_sprite : On coupe la partie au milieu à droite (quatrième sprite = 100 rouge)
    taille_sprite[ 3 ].x = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 3 ].y = TAILLE_HEIGHT_SPRITE/3;
    taille_sprite[ 3 ].w = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 3 ].h = TAILLE_HEIGHT_SPRITE/3;
    //taille_sprite : On coupe la partie en bas à gauche (cinquième sprite = 1000 vert)
    taille_sprite[ 4 ].x = 0;
    taille_sprite[ 4 ].y = 2*TAILLE_HEIGHT_SPRITE/3;
    taille_sprite[ 4 ].w = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 4 ].h = TAILLE_HEIGHT_SPRITE/3;
    //taille_sprite : On coupe la partie en bas à droite (sixième sprite = 1000 rouge)
    taille_sprite[ 5 ].x = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 5 ].y = 2*TAILLE_HEIGHT_SPRITE/3;
    taille_sprite[ 5 ].w = TAILLE_WIDTH_SPRITE/2;
    taille_sprite[ 5 ].h = TAILLE_HEIGHT_SPRITE/3;
    //plus_moins_sprite : On coupe la partie en haut à gauche (premier sprite = plus pas brillant)
    plus_moins_sprite[ 0 ].x = 0;
    plus_moins_sprite[ 0 ].y = 0;
    plus_moins_sprite[ 0 ].w = PLUS_MOINS_WIDTH_SPRITE/2;
    plus_moins_sprite[ 0 ].h = PLUS_MOINS_HEIGHT_SPRITE/2;
    //plus_moins_sprite : On coupe la partie en haut à droite (deuxième sprite = moins pas brillant)
    plus_moins_sprite[ 1 ].x = PLUS_MOINS_WIDTH_SPRITE/2;
    plus_moins_sprite[ 1 ].y = 0;
    plus_moins_sprite[ 1 ].w = PLUS_MOINS_WIDTH_SPRITE/2;
    plus_moins_sprite[ 1 ].h = PLUS_MOINS_HEIGHT_SPRITE/2;
    //plus_moins_sprite : On coupe la partie en bas à gauche (troisième sprite = plus brillant)
    plus_moins_sprite[ 2 ].x = 0;
    plus_moins_sprite[ 2 ].y = PLUS_MOINS_HEIGHT_SPRITE/2;
    plus_moins_sprite[ 2 ].w = PLUS_MOINS_WIDTH_SPRITE/2;
    plus_moins_sprite[ 2 ].h = PLUS_MOINS_HEIGHT_SPRITE/2;
    //plus_moins_sprite : On coupe la partie en bas à droite (quatrième sprite = moins brillant)
    plus_moins_sprite[ 3 ].x = PLUS_MOINS_WIDTH_SPRITE/2;
    plus_moins_sprite[ 3 ].y = PLUS_MOINS_HEIGHT_SPRITE/2;
    plus_moins_sprite[ 3 ].w = PLUS_MOINS_WIDTH_SPRITE/2;
    plus_moins_sprite[ 3 ].h = PLUS_MOINS_HEIGHT_SPRITE/2;
    //reboot_sprite : On coupe la partie à gauche (premier sprite = reboot non brillant)
    reboot_sprite[ 0 ].x = 0;
    reboot_sprite[ 0 ].y = 0;
    reboot_sprite[ 0 ].w = REBOOT_WIDTH_SPRITE/2;
    reboot_sprite[ 0 ].h = REBOOT_HEIGHT_SPRITE;
    //reboot_sprite : On coupe la partie à droite (deuxième sprite = reboot brillant)
    reboot_sprite[ 1 ].x = REBOOT_WIDTH_SPRITE/2;
    reboot_sprite[ 1 ].y = 0;
    reboot_sprite[ 1 ].w = REBOOT_WIDTH_SPRITE/2;
    reboot_sprite[ 1 ].h = REBOOT_HEIGHT_SPRITE;
}

//Chargement des images
void init_charger_images(SDL_Surface **imageDeFond, SDL_Surface **PC, SDL_Surface **hub, SDL_Surface **run,SDL_Surface **debit ,SDL_Surface **taille, SDL_Surface **plus_moins,
                    SDL_Surface **effacer_PC, SDL_Surface **ouvrir_sauvegarder,SDL_Surface **PC_source,SDL_Surface **PC_destination, SDL_Surface **reboot,
                    SDL_Surface **image_sauvegarde, SDL_Surface **message)
{
    *imageDeFond = IMG_Load("fond.png");
    *PC = IMG_Load("pc.png");
    *hub = IMG_Load("hub.png");
    *run = IMG_Load("run.png");
    *debit = IMG_Load("debit.png");
    *taille = IMG_Load("taille.png");
    *plus_moins = IMG_Load("plus_moins.png");
    *effacer_PC = IMG_Load("effacer_PC.png");
    *ouvrir_sauvegarder = IMG_Load("ouvrir_sauvegarder.png");
    //PC source = vert
    *PC_source = IMG_Load("pc_source.png");
    //PC destination = rouge
    *PC_destination = IMG_Load("pc_destination.png");
    //Pour le bouton reboot
    *reboot = IMG_Load("reboot.png");
    //Pour la sauvegarder
    *image_sauvegarde = IMG_Load("image_sauvegarde.png");
    //Pour l'envoi de message
    *message = IMG_Load("message.png");
}

//Blitter images de base
void init_blitter_images(SDL_Surface **ecran,SDL_Surface **imageDeFond, SDL_Surface **PC, SDL_Surface **hub, SDL_Rect *positionFond, SDL_Rect *positionPC_hub1,
                    SDL_Rect *positionPC_hub2, SDL_Rect *positionPC_hub3, SDL_Rect *positionHub1, SDL_Rect *positionHub2, SDL_Rect *positionHub3)
{
    SDL_BlitSurface(*imageDeFond, NULL, *ecran,positionFond);
    SDL_BlitSurface(*PC,NULL,*ecran,&positionPC_hub1[0]);
    SDL_BlitSurface(*PC,NULL,*ecran,&positionPC_hub2[0]);
    SDL_BlitSurface(*PC,NULL,*ecran,&positionPC_hub3[0]);
    SDL_BlitSurface(*hub,NULL,*ecran,positionHub1);
    SDL_BlitSurface(*hub,NULL,*ecran,positionHub2);
    SDL_BlitSurface(*hub,NULL,*ecran,positionHub3);
}

//Tracer des lignes de base
void init_tracer_lignes(SDL_Surface **ecran,SDL_Rect* positionPC_hub1,SDL_Rect* positionPC_hub2,SDL_Rect* positionPC_hub3,SDL_Rect positionHub1,
                   SDL_Rect positionHub2,SDL_Rect positionHub3, SDL_Surface** PC, SDL_Surface** hub)
{
    //Entre le PC du hub 1 et le hub 1
    drawLine(*ecran,positionPC_hub1[0].x + (*PC)->w/2,positionPC_hub1[0].y,positionHub1.x + (*hub)->w/2,positionHub1.y + (*hub)->h,0,0,0);
    //Entre le PC du hub 2 et le hub 2
    drawLine(*ecran,positionPC_hub2[0].x + (*PC)->w/2,positionPC_hub2[0].y,positionHub2.x + (*hub)->w/2,positionHub2.y + (*hub)->h,0,0,0);
    //Entre le PC du hub 3 et le hub 3
    drawLine(*ecran,positionPC_hub3[0].x + (*PC)->w/2,positionPC_hub3[0].y + (*PC)->h,positionHub3.x + (*hub)->w/2,positionHub3.y,0,0,0);
    //Entre le hub 1 et le hub 2
    drawLine(*ecran,positionHub1.x + (*hub)->w,positionHub1.y + (*hub)->h/2,positionHub2.x,positionHub2.y + (*hub)->h/2,0,0,0);
    //Entre le hub 1 et le hub 3
    drawLine(*ecran,positionHub1.x + (*hub)->w,positionHub1.y + (*hub)->h/2,positionHub3.x + (*hub)->w/2,positionHub3.y + (*hub)->h,0,0,0);
    //Entre le hub 2 et le hub 3
    drawLine(*ecran,positionHub3.x + (*hub)->w/2,positionHub3.y + (*hub)->h,positionHub2.x,positionHub2.y + (*hub)->h/2,0,0,0);//
}

//On affiche les boutons
void init_blitter_boutons(SDL_Surface **ecran,SDL_Surface **run,SDL_Rect *run_cancel_sprite,SDL_Surface **debit,SDL_Rect *debit_sprite,SDL_Surface **taille,SDL_Rect *taille_sprite,
                SDL_Surface **plus_moins,SDL_Rect *plus_moins_sprite,SDL_Surface **ouvrir_sauvegarder,SDL_Rect *ouvrir_sauvegarder_sprite,SDL_Surface **reboot,SDL_Rect *reboot_sprite)
{
    //Bouton RUN: par défaut le bouton est vert
    apply_surface( RUN_CANCEL_X, RUN_CANCEL_Y, *run, *ecran, &run_cancel_sprite[ 0 ] );
    //Les débits : par défaut, on met le débit à 10
    apply_surface( DEBIT_10_X, DEBIT_10_Y, *debit, *ecran, &debit_sprite[ 0 ]);
    apply_surface( DEBIT_100_X, DEBIT_100_Y, *debit, *ecran, &debit_sprite[ 3 ]);
    apply_surface( DEBIT_1000_X, DEBIT_1000_Y, *debit, *ecran, &debit_sprite[ 5 ]);
    //Les débits : par défaut, on met la taille à 10
    apply_surface( TAILLE_10_X, TAILLE_10_Y, *taille, *ecran, &taille_sprite[ 0 ]);
    apply_surface( TAILLE_100_X, TAILLE_100_Y, *taille, *ecran, &taille_sprite[ 3 ]);
    apply_surface( TAILLE_1000_X, TAILLE_1000_Y, *taille, *ecran, &taille_sprite[ 5 ]);
    //Bouton +
    apply_surface(PLUS_X, PLUS_Y,*plus_moins, *ecran,&plus_moins_sprite[ 0 ]);
    //Bouton -
    apply_surface(MOINS_X, MOINS_Y,*plus_moins, *ecran,&plus_moins_sprite[ 1 ]);
    //Bouton ouvrir non surbrilliant
    apply_surface(OUVRIR_X, OUVRIR_Y,*ouvrir_sauvegarder, *ecran,&ouvrir_sauvegarder_sprite[ 0 ]);
    //Bouton sauvegarder non surbrilliant
    apply_surface(SAUVEGARDER_X, SAUVEGARDER_Y,*ouvrir_sauvegarder, *ecran,&ouvrir_sauvegarder_sprite[ 1 ]);
    //Bouton reboot non surbrilliant
    apply_surface(REBOOT_X, REBOOT_Y,*reboot, *ecran,&reboot_sprite[ 0 ]);
}

//Fonction sauvegarde réseau
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
                int indice_PC_hub3_selec_destination){
    FILE *f = NULL;
    //Ouverture du fichier de sauvegarde
    if((f = fopen("sauvreseau.dat" , "w+")) == (FILE*) NULL)
    {
        printf("Erreur a l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    fwrite(&nombre_PC_hub1 , sizeof(int) , 1 , f);
    fwrite(positionPC_hub1 , sizeof(SDL_Rect) , 4 , f);
    fwrite(&nombre_PC_hub2 , sizeof(int) , 1 , f);
    fwrite(positionPC_hub2 , sizeof(SDL_Rect) , 4 , f);
    fwrite(&nombre_PC_hub3 , sizeof(int) , 1 , f);
    fwrite(positionPC_hub3 , sizeof(SDL_Rect) , 4 , f);
    fwrite(&PC_hub1_selec_source , sizeof(int) , 1 , f);
    fwrite(&PC_hub2_selec_source , sizeof(int) , 1 , f);
    fwrite(&PC_hub3_selec_source , sizeof(int) , 1 , f);
    fwrite(&PC_hub1_selec_destination , sizeof(int) , 1 , f);
    fwrite(&PC_hub2_selec_destination , sizeof(int) , 1 , f);
    fwrite(&PC_hub3_selec_destination , sizeof(int) , 1 , f);
    fwrite(&indice_PC_hub1_selec_source , sizeof(int) , 1 , f);
    fwrite(&indice_PC_hub2_selec_source , sizeof(int) , 1 , f);
    fwrite(&indice_PC_hub3_selec_source , sizeof(int) , 1 , f);
    fwrite(&indice_PC_hub1_selec_destination , sizeof(int) , 1 , f);
    fwrite(&indice_PC_hub2_selec_destination , sizeof(int) , 1 , f);
    fwrite(&indice_PC_hub3_selec_destination , sizeof(int) , 1 , f);
    fwrite(&nombre_PC_selec , sizeof(int) , 1 , f);
    //On ferme le fichier de sauvegarde
    fclose(f);
}
//Fonction ouverture réseau
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
                int *indice_PC_hub3_selec_destination){

    FILE *f = NULL;
    //    //Ouverture du fichier de sauvegarde
    if((f = fopen("sauvreseau.dat" , "rb")) == (FILE*) NULL)
    {
        printf("Erreur a l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    fread(nombre_PC_hub1 , sizeof(int) , 1 , f);
    fread(positionPC_hub1 , sizeof(SDL_Rect) , 4 , f);
    fread(nombre_PC_hub2 , sizeof(int) , 1 , f);
    fread(positionPC_hub2 , sizeof(SDL_Rect) , 4 , f);
    fread(nombre_PC_hub3 , sizeof(int) , 1 , f);
    fread(positionPC_hub3 , sizeof(SDL_Rect) , 4 , f);
    fread(PC_hub1_selec_source , sizeof(int) , 1 , f);
    fread(PC_hub2_selec_source , sizeof(int) , 1 , f);
    fread(PC_hub3_selec_source , sizeof(int) , 1 , f);
    fread(PC_hub1_selec_destination , sizeof(int) , 1 , f);
    fread(PC_hub2_selec_destination , sizeof(int) , 1 , f);
    fread(PC_hub3_selec_destination , sizeof(int) , 1 , f);
    fread(indice_PC_hub1_selec_source , sizeof(int) , 1 , f);
    fread(indice_PC_hub2_selec_source , sizeof(int) , 1 , f);
    fread(indice_PC_hub3_selec_source , sizeof(int) , 1 , f);
    fread(indice_PC_hub1_selec_destination , sizeof(int) , 1 , f);
    fread(indice_PC_hub2_selec_destination , sizeof(int) , 1 , f);
    fread(indice_PC_hub3_selec_destination , sizeof(int) , 1 , f);
    fread(nombre_PC_selec , sizeof(int) , 1 , f);
    //On ferme le fichier de sauvegarde
    fclose(f);
}
