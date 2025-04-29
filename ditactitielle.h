// Nouveau fichier : ditactitielle.h

#ifndef DITACTITIELLE_H
#define DITACTITIELLE_H

#include <allegro.h>
#include "jeu.h"
void afficher_canon(bool *canon_active, BITMAP *fond_dic2, BITMAP *fond_dic, BITMAP *imgcanon[], int *imgcourante_canon, int *cptimg_canon, int tmpimg_canon, int y_canon_ditactitielle);
void gerer_mouvement_objet(bool *marche,bool *canon_active, bool *mouvement, int *imgcourante_canon, int *angle_propulsion, BITMAP *buffer, BITMAP *img[], t_pro *objet, t_personnage_jeux *perso);
void afficher_message_ditactitielle(bool *marche, int *message_dic, BITMAP *buffer, BITMAP *img[], t_pro *objet, t_ill *ill, BITMAP *imgaile[], int *imgcourante_aile, int *cptimg_aile, float *t, int offset, int amplitude, int frequence, float scroll_x);
void gerer_saut_et_mouvement(int *message_dic, t_pro *objet, bool *saut, float *vitesse_y, int *imgcourante, int *cptimg, int tmpimg, BITMAP *fond_dic, BITMAP *mur_colision, BITMAP *img[], BITMAP *imgsaut[],BITMAP *buffer, float scroll_x);
#endif
