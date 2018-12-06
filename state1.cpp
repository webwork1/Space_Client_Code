#include "state1.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <SDL_ttf.h>
#include <sstream> 

//variables

//state Variable
int setState1 = 1;

//state in state one
int stateOfState1 = 0;
//resizing x and y variable to scale of window
double resizeImageXVar1 = 1;
double resizeImageYVar1 = 1;

//is left button pressed
bool isLeftButtonPressed = false;
int mouseX = 0;
int mouseY = 0;

//players connected to the server
int playersConnected = 0;

state1::state1()
{
	//images
	playButton = TextureManager::LoadTexture("assets/playButton.png");
	background = TextureManager::LoadTexture("assets/background.png");

	src.x = 0;
	src.y = 0;
	src.w = 200;
	src.h = 200;
}


state1::~state1()
{
}

void state1::setState(int x) {
	setState1 = x;
}

int state1::getState() {
	return setState1;
}

int xpos = 0;
int ypos = 0;

//DRAWING IMAGES (always updated on this state)
void state1::drawImagesState1() {

	//which state in state 1
	switch (stateOfState1) {

		///////////////////////////   FIRST STATE   //////////////////////////

	case 0:
		//init for random number
		srand(time(0));

		//beginning of menu

		//drawing background
		dest.x = 0;
		dest.y = 0;
		dest.w = resizeImageXVar1 * 1500;
		dest.h = resizeImageYVar1 * 1000;

		TextureManager::Draw(background, src, dest, NULL, NULL, SDL_FLIP_NONE);

		//drawing background stars
		//setting x and y for background stars
		if (tempBoolean) {

			declaringBackgroundStars();
			tempBoolean = false;
		}
		for (int i = 0; i < 100; i++) {
		//setting stars position

			if (xInitial[i] < 1550) {
				xInitial[i] += 1.5;
			}else {
				xInitial[i] = -10 - ((rand() % 700));
			}

			if (yInitial[i] < 1000) {
				yInitial[i] += 1;
			}
			else {
				yInitial[i] = -10 - ((rand() % 700));
			}
			
			//drawing stars
		SDL_Rect fillRect = { xInitial[i]*resizeImageXVar1, yInitial[i]*resizeImageYVar1, 2*resizeImageXVar1, 2*resizeImageYVar1 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect);
		
		
	}

		//drawing play button
		dest.x = 638 * resizeImageXVar1;
		dest.y = 444 * resizeImageYVar1;
		dest.w = 225 *resizeImageXVar1;
		dest.h = 113 * resizeImageYVar1;

		TextureManager::Draw(playButton, src, dest, NULL, NULL, SDL_FLIP_NONE);

		//drawing text
		TTF_Font* Arial = TTF_OpenFont("assets/arial.ttf", 24); //this opens a font style and sets a size

		//color
		SDL_Color Color = { 0, 0, 0 };  

		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Arial, "Play", Color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage); //now you can convert it into a texture

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = 700 * resizeImageXVar1;  
		Message_rect.y = 480 * resizeImageYVar1; 
		Message_rect.w = 100 * resizeImageXVar1; 
		Message_rect.h = 50 * resizeImageYVar1;

		SDL_RenderCopy(Game::renderer, Message, NULL, &Message_rect);

		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);

		//////   draw players connected   //////////////

				//draw "players:" button

		SDL_Rect fillRect3 = { 639 * resizeImageXVar1, 400 * resizeImageYVar1, 223 * resizeImageXVar1, 35 * resizeImageYVar1 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 110,110,110, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect3);

				//color
	
			SDL_Color Color4 = { 0,0,0 };

			SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(Arial, "Online:", Color4); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

			SDL_Texture* Message4 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage4); //now you can convert it into a texture

			SDL_Rect Message4_rect; //create a rect
			Message4_rect.x = 655 * resizeImageXVar1;
			Message4_rect.y = 405 * resizeImageYVar1;
			Message4_rect.w = 130 * resizeImageXVar1;
			Message4_rect.h = 30 * resizeImageYVar1;

			SDL_RenderCopy(Game::renderer, Message4, NULL, &Message4_rect);

			TTF_CloseFont(Arial);
			SDL_FreeSurface(surfaceMessage4);
			SDL_DestroyTexture(Message4);

			///////////////////////    players connected (int) //////////////////
			
			stringstream sstr;
			sstr << playersConnected;

			string str1 = sstr.str();

			TTF_Font* Arial2 = TTF_OpenFont("assets/arial.ttf", 15);

			SDL_Color Color5 = {0,0,0 };

			SDL_Surface* surfaceMessagePlayers = TTF_RenderText_Solid(Arial2, str1.c_str(), Color5);

			SDL_Texture* MessagePlayers = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessagePlayers);

			SDL_Rect MessageX_rect; //create a rect
			MessageX_rect.x = 790 * resizeImageXVar1;
			MessageX_rect.y = 405 * resizeImageYVar1;
			MessageX_rect.w = 28 * resizeImageXVar1;
			MessageX_rect.h = 28 * resizeImageYVar1;

			SDL_RenderCopy(Game::renderer, MessagePlayers, NULL, &MessageX_rect);

			TTF_CloseFont(Arial2);
			SDL_FreeSurface(surfaceMessagePlayers);
			SDL_DestroyTexture(MessagePlayers);
	
		//checking for user clicking play button
		if(isLeftButtonPressed){
		if (mouseX > 637 && mouseX < 860) {
			if (mouseY > 443 && mouseY < 553) {

					setState1 = 2;
					cout << "Entering state 2" << endl;
			}
		}
		}
		//END STATE 1 OF 1
		break;
	}


}


void state1::stateoneResizeX(int x) {
	resizeImageXVar1 = (double)x/1500;
}

void state1::stateoneResizeY(int x) {
	resizeImageYVar1 = (double)x/1000;
}

void state1::declaringBackgroundStars() {

	for (int i = 0; i < 100; i++) {

		//random number variable
		int xRand = (rand() % 3000) + 1;
		int yRand = (rand() % 2000) + 1;

		xInitial[i] = xRand;
		yInitial[i] = yRand;
	}
}

//getting left button pressed
void state1::getLeftButton(bool x) {
	isLeftButtonPressed = x;
}

void state1::getMouseX(int x) {
	
	mouseX = ((double)x*(1500/(resizeImageXVar1*1500)));
}

void state1::getMouseY(int x) {
	mouseY = ((double)x*(1000 / (resizeImageYVar1 * 1000)));
}

void state1::getplayersConnected(int x) {
	playersConnected = x;
}
	