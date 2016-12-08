
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
#define NB_LIVES 14
#define DICTIONARY      "file.txt"
#define NB_WORD         331612      /* Number of words   */
#define MAX_LEN         50          /* Max lenght of words              */



    SDL_Surface *ecran = NULL, *menu = NULL, *fond = NULL, *guessedword = NULL , *WinLose[NB_LIVES];
    SDL_Rect menuPosition,WordPos, BgPosition, HangPosition;
    SDL_Event ongame;//, textin;
    TTF_Font *police = NULL;
    SDL_Color Black = {0, 0, 20};
    SDL_Color White = {255,255,255};
    int play = 1, lives=1, onplay=0;
    
    
    const char* letterinput = "ddddddddddddddddddddddd";

    
    SDL_Surface *TextOnScreen = NULL;
    
    


 
    
    
    
    
int RandomWordPos (void)
{
   srand (time (NULL));
   return (int)(rand() / (double)RAND_MAX * (NB_WORD - 1));
}
    
    
    
    
    
/*
 * 
 */
char * RandomWord (int word_pos, const char * dictionary)
{
   char * word = NULL;
   
   
   if (dictionary != NULL)
   {
      FILE * fp = fopen (dictionary, "r");
      
      if (fp != NULL)
      {
         int count = 0;
         char buf [MAX_LEN];
         
         
         while (fgets (buf, sizeof buf, fp) != NULL)
         {
/
            if (count == word_pos)
            {

               {
                  char * p = strchr (buf, '\n');

                  if (p != NULL)
                  {
                     *p = 0;
                  }
               }
               word = (char*)(malloc (strlen (buf) + 1));
               
               if (word != NULL)
               {
                  strcpy (word, buf);
               }
               else
               
               break;
            }
            
            count++;
         }
         
         
         fclose (fp);
      }
   }
   
   
   return word;
}
    





    
void lSprites(){
    for(int i = 0; i < NB_LIVES; i++){
        WinLose[i]=NULL;
    }
}
void loadSprites(){
    fond = IMG_Load("Images/background.jpg");
    WinLose[0] = IMG_Load("Images/pendu-1.png");
    WinLose[1] = IMG_Load("Images/pendu-2.png");
    WinLose[2] = IMG_Load("Images/pendu-3.png");
    WinLose[3] = IMG_Load("Images/pendu-4.png");
    WinLose[4] = IMG_Load("Images/pendu-5.png");
    WinLose[5] = IMG_Load("Images/pendu-6.png");
    WinLose[6] = IMG_Load("Images/pendu-7.png");
    WinLose[7] = IMG_Load("Images/pendu-8.png");
    WinLose[8] = IMG_Load("Images/pendu-9.png");
    WinLose[9] = IMG_Load("Images/pendu-10.png");
    WinLose[10] = IMG_Load("Images/pendu-11.png");
    WinLose[11] = IMG_Load("Images/pendu-12.png");
    WinLose[12] = IMG_Load("Images/gained.png");
    WinLose[13] = IMG_Load("Images/lost.png");
}

int main(int argc, char *argv[])
{


    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_EnableKeyRepeat(300, 10);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Welcome to hangman", NULL);

    /* load font */
    police = TTF_OpenFont("angelina.ttf", 30);
    /* texte du menu */
    menu = TTF_RenderText_Blended(police, "press space to play", White);
    guessedword = TTF_RenderText_Shaded(police, letterinput, Black, White);
    /*  loadSprites  */
    lSprites();
    loadSprites();

    
    /*   game loop   */
    while (play)
    {
        SDL_WaitEvent(&ongame);
        switch(ongame.type)
        {
            case SDL_QUIT:
                play = 0;
                break;
            case SDL_KEYDOWN:
                switch(ongame.key.keysym.sym)
                  {
                    case SDLK_ESCAPE:
                    onplay =0;
                    play=0;
                    break;
                    case SDLK_w:
                    letterinput = "w";
                    break;
                    case SDLK_e:
                    letterinput = "e";
                    break;
                    case SDLK_r:
                    letterinput = "r";
                    break;
                    case SDLK_t:
                    letterinput = "t";
                    break;
                    case SDLK_y:
                    letterinput = "y";
                    break;
                    case SDLK_u:
                    letterinput = "u";
                    break;
                    case SDLK_i:
                    letterinput = "i";
                    break;
                    case SDLK_o:
                    letterinput = "o";
                    break;
                    case SDLK_p:
                    letterinput = "p";
                    break;
                    case SDLK_a:
                    letterinput = "a";
                    break;
                    case SDLK_s:
                    letterinput = "s";
                    break;
                    case SDLK_d:
                    letterinput = "d";
                    break;
                    case SDLK_f:
                    letterinput = "f";
                    break;
                    case SDLK_g:
                    letterinput = "g";
                    break;
                    case SDLK_h:
                    letterinput = "h";
                    break;
                    case SDLK_j:
                    letterinput = "i";
                    break;
                    case SDLK_k:
                    letterinput = "k";
                    break;
                    case SDLK_l:
                    letterinput = "l";
                    break;
                    case SDLK_z:
                    letterinput = "z";
                    break;
                    case SDLK_x:
                    letterinput = "x";
                    break;
                    case SDLK_c:
                    letterinput = "c";
                    break;
                    case SDLK_v:
                    letterinput = "v";
                    break;
                    case SDLK_b:
                    letterinput = "b";
                    break;
                    case SDLK_n:
                    letterinput = "n";
                    break;
                    case SDLK_m:
                    letterinput = "m";
                    break;
                    case SDLK_SPACE:
                        onplay++;
                        break;
                        
                        }
        }
        
        if (onplay>9)
        {
            onplay =1;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        BgPosition.x = 0;
        BgPosition.y = 0;
        HangPosition.x = 65;
        HangPosition.y = 100;
        WordPos.x = 220;
        WordPos.y = 360;

        

        SDL_BlitSurface(fond, NULL, ecran, &BgPosition); /* Blit du fond */
        
// //         SDL_BlitSurface(WinLose[7], NULL, ecran, &HangPosition);
// //         for (int i = 0; i<NB_LIVES; i++){            
// //                 SDL_BlitSurface(WinLose[i], NULL, ecran, &HangPosition);
// //             }
// //         }
        if (onplay){
//             if (onplay>=13) onplay=1;
            menu = NULL;
//             guessedword = TTF_RenderText_Blended(police, letterinput, White);
            guessedword = TTF_RenderText_Solid(police, letterinput, White);
            char * s_word = RandomWord (RandomWordPos (), DICTIONARY);
            letterinput =s_word;
            SDL_BlitSurface(guessedword, NULL, ecran, &WordPos);
            SDL_BlitSurface(WinLose[onplay+4], NULL, ecran, &HangPosition);
            
        }

        menuPosition.x = 207;
        menuPosition.y = 200;
        SDL_BlitSurface(menu, NULL, ecran, &menuPosition); /* Blit du menu */
        
        SDL_Flip(ecran);
    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(menu);
    SDL_FreeSurface(fond);
//     SDL_FreeSurface(TextOnScreen);
    for (int i = 0; i<NB_LIVES; i++){
        SDL_FreeSurface(WinLose[i]);
        }
//     SDL_FreeSurface(WinLose[7]);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(guessedword);
    SDL_Quit();

    return EXIT_SUCCESS;
}
