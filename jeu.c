#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "jeu.h"
#include "menu.h"
#define NCANON 5
#define NAILE 9
#define NIMAGE 9
#define NSAUT 4

void charger_images_canon(BITMAP **imgcanon) { //charger images sprites
    char nomfichier_canon[50];
    for (int i = 0; i < NCANON; i++) {
        sprintf(nomfichier_canon, "canon%d.bmp",i);
        imgcanon[i] = load_bitmap(nomfichier_canon, NULL);
        if (!imgcanon[i]) {
            allegro_message("Impossible de charger %s", nomfichier_canon);
            exit(EXIT_FAILURE);
        }
    }
}

void charger_images_saut(BITMAP **img) { //charger images sprites
    char nomfichier_saut[50];
    for (int i = 0; i < NSAUT; i++) {
        sprintf(nomfichier_saut, "monstre_saut%d.bmp",i);
        img[i] = load_bitmap(nomfichier_saut, NULL);
        if (!img[i]) {
            allegro_message("Impossible de charger %s", nomfichier_saut);
            exit(EXIT_FAILURE);
        }
    }
}

void gerer_animation_canon(int x,int y, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,bool *canon) {
    fixed angle = itofix(10);
    rotate_sprite(buffer, img[*imgcourante], x, y, angle);
    if (*cptimg >= tmpimg) {
        *cptimg = 0;
        (*imgcourante)++;
        if (*imgcourante >= NCANON) *imgcourante = 0;
    }
    (*cptimg)++;
    if (*imgcourante == 4) {
        *canon = false;
    }
}


void gerer_animation_saut(t_pro p,BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer) {
    draw_sprite(buffer, img[*imgcourante], p.x, p.y);
    if (*cptimg >= tmpimg) {
        *cptimg = 0;
        (*imgcourante)++;
        if (*imgcourante >= NSAUT) *imgcourante = 0;
    }
    (*cptimg)++;
}

void gerer_animation_perso_ailes(t_ill *i, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,float *t, float offset, float amplitude, float frequence,int scroll_x) {
    draw_sprite_h_flip(buffer, img[*imgcourante],(int)(i->x - scroll_x), (int)i->y);  // affichage inversé

    if (*cptimg >= tmpimg) {
        *cptimg = 0;
        (*imgcourante)++;
        if (*imgcourante >= NAILE) *imgcourante = 0;
    }
    i->y = amplitude * sinf(frequence * (*t)) + offset;

    *t += 0.1f;
    (*cptimg)++;
}

void gerer_animation_perso_jeux(t_pro p, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,int scroll_x ) {
    draw_sprite(buffer, img[*imgcourante], p.x, p.y);
    if (*cptimg >= tmpimg) {
        *cptimg = 0;
        (*imgcourante)++;
        if (*imgcourante >= NIMAGE) *imgcourante = 0;
    }
    (*cptimg)++;
}

bool colisition(t_pro p,BITMAP *mur,int *y) {
    int startX = (int)p.x+107; // petit peu à gauche
    int endX = (int)p.x + 170;  // petit peu à droite
    int footY = (int)p.y+251;  // niveau des pieds
    int footENDY = (int)p.y+ 260;  // niveau des pieds
    int color = makecol(0, 0, 0);
    for (int i = startX; i <= endX; i++) {
        for (int j = footY; j <= footENDY; j++ ) {
            if (getpixel(mur, i, j) == color) {
                printf("colision\n");
                *y=j;
                return true;
            }
        }
    }
    return false;

}

bool colisition_devant(t_pro p,BITMAP *mur) {
    int x = (int)p.x , y = (int)p.y + 254;
    int startX = (int)p.x+226; // petit peu à gauche
    int endX = (int)p.x + 244;  // petit peu à droite
    int footY = (int)p.y+19;  // niveau des pieds
    int footENDY = (int)p.y+ 210;  // niveau des pieds
    int color = makecol(255, 245, 45);
    for (int i = startX; i <= endX; i++) {
        for (int j = footY; j <= footENDY; j++ ) {
            if (getpixel(mur, i, j) == color) {
                printf("colision\n");
                return true;
            }
        }
    }
    return false;

}

bool colisition_mort(t_pro p,BITMAP *mur) {
    int x = (int)p.x , y = (int)p.y + 254;
    int startX = (int)p.x+60;
    int endX = (int)p.x + 244;
    int footY = (int)p.y+10;
    int footENDY = (int)p.y+ 244;
    int color = makecol(255, 0, 0);
    for (int i = startX; i <= endX; i++) {
        for (int j = footY; j <= footENDY; j++ ) {
            if (getpixel(mur, i, j) == color) {
                printf("colision\n");
                return true;
            }
        }
    }
    return false;

}


void afficher_roue_jeux(BITMAP *roue, t_obstacle r, int *angle, BITMAP *fonds) {
    *angle += 1000;
    rotate_sprite(fonds, roue, r.x, r.y, *angle);
}

void afficher_scie(BITMAP *scie,BITMAP *scie_colision,BITMAP *fonds,BITMAP *mur_colision,int *x,int y,t_pro *objet, int *angle) {
    if(objet[0].x > 1800) {
        *angle += 10000;
        *x-=5;
        rotate_sprite(fonds, scie, *x, y, *angle);
        rotate_sprite(mur_colision, scie_colision, *x, y, *angle);
    }
}

