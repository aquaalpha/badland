#ifndef MENU_H
#define MENU_H

typedef struct perso {
    float px, py;
} t_perso;

typedef struct props{
    int rx, ry;
} t_props;

typedef struct yeux{
    int yx, yy;
} t_yeux;

typedef struct niv {
    int niv_1, niv_2, niv_3;

}t_niv;

void charger_images(BITMAP *img[], const char *prefixe);
void charger_images_yeux(BITMAP **imgyeux);
void charger_images_aile(BITMAP **imgyeux);
void afficher_boutons(BITMAP *quitter, BITMAP *quitter_click, BITMAP *param, BITMAP *param_click, BITMAP *jouer,BITMAP *jouer_click, BITMAP *buffer,bool *menu_principale,bool *menu_quitter,bool *menu_jouer);
void gerer_animation_perso(t_perso *p, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer);
void gerer_animation_perso_aile(t_perso *p, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,float *t, float offset, float amplitude, float frequence);
void afficher_roue(BITMAP *roue, t_props *r, int *angle, BITMAP *buffer);
void gerer_animation_yeux(t_yeux *y, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer, volatile int *timer_yeux,bool *valide, int *i);
void recherche(t_niv *niveau,char *nom_final,int *existant);
void inscription(t_niv *niveau,char *nom_final,int *existant);

#endif //MENU_H
