#include "tile.h"

typedef void (*GameFunc)(Context *context);
static Context ctx;
GameFunc funcs[4];

void init()
{
    SDLX_Start();
    funcs[0] = ComputerTurn;
    funcs[1] = PlayerTurn;
    funcs[2] = WinScreen;
    funcs[3] = LoseScreen;
    ctx.display = SDLX_DisplayGet();
    ctx.level   = 0;
    ctx.moves = 2;
    ctx.mul = 1;
    // ctx.font = TTF_OpenFont("Assets/Pixel_Font.ttf", 14);
}

Context *GetContext(){return &ctx;}
SDLX_Display *display;

void main_loop(void)
{

	PollInput(ctx.turn, &ctx);
	if (ctx.turn < 2)
		RenderButtons();
	SDLX_RenderQueueDisplay(SDLX_RenderQueueFetch(NULL)[0], display);
	// SDLX_RenderMessage(ctx.font, SDL_itoa(ctx.level, buff, 10), NULL, &dst);
	SDL_RenderPresent(display->renderer);
	SDLX_ResetWindow();
	funcs[ctx.turn](&ctx);
	if (ctx.turn == 0)
		SDL_Delay(250);
	SDLX_FPSAdjust();
}


int main(void)
{
	SDL_Rect dst;
	char buff[10];

	dst.x = 5;
	dst.y = 5;
	dst.w = 20;
	dst.h = 20;

	init();
	display = SDLX_DisplayGet();
	ctx.display = display;

	CreateButtons();
	emscripten_set_main_loop(main_loop, 0, 1);
}
