#pragma once

#include "SDL.h"
#include <stdio.h>
#include <iostream>
#include "SDL_image.h"
#include <string>

using namespace std;
class Game{

public:
	Game();
	~Game();

	void init(const char *title, int xpos, int ypos, int width, int height);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }
	//sending resized x
	double getxVar() { return resizeImageVarX; }
	//sending resized y
	double getyVar() { return resizeImageVarY; }

	//stuff for mouse input
	
	//left button down
	bool getLeftButtonDown() { return mouseLeftDown; }
	//x and y mouse
	int getMouseX() { return mouseX; }
	int getMouseY() { return mouseY; }

	//keyboard events
	bool getUpKeyPressed() { return upKeyPressed; }
	bool getLeftKeyPressed() { return leftKeyPressed; }
	bool getRightKeyPressed() { return rightKeyPressed; }
	bool getDownKeyPressed() { return downKeyPressed; }
	bool getSpaceKeyPressed() { return spaceKeyPressed; }
	bool getFKeyPressed() { return FKeyPressed; }

	void stateStuff();

	int resizeImageVar = 1;

	static SDL_Renderer* renderer;

	//VARIABLE FOR STATE
	int state = 0;

	//getting state
	int getStateGame() { return state; }

	//getting player x and y cords and rotation angle
	int returnPlayerX();
	int returnPlayerY();
	int returnPlayerR();
	double returnSpeedX();
	double returnSpeedY();
	string returnSpacekey();

	void returnWhatKeyPressed();

	//sending variable to main to send to server
	void sendingUserInput(string s);
	string getsendVariable();
	void setSendVariable();
private:

	//variables for mouse input
	bool mouseLeftDown = false;
	int mouseX = 0;
	int mouseY = 0;

	int resizeImageVarX = 1500;
	int resizeImageVarY = 1000;

	//keyboard events
	bool upKeyPressed = false;
	bool leftKeyPressed = false;
	bool rightKeyPressed = false;
	bool downKeyPressed = false;
	bool spaceKeyPressed = false;
	bool FKeyPressed = false;

	bool isRunning;
	SDL_Window *window;
	
};

