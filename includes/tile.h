#ifndef TILE_H
# define TILE_H

#include "SDLX/SDLX.h"
#include <emscripten.h>

#define MAX_MOVES 25

typedef struct Button
{
    SDLX_Sprite sprite;
    int         color;
    int         id;
    void (*OnClick)(struct Button *button, int correct);
    void (*OnHover)(struct Button *button);
}               Button;

typedef struct Mouse
{
    int         x;
    int         y;
    int         click;
}               Mouse;

typedef struct Context
{
    int         turn;
    int         lives;
    int         level;
    int         mul;
    int         moves;
    int         nbuttons;
    int         order[100];
    Mouse       mouse;
    Button      buttons[25];
    TTF_Font    *font;
    SDLX_Display*display;
}               Context;


Context *GetContext();
void    CreateButtons();

void PollButtons(int x, int y, int clicked);
void PollInput(int turn, Context *ctx);

void OnHover(Button *button);
void OnClick(Button *button, int correct);
void RenderButtons();

void ComputerTurn(Context *ctx);
void PlayerTurn(Context *ctx);
void WinScreen(Context *ctx);
void LoseScreen(Context *ctx);
void AIClick(Button *button);

#endif
