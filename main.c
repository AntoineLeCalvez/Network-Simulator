/*!
 * \file    main.c
 * \brief   Fonction principale (d�clarations des variables, initialisations et d�roulement du programme selon les �v�nements)
 * \author  Valentin Caillard & Domitille Buttin & Antoine Le Calvez & Thibault Perel
 * \date 18/03/2015
 */

#include "commun.h"
#include "geometrie.h"
#include <SDL/SDL_ttf.h>

int main(int argc, char *argv[])
{
    //Autorisation de l'utilisation de la console
    freopen("CON","w",stdout);
    freopen("CON","r",stdin);
    freopen("CON","w",stderr);
    //Les surfaces
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *PC = NULL, *effacer_PC = NULL, *icone = NULL, *ouvrir_sauvegarder = NULL, *reboot = NULL, *message = NULL, *image_actualise_sans_message = NULL, *texte = NULL, *texteOk = NULL;
    SDL_Surface *hub = NULL, *run = NULL, *debit = NULL, *taille = NULL, *plus_moins = NULL, *PC_source = NULL,*PC_destination = NULL, *image_sauvegarde = NULL, *image_actualise = NULL, *texteTemps = NULL;
    //La structure d'�v�nements
    SDL_Event event;
    //Position des images qui ne bougent jamais : les hubs et le fond||Position des images qui changent : Run/Cancel et le message
    SDL_Rect positionFond, positionHub1, positionHub2, positionHub3, positionRunCancel, positionMessage;
    //Tableaux de positions des PC pour le hub1, le hub2, le hub3, feuille de sprite pour le run_cancel, ouvrir_sauvegarder, d�bits,
    SDL_Rect positionPC_hub1 [ 4 ], positionPC_hub2 [ 4 ], positionPC_hub3 [ 4 ], run_cancel_sprite[ 2 ], ouvrir_sauvegarder_sprite[ 4 ], debit_sprite[ 6 ],
    //Nombre de paquets � envoyer, boutons + -, reboot, Position du texte d'information, Coordonn�es du clic
    taille_sprite[ 6 ], plus_moins_sprite[ 4 ], reboot_sprite[ 2 ], positionInfo, positionInfoOk, position_clic, positionTemps;
    //Initialisation pour l'al�atoire
    srand(time(NULL));
    //VARIABLES ENTIERES
    //Arr�t de la boucle d'�v�nements, Pour le parcours des boucles for, Pour sortir plus vite des boucles quand un �l�ment est trouv�
    int continuer = 1, i = 0, trouve = 0;
    //Pour caract�riser le nombre de PC par hub
    int nombre_PC_hub1 = 1, nombre_PC_hub2 = 1, nombre_PC_hub3 = 1;
    //Pour savoir si le bouton + est activ�, le bouton - est activ�, le bouton ouvrir a �t� cliqu�, le bouton sauvegarder a �t� cliqu�, le bouton reboot a �t� cliqu�
    int bouton_plus = 0, bouton_moins = 0, bouton_ouvrir = 0, bouton_sauvegarder = 0, bouton_reboot = 0;
    //Pour savoir quel d�bit est choisi par l'utilisateur, quelle taille est choisie (nombre de paquets envoy�s), copier cette taille et la d�cr�menter pour la boucle d'envoi de plusieurs paquets
    int debit_choisi = 10, taille_choisi = 1, copie_taille = 0;
    //Si run_ok = 1, bouton run || si run_ok = 0, bouton cancel, Pour la vitesse, Pour savoir combien de PC ont �t� s�lectionn�s
    int run_ok = 1, vitesse = 1, nombre_PC_selec = 0;
    //Pour savoir si un pc source fait partie d'un hub
    int PC_hub1_selec_source = 0, PC_hub2_selec_source = 0, PC_hub3_selec_source = 0;
    //Pour savoir si un pc destination fait partie d'un hub
    int PC_hub1_selec_destination = 0, PC_hub2_selec_destination = 0, PC_hub3_selec_destination = 0;
    //Pour savoir l'indice du PC source s�lectionn�
    int indice_PC_hub1_selec_source = -1, indice_PC_hub2_selec_source = -1, indice_PC_hub3_selec_source = -1;
    //Pour savoir l'indice du PC destination s�lectionn�
    int indice_PC_hub1_selec_destination = -1, indice_PC_hub2_selec_destination = -1, indice_PC_hub3_selec_destination = -1;
    //Variables pour le calcul du temps d'envoi
    clock_t temps;
    double temps_envoi;
    char str[20];
    //Variable pour d�tecter quand l'envoi est termin� et qu'il faut calculer le temps d'envoi
    int envoi_termine = 0;
    //DECOUPAGE DES SPRITES
    init_sprite(ouvrir_sauvegarder_sprite,run_cancel_sprite,debit_sprite,taille_sprite,reboot_sprite,plus_moins_sprite);
    //Initialisation des positions
    init_position(&positionFond,&positionInfo,&positionInfoOk,&positionTemps,positionPC_hub1,positionPC_hub2,positionPC_hub3,&positionHub1,&positionHub2,&positionHub3,&positionRunCancel);
    //Initialisation de SDL
    if(SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    //Initialisation de TTF
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    //Icone de la fenetre
    icone = IMG_Load("icone.png");
    SDL_WM_SetIcon(icone, NULL);
    //Param�tres de la fen�tre
    ecran = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE | SDL_RESIZABLE);
    SDL_WM_SetCaption("Network simulator", NULL); //Nom de la fen�tre
    //D�finition des caracteristiques des informations
    TTF_Font *police = NULL;
    police = TTF_OpenFont("monofonto.ttf", 40);
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurOk = {13,221,18};
    //Chargement des images
    init_charger_images(&imageDeFond,&PC,&hub,&run,&debit,&taille,&plus_moins,&effacer_PC,&ouvrir_sauvegarder,&PC_source,&PC_destination,&reboot,&image_sauvegarde,&message);
    //Affichage des �l�ments de base (hub, fond, PC initiaux)
    init_blitter_images(&ecran,&imageDeFond,&PC,&hub,&positionFond,positionPC_hub1,positionPC_hub2,positionPC_hub3,&positionHub1,&positionHub2,&positionHub3);
    //Tracer les lignes
    init_tracer_lignes(&ecran,positionPC_hub1,positionPC_hub2,positionPC_hub3,positionHub1,positionHub2,positionHub3,&PC,&hub);
    //Affichage des boutons
    init_blitter_boutons(&ecran,&run,run_cancel_sprite,&debit,debit_sprite,&taille,taille_sprite,&plus_moins,plus_moins_sprite,&ouvrir_sauvegarder,ouvrir_sauvegarder_sprite,
                         &reboot,reboot_sprite);

//Raffraichissement de l'�cran
    SDL_Flip(ecran);
//FIN DES INITIALISATIONS
    //Fonction principale de gestion des �v�nements
    while (continuer)
    {//Tant que l'utilisateur veut continuer (pas de clic sur la croix rouge)
        //On attend un �v�nement
        SDL_WaitEvent(&event);
        switch(event.type)
        {

            //Si l'utilisateur clique sur la croix rouge
            case SDL_QUIT:
                //Mise � 0 de la variable de la boucle
                continuer = 0;
                break;

            //Si l'utilisateur clique sur un bouton de la souris
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {//Si l'�v�nement est un clic gauche
                    //R�cup�ration des coordonn�es du clic
                    position_clic.x = event.motion.x;
                    position_clic.y = event.motion.y;

                    if (run_ok)
                    {//Si le bouton est sur run
                        if ( position_clic.x > OUVRIR_X && position_clic.x < OUVRIR_X+OUVRIR_SAUVEGARDER_WIDTH && position_clic.y > OUVRIR_Y && position_clic.y < OUVRIR_Y+OUVRIR_SAUVEGARDER_HEIGHT)
                        {//Si on clique sur le bouton ouvrir
                            //On met en surbrilliance le bouton ouvrir
                            apply_surface( OUVRIR_X, OUVRIR_Y, ouvrir_sauvegarder, ecran, &ouvrir_sauvegarder_sprite[ 2 ] );
                            //On indique que le bouton ouvrir a �t� cliqu�
                            bouton_ouvrir = 1;
                        }
                        else if (position_clic.x > SAUVEGARDER_X && position_clic.x < SAUVEGARDER_X+OUVRIR_SAUVEGARDER_WIDTH && position_clic.y > SAUVEGARDER_Y && position_clic.y < SAUVEGARDER_Y+OUVRIR_SAUVEGARDER_HEIGHT)
                        {//Si on clique sur le bouton sauvegarder
                            //On met en surbrillance le bouton sauvegarder
                            apply_surface( SAUVEGARDER_X, SAUVEGARDER_Y, ouvrir_sauvegarder, ecran, &ouvrir_sauvegarder_sprite[ 3 ] );
                            //On indique que le bouton sauvegarder a �t� cliqu�
                            bouton_sauvegarder = 1;
                        }
                        else if ( position_clic.x > RUN_CANCEL_X && position_clic.x < RUN_CANCEL_X+RUN_CANCEL_WIDTH && position_clic.y > RUN_CANCEL_Y && position_clic.y < RUN_CANCEL_Y+RUN_CANCEL_HEIGHT)
                        {//Si ce clic est situ� sur le bouton run
                                //On efface le bouton run
                                SDL_FillRect(ecran,&positionRunCancel,Color(223,223,223));
                                //On place le bouton cancel (qui a le m�me nom car sur la m�me feuille de sprite)
                                apply_surface( RUN_CANCEL_X, RUN_CANCEL_Y, run, ecran, &run_cancel_sprite[ 1 ] );
                                //On indique que le bouton est desormais cancel
                                run_ok = 0;
                                //On sauvegarde l'image, cela servira pour l'envoi du message
                                SDL_SaveBMP(ecran,"image_actualise.bmp");
                                //On charge l'image qu'on vient de sauvegarder, cela servira �galement pour l'envoi de message
                                image_actualise = IMG_Load("image_actualise.bmp");
                                //Utile pour l'envoi de plusieurs messages � la suite en conservant les 1er messages au PC de destination
                                image_actualise_sans_message = IMG_Load("image_actualise.bmp");
                        }
                        else if (position_clic.x > DEBIT_10_X && position_clic.x < DEBIT_10_X+DEBIT_WIDTH && position_clic.y > DEBIT_10_Y && position_clic.y < DEBIT_10_Y+DEBIT_HEIGHT)
                        {// Si le clic est sur le debit 10
                            //On indique le d�bit choisi est 10
                            debit_choisi = 10;
                            //Debit 10 vert
                            apply_surface( DEBIT_10_X, DEBIT_10_Y, debit, ecran, &debit_sprite[ 0 ] );
                            //Debit 100 rouge
                            apply_surface( DEBIT_100_X, DEBIT_100_Y, debit, ecran, &debit_sprite[ 3 ] );
                            //Debit 1000 rouge
                            apply_surface( DEBIT_1000_X, DEBIT_1000_Y, debit, ecran, &debit_sprite[ 5 ] );
                        }
                        else if ( position_clic.x > DEBIT_100_X && position_clic.x < DEBIT_100_X+DEBIT_WIDTH && position_clic.y > DEBIT_100_Y && position_clic.y < DEBIT_100_Y+DEBIT_HEIGHT)
                        {// Si le clic est sur le debit 100
                            //On indique le d�bit choisi est 100
                            debit_choisi = 100;
                            //Debit 10 rouge
                            apply_surface( DEBIT_10_X, DEBIT_10_Y, debit, ecran, &debit_sprite[ 1 ] );
                            //Debit 100 vert
                            apply_surface( DEBIT_100_X, DEBIT_100_Y, debit, ecran, &debit_sprite[ 2 ] );
                            //Debit 1000 rouge
                            apply_surface( DEBIT_1000_X, DEBIT_1000_Y, debit, ecran, &debit_sprite[ 5 ] );
                        }
                        else if ( position_clic.x > DEBIT_1000_X && position_clic.x < DEBIT_1000_X+DEBIT_WIDTH && position_clic.y > DEBIT_1000_Y && position_clic.y < DEBIT_1000_Y+DEBIT_HEIGHT)
                        {// Si le clic est sur le debit 1000
                            //On indique le d�bit choisi est 1000
                            debit_choisi = 1000;
                            //Debit 10 rouge
                            apply_surface( DEBIT_10_X, DEBIT_10_Y, debit, ecran, &debit_sprite[ 1 ] );
                            //Debit 100 rouge
                            apply_surface( DEBIT_100_X, DEBIT_100_Y, debit, ecran, &debit_sprite[ 3 ] );
                            // Debit 1000 vert
                            apply_surface( DEBIT_1000_X, DEBIT_1000_Y, debit, ecran, &debit_sprite[ 4 ] );
                        }
                        else if ( position_clic.x > TAILLE_10_X && position_clic.x < TAILLE_10_X+TAILLE_WIDTH && position_clic.y > TAILLE_10_Y && position_clic.y < TAILLE_10_Y+TAILLE_HEIGHT)
                        {// Si le clic est sur la taille 1
                            //On indique la taille choisie est 1
                            taille_choisi = 1;
                            //Taille 1 vert
                            apply_surface( TAILLE_10_X, TAILLE_10_Y, taille, ecran, &taille_sprite[ 0 ] );
                            //Taille 2 rouge
                            apply_surface( TAILLE_100_X, TAILLE_100_Y, taille, ecran, &taille_sprite[ 3 ] );
                            //Taille 3 rouge
                            apply_surface( TAILLE_1000_X, TAILLE_1000_Y, taille, ecran, &taille_sprite[ 5 ] );
                        }
                        else if ( position_clic.x > TAILLE_100_X && position_clic.x < TAILLE_100_X+TAILLE_WIDTH && position_clic.y > TAILLE_100_Y && position_clic.y < TAILLE_100_Y+TAILLE_HEIGHT)
                        {// Si le clic est sur la taille 2
                            //On indique la taille choisie est 2
                            taille_choisi = 2;
                            //Taille 1 rouge
                            apply_surface( TAILLE_10_X, TAILLE_10_Y, taille, ecran, &taille_sprite[ 1 ] );
                            //Taille 2 vert
                            apply_surface( TAILLE_100_X, TAILLE_100_Y, taille, ecran, &taille_sprite[ 2 ] );
                            //Taille 3 rouge
                            apply_surface( TAILLE_1000_X, TAILLE_1000_Y, taille, ecran, &taille_sprite[ 5 ] );
                        }
                        else if ( position_clic.x > TAILLE_1000_X && position_clic.x < TAILLE_1000_X+TAILLE_WIDTH && position_clic.y > TAILLE_1000_Y && position_clic.y < TAILLE_1000_Y+TAILLE_HEIGHT)
                        {// Si le clic est sur la taille 3
                            //On indique la taille choisie est 3
                            taille_choisi = 3;
                            //Taille 1 rouge
                            apply_surface( TAILLE_10_X, TAILLE_10_Y, taille, ecran, &taille_sprite[ 1 ] );
                            //Taille 2 rouge
                            apply_surface( TAILLE_100_X, TAILLE_100_Y, taille, ecran, &taille_sprite[ 3 ]) ;
                            //Taille 3 vert
                            apply_surface( TAILLE_1000_X, TAILLE_1000_Y, taille, ecran, &taille_sprite[ 4 ] );
                        }
                        else if ( position_clic.x > PLUS_X && position_clic.x < PLUS_X+PLUS_MOINS_WIDTH && position_clic.y > PLUS_Y && position_clic.y < PLUS_Y+PLUS_MOINS_HEIGHT && nombre_PC_selec==0)
                        {// Si le clic est sur le plus et qu'aucun PC n'est s�lectionn�
                            if(!bouton_plus)
                            {//Si le bouton plus n'�tait pas actif, on l'active
                                //On met le plus surbrillant
                                apply_surface( PLUS_X, PLUS_Y, plus_moins, ecran, &plus_moins_sprite[ 2 ] );
                                //On indique que le bouton est d�sormais cliqu�
                                bouton_plus = 1;
                                if (bouton_moins)
                                {//Si le bouton moins �tait actif, on le d�sactive
                                    //On met le bouton moins non surbrillant
                                    apply_surface( MOINS_X, MOINS_Y, plus_moins, ecran, &plus_moins_sprite[ 1 ] );
                                    //On indique que le bouton moins n'est plus cliqu�
                                    bouton_moins = 0;
                                }
                            }
                            else
                            {//Si le bouton plus �tait cliqu�, on le d�sactive
                                //On met le bouton plus non surbrillant
                                apply_surface( PLUS_X, PLUS_Y, plus_moins, ecran, &plus_moins_sprite[ 0 ] );
                                //On indique que le bouton n'est plus cliqu�
                                bouton_plus = 0;
                            }
                        }
                        else if ( position_clic.x > MOINS_X && position_clic.x < MOINS_X+PLUS_MOINS_WIDTH && position_clic.y > MOINS_Y && position_clic.y < MOINS_Y+PLUS_MOINS_HEIGHT && nombre_PC_selec==0)
                        {// Si le clic est sur le moins et qu'aucun PC n'est s�lectionn�
                            if(!bouton_moins)
                            {//Si le bouton moins n'�tait pas actif, on l'active
                                //On met le bouton moins en surbrillance
                                apply_surface( MOINS_X, MOINS_Y, plus_moins, ecran, &plus_moins_sprite[ 3 ] );
                                //On indique que le bouton moins a �t� cliqu�
                                bouton_moins = 1;
                                if(bouton_plus)
                                {//Si le bouton plus �tait actif, on le d�sactive
                                    //On met le bouton plus non surbrillant
                                    apply_surface( PLUS_X, PLUS_Y, plus_moins, ecran, &plus_moins_sprite[ 0 ] );
                                    bouton_plus = 0;
                                }
                            }
                            else
                            {//Si le bouton moins �tait actif, on le d�sactive
                                //On met le bouton moins non surbrillant
                                apply_surface( MOINS_X, MOINS_Y, plus_moins, ecran, &plus_moins_sprite[ 1 ] );
                                //On indique que le bouton moins n'est plus cliqu�
                                bouton_moins = 0;
                            }

                        }
                        else if ( position_clic.x > REBOOT_X && position_clic.x < REBOOT_X+REBOOT_WIDTH && position_clic.y > REBOOT_Y && position_clic.y < REBOOT_Y+REBOOT_HEIGHT)
                        {//Si le clic est sur le bouton reboot
                            //On met en surbrillance le bouton reboot
                            apply_surface(REBOOT_X, REBOOT_Y,reboot, ecran,&reboot_sprite[ 1 ]);
                            //On indique que le bouton reboot a �t� cliqu�
                            bouton_reboot = 1;
                            //On teste les indices de destination pour d�tecter les PC selectionn�s et on les d�selectionne
                            if(indice_PC_hub1_selec_destination != -1) SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub1[indice_PC_hub1_selec_destination]);
                            else if(indice_PC_hub2_selec_destination != -1) SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub2[indice_PC_hub2_selec_destination]);
                            else if(indice_PC_hub3_selec_destination != -1) SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub3[indice_PC_hub3_selec_destination]);
                            //On teste les indices de source pour d�tecter les PC selectionn�s et on les d�selectionne
                            if(indice_PC_hub1_selec_source != -1) SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub1[indice_PC_hub1_selec_source]);
                            else if(indice_PC_hub2_selec_source != -1) SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub2[indice_PC_hub2_selec_source]);
                            else if(indice_PC_hub3_selec_source != -1) SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub3[indice_PC_hub3_selec_source]);
                            //On reinitialise les variables � leur valeur initiale
                            //Aucun PC selectionn�
                            nombre_PC_selec = 0;
                            //Aucun PC source
                            PC_hub1_selec_source = 0;
                            PC_hub2_selec_source = 0;
                            PC_hub3_selec_source = 0;
                            //Aucun PC destination
                            PC_hub1_selec_destination = 0;
                            PC_hub2_selec_destination = 0;
                            PC_hub3_selec_destination = 0;
                            //Les indices sources � -1 comme dans l'initialisation
                            indice_PC_hub1_selec_source = -1;
                            indice_PC_hub2_selec_source = -1;
                            indice_PC_hub3_selec_source = -1;
                            //Les indices destination � -1 comme dans l'initialisation
                            indice_PC_hub1_selec_destination = -1;
                            indice_PC_hub2_selec_destination = -1;
                            indice_PC_hub3_selec_destination = -1;
                        }
                        else if (position_clic.x > 100 && position_clic.x < 1600 && position_clic.y > 10 && position_clic.y < 250)
                        {//Si le clic a lieu dans la partie haute
                            if (bouton_plus && nombre_PC_hub3 < 4 && nombre_PC_selec==0)
                            {//Si le bouton plus est actif, il y a moins de 4 PC sur le hub3 et aucun PC n'est selectionn� -> AJOUT D'UN PC HUB3
                                //On ajoute un PC � la position du clic
                                SDL_BlitSurface(PC,NULL,ecran,&position_clic);
                                //On dessine le fil vers le hub3
                                drawLine(ecran,position_clic.x + PC->w/2,position_clic.y + PC->h,positionHub3.x + hub->w/2,positionHub3.y,0,0,0);
                                //On remplit le tableau des positions de PC du hub 3
                                positionPC_hub3[nombre_PC_hub3].x = position_clic.x;
                                positionPC_hub3[nombre_PC_hub3].y = position_clic.y;
                                //Incr�mentation du nombre de PC sur le hub3
                                nombre_PC_hub3++;
                            }
                            else if (bouton_moins && nombre_PC_hub3 > 1 && nombre_PC_selec==0)
                            {//Si le bouton moins est actif, que le nombre de PC du hub3 est sup�rieur � 1 et qu'il n'y a pas de PC selectionn� -> SUPPRESSION D'UN PC HUB3
                                //Remise � 0 de l'indicateur
                                trouve = 0;
                                for(i=1;i<=nombre_PC_hub3 && !trouve;i++)
                                {//Boucle pour d�tecter si un PC du hub3 doit �tre supprim� (i commence � 1 pour ne pas supprimer le PC d'initialisation)
                                    if(position_clic.x > positionPC_hub3[i].x && position_clic.x < positionPC_hub3[i].x + PC->w && position_clic.y > positionPC_hub3[i].y && position_clic.y < positionPC_hub3[i].y + PC->h )
                                    {//Si on clique sur un des PC du hub3
                                        //On dessine un trait gris (223,223,223) entre le PC et le hub 3 pour effacer le noir
                                        drawLine(ecran,positionPC_hub3[i].x + PC->w/2,positionPC_hub3[i].y + PC->h,positionHub3.x + hub->w/2,positionHub3.y,223,223,223);
                                        //On met le carr� gris pour effacer l'image du PC
                                        SDL_BlitSurface(effacer_PC,NULL,ecran,&positionPC_hub3[i]);
                                        //Dans le tableau des PC du hub 3, on remplace l'�l�ment qu'on a supprim� par le dernier
                                        positionPC_hub3[i].x=positionPC_hub3[nombre_PC_hub3-1].x;
                                        positionPC_hub3[i].y=positionPC_hub3[nombre_PC_hub3-1].y;
                                        //On decr�mente le nombre de PC sur le hub1
                                        nombre_PC_hub3--;
                                        //On indique qu'on a trouv� le PC correspondant pour sortir plus vite de la boucle
                                        trouve = 1;
                                    }
                                }
                            }
                            else if (nombre_PC_selec < 2)
                            {//Si le nombre de PC s�lectionn� est inf�fieur � 2 -> SELECTION D'UN PC HUB3
                                //Remise � 0 de l'indicateur
                                trouve = 0;
                                for(i=0;i<=nombre_PC_hub3 && !trouve;i++)
                                {//On cherche sur quel PC on a cliqu�
                                    if(position_clic.x > positionPC_hub3[i].x && position_clic.x < positionPC_hub3[i].x + PC->w && position_clic.y > positionPC_hub3[i].y && position_clic.y < positionPC_hub3[i].y + PC->h )
                                    {//Si on clique sur un des PC du hub3
                                        if(!nombre_PC_selec)
                                        {//Si aucun PC n'�tait s�lectionn�
                                            //On met en vert le PC selectionn�
                                            SDL_BlitSurface(PC_source,NULL,ecran,&positionPC_hub3[i]);
                                            //On met � jour les variables, ce PC est donc un PC source
                                            PC_hub3_selec_source = 1;
                                            nombre_PC_selec = 1;
                                            indice_PC_hub3_selec_source = i;
                                        }
                                        else if(nombre_PC_selec==1)
                                        {//Si un PC �tait s�lectionn� auparavant -> selection d'un PC de destination
                                            if(indice_PC_hub3_selec_source!=i)
                                            {//Si le PC cliqu� n'est pas le m�me que celui de selection
                                                //On met en rouge le PC s�lectionn�
                                                SDL_BlitSurface(PC_destination,NULL,ecran,&positionPC_hub3[i]);
                                                //On met � jour les variables, ce PC est une destination
                                                PC_hub3_selec_destination = 1;
                                                //Le nombre de PC selectionn� est maintenant de 2
                                                nombre_PC_selec = 2;
                                                //L'indice du PC de destination du hub 3
                                                indice_PC_hub3_selec_destination = i;
                                            }
                                        }
                                        //On indique qu'on a trouv� le PC correspondant pour sortir plus vite de la boucle
                                        trouve = 1;
                                    }
                                }
                            }
                        }
                        else if (position_clic.x > 200 && position_clic.x < HUB3_X+hub->w/2-PC->w && position_clic.y > 550 && position_clic.y < 750)
                        {//Si le clic a lieu dans la partie en bas � gauche
                            if (bouton_plus && nombre_PC_hub1 < 4 && nombre_PC_selec==0)
                            {//Si le bouton plus est actif, qu'il y a moins de 4 PC ajout�s et qu'aucun PC n'est selectionn� -> AJOUT D'UN PC HUB 1
                                //On ajoute un PC � la position du clic
                                SDL_BlitSurface(PC,NULL,ecran,&position_clic);
                                //On dessine le fil vers le hub1
                                drawLine(ecran,position_clic.x + PC->w/2,position_clic.y ,positionHub1.x + hub->w/2,positionHub1.y + hub->h,0,0,0);
                                //On remplit le tableau des positions de PC
                                positionPC_hub1[nombre_PC_hub1].x = position_clic.x;
                                positionPC_hub1[nombre_PC_hub1].y = position_clic.y;
                                //Incr�mentation du nombre de PC sur le hub1
                                nombre_PC_hub1++;
                            }
                            else if (bouton_moins && nombre_PC_hub1 > 1 && nombre_PC_selec==0)
                            {//Si le bouton moins est actif, que le nombre de PC du hub1 est sup�rieur � 1 et qu'aucun PC n'est selectionn� -> SUPPRESSION D'UN PC HUB 1
                                trouve = 0;
                                for(i=1;i<=nombre_PC_hub1 && !trouve;i++)
                                {//Recherche du PC � supprimer (i commence � 1 pour ne pas supprimer le PC d'initialisation)
                                    if(position_clic.x > positionPC_hub1[i].x && position_clic.x < positionPC_hub1[i].x + PC->w && position_clic.y > positionPC_hub1[i].y && position_clic.y < positionPC_hub1[i].y + PC->h )
                                    {
                                        //Dessine un trait gris pour effacer le noir
                                        drawLine(ecran,positionPC_hub1[i].x + PC->w/2,positionPC_hub1[i].y ,positionHub1.x + hub->w/2,positionHub1.y + hub->h,223,223,223);
                                        //On met le carr� gris pour effacer l'image du PC
                                        SDL_BlitSurface(effacer_PC,NULL,ecran,&positionPC_hub1[i]);
                                        //On remplace l'�l�ment qu'on a supprim� par le dernier
                                        positionPC_hub1[i].x=positionPC_hub1[nombre_PC_hub1-1].x;
                                        positionPC_hub1[i].y=positionPC_hub1[nombre_PC_hub1-1].y;
                                        //On decr�mente le nombre de PC sur le hub1
                                        nombre_PC_hub1--;
                                        //On indique qu'on a trouv� le PC correspondant
                                        trouve = 1;
                                    }
                                }
                            }
                            else if (nombre_PC_selec < 2)
                            {//Si le nombre de PC selectionn� est inf�rieur � 2 -> SELECTION D'UN PC HUB1
                                //On remet � 0 l'indicateur
                                trouve = 0;
                                for(i=0;i<=nombre_PC_hub1 && !trouve;i++)
                                {//On cherche quel PC a �t� cliqu�
                                    if(position_clic.x > positionPC_hub1[i].x && position_clic.x < positionPC_hub1[i].x + PC->w && position_clic.y > positionPC_hub1[i].y && position_clic.y < positionPC_hub1[i].y + PC->h )
                                    {//Si on clique sur un des PC du hub1
                                        if(!nombre_PC_selec)
                                        {//Si aucune PC n'�tait s�lectionn�
                                            //On met en vert ce PC
                                            SDL_BlitSurface(PC_source,NULL,ecran,&positionPC_hub1[i]);
                                            //On met � jour les variables, ce PC est une source
                                            PC_hub1_selec_source = 1;
                                            nombre_PC_selec = 1;
                                            indice_PC_hub1_selec_source = i;
                                        }
                                        else if(nombre_PC_selec==1)
                                        {//Si un PC �tait s�lectionn� avant
                                            if(indice_PC_hub1_selec_source!=i)
                                            {//Si le PC cliqu� n'est pas la source
                                                //On met en rouge ce PC
                                                SDL_BlitSurface(PC_destination,NULL,ecran,&positionPC_hub1[i]);
                                                //On met � jour les variables, Ce PC est une destination
                                                PC_hub1_selec_destination = 1;
                                                nombre_PC_selec = 2;
                                                indice_PC_hub1_selec_destination = i;
                                            }
                                        }
                                        //On indique qu'on a trouv� le PC correspondant
                                        trouve = 1;
                                    }
                                }
                            }

                        }
                        else if (position_clic.x > HUB3_X+hub->w/2 && position_clic.x < 1600 && position_clic.y > 550 && position_clic.y < 750)
                        {//Si le clic a lieu dans la partie en bas � droite
                            if (bouton_plus && nombre_PC_hub2 < 4 && nombre_PC_selec==0)
                            {//Si le bouton plus est actif, que le nombre de PC ajout�s au hub2 est inf�rieur � 4 et qu'aucun PC n'est s�lectionn� -> AJOUT D'UN PC HUB2
                                //On ajoute un PC � la position du clic
                                SDL_BlitSurface(PC,NULL,ecran,&position_clic);
                                //On dessine le fil vers le hub1
                                drawLine(ecran,position_clic.x + PC->w/2,position_clic.y ,positionHub2.x + hub->w/2,positionHub2.y + hub->h,0,0,0);
                                //On remplit le tableau des positions de PC
                                positionPC_hub2[nombre_PC_hub2].x = position_clic.x;
                                positionPC_hub2[nombre_PC_hub2].y = position_clic.y;
                                //Incr�mentation du nombre de PC sur le hub2
                                nombre_PC_hub2++;
                            }
                            else if (bouton_moins && nombre_PC_hub2 > 1 && nombre_PC_selec==0)
                            {//Si le bouton moins est actif, que le nombre de PC du hub2 est sup�rieur � 1 et qu'aucun PC n'est selectionn� ->SUPPRESSION D'UN PC HUB2
                                //On met � 0 l'indicateur
                                trouve = 0;
                                for(i=1;i<=nombre_PC_hub2 && !trouve;i++)
                                {//On recherche le PC cliqu� (i commence � 1 pour ne pas supprimer le PC initial)
                                    if(position_clic.x > positionPC_hub2[i].x && position_clic.x < positionPC_hub2[i].x + PC->w && position_clic.y > positionPC_hub2[i].y && position_clic.y < positionPC_hub2[i].y + PC->h )
                                    {//Si on clique sur un PC du hub2
                                        //Dessine un trait gris pour effacer le noir
                                        drawLine(ecran,positionPC_hub2[i].x + PC->w/2,positionPC_hub2[i].y ,positionHub2.x + hub->w/2,positionHub2.y + hub->h,223,223,223);
                                        //On met le carr� gris pour effacer l'image du PC
                                        SDL_BlitSurface(effacer_PC,NULL,ecran,&positionPC_hub2[i]);
                                        //On remplace l'�l�ment qu'on a supprim� par le dernier
                                        positionPC_hub2[i].x=positionPC_hub2[nombre_PC_hub1-1].x;
                                        positionPC_hub2[i].y=positionPC_hub2[nombre_PC_hub1-1].y;
                                        //On decr�mente le nombre de PC sur le hub1
                                        nombre_PC_hub2--;
                                        //On indique qu'on a trouv� le PC correspondant
                                        trouve = 1;
                                    }
                                }
                            }
                            else if (nombre_PC_selec < 2)
                            {//Si le nombre de PC s�lectionn� est inf�rieur � 2 -> SELECTION D'UN PC HUB2
                                //On met � 0 l'indicateur
                                trouve = 0;
                                for(i=0;i<=nombre_PC_hub2 && !trouve;i++)
                                {//On cherche le PC qui a �t� cliqu�
                                    if(position_clic.x > positionPC_hub2[i].x && position_clic.x < positionPC_hub2[i].x + PC->w && position_clic.y > positionPC_hub2[i].y && position_clic.y < positionPC_hub2[i].y + PC->h )
                                    {//Si on clique sur un des PC du hub2
                                        if(!nombre_PC_selec)
                                        {//Si aucun PC n'�tait s�lectionn�
                                            //On met en vert ce PC
                                            SDL_BlitSurface(PC_source,NULL,ecran,&positionPC_hub2[i]);
                                            //On met � jour les variables, ce PC est une source
                                            PC_hub2_selec_source = 1;
                                            nombre_PC_selec = 1;
                                            indice_PC_hub2_selec_source = i;
                                        }
                                        else if(nombre_PC_selec==1)
                                        {//Si un PC �tait s�lectionn� avant
                                            if(indice_PC_hub2_selec_source!=i)
                                            {//Si ce PC n'est pas une source
                                                //On met en rouge ce PC
                                                SDL_BlitSurface(PC_destination,NULL,ecran,&positionPC_hub2[i]);
                                                //On met � jour les variables, ce PC est une destination
                                                PC_hub2_selec_destination = 1;
                                                nombre_PC_selec = 2;
                                                indice_PC_hub2_selec_destination = i;
                                            }
                                        }
                                        //On indique qu'on a trouv� le PC correspondant pour sortir de la boucle
                                        trouve = 1;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {//Si le bouton est le bouton cancel
                        if ( position_clic.x > RUN_CANCEL_X && position_clic.x < RUN_CANCEL_X+RUN_CANCEL_WIDTH && position_clic.y > RUN_CANCEL_Y && position_clic.y < RUN_CANCEL_Y+RUN_CANCEL_HEIGHT)
                        {//Si on clique sur le bouton cancel
                            //On efface le bouton cancel
                            SDL_FillRect(ecran,&positionRunCancel,Color(223,223,223));
                            //On indique que le bouton est desormais run
                            run_ok = 1;
                            envoi_termine = 0;
                            SDL_BlitSurface(image_actualise_sans_message,NULL,ecran,&positionFond);
                            SDL_Flip(ecran);
                            //On place le bouton run
                            apply_surface(RUN_CANCEL_X, RUN_CANCEL_Y, run, ecran, &run_cancel_sprite[0]);
                            SDL_Flip(ecran);
                        }
                    }
                //Mise � jour de l'�cran
                SDL_Flip(ecran);
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {// Si l'�v�nement est un relachement du clic gauche
                    //R�cup�ration des coordonn�es du relachement du clic
                    position_clic.x = event.motion.x;
                    position_clic.y = event.motion.y;
                    if (bouton_ouvrir)
                    {//Si le bouton ouvrir a �t� lach�
                        //On enl�ve la surbrillance du bouton ouvrir
                        apply_surface( OUVRIR_X, OUVRIR_Y, ouvrir_sauvegarder, ecran, &ouvrir_sauvegarder_sprite[ 0 ] );
                        //On indique que le bouton ouvrir n'est plus cliqu�
                        bouton_ouvrir = 0;
                        //On ouvre le reseau � partir du fichier de sauvegarde
                        ouvrirReseau(positionPC_hub1,
                                    positionPC_hub2,
                                    positionPC_hub3,
                                    &nombre_PC_hub1,
                                    &nombre_PC_hub2,
                                    &nombre_PC_hub3,
                                    &nombre_PC_selec,
                                    &PC_hub1_selec_source,
                                    &PC_hub2_selec_source,
                                    &PC_hub3_selec_source,
                                    &PC_hub1_selec_destination,
                                    &PC_hub2_selec_destination,
                                    &PC_hub3_selec_destination,
                                    &indice_PC_hub1_selec_source,
                                    &indice_PC_hub2_selec_source,
                                    &indice_PC_hub3_selec_source,
                                    &indice_PC_hub1_selec_destination,
                                    &indice_PC_hub2_selec_destination,
                                    &indice_PC_hub3_selec_destination
                                    );
                        //Par d�faut, on remet le taille � 1
                        taille_choisi=1;
                        //Par d�faut, on remet le d�bit � 10
                        debit_choisi=10;
                        //On remplace l'image actuelle par l'image vierge avec que les PC initiaux, les hubs et les fils initiaux
                        SDL_BlitSurface(image_sauvegarde,NULL,ecran,&positionFond);
                        for(i=0;i<nombre_PC_hub1;i++)
                        {//On replace les PC du hub1
                            if(indice_PC_hub1_selec_source==i)
                            {//Si le PC source fait partie du hub1
                                //On met ce PC vert
                                SDL_BlitSurface(PC_source,NULL,ecran,&positionPC_hub1[i]);
                            }
                            if (indice_PC_hub1_selec_destination==i)
                            {//Si le PC de destination fait partie du hub1
                                //On met ce PC rouge
                                SDL_BlitSurface(PC_destination,NULL,ecran,&positionPC_hub1[i]);
                            }
                            //Si ce n'est ni une source ni une destination, on met un PC normal
                            else SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub1[i]);
                            //Dans tous les cas, on met le fil entre le PC et le hub1
                            drawLine(ecran,positionPC_hub1[i].x + PC->w/2,positionPC_hub1[i].y,positionHub1.x + hub->w/2,positionHub1.y + hub->h,0,0,0);
                        }

                        for(i=0;i<nombre_PC_hub2;i++)
                        {//On replace les PC du hub2
                            if(indice_PC_hub2_selec_source==i)
                            {//Si le PC source fait partie du hub2
                                //On met ce PC vert
                                SDL_BlitSurface(PC_source,NULL,ecran,&positionPC_hub2[i]);
                            }
                            else if (indice_PC_hub2_selec_destination==i)
                            {//Si le PC de destination fait partie du hub2
                                //On met ce PC rouge
                                SDL_BlitSurface(PC_destination,NULL,ecran,&positionPC_hub2[i]);
                            }
                            //Si ce n'est ni une source ni une destination, on met un PC normal
                            else SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub2[i]);
                            //Dans tous les cas, on met le fil entre le PC et le hub2
                            drawLine(ecran,positionPC_hub2[i].x + PC->w/2,positionPC_hub2[i].y,positionHub2.x + hub->w/2,positionHub2.y + hub->h,0,0,0);
                        }
                        for(i=0;i<nombre_PC_hub3;i++)
                        {//On replace les PC du hub3
                            if(indice_PC_hub3_selec_source==i)
                            {//Si le PC source fait partie du hub3
                                //On met ce PC vert
                                SDL_BlitSurface(PC_source,NULL,ecran,&positionPC_hub3[i]);
                            }
                            else if (indice_PC_hub3_selec_destination==i)
                            {//Si le PC de destination fait partie du hub3
                                //On met ce PC rouge
                                SDL_BlitSurface(PC_destination,NULL,ecran,&positionPC_hub3[i]);
                            }
                            //Si ce n'est ni une source ni une destination, on met un PC normal
                            else SDL_BlitSurface(PC,NULL,ecran,&positionPC_hub3[i]);
                            //Dans tous les cas, on met le fil entre le PC et le hub3
                            drawLine(ecran,positionPC_hub3[i].x + PC->w/2,positionPC_hub3[i].y + PC->h,positionHub3.x + hub->w/2,positionHub3.y,0,0,0);
                        }
                    }
                    if (bouton_sauvegarder)
                    {//Si le bouton sauvegarder a �t� lach�
                        //On enl�ve la surbrillance du bouton sauvegarder
                        apply_surface( SAUVEGARDER_X, SAUVEGARDER_Y, ouvrir_sauvegarder, ecran, &ouvrir_sauvegarder_sprite[ 1 ] );
                        //On indique que le bouton sauvegarder n'est plus cliqu�
                        bouton_sauvegarder = 0;
                        //On sauvegarde le reseau dans un fichier
                        sauvReseau(positionPC_hub1,
                                    positionPC_hub2,
                                    positionPC_hub3,
                                    nombre_PC_hub1,
                                    nombre_PC_hub2,
                                    nombre_PC_hub3,
                                    nombre_PC_selec,
                                    PC_hub1_selec_source,
                                    PC_hub2_selec_source,
                                    PC_hub3_selec_source,
                                    PC_hub1_selec_destination,
                                    PC_hub2_selec_destination,
                                    PC_hub3_selec_destination,
                                    indice_PC_hub1_selec_source,
                                    indice_PC_hub2_selec_source,
                                    indice_PC_hub3_selec_source,
                                    indice_PC_hub1_selec_destination,
                                    indice_PC_hub2_selec_destination,
                                    indice_PC_hub3_selec_destination
                                    );
                    }
                    if (bouton_reboot)
                    {//Si le bouton reboot a �t� cliqu�
                        //On enl�ve la surbrillance
                        apply_surface(REBOOT_X, REBOOT_Y,reboot, ecran,&reboot_sprite[ 0 ]);
                        //On indique que le bouton reboot n'est plus cliqu�
                        bouton_reboot = 0;
                    }
                    else if (!run_ok && nombre_PC_selec==2 && position_clic.x > RUN_CANCEL_X && position_clic.x < RUN_CANCEL_X+RUN_CANCEL_WIDTH && position_clic.y > RUN_CANCEL_Y && position_clic.y < RUN_CANCEL_Y+RUN_CANCEL_HEIGHT)
                    {//Si on relache le bouton Run/Cancel apr�s avoir cliqu� sur le run et que le nombre de PC selectionn� est 2 -> ENVOI D'UN MESSAGE
                        //On copie le nombre de paquets � envoyer pour ne pas le modifier lors de la d�crementation pour la boucle while
                        copie_taille = taille_choisi;
                        //On lance le chrono car l'envoi d�bute
                        temps=clock();
                        while(copie_taille!=0)
                        {//Tant que le nombre de paquets � envoyer n'est pas 0
                            if(copie_taille!=taille_choisi)
                            {//Si le nombre de paquets � envoyer est diff�rent de l'indicateur d'envoi que l'on d�cr�mente, c'est qu'un message a �t� envoy�
                                if(indice_PC_hub1_selec_destination!=-1)
                                {//Si le PC de destination est sur le hub1
                                    //On place un message au niveau du hub1 sur l'image actualis�e
                                    positionMessage.x = positionPC_hub1[indice_PC_hub1_selec_destination].x+PC->w/2-message->w/2;
                                    positionMessage.y = positionPC_hub1[indice_PC_hub1_selec_destination].y-message->h/2;
                                    SDL_BlitSurface(message,NULL,image_actualise,&positionMessage);
                                }
                                else if(indice_PC_hub2_selec_destination!=-1)
                                {//Si le PC de destination est sur le hub2
                                    //On place un message au niveau du hub2 sur l'image actualis�e
                                    positionMessage.x = positionPC_hub2[indice_PC_hub2_selec_destination].x+PC->w/2-message->w/2;
                                    positionMessage.y = positionPC_hub2[indice_PC_hub2_selec_destination].y-message->h/2;
                                    SDL_BlitSurface(message,NULL,image_actualise,&positionMessage);
                                }
                                else if(indice_PC_hub3_selec_destination!=-1)
                                {//Si le PC de destination est sur le hub3
                                    //On place un message au niveau du hub3 sur l'image actualis�e
                                    positionMessage.x = positionPC_hub3[indice_PC_hub3_selec_destination].x+PC->w/2-message->w/2;
                                    positionMessage.y = positionPC_hub3[indice_PC_hub3_selec_destination].y+PC->h-message->h/2;
                                    SDL_BlitSurface(message,NULL,image_actualise,&positionMessage);
                                }
                            }
                            //On d�cr�mente le nombre de message � envoyer
                            copie_taille--;
                            //Determination de la vitesse selon le d�bit choisi
                            switch(debit_choisi){
                            case 10:
                                vitesse = 70;
                            break;
                            case 100:
                                vitesse = 30;
                                break;
                            case 1000:
                                vitesse = 5;
                                break;
                            }
                                if(indice_PC_hub1_selec_source!=-1)
                                {//Si le PC source est sur le hub1 -> ENVOI D'UN PC DU HUB1
                                    //Variable qui determine combien de d�placements du message on veut pour arriver au point suivant
                                    i = 20;
                                    //On initialise la position de la lettre
                                    positionMessage.x = positionPC_hub1[indice_PC_hub1_selec_source].x+PC->w/2-message->w/2;
                                    positionMessage.y = positionPC_hub1[indice_PC_hub1_selec_source].y;
                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                    while(i>=0)
                                    {//On envoie la lettre du PC vers le bas du hub1
                                        //On modifie les coordonn�es de la lettre
                                        positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                        positionMessage.y = ((i*positionMessage.y + positionHub1.y+hub->h)/(i+1));
                                        i--;
                                        //Attente pour �viter que l'image ne se d�place trop vite
                                        Sleep(vitesse);
                                        //On met l'image aux nouvelles coordonn�es
                                        SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                        SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                        //On met � jour l'�cran
                                        SDL_Flip(ecran);
                                     }
                                    if(indice_PC_hub1_selec_destination==-1)
                                    {//Si le PC de destination ne fait pas partie du m�me hub (hub1)
                                        //On remet la variable i � une valeur >0
                                        i=10;//A modifier pour la vitesse
                                        while(i>=0)
                                        {//On place la lettre au milieu du hub1
                                            positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                            positionMessage.y = ((i*positionMessage.y + positionHub1.y+hub->h/2-message->h/2)/(i+1));
                                            i--;
                                            //Attente
                                            Sleep(vitesse);
                                            SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                            SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                            //Mise � jour de l'�cran
                                            SDL_Flip(ecran);
                                        }
                                        i=5;
                                        while(i>=0)
                                        {//On d�place la lettre au milieu � droite du hub1
                                            positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w-message->w/2)/(i+1));
                                            positionMessage.y = ((i*positionMessage.y + positionHub1.y+hub->h/2-message->h/2)/(i+1));
                                            i--;
                                            Sleep(vitesse);
                                            SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                            SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                            SDL_Flip(ecran);
                                        }
                                        //On g�n�re un nombre al�atoire (0 ou 1)
                                        i = (rand () % (1-0+1));
                                        if(i==0)
                                        {//Si le nombre al�atoire est 0, on d�place l'image vers le hub2
                                            i=20;
                                            while(i>=0)
                                            {//D�placement de l'image vers le hub2
                                                positionMessage.x = ((i*positionMessage.x + positionHub2.x-message->w/2)/(i+1));
                                                positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h/2)/(i+1));
                                                i--;
                                                Sleep(vitesse);
                                                SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                SDL_Flip(ecran);
                                            }
                                            if(indice_PC_hub2_selec_destination!=-1)
                                            {
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub2[indice_PC_hub2_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub2[indice_PC_hub2_selec_destination].y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                            else
                                            {//On d�place l'image vers le hub3
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas au milieu du hub3
                                                    positionMessage.x = ((i*positionMessage.x + positionHub3.x-message->w/2+hub->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en haut du hub3
                                                    positionMessage.x = ((i*positionMessage.x + positionHub3.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub3[indice_PC_hub3_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub3[indice_PC_hub3_selec_destination].y-message->h/2+PC->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }

                                        }
                                        else
                                        {//Si le nombre est 1, on d�place l'image vers le hub3
                                            i=20;
                                            while(i>=0)
                                            {
                                                positionMessage.x = ((i*positionMessage.x + positionHub3.x+hub->w/2-message->w/2)/(i+1));
                                                positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2+hub->h)/(i+1));
                                                i--;
                                                Sleep(vitesse);
                                                SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                SDL_Flip(ecran);
                                            }
                                            if(indice_PC_hub3_selec_destination!=-1)
                                            {//Si le PC de destination est sur le hub3
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre en haut au milieu du hub3
                                                    positionMessage.x = ((i*positionMessage.x + positionHub3.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub3[indice_PC_hub3_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub3[indice_PC_hub3_selec_destination].y+PC->h-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                            else
                                            {//On d�place l'image vers le hub2
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu � gauche
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub2[indice_PC_hub2_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub2[indice_PC_hub2_selec_destination].y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {//Si le PC de destination est sur le m�me hub (hub1)
                                        i=20;
                                        while(i>=0)
                                        {//On d�place l'image vers le PC de destination du hub1
                                            positionMessage.x = ((i*positionMessage.x + positionPC_hub1[indice_PC_hub1_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                            positionMessage.y = ((i*positionMessage.y + positionPC_hub1[indice_PC_hub1_selec_destination].y-message->h/2)/(i+1));
                                            i--;
                                            Sleep(vitesse);
                                            SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                            SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                            SDL_Flip(ecran);
                                        }
                                    }
                                }
                                if(indice_PC_hub2_selec_source!=-1)
                                {
                                    //Variable qui modifie la vitesse
                                    i = 20;
                                    //On initialise la position de la lettre
                                    positionMessage.x = positionPC_hub2[indice_PC_hub2_selec_source].x+PC->w/2-message->w/2;
                                    positionMessage.y = positionPC_hub2[indice_PC_hub2_selec_source].y;
                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                    while(i>=0)
                                    {//On envoie la lettre du PC vers le bas du hub2
                                        //On modifie les coordonn�es de la lettre
                                        positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                        positionMessage.y = ((i*positionMessage.y + positionHub2.y+hub->h)/(i+1));
                                        i--;
                                        //Attente pour �viter que l'image ne se d�place trop vite
                                        Sleep(vitesse);
                                        //On met l'image aux nouvelles coordonn�es
                                        SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                        SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                        //On met � jour l'�cran
                                        SDL_Flip(ecran);
                                     }
                                    if(indice_PC_hub2_selec_destination==-1)
                                    {//Si le PC de destination ne fait pas partie du m�me hub (hub2)
                                        //On remet la variable � une valeur >0
                                        i=10;//A modifier pour la vitesse
                                        while(i>=0)
                                        {//On place la lettre au milieu du hub2
                                            positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                            positionMessage.y = ((i*positionMessage.y + positionHub2.y+hub->h/2-message->h/2)/(i+1));
                                            i--;
                                            //Attente
                                            Sleep(vitesse);
                                            SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                            SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                            //Mise � jour de l'�cran
                                            SDL_Flip(ecran);
                                        }
                                        i=5; // A modifier pour la vitesse
                                        while(i>=0)
                                        {//On d�place la lettre au milieu � gauche du hub2
                                            positionMessage.x = ((i*positionMessage.x + positionHub2.x-message->w/2)/(i+1));
                                            positionMessage.y = ((i*positionMessage.y + positionHub2.y+hub->h/2-message->h/2)/(i+1));
                                            i--;
                                            Sleep(vitesse);
                                            SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                            SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                            SDL_Flip(ecran);
                                        }
                                        //On g�n�re un nombre al�atoire (0 ou 1)
                                        i = (rand () % (1-0+1));
                                        if(i==0)
                                        {//Si le nombre al�atoire est 0, on d�place l'image vers le hub1
                                            i=20;
                                            while(i>=0)
                                            {//D�placement de l'image vers le hub1
                                                positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w-message->w/2)/(i+1));
                                                positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h/2)/(i+1));
                                                i--;
                                                Sleep(vitesse);
                                                SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                SDL_Flip(ecran);
                                            }
                                            if(indice_PC_hub1_selec_destination!=-1)
                                            {
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub1[indice_PC_hub1_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub1[indice_PC_hub1_selec_destination].y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                            else
                                            {//On d�place l'image vers le hub3
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas au milieu du hub3
                                                    positionMessage.x = ((i*positionMessage.x + positionHub3.x-message->w/2+hub->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en haut du hub3
                                                    positionMessage.x = ((i*positionMessage.x + positionHub3.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub3[indice_PC_hub3_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub3[indice_PC_hub3_selec_destination].y-message->h/2+PC->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }

                                        }
                                        else
                                        {//Si le nombre est 1, on d�place l'image vers le hub3
                                            i=20;
                                            while(i>=0)
                                            {
                                                positionMessage.x = ((i*positionMessage.x + positionHub3.x+hub->w/2-message->w/2)/(i+1));
                                                positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2+hub->h)/(i+1));
                                                i--;
                                                Sleep(vitesse);
                                                SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                SDL_Flip(ecran);
                                            }
                                            if(indice_PC_hub3_selec_destination!=-1)
                                            {//Si le PC de destination est sur le hub3
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre en haut au milieu du hub3
                                                    positionMessage.x = ((i*positionMessage.x + positionHub3.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub3[indice_PC_hub3_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub3[indice_PC_hub3_selec_destination].y+PC->h-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                            else
                                            {//On d�place l'image vers le hub1
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu � gauche
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub1[indice_PC_hub1_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub1[indice_PC_hub1_selec_destination].y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {//Si le PC de destination est sur le m�me hub (hub2)
                                        i=20;
                                        while(i>=0)
                                        {//On d�place l'image vers le PC de destination du hub2
                                            positionMessage.x = ((i*positionMessage.x + positionPC_hub2[indice_PC_hub2_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                            positionMessage.y = ((i*positionMessage.y + positionPC_hub2[indice_PC_hub2_selec_destination].y-message->h/2)/(i+1));
                                            i--;
                                            Sleep(vitesse);
                                            SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                            SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                            SDL_Flip(ecran);
                                        }
                                    }
                                }
                                if(indice_PC_hub3_selec_source!=-1)
                                {
                                    //Variable qui modifie la vitesse
                                    i = 20;
                                    //On initialise la position de la lettre
                                    positionMessage.x = positionPC_hub3[indice_PC_hub3_selec_source].x+PC->w/2-message->w/2;
                                    positionMessage.y = positionPC_hub3[indice_PC_hub3_selec_source].y+PC->h-message->h/2;
                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                    while(i>=0)
                                    {//On envoie la lettre du PC vers le haut du hub3
                                        //On modifie les coordonn�es de la lettre
                                        positionMessage.x = ((i*positionMessage.x + positionHub3.x+hub->w/2-message->w/2)/(i+1));
                                        positionMessage.y = ((i*positionMessage.y + positionHub3.y-message->h/2)/(i+1));
                                        i--;
                                        //Attente pour �viter que l'image ne se d�place trop vite
                                        Sleep(vitesse);
                                        //On met l'image aux nouvelles coordonn�es
                                        SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                        SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                        //On met � jour l'�cran
                                        SDL_Flip(ecran);
                                     }
                                    i=10; // A modifier pour la vitesse
                                    if(indice_PC_hub3_selec_destination==-1)
                                    {//Si le PC de destination ne fait pas partie du m�me hub (hub3)
                                        while(i>=0)
                                        {//On d�place la lettre en bas au milieu du hub3
                                            positionMessage.x = ((i*positionMessage.x + positionHub3.x+hub->w/2-message->w/2)/(i+1));
                                            positionMessage.y = ((i*positionMessage.y + positionHub3.y+hub->h-message->h/2)/(i+1));
                                            i--;
                                            Sleep(vitesse);
                                            SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                            SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                            SDL_Flip(ecran);
                                        }
                                        //On g�n�re un nombre al�atoire (0 ou 1)
                                        i = (rand () % (1-0+1));
                                        if(i==0)
                                        {//Si le nombre al�atoire est 0, on d�place l'image vers le hub2
                                            i=20;
                                            while(i>=0)
                                            {//D�placement de l'image vers le hub2
                                                positionMessage.x = ((i*positionMessage.x + positionHub2.x-message->w/2)/(i+1));
                                                positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h/2)/(i+1));
                                                i--;
                                                Sleep(vitesse);
                                                SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                SDL_Flip(ecran);
                                            }
                                            if(indice_PC_hub2_selec_destination!=-1)
                                            {
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas au milieu du hub2
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub2[indice_PC_hub2_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub2[indice_PC_hub2_selec_destination].y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                            else
                                            {//On d�place l'image vers le hub1
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu � droite du hub1
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x-message->w/2+hub->w)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu du hub1
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas du hub1
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub1[indice_PC_hub1_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub1[indice_PC_hub1_selec_destination].y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }

                                        }
                                        else
                                        {//Si le nombre est 1, on d�place l'image vers le hub1
                                            i=20;
                                            while(i>=0)
                                            {
                                                positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w-message->w/2)/(i+1));
                                                positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h/2)/(i+1));
                                                i--;
                                                Sleep(vitesse);
                                                SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                SDL_Flip(ecran);
                                            }
                                            if(indice_PC_hub1_selec_destination!=-1)
                                            {//Si le PC de destination est sur le hub1
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu du hub1
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y+hub->h/2-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas du hub1
                                                    positionMessage.x = ((i*positionMessage.x + positionHub1.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub1.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub1[indice_PC_hub1_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub1[indice_PC_hub1_selec_destination].y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                            else
                                            {//On d�place l'image vers le hub2
                                                i=20;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu � gauche
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=10;
                                                while(i>=0)
                                                {//D�placement de la lettre en bas au milieu
                                                    positionMessage.x = ((i*positionMessage.x + positionHub2.x+hub->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionHub2.y-message->h/2+hub->h)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                                i=20;
                                                while(i>=0)
                                                {//On d�place la lettre vers le PC de destination
                                                    positionMessage.x = ((i*positionMessage.x + positionPC_hub2[indice_PC_hub2_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                                    positionMessage.y = ((i*positionMessage.y + positionPC_hub2[indice_PC_hub2_selec_destination].y-message->h/2)/(i+1));
                                                    i--;
                                                    Sleep(vitesse);
                                                    SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                                    SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                                    SDL_Flip(ecran);
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {//Si le PC de destination est sur le m�me hub (hub3)
                                        i=20;
                                        while(i>=0)
                                        {//On d�place l'image vers le PC de destination du hub3
                                            positionMessage.x = ((i*positionMessage.x + positionPC_hub3[indice_PC_hub3_selec_destination].x+PC->w/2-message->w/2)/(i+1));
                                            positionMessage.y = ((i*positionMessage.y + positionPC_hub3[indice_PC_hub3_selec_destination].y+PC->h-message->h/2)/(i+1));
                                            i--;
                                            Sleep(vitesse);
                                            SDL_BlitSurface(image_actualise,NULL,ecran,&positionFond);
                                            SDL_BlitSurface(message,NULL,ecran,&positionMessage);
                                            SDL_Flip(ecran);
                                        }
                                    }
                                }

                                switch(taille_choisi-copie_taille){
                                case 1: //Si un seul message a �t� envoy�
                                    if(taille_choisi==1)
                                    {//Si le nombre de message � envoyer est 1
                                        texte = TTF_RenderText_Blended(police, "Packets reception : 1", couleurNoire);
                                        //L'envoi est termin�
                                        envoi_termine = 1;
                                        texteOk = TTF_RenderText_Blended(police, "OK", couleurOk);
                                        SDL_BlitSurface(texteOk,NULL,ecran,&positionInfoOk);
                                    }
                                    //Si il faut envoyer plus d'un message
                                    else texte = TTF_RenderText_Blended(police, "Packets reception : 1..", couleurNoire);
                                    //On ecrit �galement dans l'image actualis�e pour qu'� chaque d�placement d'une enveloppe le texte reste
                                    SDL_BlitSurface(texte,NULL,image_actualise,&positionInfo);
                                    SDL_BlitSurface(texte,NULL,ecran,&positionInfo);
                                    break;
                                case 2: //Si 2 messages ont �t� envoy�s
                                    if(taille_choisi==2)
                                    {//Si le nombre de message � envoyer est 2
                                        texte = TTF_RenderText_Blended(police, "Packets reception : 1..2", couleurNoire);
                                        texteOk = TTF_RenderText_Blended(police, "OK", couleurOk);
                                        //On indique que l'envoi est termine
                                        envoi_termine = 1;
                                        SDL_BlitSurface(texteOk,NULL,ecran,&positionInfoOk);

                                    }
                                    //Si il faut envoyer plus de 2 messages
                                    else texte = TTF_RenderText_Blended(police, "Packets reception : 1..2..", couleurNoire);
                                    SDL_BlitSurface(texte,NULL,image_actualise,&positionInfo);
                                    SDL_BlitSurface(texte,NULL,ecran,&positionInfo);
                                    break;
                                case 3://Si 3 messages ont �t� envoy�s
                                    texte = TTF_RenderText_Blended(police, "Packets reception : 1..2..3", couleurNoire);
                                    SDL_BlitSurface(texte,NULL,image_actualise,&positionInfo);
                                    SDL_BlitSurface(texte,NULL,ecran,&positionInfo);
                                    envoi_termine = 1;
                                    texteOk = TTF_RenderText_Blended(police, "OK", couleurOk);
                                    SDL_BlitSurface(texteOk,NULL,ecran,&positionInfoOk);
                                    break;
                                default:
                                    break;
                                }
                                if(envoi_termine)
                                {//Si l'envoi est termin�, on calcule le temps d'envoi
                                    temps_envoi = (double) (clock()-temps)/CLOCKS_PER_SEC;
                                    //On convertit le nombre en chaine de caract�re
                                    sprintf(str, "Time : %3.3fs", temps_envoi);
                                    texteTemps = TTF_RenderText_Blended(police, str, couleurNoire);
                                    SDL_BlitSurface(texteTemps,NULL,ecran,&positionTemps);

                                }
                        }
                    }

                }
            //Mise � jour de l'�cran
            SDL_Flip(ecran);
            break;
            }
        }
    }

    //Lib�ration des surfaces
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(PC);
    SDL_FreeSurface(run);
    SDL_FreeSurface(icone);
    SDL_FreeSurface(hub);
    SDL_FreeSurface(debit);
    SDL_FreeSurface(taille);
    SDL_FreeSurface(plus_moins);
    SDL_FreeSurface(effacer_PC);
    SDL_FreeSurface(ouvrir_sauvegarder);
    SDL_FreeSurface(PC_source);
    SDL_FreeSurface(PC_destination);
    SDL_FreeSurface(reboot);
    SDL_FreeSurface(message);
    SDL_FreeSurface(image_actualise_sans_message);
    SDL_FreeSurface(image_actualise);
    SDL_FreeSurface(image_sauvegarde);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texteOk);

    //Quitte la police
    TTF_CloseFont(police);

    //Quitte SDL TTF
    TTF_Quit();

    //Quitte SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
