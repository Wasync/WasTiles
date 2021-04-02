#include "tile.h"

void PollInput(int turn, Context *ctx)
{
    SDL_Event event;
    int x, y;

    ctx->mouse.click  = 0;
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
			exit(0);
        if (event.type == SDL_MOUSEBUTTONDOWN)
            ctx->mouse.click = 1;
    }
    SDL_GetMouseState(&ctx->mouse.x, &ctx->mouse.y);
}

void PlayerTurn(Context *ctx)
{
    static int i;
    int correct;
    int id;
    int x;
    int y;

    x = ctx->mouse.x / (WIN_W / ctx->mul);
    y = ctx->mouse.y / (WIN_H / ctx->mul);
    id = x + y * ctx->mul;
    correct = (id == ctx->order[i]);

    if (i >= ctx->moves)
    {
        i = 0;
        ctx->level++;
        ctx->turn = 0;

        if (ctx->moves == MAX_MOVES)
            ctx->turn = 2;
        if (ctx->moves++ == (ctx->mul * ctx->mul))
        {
            CreateButtons();
            ctx->moves -= 1;
        }
        return ;
    }
    if (!ctx->mouse.click)
        OnHover((&ctx->buttons[id]));
    else
    {
        OnClick(&(ctx->buttons[id]), correct);
        if (correct)
            i++;
        else
            ctx->turn = 3;
    }
}


void ComputerTurn(Context *ctx)
{
    static int i;
    static int wait;

    wait ^= 1;
    if (wait == 0)
        return ;
    if (i < ctx->moves)
    {
        ctx->order[i] = rand() % (ctx->mul * ctx->mul);
        AIClick(&(ctx->buttons[ctx->order[i]]));
        i++;
    }
    else
    {
        i = 0;
        ctx->turn++;
    }
}

void WinScreen(Context *ctx)
{
    SDL_Rect dst;

    dst.x = 10;
    dst.y = 0;
    dst.w = WIN_W;
    dst.h = WIN_H;
    // SDLX_RenderMessage(ctx->font, "You have passed all 15 levels",NULL, &dst);
    if (ctx->mouse.click)
        ctx->turn = 0;
}

void LoseScreen(Context *ctx)
{
    SDL_Rect dst;
    char buff[10];

    dst.x = 10;
    dst.y = WIN_H / 3;
    dst.w = WIN_W - 20;
    dst.h = WIN_H / 3;
    // SDLX_RenderMessage(ctx->font, "Game Over",NULL, &dst);
    if (ctx->mouse.click)
    {
        ctx->turn = 0;
        ctx->level   = 0;
        ctx->moves = 2;
        ctx->mul = 1;
        CreateButtons();
    }
}
