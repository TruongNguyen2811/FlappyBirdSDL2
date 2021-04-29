#include <iostream>
#include <SDL.h>
#include "SDL_utils.h"
//#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

//**************************************************************
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 750;
const char WINDOW_TITLE[] = "Flappy Bird";
bool running=true;
bool menu=true;
int tuk=0,score=0,t=0,bt=0,birdx=450,birdy=250,r,e,z,f=0,g=10;
int x[1300];
int n[1300];
int m[1345][710];
SDL_Window* window;
SDL_Renderer* renderer;
void game();
void pipes();
bool gameover();
void checkscore();
//void help();
//void EndGameScreen();
void play();
bool quit();
void pipes3();
void pipes2();

int main(int argc, char* argv[])
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Texture *MenuScreen = loadTexture("MenuScreen.bmp", renderer);
    //SDL_Texture *bird = loadTexture("bird2.bmp", renderer);
    bool menu= true;
    SDL_Event e;
    while (menu)
    {
        SDL_Delay(200);
        renderTexture(MenuScreen, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        //renderTexture(bird, renderer,birdx, birdy, 70, 50);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e)) {
            // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
            if (e.type == SDL_QUIT) {
                menu = false;
                running =false;
                break;
            }
            // Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
            if (e.type == SDL_KEYDOWN) {
                // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
                if (e.key.keysym.sym == SDLK_ESCAPE||e.key.keysym.sym == SDLK_2)
                {
                    running = false;
                    menu=false;
                    break;
                }
                if(e.key.keysym.sym == SDLK_1)
                {
                    running =true;
                    menu = false;
                    break;
                }

                else
                break;
            }
        }
    }
    if(menu==false&&running==false)
    {
        SDL_DestroyTexture(MenuScreen);
         quitSDL(window, renderer);
    }
    if(menu==false&&running==true)
    {
        SDL_DestroyTexture(MenuScreen);
        quitSDL(window, renderer);
        game();
    }
    return 0;
}
void game()
{
    int g=10;
    for(int i=0;i<=1300;i++)
    {
        n[i]=0;
        x[i]=i;
    }
    for(int i=0;i<=1345;i++)
    {
        for(int k=0;k<=710;k++)
        {
            m[i][k]=0;
        }
    }
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Texture *background = loadTexture("Background2.bmp", renderer);
    SDL_Texture *ground= loadTexture("ground 2.bmp", renderer);
    if (background == nullptr||ground==nullptr){
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(background);
        quitSDL(window, renderer);
    }
    SDL_Texture *bird = loadTexture("bird2.bmp", renderer);
    SDL_Event e;
    while(running)
    {
    SDL_Delay(90);
    t++;
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture(ground, renderer,-20, 710, 1340, 40);
    pipes();
    pipes2();
    pipes3();
    renderTexture(bird, renderer,birdx, birdy, 70, 50);
    SDL_RenderPresent(renderer);
    gameover();
    tuk=0;


        while (SDL_PollEvent(&e)) {
            // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
            if (e.type == SDL_QUIT) {
                running = false;
                break;
            }
            // Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
            if (e.type == SDL_KEYDOWN) {
                // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
                if (e.key.keysym.sym == SDLK_ESCAPE) running = false;
                else tuk++;
                break;
            }
        }
      if(tuk>0)
      {
          bt=0;
          birdy=birdy-g/2*tuk*20;
      }
      else
      {
         bt++;
         birdy=birdy+25*bt;
      }
    }
    quitSDL(window, renderer);
}
void pipes()
{

    int i,k;
    SDL_Texture *pipeUp = loadTexture("pipe up.bmp", renderer);
    SDL_Texture *pipeDown= loadTexture("pipe down.bmp", renderer);
    if(t==1)
    {
        r=rand()%375;
        n[1300]=2;
        renderTexture(pipeUp, renderer, x[1300], 0, 100, r);
        renderTexture(pipeDown, renderer, x[1300], r+250, 100, 715-(r+250));
        SDL_DestroyTexture(pipeUp);
        SDL_DestroyTexture(pipeDown);

    }
    else {
    for(i=0;i<=1300;i++)
    {
        if(n[i]==2&&n[10]!=2)
        {
            n[i-15]=2;
            n[i]=0;
            renderTexture(pipeUp, renderer, x[i-15], 0, 100, r);
            renderTexture(pipeDown, renderer, x[i-15], r+250, 100, 715-(r+250));
            SDL_DestroyTexture(pipeUp);
            SDL_DestroyTexture(pipeDown);
            break;
        }

    }
        for(i=0;i<=1300;i++)
        {if(n[460]==2||n[490]==2||n[475]==2||n[520]==2)
        {

                for(k=0;k<=710;k++)
                {
                    if(k<=r||k>=r+250)
                        m[490][k]=2;
                        m[460][k]=2;
                        m[520][k]=2;                }
        }
        else
                 for(k=0;k<=710;k++)
                {
                    if(k<=r||k>=r+250)
                        m[490][k]=0;
                        m[460][k]=0;
                        m[520][k]=0;
                }
        }

    for(i=-5;i<=1300;i++)
    {
        if(n[10]==2)
        {
            n[10]=0;
            t=0;
            SDL_DestroyTexture(pipeUp);
            SDL_DestroyTexture(pipeDown);
            //SDL_RenderClear(renderer);
            break;
        }
        else break;

    }


}
}

void pipes2()
{
    int i,k;
      //r=(rand()%375);
    SDL_Texture *pipeUp2 = loadTexture("pipe up.bmp", renderer);
    SDL_Texture *pipeDown2= loadTexture("pipe down.bmp", renderer);
    if(n[880]==2)
    {
        e=(rand()%375)+75;
        n[1300]=1;
        renderTexture(pipeUp2, renderer, x[1300], 0, 100, e);
        renderTexture(pipeDown2, renderer, x[1300], e+250, 100, 715-(e+250));
        SDL_DestroyTexture(pipeUp2);
        SDL_DestroyTexture(pipeDown2);


    }
    else {
    for(i=0;i<=1300;i++)
    {
        if(n[i]==1&&n[10]!=1)
        {
            n[i-15]=1;
            n[i]=0;
            renderTexture(pipeUp2, renderer, x[i-15], 0, 100, e);
            renderTexture(pipeDown2, renderer, x[i-15], e+250, 100, 715-(e+250));
            SDL_DestroyTexture(pipeUp2);
            SDL_DestroyTexture(pipeDown2);
            break;
        }
    }
    for(i=0;i<=1300;i++)
        {if(n[445]==1)
        {

                for(k=0;k<=710;k++)
                {
                    if(k<=e||k>=e+250)
                        m[490][k]=1;
                }
        }
        else
                 for(k=0;k<=710;k++)
                {
                    if(k<=e||k>=e+250)
                        m[490][k]=0;
                }
        }
    for(i=-5;i<=1300;i++)
    {
        if(n[10]==1)
        {
            n[10]=0;
            SDL_DestroyTexture(pipeUp2);
            SDL_DestroyTexture(pipeDown2);
            break;
        }
        else break;

    }
}
}
void pipes3()
{
    int i,k;
    SDL_Texture *pipeUp2 = loadTexture("pipe up.bmp", renderer);
    SDL_Texture *pipeDown2= loadTexture("pipe down.bmp", renderer);
    if(n[880]==1)
    {
        z=(rand()%375)+75;
        n[1300]=3;
        renderTexture(pipeUp2, renderer, x[1300], 0, 100, z);
        renderTexture(pipeDown2, renderer, x[1300], z+250, 100, 715-(z+250));
        SDL_DestroyTexture(pipeUp2);
        SDL_DestroyTexture(pipeDown2);

    }
    else {
    for(i=0;i<=1300;i++)
    {
        if(n[i]==3&&n[10]!=3)
        {
            n[i-15]=3;
            n[i]=0;
            renderTexture(pipeUp2, renderer, x[i-15], 0, 100, z);
            renderTexture(pipeDown2, renderer, x[i-15], z+250, 100, 715-(z+250));
            SDL_DestroyTexture(pipeUp2);
            SDL_DestroyTexture(pipeDown2);
            break;
        }

    }
    for(i=0;i<=1300;i++)
        {if(n[445]==3)
        {

                for(k=0;k<=710;k++)
                {
                    if(k<=z||k>=z+250)
                        m[490][k]=3;
                }
        }
        else
                 for(k=0;k<=710;k++)
                {
                    if(k<=z||k>=z+250)
                        m[490][k]=0;
                }
        }
    }
    for(i=-5;i<=1300;i++)
    {
        if(n[10]==3)
        {
            n[10]=0;
            SDL_DestroyTexture(pipeUp2);
            SDL_DestroyTexture(pipeDown2);
            break;
        }
        else break;

    }
}
bool gameover()
{
    int i,k;
    if(birdy>=660)
    {
        running =false;
    }
    for(i=0;i<=1345;i++)
        {
            for( k=0;k<=710;k++)
            {
                if(m[490][birdy+50]!=0||m[490][birdy]!=0)
                {
                    running =false;
                    //break;
                }
            }
        }


}



