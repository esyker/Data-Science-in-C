#ifndef PARTE_GRAFICA_H_INCLUDED
#define PARTE_GRAFICA_H_INCLUDED


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.1415
#define ECRA_SIZE 690        // main game space size
#define LEFT_BAR_SIZE 150     // left white bar size
#define WINDOW_POSX 200       // initial position of the window: x
#define WINDOW_POSY 200       // initial position of the window: y
#define SQUARE_SEPARATOR 8    // square separator in px
#define TABLE_SIZE 650        // main game space size
#define MARGIN 5
#define MOUSE 100

#include "trips.h"

int menuGrafic();
void WriteLine(int stepstation);
void DrawCircle(SDL_Renderer*, int, int, int,Uint8, Uint8, Uint8, Uint8 a);
void Drawpoints(SDL_Renderer*, int, int, int, int, int);
int DistanciaMouse(int mouseY, int mouseX, int x, int y, float theta);
void InitEverything(int , int , TTF_Font **, SDL_Surface **, SDL_Window ** , SDL_Renderer ** );
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int , int );
SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
int RenderLogo(int, int, SDL_Surface *, SDL_Renderer *);
void RenderTable( TTF_Font *, SDL_Surface **, SDL_Renderer *);





#endif // PARTE_GRAFICA_H_INCLUDED
