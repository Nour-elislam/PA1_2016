
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
    SDL_Surface *ecran = NULL, *texte = NULL, *fond = NULL;
    SDL_Rect TextePosition, BgPosition;
    SDL_Event ongame;//, textin;
    TTF_Font *police = NULL;
    SDL_Color Black = {0, 0, 0};
    SDL_Color White = {255,255,255};
    int play = 1;

    
    SDL_Surface *TextOnScreen = NULL;
    
    	


int main(int argc, char *argv[])
{


    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Welcome to hangman", NULL);

    fond = IMG_Load("Images/background.jpg");

  
    police = TTF_OpenFont("angelina.ttf", 65);
   
    texte = TTF_RenderText_Blended(police, "YOU WILL HANG ! !", White);

    while (play)
    {
        SDL_WaitEvent(&ongame);
        switch(ongame.type)
        {
            case SDL_QUIT:
                play = 0;
                break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        BgPosition.x = 0;
        BgPosition.y = 0;
        

        SDL_BlitSurface(fond, NULL, ecran, &BgPosition); 

        TextePosition.x = 60;
        TextePosition.y = 370;
        SDL_BlitSurface(texte, NULL, ecran, &TextePosition); 
        SDL_Flip(ecran);
    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(TextOnScreen);
    SDL_Quit();

    return EXIT_SUCCESS;
}
