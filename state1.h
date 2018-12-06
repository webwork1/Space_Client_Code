#pragma once
#include <iostream>
#include "Game.h"

class state1 {
	 
public:
	state1();
	~state1();

	//setting state
	void setState(int x);

	//getting current state
	int getState();

	void drawImagesState1();

	//resized x var
	void stateoneResizeX(int x);
	void stateoneResizeY(int x);

	//mouse stuff
	void getLeftButton(bool x);
	void getMouseX(int x);
	void getMouseY(int x);

	//getting players connected
	void getplayersConnected(int x);

private:

	Game *game = new Game();
	SDL_Rect src, dest;

	void declaringBackgroundStars();

	//array for x and y variables
	int xInitial[100];
	int yInitial[100];

	//used for generating stars
	bool tempBoolean = true;

	//images
	SDL_Texture* background;
	SDL_Texture* playButton;

};