#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "jeu.h"
#include "menu.h"
#include "ditactitielle.h"

void afficher_canon(bool *canon_active, BITMAP *fond_dic2, BITMAP *fond_dic, BITMAP *imgcanon[], int *imgcourante_canon, int *cptimg_canon, int tmpimg_canon, int y_canon_ditactitielle) {
    blit(fond_dic2, fond_dic, 0, 0, 0, 0, fond_dic->w, fond_dic->h);
    if (canon_active) {
        gerer_animation_canon(-600, y_canon_ditactitielle, imgcanon, imgcourante_canon, cptimg_canon, tmpimg_canon, fond_dic, canon_active);
    } else {
        rotate_sprite(fond_dic, imgcanon[1], -600, y_canon_ditactitielle, itofix(10));
    }
}

void gerer_mouvement_objet(bool *marche,bool *canon_active, bool *mouvement, int *imgcourante_canon, int *angle_propulsion, BITMAP *buffer, BITMAP *img[], t_pro *objet, t_personnage_jeux *perso) {
    if (!*canon_active && *mouvement) {
        *imgcourante_canon = 0;
        *angle_propulsion += 1;
        rotate_sprite(buffer, img[4], (int)objet[0].x, (int)objet[0].y, itofix(*angle_propulsion));
        objet[0].x += 1;
        if (objet[0].x > 355) {
            *mouvement = false;
            *marche = true;
            perso->x = objet[0].x;
            perso->y = objet[0].y;
        }
    }
}

void afficher_message_ditactitielle(bool *marche, int *message_dic, BITMAP *buffer, BITMAP *img[], t_pro *objet, t_ill *ill, BITMAP *imgaile[], int *imgcourante_aile, int *cptimg_aile, float *t, int offset, int amplitude, int frequence, float scroll_x) {
    if (*marche && *message_dic == 0) {
        int tmpimg_aile = 50;
        gerer_animation_perso_ailes(&ill[0], imgaile, imgcourante_aile, cptimg_aile, tmpimg_aile, buffer, t, offset, amplitude, frequence, (int)scroll_x);

        int x = 150;
        int y = 200;
        int couleur_fond = makecol(255, 250, 240);
        int couleur_texte = makecol(0, 0, 0);
        int couleur_bordure = makecol(255, 255, 255);
        int largeur = 600;
        int hauteur = 40;

        rectfill(buffer, x, y, x + largeur, y + hauteur, couleur_fond);
        rect(buffer, x, y, x + largeur, y + hauteur, couleur_bordure);
        textprintf_ex(buffer, font, x + 10, y + 10, couleur_texte, -1, "Bienvenue dans le ditactitielle, appuie sur [E] pour passer mes messages");

        if (key[KEY_E]) {
            (*message_dic)++;
        }

        draw_sprite(buffer, img[4], objet[0].x, objet[0].y);
    }
}

void gerer_saut_et_mouvement(int *message_dic, t_pro *objet, bool *saut, float *vitesse_y, int *imgcourante, int *cptimg, int tmpimg, BITMAP *fond_dic, BITMAP *mur_colision, BITMAP *img[], BITMAP *imgsaut[], BITMAP *buffer,float scroll_x) {
    if (*message_dic == 1) {
        int y;

        if (colisition(objet[0], fond_dic, &y)) {
            objet[0].y -= 1;
        } else if (!colisition(objet[0], mur_colision, &y)) {
            objet[0].y += 1;
        }

        if (!colisition_devant(objet[0], mur_colision)) {
            if (key[KEY_D]) {
                objet[0].x += 1;
            }
        }
        if (key[KEY_A]) {
            objet[0].x -= 1;
        }

        if (!key[KEY_A] && !key[KEY_D]) {
            *imgcourante = 4;
        }

        if (key[KEY_SPACE] && !*saut) {
            *saut = true;
            *vitesse_y = -20;
        }

        if (*saut) {
            objet[0].y += *vitesse_y;
            *vitesse_y += 0.5;
            gerer_animation_saut(objet[0], imgsaut, imgcourante, cptimg, tmpimg, fond_dic);
            //gerer_animation_saut(objet[0], imgsaut, imgcourante, cptimg, tmpimg, fond_dic);
            //gerer_animation_perso_jeux(objet[0], img, imgcourante, cptimg, tmpimg, fond_dic, (int)scroll_x);

            if (colisition(objet[0], fond_dic, &y)) {
                *saut = false;
                *vitesse_y = 0;
            }
        } else {
            printf("%f %f %d %d\n", objet[0].x, objet[0].y, mouse_y, mouse_x);
            gerer_animation_perso_jeux(objet[0], img, imgcourante, cptimg, tmpimg, fond_dic, (int)scroll_x);
        }

        blit(fond_dic, buffer, objet[0].x, 0,0, 0, fond_dic->w, fond_dic->h);

    }
}
