#include "state2.h"
#include "state0.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <SDL_ttf.h>
#include <sstream> 
#include "ClientSocket.h"

//variables

//state Variable
int setStatezero = 0;

//resizing x and y variable to scale of window
double resizeImageXVar0 = 1;
double resizeImageYVar0 = 1;

//is left button pressed
bool isLeftButtonPressed0 = false;
int mouseX0 = 0;
int mouseY0 = 0;

//login state (what state login is at)
int loginState = 0;

//what key is currently pressed//
char keyPressed0;

//variable for what key is pressed
int keyVariable1 = 0;
int keyVariable2 = 0;

// bool for when username is selected
bool isUsernameSelected = false;

// bool for when password is selected
bool isPasswordSelected = false;

//bool for when enter username is selected
bool isEnterUsernameSelected = false;

//bool for enter password and reenter password
bool isEnterPasswordSelected = false;
bool isReEnterPasswordSelected = false;

string initialUsername = "";
string initialPassword = "";

string signUpInitialUsername = "";
string signUpInitialPassword = "";
string signUpInitialPassword2 = "";

//strings for showing *** instead of actual password
string hidePass1 = "";
string hidePass2 = "";
string hidePass3 = "";

//getting login error
int loginError = 0;
int signupError = 0;

//signups left on this computer
int signupNumberLeft = 0;

state0::state0()
{
	//images
	background = TextureManager::LoadTexture("assets/background.png");
	button = TextureManager::LoadTexture("assets/button.png");
	loginBackground = TextureManager::LoadTexture("assets/logbackground.png");

	src.x = 0;
	src.y = 0;
	src.w = 200;
	src.h = 200;
}


state0::~state0()
{
}

void state0::setState0(int x) {
	setStatezero = x;
}

int state0::getState0() {
	return setStatezero;
}

int xpos0 = 0;
int ypos0 = 0;

//DRAWING IMAGES (always updated on this state)
void state0::drawImagesState0() {

	//drawing background
	dest.x = 0;
	dest.y = 0;
	dest.w = resizeImageXVar0 * 1500;
	dest.h = resizeImageYVar0 * 1000;

	TextureManager::Draw(background, src, dest, NULL, NULL, SDL_FLIP_NONE);

	//drawing background stars
	//setting x and y for background stars
	if (tempBoolean) {

		declaringBackgroundStars0();
		tempBoolean = false;
	}
	for (int i = 0; i < 100; i++) {
		//setting stars position

		if (xInitial0[i] < 1550) {
			xInitial0[i] += 1.5;
		}
		else {
			xInitial0[i] = -10 - ((rand() % 700));
		}

		if (yInitial0[i] < 1000) {
			yInitial0[i] += 1;
		}
		else {
			yInitial0[i] = -10 - ((rand() % 700));
		}

		//drawing stars
		SDL_Rect fillRect = { xInitial0[i] * resizeImageXVar0, yInitial0[i] * resizeImageYVar0, 2 * resizeImageXVar0, 2 * resizeImageYVar0 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect);


	}

	//drawing login button
	dest.x = 425 * resizeImageXVar0;
	dest.y = 200 * resizeImageYVar0;
	dest.w = resizeImageXVar0 * 275;
	dest.h = resizeImageYVar0 * 125;

	TextureManager::Draw(button, src, dest, NULL, NULL, SDL_FLIP_NONE);

	//drawing signup button
	dest.x = 800 * resizeImageXVar0;
	dest.y = 200 * resizeImageYVar0;
	dest.w = resizeImageXVar0 * 275;
	dest.h = resizeImageYVar0 * 125;

	TextureManager::Draw(button, src, dest, NULL, NULL, SDL_FLIP_NONE);


	////// drawing login and signup buttons

	TTF_Font* Arial = TTF_OpenFont("assets/arial.ttf", 28); //this opens a font style and sets a size

	//color
	SDL_Color Color = { 0, 0, 0 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Arial, "Login", Color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 480 * resizeImageXVar0;
	Message_rect.y = 220 * resizeImageYVar0;
	Message_rect.w = 160 * resizeImageXVar0;
	Message_rect.h = 75 * resizeImageYVar0;

	SDL_RenderCopy(Game::renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);

	//drawing sign up button
	SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Arial, "Sign Up", Color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message2 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage2); //now you can convert it into a texture

	SDL_Rect Message_rect2; //create a rect
	Message_rect2.x = 845 * resizeImageXVar0;
	Message_rect2.y = 220 * resizeImageYVar0;
	Message_rect2.w = 180 * resizeImageXVar0;
	Message_rect2.h = 75 * resizeImageYVar0;

	SDL_RenderCopy(Game::renderer, Message2, NULL, &Message_rect2);

	SDL_FreeSurface(surfaceMessage2);
	SDL_DestroyTexture(Message2);

	TTF_CloseFont(Arial);


	///// drawing login boxes ////////

	if (loginState == 1) {
		//// login background  /////
		dest.x = 538 * resizeImageXVar0;
		dest.y = 400 * resizeImageYVar0;
		dest.w = resizeImageXVar0 * 400;
		dest.h = resizeImageYVar0 * 350;

		TextureManager::Draw(loginBackground, src, dest, NULL, NULL, SDL_FLIP_NONE);


		//selection background boxes
		
		if (isUsernameSelected) {
			SDL_Rect fillRect3 = { 580 * resizeImageXVar0, 475 * resizeImageYVar0, 310 * resizeImageXVar0, 50 * resizeImageYVar0 };

			//red, green, blue, opaqueness
			SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Game::renderer, &fillRect3);
		}

		if (isPasswordSelected) {

			SDL_Rect fillRect4 = { 580 * resizeImageXVar0, 575 * resizeImageYVar0, 310 * resizeImageXVar0, 50 * resizeImageYVar0 };

			//red, green, blue, opaqueness
			SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Game::renderer, &fillRect4);

		}

		/////////////////// drawing login white boxes //////////////////////////

		// white boxes for username and password
		SDL_Rect fillRect = { 585 * resizeImageXVar0, 480 * resizeImageYVar0, 300 * resizeImageXVar0, 40 * resizeImageYVar0 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 194, 194, 194, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect);

		SDL_Rect fillRect2 = { 585 * resizeImageXVar0, 580 * resizeImageYVar0, 300 * resizeImageXVar0, 40 * resizeImageYVar0 };
		//red, green, blue, opaqueness
		SDL_RenderFillRect(Game::renderer, &fillRect2);


		//// drawing login background ////
		SDL_Rect fillRect3 = { 687 * resizeImageXVar0, 660 * resizeImageYVar0, 90 * resizeImageXVar0, 40 * resizeImageYVar0 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 194, 194, 194, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect3);

		///////// drawing "username:" and "password:" ///////////
		TTF_Font* Arial3 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

		SDL_Color Color3 = { 0, 0, 0 };

		SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(Arial3, "Username:", Color3); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message3 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage3); //now you can convert it into a texture

		SDL_Rect Message_rect3; //create a rect
		Message_rect3.x = 585 * resizeImageXVar0;
		Message_rect3.y = 440 * resizeImageYVar0;
		Message_rect3.w = 160 * resizeImageXVar0;
		Message_rect3.h = 30 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message3, NULL, &Message_rect3);

		SDL_FreeSurface(surfaceMessage3);
		SDL_DestroyTexture(Message3);

		///// password text /////

		SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(Arial3, "Password:", Color3); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message4 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage4); //now you can convert it into a texture

		SDL_Rect Message_rect4; //create a rect
		Message_rect4.x = 585 * resizeImageXVar0;
		Message_rect4.y = 537 * resizeImageYVar0;
		Message_rect4.w = 160 * resizeImageXVar0;
		Message_rect4.h = 30 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message4, NULL, &Message_rect4);

		SDL_FreeSurface(surfaceMessage4);
		SDL_DestroyTexture(Message4);


		TTF_CloseFont(Arial3);


		//// drawing username on screen /////////////

		//// if username is selected //////

		if (isUsernameSelected) {

			if (keyPressed0 != ' ') {

				if (keyPressed0 == '&') {

					if (initialUsername.length() > 0) {
						initialUsername.pop_back();
					}

				}
				else {

					initialUsername += keyPressed0;
				}

			}
		}

			TTF_Font* Arial4 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

			SDL_Color Color5 = { 0,0,0 };

			SDL_Surface* surfaceMessage5 = TTF_RenderText_Solid(Arial4, initialUsername.c_str(), Color5);

			SDL_Texture* Message5 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage5);

			SDL_Rect Message5_rect; //create a rect
			Message5_rect.x = 590 * resizeImageXVar0;
			Message5_rect.y = 480 * resizeImageYVar0;
			Message5_rect.w = initialUsername.length() * 12 * resizeImageXVar0;
			Message5_rect.h = 35 * resizeImageYVar0;

			SDL_RenderCopy(Game::renderer, Message5, NULL, &Message5_rect);

			SDL_FreeSurface(surfaceMessage5);
			SDL_DestroyTexture(Message5);

			/////// if password is selcted ////////////

			if (isPasswordSelected) {

				if (keyPressed0 != ' ') {

					if (keyPressed0 == '&') {

						if (initialPassword.length() > 0) {
							initialPassword.pop_back();
							hidePass1.pop_back();
						}

					}
					else {

						initialPassword += keyPressed0;
						hidePass1 += '*';
						
					}

				}
			}

			SDL_Surface* surfaceMessage6 = TTF_RenderText_Solid(Arial4, hidePass1.c_str(), Color5);

			SDL_Texture* Message6 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage6);

			SDL_Rect Message6_rect; //create a rect
			Message6_rect.x = 590 * resizeImageXVar0;
			Message6_rect.y = 581 * resizeImageYVar0;
			Message6_rect.w = hidePass1.length() * 12 * resizeImageXVar0;
			Message6_rect.h = 35 * resizeImageYVar0;

			SDL_RenderCopy(Game::renderer, Message6, NULL, &Message6_rect);

			SDL_FreeSurface(surfaceMessage6);
			SDL_DestroyTexture(Message6);

			TTF_CloseFont(Arial4);


			//drawing login

			TTF_Font* Arial5 = TTF_OpenFont("assets/arial.ttf", 12); //this opens a font style and sets a size

			SDL_Surface* surfaceMessage7 = TTF_RenderText_Solid(Arial5, "Login", Color3); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

			SDL_Texture* Message7 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage7); //now you can convert it into a texture

			SDL_Rect Message_rect7; //create a rect
			Message_rect7.x = 695 * resizeImageXVar0;
			Message_rect7.y = 665 * resizeImageYVar0;
			Message_rect7.w = 73 * resizeImageXVar0;
			Message_rect7.h = 28 * resizeImageYVar0;

			SDL_RenderCopy(Game::renderer, Message7, NULL, &Message_rect7);

			SDL_FreeSurface(surfaceMessage7);
			SDL_DestroyTexture(Message7);

			TTF_CloseFont(Arial5);

			//drawing invalid username or password
			if (loginError == 1) {
				SDL_Color Color8 = { 130,0,0 };
				TTF_Font* Arial8 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

				SDL_Surface* surfaceMessage8 = TTF_RenderText_Solid(Arial8, "Invalid Username or Password", Color8); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

				SDL_Texture* Message8 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage8); //now you can convert it into a texture

				SDL_Rect Message_rect8; //create a rect
				Message_rect8.x = 600 * resizeImageXVar0;
				Message_rect8.y = 622 * resizeImageYVar0;
				Message_rect8.w = 260 * resizeImageXVar0;
				Message_rect8.h = 35 * resizeImageYVar0;

				SDL_RenderCopy(Game::renderer, Message8, NULL, &Message_rect8);

				SDL_FreeSurface(surfaceMessage8);
				SDL_DestroyTexture(Message8);

				TTF_CloseFont(Arial8);
			}
			//if user is already logged on
			else if (loginError == 9) {
				SDL_Color Color23 = { 130,0,0 };
				TTF_Font* Arial23 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

				SDL_Surface* surfaceMessage23 = TTF_RenderText_Solid(Arial23, "Already Logged in", Color23); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

				SDL_Texture* Message23 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage23); //now you can convert it into a texture

				SDL_Rect Message_rect23; //create a rect
				Message_rect23.x = 600 * resizeImageXVar0;
				Message_rect23.y = 622 * resizeImageYVar0;
				Message_rect23.w = 260 * resizeImageXVar0;
				Message_rect23.h = 35 * resizeImageYVar0;

				SDL_RenderCopy(Game::renderer, Message23, NULL, &Message_rect23);

				SDL_FreeSurface(surfaceMessage23);
				SDL_DestroyTexture(Message23);

				TTF_CloseFont(Arial23);
			}

	}

	////////////// if "sign up" is selected /////////////
	if (loginState == 2) {

		//// adding text to boxes ////
		if (isEnterUsernameSelected) {

			if (keyPressed0 != ' ') {

				if (keyPressed0 == '&') {

					if (signUpInitialUsername.length() > 0) {
						signUpInitialUsername.pop_back();
					}

				}
				else {

					signUpInitialUsername += keyPressed0;
				}

			}
		}

		if (isEnterPasswordSelected) {

			if (keyPressed0 != ' ') {

				if (keyPressed0 == '&') {

					if (signUpInitialPassword.length() > 0) {
						signUpInitialPassword.pop_back();
						hidePass2.pop_back();
					}

				}
				else {

					signUpInitialPassword += keyPressed0;
					hidePass2 += '*';
				}

			}
		}

		if (isReEnterPasswordSelected) {

			if (keyPressed0 != ' ') {

				if (keyPressed0 == '&') {

					if (signUpInitialPassword2.length() > 0) {
						signUpInitialPassword2.pop_back();
						hidePass3.pop_back();
					}

				}
				else {

					signUpInitialPassword2 += keyPressed0;
					hidePass3 += '*';
				}

			}
		}

		//// drawing background box for everything /////

		dest.x = 538 * resizeImageXVar0;
		dest.y = 400 * resizeImageYVar0;
		dest.w = resizeImageXVar0 * 400;
		dest.h = resizeImageYVar0 * 450;

		TextureManager::Draw(loginBackground, src, dest, NULL, NULL, SDL_FLIP_NONE);

		//// black selection boxes /////
		if (isEnterUsernameSelected) {
			SDL_Rect fillRect3 = { 580 * resizeImageXVar0, 475 * resizeImageYVar0, 310 * resizeImageXVar0, 50 * resizeImageYVar0 };

			SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Game::renderer, &fillRect3);
		}
		if (isEnterPasswordSelected) {
			SDL_Rect fillRect3 = { 580 * resizeImageXVar0, 575 * resizeImageYVar0, 310 * resizeImageXVar0, 50 * resizeImageYVar0 };

			SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Game::renderer, &fillRect3);
		}
		if (isReEnterPasswordSelected) {
			SDL_Rect fillRect3 = { 580 * resizeImageXVar0, 675 * resizeImageYVar0, 310 * resizeImageXVar0, 50 * resizeImageYVar0 };

			SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Game::renderer, &fillRect3);
		}

		// white box for enter username
		SDL_Rect fillRect3 = { 585 * resizeImageXVar0, 480 * resizeImageYVar0, 300 * resizeImageXVar0, 40 * resizeImageYVar0 };

		SDL_SetRenderDrawColor(Game::renderer, 194, 194, 194, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect3);

		//white box for enter password
		SDL_Rect fillRect4 = { 585 * resizeImageXVar0, 580 * resizeImageYVar0, 300 * resizeImageXVar0, 40 * resizeImageYVar0 };
		SDL_RenderFillRect(Game::renderer, &fillRect4);

		//white box for confirm password
		SDL_Rect fillRect5 = { 585 * resizeImageXVar0, 680 * resizeImageYVar0, 300 * resizeImageXVar0, 40 * resizeImageYVar0 };
		SDL_RenderFillRect(Game::renderer, &fillRect5);

		//white box for "Sign Up" button
		SDL_Rect fillRect6 = { 687 * resizeImageXVar0, 745 * resizeImageYVar0, 90 * resizeImageXVar0, 40 * resizeImageYVar0 };

		SDL_SetRenderDrawColor(Game::renderer, 194, 194, 194, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect6);

		///////// drawing "username:" and "password:" ///////////
		TTF_Font* Arial9 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

		SDL_Color Color9 = { 0, 0, 0 };

		SDL_Surface* surfaceMessage9 = TTF_RenderText_Solid(Arial9, "Username:", Color9); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message9 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage9); //now you can convert it into a texture

		SDL_Rect Message_rect9; //create a rect
		Message_rect9.x = 585 * resizeImageXVar0;
		Message_rect9.y = 440 * resizeImageYVar0;
		Message_rect9.w = 160 * resizeImageXVar0;
		Message_rect9.h = 30 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message9, NULL, &Message_rect9);

		SDL_FreeSurface(surfaceMessage9);
		SDL_DestroyTexture(Message9);

		///// password text /////

		SDL_Surface* surfaceMessage10= TTF_RenderText_Solid(Arial9, "Password:", Color9); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message10 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage10); //now you can convert it into a texture

		SDL_Rect Message_rect10; //create a rect
		Message_rect10.x = 585 * resizeImageXVar0;
		Message_rect10.y = 537 * resizeImageYVar0;
		Message_rect10.w = 160 * resizeImageXVar0;
		Message_rect10.h = 30 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message10, NULL, &Message_rect10);

		SDL_FreeSurface(surfaceMessage10);
		SDL_DestroyTexture(Message10);

		///// retype password text /////

		SDL_Surface* surfaceMessage11 = TTF_RenderText_Solid(Arial9, "Retype Password:", Color9); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message11 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage11); //now you can convert it into a texture

		SDL_Rect Message_rect11; //create a rect
		Message_rect11.x = 585 * resizeImageXVar0;
		Message_rect11.y = 637 * resizeImageYVar0;
		Message_rect11.w = 240 * resizeImageXVar0;
		Message_rect11.h = 30 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message11, NULL, &Message_rect11);

		SDL_FreeSurface(surfaceMessage11);
		SDL_DestroyTexture(Message11);

		TTF_CloseFont(Arial9);

		///// drawing enter username text ////////
		TTF_Font* Arial13 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

		SDL_Color Color13 = { 0,0,0 };

		SDL_Surface* surfaceMessage13 = TTF_RenderText_Solid(Arial13, signUpInitialUsername.c_str(), Color13);

		SDL_Texture* Message13 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage13);

		SDL_Rect Message13_rect; //create a rect
		Message13_rect.x = 590 * resizeImageXVar0;
		Message13_rect.y = 480 * resizeImageYVar0;
		Message13_rect.w = signUpInitialUsername.length() * 12 * resizeImageXVar0;
		Message13_rect.h = 35 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message13, NULL, &Message13_rect);

		SDL_FreeSurface(surfaceMessage13);
		SDL_DestroyTexture(Message13);

		///// drawing enter password text ////////

		SDL_Surface* surfaceMessage14 = TTF_RenderText_Solid(Arial13, hidePass2.c_str(), Color13);

		SDL_Texture* Message14 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage14);

		SDL_Rect Message14_rect; //create a rect
		Message14_rect.x = 590 * resizeImageXVar0;
		Message14_rect.y = 580 * resizeImageYVar0;
		Message14_rect.w = hidePass2.length() * 12 * resizeImageXVar0;
		Message14_rect.h = 35 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message14, NULL, &Message14_rect);

		SDL_FreeSurface(surfaceMessage14);
		SDL_DestroyTexture(Message14);

		///// drawing RE enter password text ////////

		SDL_Surface* surfaceMessage15 = TTF_RenderText_Solid(Arial13, hidePass3.c_str(), Color13);

		SDL_Texture* Message15 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage15);

		SDL_Rect Message15_rect; //create a rect
		Message15_rect.x = 590 * resizeImageXVar0;
		Message15_rect.y = 680 * resizeImageYVar0;
		Message15_rect.w = hidePass3.length() * 12 * resizeImageXVar0;
		Message15_rect.h = 35 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message15, NULL, &Message15_rect);

		SDL_FreeSurface(surfaceMessage15);
		SDL_DestroyTexture(Message15);

		TTF_CloseFont(Arial13);

		///// drawing "Sign Up" button on bottom ///////
		TTF_Font* Arial16 = TTF_OpenFont("assets/arial.ttf", 12); //this opens a font style and sets a size

		SDL_Color Color16 = { 0,0,0 };

		SDL_Surface* surfaceMessage16 = TTF_RenderText_Solid(Arial16, "Sign Up", Color16); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message16 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage16); //now you can convert it into a texture

		SDL_Rect Message_rect16; //create a rect
		Message_rect16.x = 695 * resizeImageXVar0;
		Message_rect16.y = 751 * resizeImageYVar0;
		Message_rect16.w = 73 * resizeImageXVar0;
		Message_rect16.h = 28 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message16, NULL, &Message_rect16);

		SDL_FreeSurface(surfaceMessage16);
		SDL_DestroyTexture(Message16);

		TTF_CloseFont(Arial16);

		////// drawing errors to screen //////////

		// username too short error message
		if (signupError == 1) {
			SDL_Color Color17 = { 130,0,0 };
			TTF_Font* Arial17 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

			SDL_Surface* surfaceMessage17 = TTF_RenderText_Solid(Arial17, "Username Too Short", Color17); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

			SDL_Texture* Message17= SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage17); //now you can convert it into a texture

			SDL_Rect Message_rect17; //create a rect
			Message_rect17.x = 600 * resizeImageXVar0;
			Message_rect17.y = 790 * resizeImageYVar0;
			Message_rect17.w = 260 * resizeImageXVar0;
			Message_rect17.h = 35 * resizeImageYVar0;

			SDL_RenderCopy(Game::renderer, Message17, NULL, &Message_rect17);

			SDL_FreeSurface(surfaceMessage17);
			SDL_DestroyTexture(Message17);

			TTF_CloseFont(Arial17);
		}
		//password too short
		else if (signupError == 2) {

			SDL_Color Color18 = { 130,0,0 };
			TTF_Font* Arial18 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

			SDL_Surface* surfaceMessage18 = TTF_RenderText_Solid(Arial18, "Password Too Short", Color18); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

			SDL_Texture* Message18 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage18); //now you can convert it into a texture

			SDL_Rect Message_rect18; //create a rect
			Message_rect18.x = 600 * resizeImageXVar0;
			Message_rect18.y = 790 * resizeImageYVar0;
			Message_rect18.w = 260 * resizeImageXVar0;
			Message_rect18.h = 35 * resizeImageYVar0;

			SDL_RenderCopy(Game::renderer, Message18, NULL, &Message_rect18);

			SDL_FreeSurface(surfaceMessage18);
			SDL_DestroyTexture(Message18);

			TTF_CloseFont(Arial18);
		}
		//passwords do not match
		else if (signupError == 3) {

			SDL_Color Color19 = { 130,0,0 };
			TTF_Font* Arial19 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

			SDL_Surface* surfaceMessage19 = TTF_RenderText_Solid(Arial19, "Passwords Do Not Match", Color19); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

			SDL_Texture* Message19 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage19); //now you can convert it into a texture

			SDL_Rect Message_rect19; //create a rect
			Message_rect19.x = 600 * resizeImageXVar0;
			Message_rect19.y = 790 * resizeImageYVar0;
			Message_rect19.w = 260 * resizeImageXVar0;
			Message_rect19.h = 35 * resizeImageYVar0;

			SDL_RenderCopy(Game::renderer, Message19, NULL, &Message_rect19);

			SDL_FreeSurface(surfaceMessage19);
			SDL_DestroyTexture(Message19);

			TTF_CloseFont(Arial19);

		}
		//username is taken
		else if (signupError == 4) {

			SDL_Color Color20 = { 130,0,0 };
			TTF_Font* Arial20 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

			SDL_Surface* surfaceMessage20 = TTF_RenderText_Solid(Arial20, "Username is Taken", Color20); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

			SDL_Texture* Message20 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage20); //now you can convert it into a texture

			SDL_Rect Message_rect20; //create a rect
			Message_rect20.x = 600 * resizeImageXVar0;
			Message_rect20.y = 790 * resizeImageYVar0;
			Message_rect20.w = 260 * resizeImageXVar0;
			Message_rect20.h = 35 * resizeImageYVar0;

			SDL_RenderCopy(Game::renderer, Message20, NULL, &Message_rect20);

			SDL_FreeSurface(surfaceMessage20);
			SDL_DestroyTexture(Message20);

			TTF_CloseFont(Arial20);

		}
		//if account is successfully created
		else if (signupError == 5) {

			SDL_Color Color21 = { 65,180,20 };
			TTF_Font* Arial21 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

			SDL_Surface* surfaceMessage21 = TTF_RenderText_Solid(Arial21, "Account Created!", Color21); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

			SDL_Texture* Message21 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage21); //now you can convert it into a texture

			SDL_Rect Message_rect21; //create a rect
			Message_rect21.x = 600 * resizeImageXVar0;
			Message_rect21.y = 790 * resizeImageYVar0;
			Message_rect21.w = 260 * resizeImageXVar0;
			Message_rect21.h = 35 * resizeImageYVar0;

			SDL_RenderCopy(Game::renderer, Message21, NULL, &Message_rect21);

			SDL_FreeSurface(surfaceMessage21);
			SDL_DestroyTexture(Message21);

			TTF_CloseFont(Arial21);

		}
		//if account is successfully created
		else if (signupError == 8) {

		SDL_Color Color22 = { 130,0,0 };
		TTF_Font* Arial22 = TTF_OpenFont("assets/arial.ttf", 14); //this opens a font style and sets a size

		SDL_Surface* surfaceMessage22 = TTF_RenderText_Solid(Arial22, "Too Many Accounts Created", Color22); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

		SDL_Texture* Message22 = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessage22); //now you can convert it into a texture

		SDL_Rect Message_rect22; //create a rect
		Message_rect22.x = 600 * resizeImageXVar0;
		Message_rect22.y = 790 * resizeImageYVar0;
		Message_rect22.w = 260 * resizeImageXVar0;
		Message_rect22.h = 35 * resizeImageYVar0;

		SDL_RenderCopy(Game::renderer, Message22, NULL, &Message_rect22);

		SDL_FreeSurface(surfaceMessage22);
		SDL_DestroyTexture(Message22);

		TTF_CloseFont(Arial22);

		}

	}


	///// dealing with mouse position /////

		//logging in stuff
	if (mouseX0 > 421 && mouseX0 < 694) {
		if (mouseY0 > 201 && mouseY0 < 321) {
			if (isLeftButtonPressed0) {

				loginState = 1;

			}
		}
	}

	//sign up stuff
	if (mouseX0 > 800 && mouseX0 < 1073) {
		if (mouseY0 > 201 && mouseY0 < 321) {
			if (isLeftButtonPressed0) {

				loginState = 2;

			}
		}
	}

	//if actual login is clicked

	if (mouseX0 > 687 && mouseX0 < 777) {
		if (mouseY0 > 660 && mouseY0 < 700) {
			if (isLeftButtonPressed0) {
				
				//checking if username and password are not ""
				if (initialUsername.length() > 3 && initialPassword.length() > 3) {
					game->sendingUserInput("!logt:" + initialUsername + "/" + initialPassword + '~');
				}
				else {
					loginError = 1;
				}
			}
		}
	}

	//if actual signup is clicked
	if (mouseX0 > 687 && mouseX0 < 777) {
		if (mouseY0 > 745 && mouseY0 < 785) {
			if (isLeftButtonPressed0) {

				if (signupNumberLeft == 0) {
					signupError = 8;

				}else if (signUpInitialUsername.length() <= 3) {
					signupError = 1;
				}
				else if (signUpInitialPassword.length() < 5) {
					signupError = 2;
				}
				else if (signUpInitialPassword != signUpInitialPassword2) {
					signupError = 3;
				}
				else {
					signupError = 0;
				}

				if (signupError == 0) {
					game->sendingUserInput("!signup:" + signUpInitialUsername + "/" + signUpInitialPassword + '~');
				}

			}
			}
			}


	//login boxes when they are clicked on
	if (isLeftButtonPressed0) {
		if (mouseX0 > 585 && mouseX0 < 885 &&
			mouseY0 > 480 && mouseY0 < 520){

			isUsernameSelected = true;

		}
		else {

			isUsernameSelected = false;

		}
	}

	// enter password selection box
	if (isLeftButtonPressed0) {
		if (mouseX0 > 585 && mouseX0 < 885 &&
			mouseY0 > 580 && mouseY0 < 620) {

			isPasswordSelected = true;

		}
		else {

			isPasswordSelected = false;

		}
	}

	// enter username selection box
	if (isLeftButtonPressed0) {
		if (mouseX0 > 585 && mouseX0 < 885 &&
			mouseY0 > 480 && mouseY0 < 520) {

			isEnterUsernameSelected = true;

		}
		else {

			isEnterUsernameSelected = false;

		}
	}

	// enter password selection box
	if (isLeftButtonPressed0) {
		if (mouseX0 > 585 && mouseX0 < 885 &&
			mouseY0 > 580 && mouseY0 < 620) {

			isEnterPasswordSelected = true;

		}
		else {

			isEnterPasswordSelected = false;

		}
	}

	// re-enter password selection box
	if (isLeftButtonPressed0) {
		if (mouseX0 > 585 && mouseX0 < 885 &&
			mouseY0 > 680 && mouseY0 < 720) {

			isReEnterPasswordSelected = true;

		}
		else {

			isReEnterPasswordSelected = false;

		}
	}
}


void state0::statezeroResizeX(int x) {
	resizeImageXVar0 = (double)x / 1500;
}

void state0::statezeroResizeY(int x) {
	resizeImageYVar0 = (double)x / 1000;
}


//getting left button pressed
void state0::getLeftButton0(bool x) {
	isLeftButtonPressed0 = x;
}

void state0::getMouseX0(int x) {
	mouseX0 = ((double)x*(1500 / (resizeImageXVar0 * 1500)));
}

void state0::getMouseY0(int x) {
	mouseY0 = ((double)x*(1000 / (resizeImageYVar0 * 1000)));
}

void state0::declaringBackgroundStars0() {

	for (int i = 0; i < 100; i++) {

		//random number variable
		int xRand = (rand() % 3000) + 1;
		int yRand = (rand() % 2000) + 1;

		xInitial0[i] = xRand;
		yInitial0[i] = yRand;
	}
}

void state0::getKeyPressed(int x) {
	keyPressed0 = x;
}

void state0::setStateFromMain(int x) {
	setStatezero = x;
}

//getting username
string state0::getUsername() {
	return initialUsername;
}

//getting login error
void state0::setLoginError(int x) {
	loginError = x;
}

//getting signup error
void state0::setSignupError(int x) {
	signupError = x;
}

//setting number of signups left
void state0::setSignupLeft(int x) {
	signupNumberLeft = x;
}


