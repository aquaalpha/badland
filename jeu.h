//
// Created by jugue on 25/04/2025.
//

#ifndef JEU_H
#define JEU_H
typedef struct pro {
    float x,y;
    float vx,vy;

}t_pro;

typedef struct  personnage_illustration{
    int x,y;

}t_ill;

typedef struct  personnage_jeux{
    int x,y;

}t_personnage_jeux;
void charger_images_canon(BITMAP **imgcanon);
void gerer_animation_canon(int x , int y, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,bool *canon_active);
void gerer_animation_perso_ailes(t_ill *i, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,float *t, float offset, float amplitude, float frequence,int scroll_x);
void gerer_animation_perso_jeux(t_pro p, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,int scroll_x );
bool colisition(t_pro perso,BITMAP* mur);
#endif //JEU_H
