/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Generique.h"
#include "Jeu.h"
#include "Keyboard.h"

Generique::Generique(Jeu* jeu) : gpJeu(jeu), anim(0) {
    imageFin = NULL;
    imageArbre = NULL;
    image = SDL_CreateRGBSurface(0, 320, 240, 32, 0, 0, 0, 0);
    imageTitre = IMG_Load("data/images/logos/titre.png");
    SDL_SetColorKey(imageTitre,SDL_TRUE,SDL_MapRGB(imageTitre->format,0,0,255));
    imageCurseur = IMG_Load("data/images/logos/curseur.png");
    SDL_SetColorKey(imageCurseur,SDL_TRUE,SDL_MapRGB(imageCurseur->format,0,0,255));
    imageNiveau = IMG_Load("data/images/logos/niveau.png");
    SDL_SetColorKey(imageNiveau,SDL_TRUE,SDL_MapRGB(imageNiveau->format,0,0,255));
    imageFee = IMG_Load("data/images/logos/fee.png");
    imageCadre = IMG_Load("data/images/logos/cadres.png");
    imageFond1 = NULL;
    imageFond2 = NULL;
    for (int i = 0; i < 5; i++) imageIntro[i]=NULL;
}

Generique::~Generique() {
    SDL_FreeSurface(imageFin);
    SDL_FreeSurface(imageArbre);
    SDL_FreeSurface(image);
    SDL_FreeSurface(imageTitre);
    SDL_FreeSurface(imageCurseur);
    SDL_FreeSurface(imageNiveau);
    SDL_FreeSurface(imageFee);
    SDL_FreeSurface(imageCadre);
    SDL_FreeSurface(imageFond1);
    SDL_FreeSurface(imageFond2);
    for (int i = 0; i < 5; i++) SDL_FreeSurface(imageIntro[i]);
}

void Generique::drawFin(SDL_Surface* gpScreen) {
    if (!imageFin) imageFin = IMG_Load("data/images/logos/fin.png");
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(imageFin, NULL, gpScreen, &dst);
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::initLogo() {
    SDL_Rect dst;
    SDL_Surface* logo = IMG_Load("data/images/logos/logo.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(logo, NULL, image, &dst);
    SDL_FreeSurface(logo);
}

void Generique::initTitre() {
    SDL_Rect dst;
    SDL_Surface* fond = IMG_Load("data/images/logos/fond.png");
    dst.x = 0; dst.y = 0; SDL_BlitSurface(fond, NULL, image, &dst);
    SDL_FreeSurface(fond);
    SDL_Surface* logo = IMG_Load("data/images/logos/titre.png");
    SDL_SetColorKey(logo,SDL_TRUE,SDL_MapRGB(logo->format,0,0,255));
    //logo = SDL_DisplayFormat(logo);
    dst.x = 86; dst.y = 45; SDL_BlitSurface(logo, NULL, image, &dst);
    SDL_FreeSurface(logo);
}

void Generique::initSelection() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
            
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 9; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 128+48; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 128+48; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 128+48; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,48,288,32);
    cadre(16,96,288,32);
    cadre(16,144,288,32);
    cadre(16,192,136,32);
    cadre(168,192,136,32);
    
    gpJeu->affiche(image, "PANTALLA DE SELECCION", 40, 16);
    gpJeu->affiche(image, "1.", 44, 56);
    gpJeu->affiche(image, "2.", 44, 104);
    gpJeu->affiche(image, "3.", 44, 152);
    gpJeu->affiche(image, "OPCIONES", 63-6, 200);
    gpJeu->affiche(image, "RECORDS", 215, 200);
    
    //stats :
    SDL_Surface* imageStat = IMG_Load("data/images/statut/statut.png");
    SDL_SetColorKey(imageStat,SDL_TRUE,SDL_MapRGB(imageStat->format,0,0,255));
    SDL_Surface* inventaire = IMG_Load("data/images/statut/inventaire.png");
    SDL_Surface* objets = IMG_Load("data/images/statut/objets.png");
    
    for (int i = 0; i < 3; i++) {
        Joueur* gpJoueur = new Joueur(gpJeu,i+1);
        if (gpJoueur->getLoader()) {
            //vie
            if(gpJoueur->getVie()>gpJoueur->getVieMax()) gpJoueur->setVie(gpJoueur->getVieMax());
            for(int j=0;j<gpJoueur->getVieMax()/2;j++) {
                src.h = 7; src.w = 7; src.y=9;
                dst.x = 64-8+((j%10)*8)+8;dst.y = 57+8*((int)(j/10))+i*48;
                if (gpJoueur->getVie()-(j*2)>1)src.x=141;
                if (gpJoueur->getVie()-(j*2)==1)src.x=149;
                if (gpJoueur->getVie()-(j*2)<1)src.x=157;
                SDL_BlitSurface(imageStat, &src, image, &dst);
            }
        
            //cristaux
            dst.x=176+8-16-16-4; dst.y=56+i*48;
            src.x=16; src.y=17*4; src.w=16; src.h=17;
            for (int j=0; j<5; j++) {
                if (gpJoueur->hasCristal(j)) src.x=16; else src.x=32;
                SDL_BlitSurface(inventaire, &src, image, &dst);
                dst.x+=16+2;
            }
            
            //épée
            dst.x=280-48+8; dst.y=56+i*48;
            src.x=16*(gpJoueur->getEpee()-1); src.y=0; src.w=16; src.h=16;
            if (gpJoueur->getEpee()) SDL_BlitSurface(objets, &src, image, &dst);
            
            //masque
            dst.x=280-32+16-4; dst.y=56+i*48;
            src.x=16*(gpJoueur->hasObjet(O_MASQUE)-1); 
            src.y=102-17*(gpJoueur->hasObjet(O_MASQUE)-1); src.w=16; src.h=16;
            if (gpJoueur->hasObjet(O_MASQUE)) SDL_BlitSurface(inventaire, &src, image, &dst);
            
            //triforce
            dst.x=272+8; dst.y=56+i*48;
            src.x=128; src.y=0; src.w=17; src.h=16;
            if (gpJoueur->getEnnemi(50)) SDL_BlitSurface(objets, &src, image, &dst);
            
            gpJeu->getKeyboard()->setSave(i,1);
        }else gpJeu->getKeyboard()->setSave(i,0);
    }
    
    SDL_FreeSurface(objets);
    SDL_FreeSurface(imageStat);
    SDL_FreeSurface(inventaire);
}

void Generique::initOption() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64,288,32);
    cadre(16,128,288,32);
    cadre(16,192,136,32);
    
    gpJeu->affiche(image, "OPCIONES", 40-1, 16);
    gpJeu->affiche(image, "MUSICA", 60, 72);
    gpJeu->affiche(image, "SONIDOS", 60, 136);
    gpJeu->affiche(image, "ANTERIOR", 63-6, 200);
    
    src.x = 0; src.y = 96; dst.x = 128; dst.y = 72; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    for (int i = 144; i < 264; i+=16) {
        src.x = 16; src.y = 96; dst.x = i; dst.y = 72; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    src.x = 32; src.y = 96; dst.x = 264; dst.y = 72; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    src.x = 0; src.y = 96; dst.x = 128; dst.y = 136; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    for (int i = 144; i < 264; i+=16) {
        src.x = 16; src.y = 96; dst.x = i; dst.y = 136; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    src.x = 32; src.y = 96; dst.x = 264; dst.y = 136; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
}

void Generique::initRecord() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(128,8,176,32);
    cadre(16,48,192,32); cadre(224,48,32,32); cadre(272,48,32,32);
    cadre(16,96,192,32); cadre(224,96,32,32); cadre(272,96,32,32);
    cadre(16,144,192,32); cadre(224,144,32,32); cadre(272,144,32,32);
    cadre(16,192,136,32);
    cadre(168,192,136,32);
    
    ostringstream oss;
    int temps = gpJeu->getKeyboard()->getTemps();
    if (temps > 359999) temps = 359999;
    int h = temps/3600;
    int m = (temps - ((int)(temps/3600))*3600)/60;
    int s = temps%60;
    if (h < 10) oss<<"0"; oss << h << ":";
    if (m < 10) oss<<"0"; oss << m << ":";
    if (s < 10) oss<<"0"; oss << s;
    
    
    gpJeu->affiche(image, "RECORDS", 40, 16);
    gpJeu->affiche(image, "MEJOR TIEMPO : " + oss.str(), 140, 16);
    gpJeu->affiche(image, "RANGO DE LOS 100%", 44, 56);
    gpJeu->affiche(image, "RANGO ULTIMO", 44, 104);
    gpJeu->affiche(image, "RANGO DE RAPIDEZ", 44, 152);
    gpJeu->affiche(image, "ANTERIOR", 63-6, 200);
    gpJeu->affiche(image, "BORRAR", 215, 200);
    
    SDL_Surface* objets = IMG_Load("data/images/statut/objets.png");
    
    //triforce
    src.y=0; src.w=17; src.h=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=231; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i) ? src.x=128 : src.x=145; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    //graäl
    src.y=16; //src.w=17; src.h=16;
    
    for (int i = 0; i < 3; i++) {
        dst.x=280; dst.y=56+i*48;
        gpJeu->getKeyboard()->getRang(i+3) ? src.x=128 : src.x=145; 
        SDL_BlitSurface(objets, &src, image, &dst);}
    
    SDL_FreeSurface(objets);
}

void Generique::initEffacer() {
    cadre(104,84,112,72);
    gpJeu->affiche(image, "BORRAR ?", 133, 93);
    gpJeu->affiche(image, "SI", 151, 113);
    gpJeu->affiche(image, "NO", 151, 133);
}

void Generique::initCharger() {
    cadre(104,84,112,72);
    gpJeu->affiche(image, "CARGAR", 139, 93);
    gpJeu->affiche(image, "BORRAR", 139, 113);
    gpJeu->affiche(image, "ANULAR", 139, 133);
}

void Generique::initIntro() {
    if (imageFond1==NULL) {
        imageFond1 = IMG_Load("data/images/logos/fond1.png");
        SDL_SetColorKey(imageFond1,SDL_TRUE,SDL_MapRGB(imageFond1->format,0,0,255));}
    if (imageFond2==NULL) imageFond2 = IMG_Load("data/images/logos/fond2.png");
    
    ostringstream oss;
    for (int i = 0; i < 5; i++) {
        if (imageIntro[i]==NULL) {
            oss.str(""); oss << (i+1);
            imageIntro[i] = IMG_Load(("data/images/logos/intro" + oss.str() + ".png").c_str());
        }
    }
    
    lastAnimTime = SDL_GetTicks(); anim=0;
    gpJeu->ecrit(218, false, true, 32, 158, 256, 64);
}

void Generique::initNuit() {
    SDL_FillRect(image, NULL, SDL_MapRGB(image->format, 0, 0, 0));
    gpJeu->ecrit(220);
}

void Generique::initAide1() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    gpJeu->affiche(image, "AYUDA 1/2", 40-3, 16);
    
    gpJeu->affiche(image, "Volver al juego : Enter  Siguiente : Derecha", 24, 208);
    
    int ligne = 64;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    gpJeu->affiche(image, "Leer / Abrir / Hablar : Espacio", 24, ligne); ligne+=16;
    gpJeu->affiche(image, "Validar / Pasar texto : Enter", 24, ligne); ligne+=16;
    gpJeu->affiche(image, "Mover a Link : Flechas de dirección", 24, ligne); ligne+=16;
    if (gpJoueur->hasObjet(O_BOTTES)) {
        gpJeu->affiche(image, "Correr : Mayus mantenido o Capslock", 24, ligne); 
        ligne+=16;}
    if (gpJoueur->getEpee()) {
        gpJeu->affiche(image, "Golpe de espada : Z o W", 24, ligne); ligne+=16;
        gpJeu->affiche(image, "Giratorio : Z o W mantenido luego soltado", 24, ligne); 
        ligne+=16;}
    gpJeu->affiche(image, "Menu de selección del objeto : Enter", 24, ligne); ligne+=16;
    if (ligne >= 176) return;
    gpJeu->affiche(image, "Utilizar el objeto seleccionnado : X", 24, ligne); ligne+=16;
    if (ligne >= 176) return;
    if (gpJoueur->hasObjet(O_GANTS)) {
        gpJeu->affiche(image, "Levantar objetos : C", 24, ligne); 
        ligne+=16;}
    if (ligne >= 176) return;
    if (gpJoueur->hasObjet(O_CARTE))
        gpJeu->affiche(image, "Ver el mapa : P (exterior o templos)", 24, ligne);
    else gpJeu->affiche(image, "Ver el mapa : P (en los templos)", 24, ligne);
    ligne+=16;
    if (ligne >= 176) return;
    if (gpJoueur->hasObjet(O_ENCYCL)) {
        gpJeu->affiche(image, "Ver los monstros vencidos : M", 24, ligne); 
        ligne+=16;}
    if (ligne >= 176) return;
    gpJeu->affiche(image, "Mirar alrededor : Ctrl y dirección", 24, ligne); ligne+=16;
    if (ligne >= 176) return;
    gpJeu->affiche(image, "Agrandar / Encoger : Ctrl y Enter", 24, ligne); ligne+=16;
    if (ligne >= 176) return;
    gpJeu->affiche(image, "Grabar / Quitar : Esc", 24, ligne); ligne+=16;
}

void Generique::initAide2() {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    src.x = 16; src.y = 16;
    for (int j = 0; j < 240; j+=16)
        for (int i = 0; i < 320; i+=16) {
            dst.x = i; dst.y = j; SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
        
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 16; dst.x = 16; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 0; src.y = 32; dst.x = 16; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    for (int i = 0; i < 4; i++) {
        src.x = 16; src.y = 0; dst.x = 32+16*i; dst.y = 0; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 64; dst.x = 32+16*i; dst.y = 16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 32; dst.x = 32+16*i; dst.y = 32; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    src.x = 32; src.y = 0; dst.x = 96; dst.y = 0; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 16; dst.x = 96; dst.y = 16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    src.x = 32; src.y = 32; dst.x = 96; dst.y = 32; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    cadre(16,64-8,288,128);
    
    cadre(16,192+8,288,32);
    
    gpJeu->affiche(image, "AYUDA 2/2", 40-3, 16);
    
    gpJeu->affiche(image, "Volver al juego : Enter  Anterior : Izquierda", 24, 208);
    
    int ligne = 64-112;
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ligne+=64;
    if (gpJoueur->hasObjet(O_BOTTES)) ligne+=16;
    if (gpJoueur->getEpee()) ligne+=32;
    if (ligne >= 64) 
    gpJeu->affiche(image, "Utilizar el objeto seleccionnado : X", 24, ligne); ligne+=16;
    if (ligne >= 64) 
    if (gpJoueur->hasObjet(O_GANTS)) {
        gpJeu->affiche(image, "Levantar objetos : C", 24, ligne); 
        ligne+=16;}
    if (ligne >= 64) {
    if (gpJoueur->hasObjet(O_CARTE))
        gpJeu->affiche(image, "Ver el mapa : P (exterior o templos)", 24, ligne);
    else gpJeu->affiche(image, "Ver el mapa : P (en los templos)", 24, ligne);}
    ligne+=16;
    if (ligne >= 64) 
    if (gpJoueur->hasObjet(O_ENCYCL)) {
        gpJeu->affiche(image, "Ver los monstruos vencidos : M", 24, ligne); 
        ligne+=16;}
    if (ligne >= 64) 
    gpJeu->affiche(image, "Mirar alrededor : Ctrl y dirección", 24, ligne); ligne+=16;
    if (ligne >= 64) 
    gpJeu->affiche(image, "Agrandar / Encoger : Ctrl y Enter", 24, ligne); ligne+=16;
    if (ligne >= 64) 
    gpJeu->affiche(image, "Grabar / Quitar : Esc", 24, ligne); ligne+=16;
}

void Generique::initRang(int i) {
    
    switch (i) {
        case 0 :
            cadre(72,96,176,48);
            if (gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Héroe de los dos Mundos", 72, 104);
            else if (gpJeu->getKeyboard()->getRang(i) && !gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Héroe de Hyrule", 72, 104);
            else if (!gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Héroe de Termina", 72, 104);
            else gpJeu->affiche(image, "RANGO : DESCONOCIDO", 72, 104);
            gpJeu->affiche(image, "Acabar el juego a 100%", 72, 120);
            break;
        case 1 :
            cadre(64,56,192,128);
            int l; l=64;
            if (gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Maestro de Esgrima", 72, l);
            else if (gpJeu->getKeyboard()->getRang(i) && !gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Chulo", 72, l);
            else if (!gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Fanfarrón", 72, l);
            else gpJeu->affiche(image, "RANGO : DESCONOCIDO", 72, l);
            l+=16;
            gpJeu->affiche(image, "Acabar el juego sin morir,", 72, l);l+=16;
            gpJeu->affiche(image, "con 15 corazones como máximo,", 72, l);l+=16;
            gpJeu->affiche(image, "sin hablar a las Grandes Hadas,", 72, l);l+=16;
            gpJeu->affiche(image, "sin comprar botellas", 72, l);l+=16;
            gpJeu->affiche(image, "sin cambiar de túnica", 72, l);l+=16;
            gpJeu->affiche(image, "y sin coger escudos.", 72, l);l+=16;
            break;
        case 2 :
            cadre(48,88,224,64);
            if (gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Corredor de los dos Mundos", 56, 96);
            else if (gpJeu->getKeyboard()->getRang(i) && !gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Corredor de Hyrule", 56, 96);
            else if (!gpJeu->getKeyboard()->getRang(i) && gpJeu->getKeyboard()->getRang(i+3)) 
                gpJeu->affiche(image, "RANGO : Corredor de Termina", 56, 96);
            else gpJeu->affiche(image, "RANGO : DESCONOCIDO", 56, 96);
            gpJeu->affiche(image, "Acabar el juego en menos de cuatro", 56, 112);
            gpJeu->affiche(image, "horas", 56, 128);
            break;
    }
}

void Generique::cadre(int x, int y, int w, int h) {
    SDL_Rect src; src.w = 16; src.h = 16;
    SDL_Rect dst;
    
    for (int j = y+16; j < y+h-16; j+=16)
        for (int i = x+16; i < x+w-16; i+=16) {
            src.x = 16; src.y = 64; dst.x = i; dst.y = j; 
            SDL_BlitSurface(imageCadre, &src, image, &dst);
        }
    
    //haut et bas
    for (int i = x+16; i < x+w-16; i+=16) {
        src.x = 16; src.y = 48; dst.x = i; dst.y = y; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 16; src.y = 80; dst.x = i; dst.y = y+h-16; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    //gauche et droite
    for (int j = y+16; j < y+h-16; j+=16) {
        src.x = 0; src.y = 64; dst.x = x; dst.y = j; 
        SDL_BlitSurface(imageCadre, &src, image, &dst);
        src.x = 32; src.y = 64; dst.x = x+w-16; dst.y = j;
        SDL_BlitSurface(imageCadre, &src, image, &dst);
    }
    
    //haut gauche
    src.x = 0; src.y = 48; dst.x = x; dst.y = y; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //haut droite
    src.x = 32; src.y = 48; dst.x = x+w-16; dst.y = y; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //bas gauche
    src.x = 0; src.y = 80; dst.x = x; dst.y = y+h-16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
    
    //bas droite
    src.x = 32; src.y = 80; dst.x = x+w-16; dst.y = y+h-16; 
    SDL_BlitSurface(imageCadre, &src, image, &dst);
}

void Generique::initScore() {
    SDL_FreeSurface(imageArbre);
    imageArbre = IMG_Load("data/images/logos/arbre.png");
    image = SDL_CreateRGBSurface(0, 320, 240, 32, 0, 0, 0, 0);
    
    SDL_Rect dst; 
    
    for (int i = 0; i < 320; i+=48) {
        dst.x = i;
        for (int j = 0; j < 240; j+=96) {
            dst.y = j;
            SDL_BlitSurface(imageArbre, NULL, image, &dst);
        }
    }
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    ostringstream oss;
    int pctg = 0;
    gpJeu->affiche(image, "RESULTADOS :", 136, 10);
    
    int temps = gpJoueur->getTemps(0)+gpJoueur->getTemps(1)*60+gpJoueur->getTemps(2)*3600;
    if (temps < gpJeu->getKeyboard()->getTemps() || gpJeu->getKeyboard()->getTemps()==0) {
        gpJeu->getKeyboard()->setTemps(temps); gpJeu->getKeyboard()->saveP();}
        
    oss.str(""); 
    if (gpJoueur->getTemps(2)<10)oss<<"0";oss << gpJoueur->getTemps(2) << ":";
    if (gpJoueur->getTemps(1)<10)oss<<"0";oss << gpJoueur->getTemps(1) << ":";
    if (gpJoueur->getTemps(0)<10)oss<<"0";oss << gpJoueur->getTemps(0);
    gpJeu->affiche(image, ("Tiempo jugando : " + oss.str()).c_str(), 10, 30);
    
    int tmp=gpJoueur->getMort();
    oss.str(""); oss << tmp;
    gpJeu->affiche(image, ("Muerto " + oss.str() + " veces").c_str(), 10, 50);
    
    tmp=gpJoueur->nbQuarts();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Cuartos de corazón : " + oss.str() + " / 16").c_str(), 10, 70);

    tmp=0;
    for (int i = 0; i < 15; i++) if (gpJoueur->hasObjet(i)) tmp++;
    if (gpJoueur->hasObjet(O_ARC) == 5) tmp++;
    if (gpJoueur->hasObjet(O_GANTS) == 2) tmp++;
    if (gpJoueur->hasObjet(O_MASQUE) == 2) tmp++;
    tmp+=gpJoueur->getBouclier();
    for (int i = 0; i < 3; i++) if (gpJoueur->hasBouteille(i)) tmp++;
    tmp+=gpJoueur->getEpee();
    tmp+=gpJoueur->getTunique();
    if (gpJoueur->getMagieMax() > 32) tmp++;
    for (int i = 0; i < 3; i++) if (gpJoueur->hasMelodie(i)) tmp++;
    for (int i = 0; i < 5; i++) if (gpJoueur->hasCristal(i)) tmp++;
    for (int j = 0; j < 15; j++) for (int i = 0; i < 3; i++) if (gpJoueur->getCle(j,i)) tmp++;
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Objetos : " + oss.str() + " / 85").c_str(), 10, 90);
    
    tmp=gpJoueur->nbEnnemis();
    oss.str(""); oss << tmp; pctg+=tmp;
    gpJeu->affiche(image, ("Tipos de enemigos vencidos : " + oss.str() + " / 62").c_str(), 10, 110);
    
    pctg=(int)((pctg*100)/163);
    oss.str(""); oss << pctg;
    gpJeu->affiche(image, ("Has acabado este juego al " + oss.str() + "%, felicitaciones !").c_str(), 
        10, 130);
    
    string result;
    int ligne = 170;
    gpJeu->affiche(image, "RANGO : ", 10, ligne);
    
    if (gpJoueur->getMort()==0 && gpJoueur->hasBouteille(0)==0
        && gpJoueur->hasBouteille(1)==0 && gpJoueur->hasBouteille(2)==0
        && gpJoueur->getVieMax()==30 && gpJoueur->getTunique()==1
        && gpJoueur->getMagieMax()==32 && gpJoueur->getBouclier()==0
        && gpJoueur->getBombeMax()==10 && gpJoueur->getFlecheMax()==30) {
        if (gpJeu->getKeyboard()->getRang(2)) result="Maestro de Esgrima"; 
            else result="Fanfarrón"; 
        gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;
        gpJeu->getKeyboard()->setRang(4); gpJeu->getKeyboard()->saveP();}
        
    else {
        if (pctg==100) {
            if (gpJeu->getKeyboard()->getRang(2)) result="Héroe de los dos Mundos"; 
            else result="Héroe de Termina"; 
            gpJeu->getKeyboard()->setRang(3); gpJeu->getKeyboard()->saveP();}
        if (pctg<100) result="Perfeccionista";
        if (pctg<95) result="Fan de Zelda";
        if (pctg<90) result="Genio del teclado";
        if (pctg<85) result="Veterano";
        if (pctg<80) result="Principiante";
        gpJeu->affiche(image, " - "+result, 52, ligne);
        ligne+=20;
    }
    
    if (gpJoueur->getMort()>=100) {
        result="Muerto en vida"; gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
    else if (gpJoueur->getMort()>=50) {
        result="Kamikaze"; gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
        
    if (temps<=14400) {
        if (gpJeu->getKeyboard()->getRang(2)) result="Corredor de los dos Mundos"; 
        else result="Corredor de Termina"; 
        gpJeu->getKeyboard()->setRang(5); gpJeu->getKeyboard()->saveP();
        gpJeu->affiche(image, " - "+result, 52, ligne); ligne+=20;}
}

void Generique::draw(SDL_Surface* gpScreen) {
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(image, NULL, gpScreen, &dst);
}

void Generique::drawSelection(SDL_Surface* gpScreen, int ligne, int colonne) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26+152*colonne; dst.y = 53+48*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
}

void Generique::drawOption(SDL_Surface* gpScreen, int ligne, int opt1, int opt2) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26; dst.y = 69+64*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
    
    src.h = 16; src.w = 8;src.x = 0;src.y=0;
    dst.x = 136+16*opt1; dst.y = 56+16;
    SDL_BlitSurface(imageNiveau, &src, gpScreen, &dst);
                
    src.h = 16; src.w = 8;src.x = 0;src.y=0;
    dst.x = 136+16*opt2; dst.y = 56+16+64;
    SDL_BlitSurface(imageNiveau, &src, gpScreen, &dst);
}

void Generique::drawRecord(SDL_Surface* gpScreen, int ligne, int colonne) {
    draw(gpScreen);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 21; src.w = 16;src.x = 0;src.y=0;
    dst.x = 26+152*colonne; dst.y = 53+48*ligne;
    
    SDL_BlitSurface(imageCurseur, &src, gpScreen, &dst);
}

void Generique::drawEffacer(SDL_Surface* gpScreen, int ligne) {
    drawRecord(gpScreen, 3, 1);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 113+20*ligne;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawCharger(SDL_Surface* gpScreen, int ligne, int ligne2) {
    drawSelection(gpScreen, ligne, 0);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 93+20*ligne2;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawEffacerSave(SDL_Surface* gpScreen, int ligne, int ligne2) {
    drawSelection(gpScreen, ligne, 0);
    SDL_Rect src;
    SDL_Rect dst;
    
    src.h = 16; src.w = 16;src.x = 0;src.y=0;
    dst.x = 112; dst.y = 113+20*ligne2;
    
    SDL_BlitSurface(imageFee, &src, gpScreen, &dst);
}

void Generique::drawIntro(SDL_Surface* gpScreen, int etape) {
    SDL_Rect src;
    SDL_Rect dst;
    
    if(SDL_GetTicks() > lastAnimTime + 40) {
        lastAnimTime = SDL_GetTicks();
        anim++;
        if (anim > 31) anim = 0;
    }
                
    src.h = 16; src.w = 16;
    for (int j=0; j<240; j+=16) 
        for (int i=0; i<320; i+=16) {
            src.x = 16-anim%16;src.y=anim%16; dst.x = i; dst.y = j;
            if (i>16 && i<288 && j>144 && j<224) src.x+=32;
            SDL_BlitSurface(imageFond2, &src, gpScreen, &dst);
        }
                
    src.h = 32; src.w = 32;
    for (int j=0; j<240; j+=32) 
        for (int i=0; i<320; i+=32) {
            src.x = anim;src.y=anim; dst.x = i; dst.y = j;
            if (i>16 && i<288 && j>144 && j<224) src.x+=64;
            SDL_BlitSurface(imageFond1, &src, gpScreen, &dst);
        }
                
    src.h = 111; src.w = 320;
    src.x = 0; src.y=0; dst.x = 0; dst.y = 17;
    SDL_BlitSurface(imageIntro[etape], &src, gpScreen, &dst);
                
    gpJeu->getTexte()->draw(gpScreen);
}

void Generique::drawDebut(SDL_Surface* gpScreen) {
    SDL_Rect dst; dst.x = 0; dst.y = 0;
    SDL_BlitSurface(image, NULL, gpScreen, &dst);
    gpJeu->getTexte()->draw(gpScreen);
}
