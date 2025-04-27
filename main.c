#include <stdio.h>
#include <allegro.h>
#include <stdbool.h>
#include <math.h>
#include "menu.h"
#include "jeu.h"
#include "ditactitielle.h"

#define NIMAGE 9
#define NYEUX 5
#define NAILE 9
#define NSAUT 4
#define NCANON 5
volatile int timer_yeux = 0;

void initialisation_allegro();
void incrementer_timer_yeux();

int main() {
    BITMAP *fond_menu, *quitter, *quitter_click, *parametre, *parametre_click;
    BITMAP *jouer, *jouer_click, *img[NIMAGE], *img2[NIMAGE],*imgyeux[NYEUX],*imgaile[NAILE], *roue, *premierPlanFond, *yeux, *buffer;
    BITMAP *mquitter , *new,*oui,*non,*oui_click,*non_click,*tableau;
    BITMAP *avancement0;
    BITMAP *texte ;
    BITMAP *imgcanon[NCANON];
    BITMAP *imgsaut[NSAUT];
    BITMAP *fond_dic;
    BITMAP *fond_dic2;
    BITMAP *mur, *mur_colision;
    int imgcourante = 0, cptimg = 0, tmpimg = 40;
    int imgcourante_yeux = 0, cptimg_yeux = 0, tmpimg_yeux = 60;
    int imgcourante_aile = 0, cptimg_aile = 0, tmpimg_aile = 20;
    int imgcourante_saut = 0, cptimg_saut = 0;
    int angle_roue = 0;

    float t = 0.02f;
    float amplitude = 20.0f;
    float frequence = 0.15f;
    float offset = 100.0f;
    float scroll_x;


    char nom[50] = "";
    char *nom_final;
    int touche = 0 ;
    float vitesse_y = 0;

   int marge_scrol = 200;


    int x_canon_ditactitielle = -400,y_canon_ditactitielle= 100;
    int imgcourante_canon = 0, cptimg_canon = 0, tmpimg_canon=80;
    int angle_propulsion = 1000;
    int message_dic = 0;
    bool canon_active = true;


    bool annimation = true, annimation2 = false;
    bool valide = true;
    bool menu_principale = true;
    bool menu_quitter = false ;
    bool menu_jouer = false;
    bool ditactitiel = false;
    bool gameplay = true;
    bool marche = false;
    bool mouvement = true;
    bool saut = false;
    bool espace_appuye = false;
    int existant = 1;

    t_perso p[3] = {{120, 550}, {216, 675},{216,200}};
    t_props r[1] = {{5, 500}};
    t_yeux yeux_position[5] = {{950, 280}, {61, 119},{1188, 301},{953, 95}};
    t_niv niveau;
    t_pro objet[1] = {{0, 450}};
    t_ill ill[1] = {{800, 500}};
    t_personnage_jeux perso;



    ///// coordonnées obstacle jeux ///////
    t_obstacle obstacle[1] = {{1047, 350}};




    int i = 0;

    float test = 0;

    initialisation_allegro();

    LOCK_VARIABLE(timer_yeux);
    LOCK_FUNCTION(incrementer_timer_yeux);
    install_int_ex(incrementer_timer_yeux, BPS_TO_TIMER(1)); // 1 fois par seconde

    charger_images(img, "monstre");
    charger_images(img2, "monstre_gris");
    charger_images_yeux(imgyeux);
    charger_images_aile(imgaile);
    charger_images_canon(imgcanon);
    charger_images_saut(imgsaut);

    fond_menu = load_bitmap("fond_menu.bmp", NULL);
    mur = load_bitmap("fond_mur_aplatie.bmp", NULL);
    mur_colision = load_bitmap("fond_mur_aplatie_colision.bmp", NULL);
    premierPlanFond = load_bitmap("premierPlanFond.bmp", NULL);
    mquitter = load_bitmap("menu_quitter.bmp", NULL);
    roue = load_bitmap("roue0.bmp", NULL);
    yeux = load_bitmap("yeux0.bmp", NULL);
    quitter = load_bitmap("quitter.bmp", NULL);
    quitter_click = load_bitmap("quitter_click.bmp", NULL);
    parametre = load_bitmap("parametre.bmp", NULL);
    parametre_click = load_bitmap("parametre_click.bmp", NULL);
    jouer = load_bitmap("jouer.bmp", NULL);
    jouer_click = load_bitmap("jouer_click.bmp", NULL);
    new = load_bitmap("new.bmp", NULL);
    oui = load_bitmap("oui.bmp", NULL);
    oui_click = load_bitmap("oui_click.bmp", NULL);
    non = load_bitmap("non.bmp", NULL);
    non_click = load_bitmap("non_click.bmp", NULL);
    tableau = load_bitmap("tableau.bmp", NULL);
    texte = create_bitmap(200, 50); // taille originale
    avancement0 = load_bitmap("avancement.bmp", NULL);
    fond_dic = load_bitmap("fonds_dic.bmp", NULL);
    fond_dic2 = load_bitmap("fonds_dic.bmp", NULL);
    buffer = create_bitmap(SCREEN_W, SCREEN_H);

    while (!key[KEY_ESC]) {
        /*if(menu_principale) {
            blit(fond_menu, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            if (annimation) {
                //gerer_animation_perso(&p[0], img, &imgcourante, &cptimg, tmpimg, buffer);
                gerer_animation_perso_aile(&p[2], imgaile, &imgcourante_aile, &cptimg_aile, tmpimg_aile, buffer,&t,offset,amplitude,frequence);
                if (p[2].px > 1200) {
                    annimation = false;
                    annimation2 = true;
                }
            }


            if (annimation2) {
                gerer_animation_perso(&p[1], img2, &imgcourante, &cptimg, tmpimg, buffer);
                if (p[1].px > 1200) {
                    annimation2 = false;
                    annimation = true;
                }
            }

            afficher_roue(roue, r, &angle_roue, buffer);
            masked_blit(premierPlanFond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            gerer_animation_yeux(yeux_position, imgyeux, &imgcourante_yeux, &cptimg_yeux, tmpimg_yeux, buffer, &timer_yeux,&valide,&i);

            afficher_boutons(quitter, quitter_click, parametre, parametre_click, jouer, jouer_click ,buffer,&menu_principale,&menu_quitter,&menu_jouer);


            show_mouse(buffer);
            printf("%d %d\n",mouse_x,mouse_y);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
        if (menu_quitter) {
            blit(mquitter, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            show_mouse(buffer);
            printf("%d %d\n",mouse_x,mouse_y);
            if (mouse_x >= 370 && mouse_x <= 500 && mouse_y >= 475 && mouse_y <= 550) {
                if (mouse_b & 1) {
                    allegro_exit();
                }
            }
            else if (mouse_x >= 635 && mouse_x <= 777 && mouse_y >= 475 && mouse_y <= 550) {
                if (mouse_b & 1) {
                    menu_principale = true;
                    menu_quitter= false;
                }
            }
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        }
        if(menu_jouer) {
            blit(fond_menu, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

            if (annimation) {
                gerer_animation_perso_aile(&p[2], imgaile, &imgcourante_aile, &cptimg_aile, tmpimg_aile, buffer,&t,offset,amplitude,frequence);
                if (p[2].px > 1200) {
                    annimation = false;
                    annimation2 = true;
                }
            }

            if (annimation2) {
                gerer_animation_perso(&p[1], img2, &imgcourante, &cptimg, tmpimg, buffer);
                if (p[1].px > 1200) {
                    annimation2 = false;
                    annimation = true;
                }
            }
            if (keypressed()) {
                int code = readkey();
                char c = code & 0xFF;
                int k = code >> 8;

                if (k == KEY_BACKSPACE && touche > 0) {
                    touche--;
                    nom[touche] = '\0';
                }
                else if (k == KEY_ENTER) {
                    nom_final = malloc(strlen(nom) + 1);
                    strcpy(nom_final, nom);
                    printf("Nom enregistrer : %s ,recherche en cour\n", nom_final);
                    recherche(&niveau,nom_final,&existant);
                }
                else if (c >= 32 && c <= 126 && touche < sizeof(nom) - 1) {
                    nom[touche++] = c;
                    nom[touche] = '\0';
                }
            }
            if(existant == 1) {
                int x = SCREEN_W / 2 - 200;
                int y = SCREEN_H / 2 - 40;
                textprintf_ex(buffer, font, x  ,y-10, makecol(255, 255, 255), -1, "Entrer votre nom :");
                rect(buffer, x, y, x + 400, y + 80, makecol(255, 255, 255));
                textprintf_ex(buffer, font, x + 10, y + 35, makecol(255, 255, 255), -1, "%s", nom);
            }
            if(existant== 0) {
                printf("%d %d\n",mouse_x,mouse_y);
                masked_blit(new, buffer, 0, 0, 330, 150, SCREEN_W, SCREEN_H);
                if (mouse_x >= 480 && mouse_x <= 560 && mouse_y >= 500 && mouse_y <= 550) {
                    masked_blit(oui_click, buffer, 0, 0, 450, 450, SCREEN_W, SCREEN_H);
                    if (mouse_b & 1) {
                        inscription(&niveau,nom_final,&existant);
                    }
                }
                else {
                    masked_blit(oui, buffer, 0, 0, 450, 450, SCREEN_W, SCREEN_H);
                }
                if (mouse_x >= 585 && mouse_x <= 665 && mouse_y >= 500 && mouse_y <= 550) {
                    masked_blit(non_click, buffer, 0, 0, 550, 450, SCREEN_W, SCREEN_H);
                    if (mouse_b & 1) {
                        existant = 1;
                    }
                }
                else {
                    masked_blit(non, buffer, 0, 0, 550, 450, SCREEN_W, SCREEN_H);
                }

            }
            if (existant == 2) { // recap info +
                //masked_blit(tableau, buffer, 0, 0, 250,400 , SCREEN_W, SCREEN_H);
                //masked_blit(avancement0, buffer, 0, 0, 330, 150, SCREEN_W, SCREEN_H);
                clear_to_color(texte, makecol(255, 0, 255)); // transparent
                textprintf_ex(texte, font, 0, 0, makecol(255, 255, 255), -1, "Bonjour %s !", nom);
                masked_stretch_blit(texte, buffer, 0, 0, 200, 50, 300, 200, 600, 150);
                if(niveau.niv_1 == 0) {
                    ditactitiel = true;
                    textprintf_ex(texte, font, 0, 0, makecol(255, 255, 255), -1, "Nous avons remarqué que vous êtes nouveau parmis nous", nom);
                    masked_stretch_blit(texte, buffer, 0, 0, 200, 50, 300, 200, 600, 150);
                }

            }

            afficher_roue(roue, r, &angle_roue, buffer);
            masked_blit(premierPlanFond, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            gerer_animation_yeux(yeux_position, imgyeux, &imgcourante_yeux, &cptimg_yeux, tmpimg_yeux, buffer, &timer_yeux,&valide,&i);

            show_mouse(buffer);
            //printf("%d %d\n",mouse_x,mouse_y);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        }*/
        /*if(gameplay) {
            if(objet[0].x > 1200) {
                test = objet[0].x- 1200;
            }
            blit(fond_dic, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            masked_blit(mur_colision, buffer, test, 0, 0, 0, SCREEN_W, SCREEN_H);
            masked_blit(mur, buffer, test, 0, 0, 0, SCREEN_W, SCREEN_H);
            if(canon_active == true) {
                gerer_animation_canon(objet[0].x,y_canon_ditactitielle, imgcanon, &imgcourante_canon, &cptimg_canon, tmpimg_canon, buffer,&canon_active);
            }
            else {
                rotate_sprite(buffer, imgcanon[1], objet[0].x, y_canon_ditactitielle, itofix(10));
            }
            if(canon_active == false && mouvement == true) {
                imgcourante_canon = 0;
                angle_propulsion += 100000;
                rotate_sprite(buffer, img[4], objet[0].x,objet[0].y , angle_propulsion);
                objet[0].x += 1;
                if(objet[0].x > 500) {
                    objet[0].y += 3;
                }
                if(getpixel(mur_colision, objet[0].x, objet[0].y+50) == makecol(0, 255, 100)) {
                    printf("collison\n");
                    marche = true;
                    mouvement = false;
                    objet[0].y-=200;
                    perso.x = objet[0].x-100;
                    perso.y = objet[0].y;

                }
                printf("collison\n");

            }
            if(marche == true) {
                if(message_dic == 0) {
                    tmpimg_aile = 50;
                    gerer_animation_perso_ailes(&ill[0], imgaile, &imgcourante_aile, &cptimg_aile, tmpimg_aile, buffer,&t,offset,amplitude,frequence,scroll_x);
                    int x = 150;
                    int y = 200;
                    int couleur_fond = makecol(255, 250, 240);
                    int couleur_texte = makecol(0, 0, 0);
                    int couleur_bordure = makecol(255, 255, 255);
                    int largeur = 600;
                    int hauteur = 40;
                    rectfill(buffer, x, y, x + largeur, y + hauteur, couleur_fond);
                    rect(buffer, x, y, x + largeur, y + hauteur, couleur_bordure);
                    textprintf_ex(buffer, font, x + 10, y + 10, couleur_texte, -1,"Bienvenue dans le ditactitielle, appuie sur [e] pour passer mes messages");
                    if(key[KEY_E]) {
                        message_dic +=1;
                    }
                    draw_sprite(buffer, img[4], objet[0].x, objet[0].y);
                }
                if(message_dic == 1) {
                    if(key[KEY_D]) {
                        objet[0].x+=1;
                        printf("%f\n",objet[0].x);
                    }
                    if(key[KEY_A]) {
                        objet[0].x-=1;
                    }
                    if(!key[KEY_A] && !key[KEY_D] ) {
                        imgcourante = 4;
                    }
                    gerer_animation_perso_jeux(perso, img, &imgcourante, &cptimg, tmpimg, buffer,scroll_x);

                }

            }


            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        }*/
        /*if(gameplay) {
            if(canon_active == true) {
                blit(fond_dic2,fond_dic , 0, 0, 0, 0, fond_dic->w, fond_dic->h);
                gerer_animation_canon(-600,y_canon_ditactitielle, imgcanon, &imgcourante_canon, &cptimg_canon, tmpimg_canon, fond_dic,&canon_active);
             }
            else {
                blit(fond_dic2,fond_dic , 0, 0, 0, 0, fond_dic->w, fond_dic->h);
                rotate_sprite(fond_dic, imgcanon[1], -600, y_canon_ditactitielle, itofix(10));
            }
            masked_blit(mur_colision, fond_dic, 0, 0, 0, 0, fond_dic->w, fond_dic->h);
            masked_blit(mur, fond_dic, 0, 0, 0, 0, fond_dic->w, fond_dic->h);
            blit(fond_dic, buffer, objet[0].x, 0,0, 0, fond_dic->w, fond_dic->h);
            if(canon_active == false && mouvement == true) {
                imgcourante_canon = 0;
                angle_propulsion += 100000;
                rotate_sprite(buffer, img[4], objet[0].x,objet[0].y , angle_propulsion);
                objet[0].x += 1;
                if(objet[0].x > 355) {
                    marche = true;
                    mouvement = false;
                    perso.x = objet[0].x;
                    perso.y = objet[0].y;

                }
            }
            if(marche == true) {
                if(message_dic == 0) {
                    tmpimg_aile = 50;
                    gerer_animation_perso_ailes(&ill[0], imgaile, &imgcourante_aile, &cptimg_aile, tmpimg_aile, buffer,&t,offset,amplitude,frequence,scroll_x);
                    int x = 150;
                    int y = 200;
                    int couleur_fond = makecol(255, 250, 240);
                    int couleur_texte = makecol(0, 0, 0);
                    int couleur_bordure = makecol(255, 255, 255);
                    int largeur = 600;
                    int hauteur = 40;
                    rectfill(buffer, x, y, x + largeur, y + hauteur, couleur_fond);
                    rect(buffer, x, y, x + largeur, y + hauteur, couleur_bordure);
                    textprintf_ex(buffer, font, x + 10, y + 10, couleur_texte, -1,"Bienvenue dans le ditactitielle, appuie sur [e] pour passer mes messages");
                    if(key[KEY_E]) {
                        message_dic +=1;
                    }
                    draw_sprite(buffer, img[4], objet[0].x, objet[0].y);
                }
                if(message_dic == 1) {
                    int y ;
                    if(colisition(objet[0],fond_dic,&y)) {
                        objet[0].y-=1;

                    }
                    else if(!colisition(objet[0],mur_colision,&y)) {
                        objet[0].y+=1;

                    }
                    if(!colisition_devant(objet[0],mur_colision)) {
                        if(key[KEY_D]) {
                            objet[0].x+=1;
                        }
                    }
                    if(key[KEY_A]) {
                        objet[0].x-=1;
                    }
                    if(!key[KEY_A] && !key[KEY_D] ) {
                        imgcourante = 4;
                    }
                    if (key[KEY_SPACE] && saut == false) {
                        saut = true;
                        vitesse_y = -20; // Lance le saut vers le haut
                    }

                    if (saut) {
                        objet[0].y += vitesse_y; // Applique la vitesse
                        vitesse_y += 0.5;         // Gravité qui tire vers le bas

                        gerer_animation_saut(objet[0], imgsaut, &imgcourante_saut, &cptimg_saut, tmpimg, fond_dic);

                        if (colisition(objet[0],fond_dic,&y)) { // Sol touché ?
                            saut = false;
                            vitesse_y = 0;
                        }
                    } else{
                        printf(" %f %f %d %d\n",objet[0].x,objet[0].y,mouse_y,mouse_x);
                        gerer_animation_perso_jeux(objet[0], img, &imgcourante, &cptimg, tmpimg, fond_dic, scroll_x);
                    }gi
                    blit(fond_dic, buffer, objet[0].x, 0,0, 0, fond_dic->w, fond_dic->h);


                }
            }
            show_mouse(buffer);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }*/
        if (gameplay) {
            afficher_canon(&canon_active, fond_dic2, fond_dic, imgcanon, &imgcourante_canon, &cptimg_canon, tmpimg_canon, y_canon_ditactitielle);
            masked_blit(mur_colision, fond_dic, 0, 0, 0, 0, fond_dic->w, fond_dic->h);
            masked_blit(mur, fond_dic, 0, 0, 0, 0, fond_dic->w, fond_dic->h);
            blit(fond_dic, buffer, objet[0].x, 0,0, 0, fond_dic->w, fond_dic->h);
            gerer_mouvement_objet(&marche,&canon_active, &mouvement, &imgcourante_canon, &angle_propulsion, buffer, img, objet, &perso);
            afficher_message_ditactitielle(&marche, &message_dic, buffer, img, objet, ill, imgaile, &imgcourante_aile, &cptimg_aile, &t, offset, amplitude, frequence, scroll_x);
            gerer_saut_et_mouvement(&message_dic, objet, &saut, &vitesse_y, &imgcourante_saut, &cptimg_saut, tmpimg, fond_dic, mur_colision, img, imgsaut, buffer,scroll_x);
            show_mouse(buffer);
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }

    }

    allegro_exit();
    return 0;
}
END_OF_MAIN()

void initialisation_allegro() {
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst�me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    set_color_depth(desktop_color_depth()); //ici : identique à celle du bureau

    //sélection du mode graphique
    // avec choix d'un driver+mode+résolution de l'écran
    /// si échec, le programme s'arrête
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,800,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void incrementer_timer_yeux() {
    timer_yeux++;
}
END_OF_FUNCTION(incrementer_timer_yeux)
