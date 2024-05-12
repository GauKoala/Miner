#ifndef BUTTONS_H
#define BUTTONS_H
#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>


class LButton
{
public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//Shows button sprite
	void render(int i, int j);

	//Shows button sprite when we lose
	void loseRender(int i, int j);

private:
	//Top left position
	SDL_Point mPosition;
};
#endif
