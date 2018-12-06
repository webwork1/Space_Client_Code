#pragma once
#pragma once
#include <iostream>
#include "Game.h"

class state0 {

public:
	state0();
	~state0();

	//setting state
	void setState0(int x);

	//getting current state
	int getState0();

	void drawImagesState0();

	//resized x var
	void statezeroResizeX(int x);
	void statezeroResizeY(int x);

	//mouse stuff
	void getLeftButton0(bool x);
	void getMouseX0(int x);
	void getMouseY0(int x);

	//stuff for getting key pressed
	void getKeyPressed(int x);

	//getting state from main to go to state1
	void setStateFromMain(int x);

	//getting username
	string getUsername();

	//setting error for login
	void setLoginError(int x);
	//setting error for signup
	void setSignupError(int x);

	//set
	void setSignupLeft(int x);
private:


	Game *game = new Game();

	void declaringBackgroundStars0();

	//array for x and y variables
	int xInitial0[100];
	int yInitial0[100];

	SDL_Rect src, dest;

	bool tempBoolean = true;

	//images

	SDL_Texture* background;
	SDL_Texture* button;
	SDL_Texture* loginBackground;
};