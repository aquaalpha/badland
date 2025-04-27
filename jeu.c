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

bool colisition(t_pro p,BITMAP *mur) {
    int x = (int)p.x , y = (int)p.y + 254;
    int startX = (int)p.x+110; // petit peu à gauche
    int endX = (int)p.x + 150;  // petit peu à droite
    int footY = (int)p.y;  // niveau des pieds
    int footENDY = (int)p.y+ 220;  // niveau des pieds
    int color = makecol(0, 255, 100);
    for (int i = startX; i <= endX; i++) {
        for (int j = footY; j <= footENDY; j++ ) {
            if (getpixel(mur, i, j) == color) {
                //printf("colision\n");
                return true;
            }
        }
    }
    return false;

}

