/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <SDL2/SDL.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Keyboard.h"
#include "Generique.h"

SDL_Window* createWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        exit(-1);
    }

    //if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
    //    printf( "Warning: Linear texture filtering not enabled!" );

    SDL_Window* window = SDL_CreateWindow("Oni Link Begins",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640,
                                          480,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP
                                          );

    if (!window)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }

    SDL_Surface* icon = SDL_LoadBMP("data/images/logos/graal.ico");
    SDL_SetColorKey(icon,SDL_TRUE,SDL_MapRGB(icon->format,0,0,0));
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_ACCELERATED// | SDL_RENDERER_PRESENTVSYNC
                                                );

    if (!renderer)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-1);
    }

    SDL_RenderSetLogicalSize(renderer, 320, 240);

    int imgFlags = IMG_INIT_PNG;

    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(-1);
    }

    return renderer;
}

int main(int, char**) {
    std::srand(std::time(NULL));
    
    SDL_Window* window = createWindow();
    SDL_Renderer* renderer = createRenderer(window);
    SDL_Surface* gpScreen = SDL_CreateRGBSurface(0, 320, 240, 32, 0, 0, 0, 0);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, gpScreen);

    SDL_ShowCursor(SDL_DISABLE);
    
    int mode = 2; //mode=0;
    
    Audio* gpAudio = new Audio();
    Jeu* gpJeu = new Jeu(gpAudio);
    Carte* gpCarte = new Carte(gpJeu);
    Encyclopedie* gpEncyclopedie = new Encyclopedie(gpJeu);
    Keyboard* gpKeyboard = new Keyboard(gpJeu, gpCarte, gpEncyclopedie, window, mode);
    gpJeu->setKeyboard(gpKeyboard);
    Generique* gpGenerique = new Generique(gpJeu);
    gpJeu->setGenerique(gpGenerique);
    gpGenerique->initLogo();
    
    //gpJeu->init(0);
    
    bool gLoop = true;
    
    Uint32 lastAnimTime = SDL_GetTicks();
    
    while (gLoop) {
        
        if (gpKeyboard->gererClavier() == -1) {gLoop = false;}
        
        switch (gpKeyboard->getMode()) {
            case 0 : //jeu normal
                gpJeu->draw(gpScreen); break;
            case 1 : //disclamer
            case 2 : //logo
            case 3 : //titre
            case 14 : //générique score
            case 17 : //menu d'aide 1
            case 18 : //menu d'aide 2
                gpGenerique->draw(gpScreen); break;
            case 4 : //selection
                gpGenerique->drawSelection(gpScreen, gpKeyboard->getLigne(),
                    gpKeyboard->getColonne()); break;
            case 6 : //options
                gpGenerique->drawOption(gpScreen, gpKeyboard->getLigneOption(),
                gpKeyboard->getVolume()/8, gpKeyboard->getVolson()/8); break;
            case 7 : //charger partie
                gpGenerique->drawCharger(gpScreen, gpKeyboard->getLigne(),
                    gpKeyboard->getLigneVal()); break;
            case 8 : //générique intro
                gpGenerique->drawIntro(gpScreen, gpKeyboard->getIntro()); break;
            case 9 : //effacer partie
                gpGenerique->drawEffacerSave(gpScreen, gpKeyboard->getLigne(),
                    gpKeyboard->getLigneVal()); break;
            case 10 : //générique début chez link
                gpGenerique->drawDebut(gpScreen); break;
            case 11 : //générique fin
                gpGenerique->drawFin(gpScreen); break;
            case 12 : //carte
            case 22 : //carte téléportation
                gpCarte->draw(gpScreen); break;
            case 13 : //encyclopédie des monstres
                gpEncyclopedie->draw(gpScreen); break;
            case 15 : //records
            case 19 : //rang 100%
            case 20 : //rang ultime
            case 21 : //rang de rapidité
                gpGenerique->drawRecord(gpScreen, gpKeyboard->getLigneRecord(),
                    gpKeyboard->getColonneRecord()); break;
            case 16 : //effacer record
                gpGenerique->drawEffacer(gpScreen, gpKeyboard->getLigneVal()); break;
            default : break;
        }
        
        SDL_UpdateTexture(texture, NULL, gpScreen->pixels, gpScreen->pitch);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        if (SDL_GetTicks() < lastAnimTime + 20) SDL_Delay(lastAnimTime+20-SDL_GetTicks());
        lastAnimTime = SDL_GetTicks();
    }
    
    SDL_FreeSurface(gpScreen);
    SDL_DestroyTexture(texture);
    
    delete gpEncyclopedie;
    delete gpGenerique;
    delete gpKeyboard;
    delete gpCarte;
    delete gpJeu;
    delete gpAudio;
    
    SDL_ShowCursor(SDL_ENABLE);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
