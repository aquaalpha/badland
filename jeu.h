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

typedef struct obstacle{
    int x,y;

}t_obstacle;

void charger_images_canon(BITMAP **imgcanon);
void charger_images_saut(BITMAP **img);
void gerer_animation_canon(int x , int y, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,bool *canon_active);
void gerer_animation_perso_ailes(t_ill *i, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,float *t, float offset, float amplitude, float frequence,int scroll_x);
void gerer_animation_perso_jeux(t_pro p, BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer,int scroll_x );
bool colisition(t_pro perso,BITMAP* mur,int *y);
bool colisition_devant(t_pro p,BITMAP *mur);
void afficher_roue_jeux(BITMAP *roue, t_obstacle r, int *angle, BITMAP *fonds);
void afficher_scie(BITMAP *scie,BITMAP *fonds,int *x,int y,t_pro *objet,int *angle);
void gerer_animation_saut(t_pro p,BITMAP *img[], int *imgcourante, int *cptimg, int tmpimg, BITMAP *buffer);
#endif //JEU_H
