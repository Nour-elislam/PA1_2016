
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
#define NB_IMG 14
#define NB_LIVES 6
#define DICTIONARY      "file.txt"
#define NB_TEST         12          
#define NB_WORD         331612      
#define MAX_LEN         50          
#define NOT_FOUND  '-' 



    SDL_Surface *ecran = NULL, *menu = NULL, *menu2 = NULL, *fond = NULL, *guessedword = NULL , *WinLose[NB_IMG];
    SDL_Rect menuPosition, WordPos, WinLosePos, BgPosition, HangPosition, menu2Pos;
    SDL_Event ongame;//, textin;
    TTF_Font *police = NULL;
    SDL_Color Black = {0, 0, 20};
    SDL_Color White = {255,255,255};
    char t_wordtoguess[MAX_LEN];
    char* wordtoguess;
    char t_wordtoshow[MAX_LEN];
    char* wordtoshow;
    int play = 1, lives=1, onplay=0, onmenu, onmenu2, newgame;
    size_t WordLen;
    
    const char* letterinput = "ddddddddddddddddddddddd";

    
    SDL_Surface *TextOnScreen = NULL;
    


 
    
void LoadRandomWord();
    
    
int RandomWordPos (void)
{
   srand (time (NULL));
   return (int)(rand() / (double)RAND_MAX * (NB_WORD - 1));

}
    
    
    
    
    
/*
 * Recherche du mot d'apres le nombre tire au sort par RandomWordPos.
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
    for(int i = 0; i < NB_IMG; i++){
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

void Initialisation(){
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_EnableKeyRepeat(300, 10);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Welcome to hangman", NULL);

    /* load font */
    police = TTF_OpenFont("angelina.ttf", 30);
    
        /*  loadSprites  */
    lSprites();
    loadSprites();

        /* Init positions */
    BgPosition.x = 0;
    BgPosition.y = 0;
    HangPosition.x = 65;
    HangPosition.y = 100;
    WordPos.x = 245;
    WordPos.y = 360;
    menuPosition.x = 207;
    menuPosition.y = 200;
    WinLosePos.x = 180;
    WinLosePos.y = 70;
    menu2Pos.x = 200;
    menu2Pos.y =20;
    
    onmenu=1;
    
    menu = TTF_RenderText_Blended(police, "press space to play", White);
    menu2 = TTF_RenderText_Blended(police, "press Enter to replay", Black);
    LoadRandomWord(); 
    

    
}

void LoadRandomWord(){
    wordtoguess =RandomWord (RandomWordPos (), DICTIONARY);
    strcpy(t_wordtoguess, wordtoguess);
    WordLen = strlen(t_wordtoguess);
   printf ("longueur = %d\n", WordLen);
//    for(int i = 0; i < WordLen; i++){
//        printf("%c\t",t_wordtoguess[i]);
// }
    
 //   guessedword = TTF_RenderText_Solid(police,wordtoguess , White);
    
}
void losewin(){
    memset (t_wordtoshow, 0, sizeof (t_wordtoshow));
    for(int i = 0; i < WordLen; i++){
        t_wordtoshow[i]=NOT_FOUND;
    }
    t_wordtoshow[0]=t_wordtoguess[0];
    t_wordtoshow[WordLen-1]=t_wordtoguess[WordLen-1];
    wordtoshow=(char*)t_wordtoshow;
    guessedword = TTF_RenderText_Solid(police,wordtoshow , White);
}

int main(int argc, char *argv[])
{


    Initialisation();
    



    
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
                    case SDLK_a:
                        letterinput = "A";
                        break;
                    case SDLK_z:
                        letterinput = "Z";
                        break;
                    case SDLK_e:
                        letterinput = "E";
                        break;
                    case SDLK_r:
                        letterinput = "R";
                        break;
                    case SDLK_t:
                        letterinput = "T";
                        break;
                    case SDLK_y:
                        letterinput = "Y";
                        break;
                    case SDLK_u:
                        letterinput = "U";
                        break;
                    case SDLK_i:
                        letterinput = "I";
                        break;
                    case SDLK_o:
                        letterinput = "O";
                        break;
                    case SDLK_p:
                        letterinput = "P";
                        break;
                    case SDLK_q:
                        letterinput = "Q";
                        break;
                    case SDLK_s:
                        letterinput = "S";
                        break;
                    case SDLK_d:
                        letterinput = "D";
                        break;
                    case SDLK_f:
                        letterinput = "F";
                    break;
                    case SDLK_g:
                        letterinput = "G";
                    break;
                    case SDLK_h:
                        letterinput = "H";
                    break;
                    case SDLK_j:
                        letterinput = "J";
                    break;
                    case SDLK_k:
                        letterinput = "K";
                    break;
                    case SDLK_l:
                        letterinput = "L";
                    break;
                    case SDLK_m:
                        letterinput = "M";
                    case SDLK_w:
                        letterinput = "W";
                    break;
                    case SDLK_x:
                        letterinput = "X";
                    case SDLK_c:
                        letterinput = "C";
                    break;
                    case SDLK_v:
                        letterinput = "V";
                    break;
                    case SDLK_b:
                        letterinput = "B";
                    break;
                    case SDLK_n:
                        letterinput = "N";
                    break;

                    case SDLK_SPACE:
                        onplay++;
                        break;
                    case SDLK_RETURN:
                        onmenu2=0;
                        onplay=1;
                        newgame=1;
                        break;
                        
                        }
        }
        
        if (onplay>=9)onplay =9;
        if(onplay>7)onmenu2 =1;



        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        if(newgame){
            LoadRandomWord();
            newgame =0;
        }


        
        /* screen blit */
        SDL_BlitSurface(fond, NULL, ecran, &BgPosition); 
                if (onmenu2){
            SDL_BlitSurface(menu2, NULL, ecran, &menu2Pos);
        }
        

        if (onplay){
//             if (onplay>=13) onplay=1;
//             menu = NULL;


//             char * s_word = RandomWord (RandomWordPos (), DICTIONARY);
            
//             letterinput =s_word;
            
            losewin();

            
            
            onmenu =0;
            
            /* word blit */
            SDL_BlitSurface(guessedword, NULL, ecran, &WordPos);
            
            /*    hangman blit */
            if (onplay>7){
                SDL_BlitSurface(WinLose[onplay+4], NULL, ecran, &WinLosePos);
                
            }
            else{
            SDL_BlitSurface(WinLose[onplay+4], NULL, ecran, &HangPosition);
            }
            
            
        }
        if(onmenu) {
                    /* menu Blit */
        SDL_BlitSurface(menu, NULL, ecran, &menuPosition); 
        }


        
        SDL_Flip(ecran);
    }

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(menu);
    SDL_FreeSurface(menu2);
    SDL_FreeSurface(fond);
//     SDL_FreeSurface(TextOnScreen);
    for (int i = 0; i<NB_IMG; i++){
        SDL_FreeSurface(WinLose[i]);
        }
//     SDL_FreeSurface(WinLose[7]);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(guessedword);
    SDL_Quit();

    return EXIT_SUCCESS;
}
