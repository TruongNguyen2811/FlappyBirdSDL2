#include <iostream>
#include <SDL.h>
#include "SDL_utils.h"
#include <cmath>
#include <cstdlib>
using namespace std;

//**************************************************************
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 750;
const char WINDOW_TITLE[] = "Flappy Bird";
bool running=true;
int tuk=0,score=0,t=0,bt=0,birdx=450,birdy=250,check=0,r,e,z;
int x[1300];
int n[1300];
SDL_Window* window;
SDL_Renderer* renderer;
void game();
bool gameover();
void checkscore();
void EndGameScreen();
void pipes();
void pipes3();
void pipes2();
SDL_Texture *background ;

int main(int argc, char* argv[])
{
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Texture *MenuScreen = loadTexture("MenuScreen.bmp", renderer);
    bool menu= true;
    SDL_Event e;
    while (menu)
    {
        SDL_Delay(200);
        renderTexture(MenuScreen, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
    SDL_DestroyTexture(MenuScreen);
    quitSDL(window, renderer);
    if (running==true) game();
    return 0;
}
void game()
{
    int g=50;
    for(int i=0;i<=1300;i++)
    {
        n[i]=0;
        x[i]=i;
    }
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Texture *background = loadTexture("BackgroundNight2.bmp", renderer);
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
    SDL_Delay(40);
    t++;
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture(ground, renderer,-20, 710, 1340, 40);
    pipes();
    pipes2();
    pipes3();
    renderTexture(bird, renderer,birdx, birdy, 70, 50);
    SDL_RenderPresent(renderer);
    gameover();
    checkscore();
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
      /*if(tuk>0)
      {
          bt=0;
          birdy=birdy-g/2*tuk*15;
      }
      else
      {
         bt++;
         birdy=birdy+15*bt;
      }
    }*/
        if(tuk>0) {bt = -80.0f;}
        else {bt = bt + g*0.4f;}
    birdy = birdy + bt*0.4f;
}
    quitSDL(window, renderer);
    EndGameScreen();

}
void pipes()
{

    int i;
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
    }
        if(n[475]==2||n[400]==2||n[445]==2)
        {
            if(birdy<=r||(birdy+50)>=(r+250))
            {
                check=1;
                gameover();
            }
            else
                check=0;

        }
      if(n[10]==2)
        {
            n[10]=0;
            t=0;
            SDL_DestroyTexture(pipeUp);
            SDL_DestroyTexture(pipeDown);
        }
}

void pipes2()
{
    int i;
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
    }
        if(n[475]==1||n[400]==1||n[445]==1)
        {
            if(birdy<=e||birdy+50>=e+250)
            {
                check=1;
                gameover();
            }
            else
                check=0;
        }
    if(n[10]==1)
        {
            n[10]=0;
            SDL_DestroyTexture(pipeUp2);
            SDL_DestroyTexture(pipeDown2);
        }
}
void pipes3()
{
    int i;
    SDL_Texture *pipeUp3 = loadTexture("pipe up.bmp", renderer);
    SDL_Texture *pipeDown3= loadTexture("pipe down.bmp", renderer);
    if(n[880]==1)
    {
        z=(rand()%375)+75;
        n[1300]=3;
        renderTexture(pipeUp3, renderer, x[1300], 0, 100, z);
        renderTexture(pipeDown3, renderer, x[1300], z+250, 100, 715-(z+250));
        SDL_DestroyTexture(pipeUp3);
        SDL_DestroyTexture(pipeDown3);

    }
    else {
    for(i=0;i<=1300;i++)
    {
        if(n[i]==3&&n[10]!=3)
        {
            n[i-15]=3;
            n[i]=0;
            renderTexture(pipeUp3, renderer, x[i-15], 0, 100, z);
            renderTexture(pipeDown3, renderer, x[i-15], z+250, 100, 715-(z+250));
            SDL_DestroyTexture(pipeUp3);
            SDL_DestroyTexture(pipeDown3);
            break;
        }
    }
    }
        if(n[475]==3||n[400]==3||n[445]==3)
        {
            if(birdy<=z||birdy+50>=z+250)
            {
                check=1;
                gameover();
            }
            else
                check=0;
        }
        if(n[10]==3)
        {
            n[10]=0;
            SDL_DestroyTexture(pipeUp3);
            SDL_DestroyTexture(pipeDown3);

        }
}
bool gameover()
{
    if(birdy>=660)
    {
        running =false;
    }
    if(check==1)
    {
        running =false;
    }
}
void checkscore()
{
    if(n[370]!=0)
    {
        score++;
    }
}
void EndGameScreen()
{
    cout<<"       ~GAME OVER~       "<<endl;
    cout<<"YOUR SCORE: "<<score<<endl;
}

