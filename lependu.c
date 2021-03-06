
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
#define NB_IMG 14 		// nombre d'image	
		
#define DICTIONARY      "file.txt" // FICHIER DICTIONNAIRE AVEC TOUT LES MOTS

#define NB_WORD         331612     // le nombre de mots dans le fichier dictionnaire
#define MAX_LEN         50          // LONGEUR MAXIMAL D'UN MOT
#define NOT_FOUND  '-' 




    SDL_Surface *ecran = NULL,		/**/
 	*menu = NULL, 			/*TEXTE DU MENU*/
 	*menu2 = NULL,			/*TEXTE DU 2eme Menu*/
 	*fond = NULL,			/*arriere plan*/
 	*guessedword = NULL ,/*mot devinee*/
 	*WinLose[NB_IMG];/*lependu gangnat ou perdu*/
    SDL_Rect menuPosition, WordPos, winpos, losePos, BgPosition, HangPosition, menu2Pos;				//position de rectangle
    SDL_Event ongame;        		// evenement pricipal
    TTF_Font *menupolice = NULL, *wordpolice = NULL; // CHARGEMENT DES POLICES
    SDL_Color Black = {0, 0, 0}; 
    SDL_Color White = {255,255,255};			// DEF COULEUR


    char t_wordtoguess[MAX_LEN];		// mot a deviner
    char* wordtoguess;				
    char t_wordtoshow[MAX_LEN];			// mot deviner et afficher
    char* wordtoshow;
  
    int play = 1, onplay=0, onmenu = 1, onmenu2, newgame=1; // initialisation
    unsigned int count = 0;
    size_t WordLen;   // longeur des mots
 
    
    char letterinput = 'd';   //

    
    

 
    
void LoadRandomWord();
int existe(char *str, char caract);
    
int RandomWordPos (void)
{// fonction qui retourne un nombre aleatoire parmi le nombre des mots
   srand (time (NULL));
   return (int)(rand() / (double)RAND_MAX * (NB_WORD - 1));

}
    
    
    
   

char * RandomWord (int word_pos, const char * dictionary)
{// fonction qui prend en paramatre la position et le fichier dictionnaire.txt et retourne le mot correspondant 
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
    

    
void lSprites(){ // initialisation des sprites
    for(int i = 0; i < NB_IMG; i++){
        WinLose[i]=NULL;
    }
}
void loadSprites(){ // chargement des images
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

void Initialisation(){ // INITIALISATION DE LA SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_EnableKeyRepeat(300, 10);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Welcome to hangman", NULL);

    /* load font */
    menupolice = TTF_OpenFont("Polices/angelina.ttf", 40);
    wordpolice = TTF_OpenFont("Polices/arial.ttf", 30);
    
        /*  loadSprites  */
    lSprites();
    loadSprites();

        /* Init positions */
    BgPosition.x = 0;
    BgPosition.y = 0;
    HangPosition.x = 65;
    HangPosition.y = 100;
    WordPos.x = 230;
    WordPos.y = 360;
    menuPosition.x = 207;
    menuPosition.y = 200;
    winpos.x = 180;
    winpos.y = 70;
    losePos.x = 310;
    losePos.y = 70;
    menu2Pos.x = 200;
    menu2Pos.y =20;
    
    onmenu=1;
    
    menu = TTF_RenderText_Blended(menupolice, "press ENTER to play", White);
    menu2 = TTF_RenderText_Blended(menupolice, "press ENTER to replay", Black);
    LoadRandomWord(); 
    

    
}


int existe(char *str, char caract)
    { // fonction verifier si la lettre saisie existe elle retourne 1 sinon 0
    unsigned int i;
    for(i=0 ; i<WordLen ; i++)
    {
      if (str[i] == caract)
       return 1;
    }
    return (0);
    }


    
void LoadRandomWord(){ // procedure Charge le mot aleatoire dans la surface
    wordtoguess =RandomWord (RandomWordPos (), DICTIONARY);
    strcpy(t_wordtoguess, wordtoguess);
    WordLen = strlen(t_wordtoguess);
   printf ("longueur = %d\n", WordLen);
   printf("%s\n",t_wordtoguess);

}



void initlosewin(){ // procedure initialise le mot a deviner et a afficher sur ecran
    memset (t_wordtoshow, 0, sizeof (t_wordtoshow));
    for(int i = 1; i < WordLen-1; i++){
        t_wordtoshow[i]=NOT_FOUND;
        if(t_wordtoguess[0]==t_wordtoguess[i]){
            t_wordtoshow[i]=t_wordtoguess[0];
        }
        if(t_wordtoguess[WordLen-1]==t_wordtoguess[i]){
            t_wordtoshow[i]=t_wordtoguess[WordLen-1];
            
        }
    }
    t_wordtoshow[0]=t_wordtoguess[0];
    t_wordtoshow[WordLen-1]=t_wordtoguess[WordLen-1];
    wordtoshow=(char*)t_wordtoshow;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
}


void playlosewin (){ // procedure mise a jour du mot a deviner et a afficher sur ecran
    for(int i = 1; i < WordLen-1; i++){
        if(t_wordtoguess[i]==letterinput){
            t_wordtoshow[i]=letterinput;
        }
    }
     guessedword = TTF_RenderText_Solid(wordpolice,wordtoshow , White);
}

int win(){ // Detection de l'evenement gagner';p
    if (strcmp(wordtoguess,wordtoshow) == 0)
    return 1;
    else return 0;
}
void Handlekeyboard(){// gestion du clavier
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
                        play=0;
                        break;
                    case SDLK_a:
                        letterinput = 'A';                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;                        
                        break;
                    case SDLK_z:
                        letterinput = 'Z';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_e:
                        letterinput = 'E';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_r:
                        letterinput = 'R';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        
                        break;
                    case SDLK_t:
                        letterinput = 'T';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_y:
                        letterinput = 'Y';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_u:
                        letterinput = 'U';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_i:
                        letterinput = 'I';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_o:
                        letterinput = 'O';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_p:
                        letterinput = 'P';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_q:
                        letterinput = 'Q';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_s:
                        letterinput = 'S';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_d:
                        letterinput = 'D';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_f:
                        letterinput = 'F';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_g:
                        letterinput = 'G';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_h:
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        letterinput = 'H';
                        break;
                    case SDLK_j:
                        letterinput = 'J';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_k:
                        letterinput = 'K';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_l:
                        letterinput = 'L';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_m:
                        letterinput = 'M';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_w:
                        letterinput = 'W';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_x:
                        letterinput = 'X';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                    case SDLK_c:
                        letterinput = 'C';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_v:
                        letterinput = 'V';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_b:
                        letterinput = 'B';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;
                    case SDLK_n:
                        letterinput = 'N';
                          
                        if ((existe(t_wordtoguess, letterinput)==0) && count<7) count++;
                        break;


                    case SDLK_RETURN:
                        if(onmenu || onmenu2 ){ // passage du menu1 ou menu2 du jeu
                            onmenu = 0;
                            onmenu2=0;
                            onplay=1;
                            newgame=1;
                            count = 0;
                        }
                        break;
                        
                        }
        }
}


int main(int argc, char *argv[])
{
    Initialisation();    
    /* Boucle principal de jeu */
    while (play)
    {
      

	Handlekeyboard();

        

        if(newgame){
            LoadRandomWord();
            initlosewin();
            newgame =0;
        }
              	        /* screen blit */
        SDL_BlitSurface(fond, NULL, ecran, &BgPosition); 

        

        if (onmenu2){
            SDL_BlitSurface(menu2, NULL, ecran, &menu2Pos);
        }
        
        if(win()){
            onplay = 0;
	    onmenu2 = 1;
            SDL_BlitSurface(WinLose[NB_IMG-2], NULL, ecran, &winpos);
	    SDL_BlitSurface(menu2, NULL, ecran, &menu2Pos);
        }

        if (onplay){
            playlosewin();
            /* word blit */
            SDL_BlitSurface(guessedword, NULL, ecran, &WordPos);
            
            /*    hangman blit */
                if (count == 7){
                    SDL_BlitSurface(WinLose[count+4], NULL, ecran, &HangPosition);
                    SDL_BlitSurface(WinLose[NB_IMG-1], NULL, ecran, &losePos);

                    onmenu2 =1;

                    
                }
                if (count < 7){
                    SDL_BlitSurface(WinLose[count+4], NULL, ecran, &HangPosition);            
                }
        }
            if(onmenu) {
        SDL_BlitSurface(menu, NULL, ecran, &menuPosition); 
        
        }
    
        SDL_Flip(ecran);
    }
 
    
    
    

    TTF_CloseFont(menupolice);
    TTF_CloseFont(wordpolice);
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
