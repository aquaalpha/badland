#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "menu.h"
#define NIMAGE 9
#define NYEUX 5
#define NAILE 9
#define NCANON 5

void charger_images(BITMAP *img[], const char *prefixe) { //charger images sprites
    char nomfichier[50];
    for (int i = 0; i < NIMAGE; i++) {
        sprintf(nomfichier, "%s%d.bmp", prefixe, i);
        img[i] = load_bitmap(nomfichier, NULL);
        if (!img[i]) {
            allegro_message("Impossible de charger %s", nomfichier);
            exit(EXIT_FAILURE);
        }
    }
}

void charger_images_yeux(BITMAP **imgyeux) { //charger images sprites
    char nomfichier_yeux[50];
    for (int i = 0; i < NYEUX; i++) {
        sprintf(nomfichier_yeux, "yeux%d.bmp",i);
        imgyeux[i] = load_bitmap(nomfichier_yeux, NULL);
        if (!imgyeux[i]) {
            allegro_message("Impossible de charger %s", nomfichier_yeux);
            exit(EXIT_FAILURE);
        }
    }
}

void charger_images_aile(BITMAP **imgyeux) { //charger images sprites
    char nomfichier_aile[50];
    for (int i = 0; i < NAILE; i++) {
        sprintf(nomfichier_aile, "monstre_aile%d.bmp",i);
        imgyeux[i] = load_bitmap(nomfichier_aile, NULL);
        if (!imgyeux[i]) {
            allegro_message("Impossible de charger %s", nomfichier_aile);
            exit(EXIT_FAILURE);
        }
    }
}

void afficher_boutons(BITMAP *quitter, BITMAP *quitter_click, BITMAP *param, BITMAP *param_click, BITMAP *jouer,BITMAP *jouer_click, BITMAP *buffer,bool *menu_principale,bool *menu_quitter,bool *menu_jouer) {
    if (mouse_x >= 620 && mouse_x <= 730 && mouse_y >= 600 && mouse_y <= 650) {
        masked_blit(quitter_click, buffer, 0, 0, 600, 550, SCREEN_W, SCREEN_H);
        if (mouse_b & 1) {
            *menu_principale = false;
            *menu_quitter = true;
        }
    } else {
        masked_blit(quitter, buffer, 0, 0, 600, 550, SCREEN_W, SCREEN_H);
    }

    if (mouse_x >= 410 && mouse_x <= 530 && mouse_y >= 600 && mouse_y <= 650) {
        masked_blit(param_click, buffer, 0, 0, 430, 550, SCREEN_W, SCREEN_H);
    } else {
        masked_blit(param, buffer, 0, 0, 430, 550, SCREEN_W, SCREEN_H);
    }
    if (mouse_x >= 395 && mouse_x <= 765 && mouse_y >= 315 && mouse_y <= 490) {
        masked_blit(jouer_click, buffer, 0, 0, 330, 150, SCREEN_W, SCREEN_H);
        if (mouse_b & 1) {
            *menu_principale = false;
            *menu_quitter = false;
            *menu_jouer = true;
        }
    }
    else {
        masked_blit(jouer, buffer, 0, 0, 330, 150, SCREEN_W, SCREEN_H);
    }
}

void gerer_animation_perso(t_perso *p, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer) {
    draw_sprite(buffer, img[*imgcourante], (int)p->px, (int)p->py);
    if (*cptimg >= tmpimg) {
        *cptimg = 0;
        (*imgcourante)++;
        if (*imgcourante >= NIMAGE) *imgcourante = 0;
    }
    p->px += 0.1;
    (*cptimg)++;
}

void gerer_animation_perso_aile(t_perso *p, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,float *t, float offset, float amplitude, float frequence) {
    draw_sprite(buffer, img[*imgcourante], (int)p->px , (int)p->py);
    if (*cptimg >= tmpimg) {
        *cptimg = 0;
        (*imgcourante)++;
        if (*imgcourante >= NIMAGE) *imgcourante = 0;
    }
    p->px += 0.3;
    p->py = amplitude * sinf(frequence * (*t)) + offset;

    *t += 0.1f;
    (*cptimg)++;
}

void gerer_animation_yeux(t_yeux *r, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer, volatile int *timer_yeux,bool *valide, int *i) {
     if(*valide) {
         draw_sprite(buffer, img[*imgcourante], r[*i].yx, r[*i].yy);
     }
    if (*cptimg >= tmpimg ) {
        *cptimg = 0;
        (*imgcourante)++;
        if( *imgcourante ==1) {
            *valide = false;
        }
        if (*imgcourante >= NYEUX) {
            *imgcourante = 0;
        }
    }
    (*cptimg)++;
    if (*timer_yeux >= 5) {
        *i= *i +1;
        *timer_yeux = 0;
        *valide = true;
        if(*i>3) {
            *i=0;
        }
    }

}

void afficher_roue(BITMAP *roue, t_props *r, int *angle, BITMAP *buffer) {
    *angle += 1000;
    rotate_sprite(buffer, roue, r[0].rx, r[0].ry, *angle);
}

void recherche(t_niv *niveau ,char *nom_final,int *existant) {
    char nom[50];
    FILE *f = fopen("donnees_joueur.txt", "r");
    if (f == NULL) {
        printf("Erreur d'ouvrir le fichier\n");
    }
        while(fscanf(f, "%s %d %d %d", nom,&niveau->niv_1,&niveau->niv_2,&niveau->niv_3) == 4) {
            if(strcmp(nom, nom_final) == 0) {
                printf("existant\n");
                *existant = 2;
                fclose(f);
                return;
            }
        }
    fclose(f);
    printf("non existant\n");
    *existant = 0;
}

void inscription(t_niv *niveau ,char *nom_final,int *existant) {
    FILE *f = fopen("donnees_joueur.txt", "a");
    niveau->niv_1 = niveau->niv_2 = niveau->niv_3 = 0;
    *existant = 2;
    fprintf(f,"%s %d %d %d\n",nom_final,niveau->niv_1,niveau->niv_2,niveau->niv_3);
    printf("inscription reusssie\n");
    fclose(f);
}
