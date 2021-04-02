#include "../includes/tile.h"

static SDLX_Anim *colors;

void CreateButtons()
{
    SDL_Rect rect;
    Context  *ctx;
    int       i;
    int       n;

    i = 0;
    ctx = GetContext();
    if (!colors)
    {
        SDL_Texture *tex;
        SDL_Surface *surf;

        surf = IMG_Load("Assets/buttons.png");
        tex = SDL_CreateTextureFromSurface(ctx->display->renderer, surf);
        colors = SDLX_AnimLoad(tex, 5, 300, 300, SDL_FALSE, 0, 0);
    }
    ctx->mul++;
    ctx->nbuttons = ctx->mul * ctx->mul;

    rect.y = 0;
    rect.h = WIN_H / ctx->mul;
    rect.w = WIN_W / ctx->mul;
    while (i < ctx->mul)
    {
        n = 0;
        rect.x = 0;
        while(n < ctx->mul)
        {
            ctx->buttons[n + (i * ctx->mul)].sprite = colors->sprites[4];
            ctx->buttons[n + (i * ctx->mul)].sprite.dst = rect;
            ctx->buttons[n + (i * ctx->mul)].sprite.dstptr = &(ctx->buttons[n + (i * ctx->mul)].sprite.dst);
            ctx->buttons[n + (i * ctx->mul)].OnClick = &OnClick;
            ctx->buttons[n + (i * ctx->mul)].OnHover = &OnHover;
            ctx->buttons[n + (i * ctx->mul)].id = n + (i * ctx->mul);
            rect.x += rect.w;
            n++;
        }
        rect.y += rect.h;
        i++;
    }

}

void RenderButtons()
{
    Context *ctx;
    int i;

    i = 0;
    ctx = GetContext();
    while(i < ctx->nbuttons)
    {
        SDLX_RenderQueueAdd(0, ctx->buttons[i].sprite);
        ctx->buttons[i].sprite.src = colors->sprites[4].src;
        ctx->buttons[i].sprite.srcptr = colors->sprites[4].srcptr;
        i++;
    }
}

void OnClick(Button *button, int correct)
{
    if (correct)
    {
        button->sprite.src = colors->sprites[2].src;
        button->sprite.srcptr = colors->sprites[2].srcptr;
    }
    else
    {
        button->sprite.src = colors->sprites[1].src;
        button->sprite.srcptr = colors->sprites[1].srcptr;
    }
}

void OnHover(Button *button)
{
    button->sprite.src = colors->sprites[0].src;
    button->sprite.srcptr = colors->sprites[0].srcptr;
}

void AIClick(Button *button)
{
    button->sprite.src = colors->sprites[3].src;
    button->sprite.srcptr = colors->sprites[3].srcptr;
}
