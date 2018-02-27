#include <iostream>
#include "SDL.h"
#include "SDL_gpu.h"

using namespace std;

unsigned gw = 640;
unsigned gh = 360;
unsigned stepScale = 1;
float w = gw * stepScale;
float h = gh * stepScale;

void setWindowIcon(GPU_Target* target, GPU_Image* icon)
{
	if (target == NULL || target->context == NULL)
		return;

	SDL_Surface* surf = GPU_CopySurfaceFromImage(icon);
	SDL_SetWindowIcon(SDL_GetWindowFromID(target->context->windowID), surf);
	SDL_FreeSurface(surf);
}

void setWindowTitle(GPU_Target* target, const char* title) {
	if (target == NULL || target->context == NULL)
		return;

	SDL_SetWindowTitle(SDL_GetWindowFromID(target->context->windowID), title);
}

void setWindowPosition(GPU_Target* target, int x, int y) {
	if (target == NULL || target->context == NULL)
		return;

	SDL_SetWindowPosition(SDL_GetWindowFromID(target->context->windowID), x, y);
}

void setWindowScale(float s) {
	if (s == stepScale)
		return;

	stepScale = s;
	w = gw * s;
	h = gh * s;
	
	GPU_SetWindowResolution(w, h);
}

int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else {
		cout << "SDL initialization succeeded!";
	}

	SDL_Color clearColor = { 23, 22, 30, 255 };
	SDL_Color circleColor = { 123, 111, 240, 255 };

	GPU_Target* screen = GPU_Init(w, h, GPU_DEFAULT_INIT_FLAGS);
	
	if (screen == NULL) {
		cout << "GPU INIT FAILED";
		return -1;
	}

	SDL_ShowCursor(SDL_DISABLE);
	setWindowTitle(screen, "TITLE");
	setWindowPosition(screen, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	GPU_Image* renderTargetImage;
	renderTargetImage = GPU_CreateImage(gw, gh, GPU_FORMAT_RGBA);
	GPU_LoadTarget(renderTargetImage);
	
	GPU_SetImageFilter(renderTargetImage, GPU_FILTER_NEAREST);
	
	Uint8 done;
	SDL_Event event;
	done = 0;

	unsigned mousex = 0;
	unsigned mousey = 0;

	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				done = 1;
			/* If a button on the mouse is pressed. */
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				/* If the left button was pressed. */
				if (event.button.button == SDL_BUTTON_LEFT)
					/* Quit the application */
					printf(" \n%d %d", event.button.x, event.button.y);
					//done = 1;
			}
			if (event.type == SDL_MOUSEMOTION)
			{
				mousex = event.motion.x;
				mousey = event.motion.y;
				///* If the mouse is moving to the left */
				//if (event.motion.xrel < 0)
				//	SDL_FillRect(screen, NULL, SDL_MapRGB(fmt, 255, 0, 0));
				///* If the mouse is moving to the right */
				//else if (event.motion.xrel > 0)
				//	SDL_FillRect(screen, NULL, SDL_MapRGB(fmt, 0, 255, 0));
				///* If the mouse is moving up */
				//else if (event.motion.yrel < 0)
				//	SDL_FillRect(screen, NULL, SDL_MapRGB(fmt, 0, 0, 255));
				///* If the mouse is moving down */
				//else if (event.motion.yrel > 0)
				//	SDL_FillRect(screen, NULL, SDL_MapRGB(fmt, 0, 255, 255));
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = 1;
				else if (event.key.keysym.sym == SDLK_1)
					setWindowScale(1);
				else if (event.key.keysym.sym == SDLK_2)
					setWindowScale(2);
				else if (event.key.keysym.sym == SDLK_3)
					setWindowScale(3);
				else if (event.key.keysym.sym == SDLK_4)
					setWindowScale(2.5);
				else if (event.key.keysym.sym == SDLK_f) {
					setWindowScale(3);
					GPU_SetFullscreen(!GPU_GetFullscreen(), 0);
				}
				else if (event.key.keysym.sym == SDLK_g) {
					setWindowScale(3);
					GPU_SetFullscreen(!GPU_GetFullscreen(), 1);
				}
				
					/*GPU_SetVirtualResolution(screen, 100, 100);
				else if (event.key.keysym.sym == SDLK_3)
					GPU_SetVirtualResolution(screen, 320, 240);
				else if (event.key.keysym.sym == SDLK_4)
					GPU_SetVirtualResolution(screen, 640, 480);
				else if (event.key.keysym.sym == SDLK_5)
					GPU_SetVirtualResolution(screen, 800, 600);*/
				//else if (event.key.keysym.sym == SDLK_SPACE)
				//{
				//	// Take a window capture
				//	GPU_FreeImage(image4);
				//	image4 = GPU_CopyImageFromTarget(screen);
				//}
			}
		}

		GPU_Target* target = renderTargetImage->target;

		GPU_ClearColor(target, clearColor);

		GPU_Circle(target, mousex, mousey, 3, circleColor);

		GPU_Circle(target, gw / 2, gh / 2, 20, circleColor);

		GPU_BlitScale(renderTargetImage, NULL, screen, w / 2, h / 2, stepScale, stepScale);
		//GPU_Blit(renderTargetImage, NULL, screen, renderTargetImage->w / 2, renderTargetImage->h / 2);

		GPU_Flip(screen);
	}

	GPU_FreeImage(renderTargetImage);

	GPU_Quit();

	return 0;
}