#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "state1.h"
#include "state2.h"
#include <SDL_ttf.h>
#include <string>
#include "state0.h"

SDL_Renderer* Game::renderer = nullptr;

//object for state1
state1* stateone;

//object for state2
state2* statetwo;

//object for state0
state0* statezero;

//what key is pressed
char keyPressed = ' ';

//variable for sending text to server
string sendVariable = "";

Game::Game()
{
}


Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		std::cout << "Subsystems initialized..." <<std::endl;

		//initial height and width
		resizeImageVarX = 2250;
		resizeImageVarY = 1500;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_RESIZABLE);
		if (window) {
			std::cout << "Window created" << std::endl;
			SDL_SetWindowResizable(window, SDL_TRUE);
			SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		}
		
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	if (TTF_Init() < 0) {
		cout << "error loading fonts" << endl;
	}

	//objects for states
	statezero = new state0();
	stateone = new state1();
	statetwo = new state2();
}

void Game::handleEvents() {

	SDL_Event event;

	SDL_PollEvent(&event);

	//SETTING MOUSE ATTRIBUTES FOR EACH STATE

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		mouseLeftDown = true;
	}
	else {
		mouseLeftDown = false;
	}

	//mouse x and y
	if (event.type == SDL_MOUSEMOTION) {
		mouseX = event.button.x;
		mouseY = event.button.y;
	}
	
	//KEYBOARD EVENTS FOR EACH STATE
	Uint8 const *keystate = SDL_GetKeyboardState(NULL);

	keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_ESCAPE]) {
					TTF_Quit();
			isRunning = false;
	}
		//quitting game
	switch (event.type) {

		case SDL_QUIT:
			TTF_Quit();
			isRunning = false;
			
			break;
		
		default:
			break;
	}

	// if key is pressed, get what key is pressed
	if (event.type == SDL_KEYDOWN) {

		//if key pressed is a number or letter..
		if ((event.key.keysym.sym >= 48 && event.key.keysym.sym <= 122) || keystate[SDL_SCANCODE_BACKSPACE]) {

			//if user does backspace
			if (keystate[SDL_SCANCODE_BACKSPACE]) {

				keyPressed = '&';
				returnWhatKeyPressed();

			}
			else {
				keyPressed = event.key.keysym.sym;
				returnWhatKeyPressed();
			}

		}

	}


	if (keystate[SDL_SCANCODE_UP]) {
		upKeyPressed = true;
	}
	else {
		upKeyPressed = false;
	}

	if (keystate[SDL_SCANCODE_DOWN]) {
		downKeyPressed = true;
	}
	else {
		downKeyPressed = false;
	}

	if (keystate[SDL_SCANCODE_LEFT]) {
		leftKeyPressed = true;
	}
	else {
		leftKeyPressed = false;
	}

	if (keystate[SDL_SCANCODE_RIGHT]) {
		rightKeyPressed = true;
	}
	else {
		rightKeyPressed = false;
	}

	if (keystate[SDL_SCANCODE_SPACE]) {
		spaceKeyPressed = true;
	}
	else {
		spaceKeyPressed = false;
	}

	if (keystate[SDL_SCANCODE_F]) {
		FKeyPressed = true;
	}
	else {
		FKeyPressed = false;
	}

	//setting new x and y when window is resized

	if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
		SDL_GetWindowSize(window, &resizeImageVarX,&resizeImageVarY);
	}
	
}

void Game::update() {


//updating Images;
	stateStuff();
}

void Game::render() {
	SDL_RenderClear(renderer);

	//this is where stuff is added to render

	switch (state) {
		case 0:
			statezero->drawImagesState0();
			keyPressed = ' ';
			returnWhatKeyPressed();
		break;
		case 1:
		stateone->drawImagesState1();
		break;
		case 2:
		statetwo->drawImagesState2();
		
		default:
			break;

	}

	SDL_RenderPresent(renderer);
	
}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;

}

//////////////////////////////         STATES                /////////////////////////////

void Game::stateStuff(){

//defining state
//checking for changed state
switch (state) {
case 0:
	state = statezero->getState0();
	break;
case 1:
	state = stateone->getState();
	break;
case 2:
	state = statetwo->getState2();
default:
	break;

}
//setting state
switch (state) {
case 0:
	statezero->setState0(0);
	break;

case 1:

	stateone->setState(1);

	break;

case 2:
	statetwo->setState2(2);
	break;

default:
	break;
}
}

int Game::returnPlayerX() {
	return statetwo->getPlayerX();
}

int Game::returnPlayerY() {
	return statetwo->getPlayerY();
}

int Game::returnPlayerR() {
	return statetwo->getPlayerR();
}

double Game::returnSpeedX() {
	return statetwo->getPlayerSpeedX();
}

double Game::returnSpeedY() {
	return statetwo->getPlayerSpeedY();
}

string Game::returnSpacekey() {

	return statetwo->getPlayerSpacebar();
}


//returning what key is pressed and key pressed variable
void Game::returnWhatKeyPressed() {
	statezero->getKeyPressed(keyPressed);
}

//sending user input from any state
void Game::sendingUserInput(string s) {

	sendVariable = s;
}

string Game::getsendVariable() {
	return sendVariable;
}

void Game:: setSendVariable() {
	sendVariable = "";
}


