#include "state2.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <SDL_ttf.h>
#include <math.h>
#include <string>   
#include <iostream>     
#include <sstream> 
#include <vector>
#include <chrono>

#define PI 3.14159265

//variables

//state Variable
int setStatetwo = 0;

//resizing x and y variable to scale of window
double state2resizeImageXVar1 = 1;
double state2resizeImageYVar1 = 1;

//is left button pressed
bool state2isLeftButtonPressed = false;
int state2mouseX = 0;
int state2mouseY = 0;

//variables for keyboard
bool upKeyPressed2 = false;
bool leftKeyPressed2 = false;
bool rightKeyPressed2 = false;
bool downKeyPressed2 = false;
bool spaceKeyPressed2 = false;
bool FKeyPressed2 = false;

//ship x and y velocity
double xVelocityShip = 0;
double yVelocityShip = 0;

//ship rotation
double shipRotationAngle = 7200;
double shipRotationAngleReal = 0;
double shipRotationHolder = 0;

/////////////// SERVER PLAYER VARIABLES /////////////

//real x, y, and rotation
double serverXCoordinate[50];
double serverYCoordinate[50];
int serverRotation[50];
double serverSpeedX[50];
double serverSpeedY[50];
bool spaceKeyPressedServer[50];

double serverXCoordinateHold[50];
double serverYCoordinateHold[50];
double serverRotationHold[50];
string serverPlayers[50];

//variables for calculating xp from killing player
int serverExperienceTimer[50];
bool serverExperienceGain[50];

 //vector for what chunks need to be loaded
 vector <string> chunkCurrentLoads;

 //variable for loading current chunks
 int chunkLoadTimer = 0;

//int for delaying chunk checking
 int chunkTimer = 0;

 //VARIABLES FOR PLANETS;

 double planetX[50][12];
 double planetY[50][12];
 int planetR[50][12];
 int planetG[50][12];
 int planetB[50][12];
 int planetDiameter[50][12];
 int planetImageNumber[50][12];

 //maximum speed
 double maxSpeed = 22;
 double currentSpeed = 0;

 //temp variables for max speed
 double tempxVelocityShip;
 double tempyVelocityShip;

 //array for which chunks are loaded
 string chunkActualLoad[12];

 //username of player
 string username2 = "";

 //type of shot
 string typeOfShot = "blaster";

 //stuff for shooting
 std::vector<string> shotName;
 std::vector<int> shotRotation;
 std::vector<string> shotType;
 std::vector<string> uniqueName;
 std::vector<double> shotTime;
 std::vector<double> shotXHold;
 std::vector<double> shotYHold;
 std::vector<int> shotStartVelocityX;
 std::vector<int> shotStartVelocityY;
 std::vector<bool> shotHit;

 //shooting timer (based on which gun is selected

 int shootTimer = 0;

 //variables for timer
 double holdTime;
 double currentTime;
 double duration;

 //variables for showing FPS
 double FPSTime;
 double FPSCurrent;
 double FPSCounter;

 //variable for health
 int playerHealth = 100;
 int playerMaxHealth = 100;
 int serverCurrentHealth[50];
 int serverMaxHealth[50];

 //variables for player experience
 int currentExperience = 0;
 int currentLevel = 1;
 int currentMaxExperience = 100;
state2::state2()
{
	//images
	background = TextureManager::LoadTexture("assets/background.png");
	playerShip = TextureManager::LoadTexture("assets/ship1.png");
	pointer = TextureManager::LoadTexture("assets/pointer.png");
	pointerFoe = TextureManager::LoadTexture("assets/pointerFoe.png");
	speedBar = TextureManager::LoadTexture("assets/speedBar.png");
	healthBar = TextureManager::LoadTexture("assets/healthBar.png");
	experience_bar = TextureManager::LoadTexture("assets/experience_bar.png");
	experience_bar_bg = TextureManager::LoadTexture("assets/experience_bar_bg.png");

	//bullets
	bullet1 = TextureManager::LoadTexture("assets/bullet1.png");

	//planet images
	planet0 = TextureManager::LoadTexture("assets/planets/planet0.png");
	planet1 = TextureManager::LoadTexture("assets/planets/planet1.png");
	planet2 = TextureManager::LoadTexture("assets/planets/planet2.png");
	planet3 = TextureManager::LoadTexture("assets/planets/planet3.png");
	planet4 = TextureManager::LoadTexture("assets/planets/planet4.png");
	planet5 = TextureManager::LoadTexture("assets/planets/planet5.png");
	planet6 = TextureManager::LoadTexture("assets/planets/planet6.png");
	planet7 = TextureManager::LoadTexture("assets/planets/planet7.png");
	planet8 = TextureManager::LoadTexture("assets/planets/planet8.png");
	planet9 = TextureManager::LoadTexture("assets/planets/planet9.png");
	planet10 = TextureManager::LoadTexture("assets/planets/planet10.png");
	planet11 = TextureManager::LoadTexture("assets/planets/planet11.png");
	planet12 = TextureManager::LoadTexture("assets/planets/planet12.png");
	planet13 = TextureManager::LoadTexture("assets/planets/planet13.png");
	planet14 = TextureManager::LoadTexture("assets/planets/planet14.png");
	planet15 = TextureManager::LoadTexture("assets/planets/planet15.png");
	planet16 = TextureManager::LoadTexture("assets/planets/planet16.png");
	planet17 = TextureManager::LoadTexture("assets/planets/planet17.png");
	planet18 = TextureManager::LoadTexture("assets/planets/planet18.png");
	planet19 = TextureManager::LoadTexture("assets/planets/planet19.png");
	planet20 = TextureManager::LoadTexture("assets/planets/planet20.png");
	planet21 = TextureManager::LoadTexture("assets/planets/planet21.png");
	planet22 = TextureManager::LoadTexture("assets/planets/planet22.png");
	planet23 = TextureManager::LoadTexture("assets/planets/planet23.png");
	planet24 = TextureManager::LoadTexture("assets/planets/planet24.png");
	planet25 = TextureManager::LoadTexture("assets/planets/planet25.png");
	planet26 = TextureManager::LoadTexture("assets/planets/planet26.png");
	planet27 = TextureManager::LoadTexture("assets/planets/planet27.png");
	planet28 = TextureManager::LoadTexture("assets/planets/planet28.png");
	planet29 = TextureManager::LoadTexture("assets/planets/planet29.png");




	src.x = 0;
	src.y = 0;
	src.w = 1000;
	src.h = 1000;

	playerXCoordinate = (rand() % 300) - 150;
	playerYCoordinate = (rand() % 300) - 150;

	//setting server players to "";
	for (int i = 0; i < 50; i++) {
		serverMaxHealth[i] = 100;
		serverExperienceGain[i] = false;
		serverCurrentHealth[i] = 100;
		serverXCoordinate[i] = -5000;
		serverYCoordinate[i] = -2000;
		serverPlayers[i] = "";
		serverRotationHold[i] = 7200;
		serverRotation[i] = 7200;
		spaceKeyPressedServer[i] = false;

		for (int b = 0; b < 150; b++) {
			exhaustOnServer[i][b] = false;
		}

		for (int z = 0; z < 12; z++) {
			planetX[i][z] = 0;
			planetY[i][z] = 0;
			planetDiameter[i][z] = 0;
			planetR[i][z] = 0;
			planetG[i][z] = 0;
			planetB[i][z] = 0;
			planetImageNumber[i][z] = 0;
		}

	}

	for (int i = 0; i < 12; i++) {
		chunkActualLoad[i] = "";
	}
}

state2::~state2()
{
}

void state2::setState2(int x) {
	setStatetwo = x;
}

int state2::getState2() {
	return setStatetwo;
}

int state2::getPlayerX() {
	return playerXCoordinate - (80/2);
}

int state2::getPlayerY() {
	return playerYCoordinate + (84/2);
}

int state2::getPlayerR() {
	return shipRotationAngle;
}

double state2::getPlayerSpeedX() {
	return xVelocityShip;
}

double state2::getPlayerSpeedY() {
	return yVelocityShip;
}

string state2::getPlayerSpacebar() {

	if (spaceKeyPressed2) {
		return "true";
	}
	else {
		return "false";
	}

}

//DRAWING IMAGES (always updated on this state)
void state2::drawImagesState2() {

	if (chunkTimer == 60) {

		chunkTimer = 0;
		chunkLoadTimer = 30;
		//which chunk needs to be loaded

		int chunkX = 0;
		int chunkY = 0;
		
		//chunk that player is currently in
		chunkY = ((int)(playerYCoordinate - 5000) / 20000);

		chunkX = ((int)(playerXCoordinate + 5000) / 20000);

		//checking if chunk needs to be loaded
		for (int z = 0; z < 9; z++) {

			//string for which chunk to check
			string x = "";

			if (z == 0) {
				x = to_string(chunkX) + "," + to_string(chunkY);
			}
			else if (z == 1) {
				x = to_string(chunkX + 1) + "," + to_string(chunkY);
			}
			else if (z == 2) {
				x = to_string(chunkX + 1) + "," + to_string(chunkY - 1);
			}
			else if (z == 3) {
				x = to_string(chunkX) + "," + to_string(chunkY - 1);
			}
			else if (z == 4) {
				x = to_string(chunkX - 1) + "," + to_string(chunkY - 1);
			}
			else if (z == 5) {
				x = to_string(chunkX - 1) + "," + to_string(chunkY);
			}
			else if (z == 6) {
				x = to_string(chunkX - 1) + "," + to_string(chunkY + 1);
			}
			else if (z == 7) {
				x = to_string(chunkX) + "," + to_string(chunkY + 1);
			}
			else if (z == 8) {
				x = to_string(chunkX + 1) + "," + to_string(chunkY + 1);
			}

			bool chunkNeedsLoading = true;

			//checking if current chunk is loaded
			if (chunkActualLoad[0] != "") {
				for (int i = 0; i < 12; i++) {

					if (x == chunkActualLoad[i]) {

						chunkNeedsLoading = false;

					}
				}
			}
			else {
				chunkNeedsLoading = true;
			}

			//adding chunk if it is in range
			if (chunkNeedsLoading) {
				
				chunkCurrentLoads.push_back(x);

			}

		}

		//checking if chunk needs to be deleted
		for (int a = 0; a < 12; a++) {

			//bool for if chunks needs to be deleted
			bool deleteChunk = true;


			if ((to_string(chunkX) + "," + to_string(chunkY)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}
			else if ((to_string(chunkX + 1) + "," + to_string(chunkY)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}
			else if ((to_string(chunkX + 1) + "," + to_string(chunkY - 1)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}
			else if ((to_string(chunkX) + "," + to_string(chunkY - 1)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}
			else if ((to_string(chunkX - 1) + "," + to_string(chunkY - 1)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}
			else if ((to_string(chunkX - 1) + "," + to_string(chunkY)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}
			else if ((to_string(chunkX - 1) + "," + to_string(chunkY + 1)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}
			else if ((to_string(chunkX) + "," + to_string(chunkY + 1)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}
			else if ((to_string(chunkX + 1) + "," + to_string(chunkY + 1)) == chunkActualLoad[a]) {
				deleteChunk = false;
			}

			if (deleteChunk) {		

						for (int y = 0; y < 50; y++) {

							planetX[y][a] = 0;
							planetY[y][a] = 0;

						}

						chunkActualLoad[a] = "";
			}

		}

	}
	else {
	chunkTimer++;
	}

	// calling chunks to load
	if (chunkLoadTimer > 0 && (chunkLoadTimer % 3) == 0) {
		loadChunks();
	}
	
	
	
	//drawing background stars
//setting x and y for background stars
	if (tempBoolean) {

		declaringBackgroundStars();
		tempBoolean = false;
	}

	//drawing background
	dest.x = 0;
	dest.y = 0;
	dest.w = state2resizeImageXVar1 * 1500;
	dest.h = state2resizeImageYVar1 * 1000;

	TextureManager::Draw(background, src, dest, NULL, NULL, SDL_FLIP_NONE);

			//drawing background stars
		//setting x and y for background stars
		if (tempBoolean) {

			declaringBackgroundStars();
			tempBoolean = false;
		}
		for (int i = 0; i < 50; i++) {
			//setting stars position
			//((rand() % 700));
			
			if (yInitial[i] < -1000) {
				xInitial[i] = -1000 + ((rand() % 3000));
				yInitial[i] = 1000 + ((rand() % 1000));
			}
			if (yInitial[i] > 2000) {
				xInitial[i] = -1000 + ((rand() % 3000));
				yInitial[i] = 0 - ((rand() % 1000));
			}
			if (xInitial[i] < -1000) {
				xInitial[i] = 1500 + ((rand() % 500));
				yInitial[i] = -1000 + ((rand() % 3000));
			}
			if (xInitial[i] > 2500) {
				xInitial[i] = 0 - ((rand() % 1000));
				yInitial[i] = -1000 + ((rand() % 3000));
			}

			xInitial[i] += ( (xVelocityShip*-1)/5);
			yInitial[i] += (yVelocityShip)/5;
			//drawing stars
			SDL_Rect fillRect = { xInitial[i] * state2resizeImageXVar1, yInitial[i] * state2resizeImageYVar1, 2 * state2resizeImageXVar1, 2 * state2resizeImageYVar1 };

			//red, green, blue, opaqueness
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(Game::renderer, &fillRect);

		}
	//checking for keyboard input
	if (upKeyPressed2) {
		if (minimapSize < 120) {
			minimapSize++;
		}

	}
	if (downKeyPressed2) {
		if (minimapSize > 50) {
			minimapSize--;
		}
	}
	if (leftKeyPressed2) {
		shipRotationAngle -= 3.5;
	}
	if (rightKeyPressed2) {
		shipRotationAngle += 3.5;
	}

	/////setting real ship rotation ////////
		
		shipRotationHolder = ((int) abs(shipRotationAngle) % 360);

		if (shipRotationHolder >= 0 && shipRotationHolder < 90) {
			shipRotationAngleReal = 90 - shipRotationHolder;
		}
		else {
			shipRotationAngleReal = (360 - shipRotationHolder) + 90;
		}


	////////////// drawing exhaust ////////////////

//init for random number

	if (spaceKeyPressed2) {

		//changing velocity of the ship when the space bar is pressed
		if (collisionCounter <= 0) {

			//temp variables to see if ship is trying to go past max speed
			tempxVelocityShip= xVelocityShip + cos((shipRotationAngleReal)*3.14159 / 180) / 3.6;
			tempyVelocityShip = yVelocityShip + sin((shipRotationAngleReal)*3.14159 / 180) / 3.6;

			//if ship is not going past max speed
			if ((sqrt((tempxVelocityShip * tempxVelocityShip) + (tempyVelocityShip * tempyVelocityShip))) < maxSpeed) {

				exhaustTotalTime = 80;

				xVelocityShip += cos((shipRotationAngleReal)*3.14159 / 180) / 3.6;
				yVelocityShip += sin((shipRotationAngleReal)*3.14159 / 180) / 3.6;
			}
			else {

				if ((sqrt((tempxVelocityShip * tempxVelocityShip) + (tempyVelocityShip * tempyVelocityShip))) < currentSpeed) {

					exhaustTotalTime = 80;

					xVelocityShip += cos((shipRotationAngleReal)*3.14159 / 180) / 3.6;
					yVelocityShip += sin((shipRotationAngleReal)*3.14159 / 180) / 3.6;

				}

			}
		}
	}

	if (exhaustTotalTime == 1) {
		for (int i = 0; i < 150; i++) {
			exhaustOn[i] = false;
			exhaustTime[i] = 0;
		}
	}

	if (exhaustTotalTime > 0) {
		exhaustTotalTime--;
		if(spaceKeyPressed2){
		for (int i = 0; i < 150; i++) {
			if (exhaustOn[i] == false) {
				//setting exhaust initial variables
				if (rand() % 15 == 2) {
					exhaustOn[i] = true;
					exhaustTime[i] = 28 + (rand() % 3);
					exhaustXHold[i] = sin((shipRotationAngleReal-90)*3.14159 / 180);
					exhaustYHold[i] = cos((shipRotationAngleReal-90)*3.14159 / 180);

						exhaustX[i] = 750 + (rand() % 10);
						exhaustY[i] = 500 + (rand() % 10);
				}
			}
			}
		}
		
	}


	//drawing exhaust
	if (exhaustTotalTime > 0) {
		for (int i = 0; i < 150; i++) {

			if (exhaustTime[i] <= 0) {
				exhaustOn[i] = false;
			}

			if (exhaustOn[i]) {
				if (exhaustTime[i] > 0) {
					exhaustTime[i]--;
					exhaustX[i] = exhaustX[i] + (6 * exhaustXHold[i]);
					exhaustY[i] = exhaustY[i] + (6 * exhaustYHold[i]);

					if (exhaustTime[i] < 21) {
						SDL_Rect fillRect = { exhaustX[i] * state2resizeImageXVar1, exhaustY[i] * state2resizeImageYVar1, 2 * state2resizeImageXVar1, 2 * state2resizeImageYVar1 };

						//red, green, blue, opaqueness
						SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
						SDL_RenderFillRect(Game::renderer, &fillRect);
					}
				}
			}
		}
	}
	//////////////    UPDATING X AND Y COORDINATES OF PLAYER ///////////
	playerXCoordinate += (xVelocityShip);
	playerYCoordinate += (yVelocityShip);
	
	//drag on player...
	
	if (xVelocityShip > 0.01) {
		xVelocityShip -= 0.005;
	}
	if (xVelocityShip < -0.01) {
		xVelocityShip += 0.005;
	}

	if (yVelocityShip > 0.01) {
		yVelocityShip -= 0.005;
	}
	if (yVelocityShip < -0.01) {
		yVelocityShip += 0.005;
	}

	////////////////        DRAWING PLANET STUFF        //////////////////////

	for (int z = 0; z < 12; z++) {

		if(chunkActualLoad[z] != ""){

		for (int i = 0; i < 50; i++) {

			if (planetX[i][z] != 0 || planetY[i][z] != 0) {

				//testing if planet actually appears on screen
				if ((correctingMapPlacementX(planetX[i][z]) + planetDiameter[i] > 0) && (((correctingMapPlacementX(planetX[i][z])) - planetDiameter[i][z]) < 1500)) {
					if ((correctingMapPlacementY(planetY[i][z]) + planetDiameter[i] > 0) && (((correctingMapPlacementY(planetY[i][z])) - planetDiameter[i][z]) < 1000)) {

						dest.x = correctingMapPlacementX(planetX[i][z]) * state2resizeImageXVar1;
						dest.y = correctingMapPlacementY(planetY[i][z]) * state2resizeImageYVar1;
						dest.w = planetDiameter[i][z] * state2resizeImageXVar1;
						dest.h = planetDiameter[i][z] * state2resizeImageYVar1;

						//which planet to draw

						switch (planetImageNumber[i][z]) {

						case 0:
							SDL_SetTextureColorMod(planet0, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet0, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 1:
							SDL_SetTextureColorMod(planet1, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet1, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 2:
							SDL_SetTextureColorMod(planet2, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet2, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 3:
							SDL_SetTextureColorMod(planet3, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet3, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 4:
							SDL_SetTextureColorMod(planet4, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet4, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 5:
							SDL_SetTextureColorMod(planet5, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet5, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 6:
							SDL_SetTextureColorMod(planet6, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet6, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 7:
							SDL_SetTextureColorMod(planet7, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet7, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 8:
							SDL_SetTextureColorMod(planet8, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet8, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 9:
							SDL_SetTextureColorMod(planet9, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet9, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 10:
							SDL_SetTextureColorMod(planet10, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet10, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 11:
							SDL_SetTextureColorMod(planet11, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet11, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 12:
							SDL_SetTextureColorMod(planet12, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet12, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 13:
							SDL_SetTextureColorMod(planet13, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet13, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 14:
							SDL_SetTextureColorMod(planet14, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet14, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 15:
							SDL_SetTextureColorMod(planet15, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet15, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 16:
							SDL_SetTextureColorMod(planet16, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet16, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 17:
							SDL_SetTextureColorMod(planet17, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet17, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 18:
							SDL_SetTextureColorMod(planet18, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet18, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 19:
							SDL_SetTextureColorMod(planet19, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet19, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 20:
							SDL_SetTextureColorMod(planet20, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet20, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 21:
							SDL_SetTextureColorMod(planet21, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet21, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 22:
							SDL_SetTextureColorMod(planet22, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet22, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 23:
							SDL_SetTextureColorMod(planet23, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet23, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 24:
							SDL_SetTextureColorMod(planet24, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet24, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 25:
							SDL_SetTextureColorMod(planet25, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet25, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 26:
							SDL_SetTextureColorMod(planet26, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet26, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 27:
							SDL_SetTextureColorMod(planet27, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet27, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 28:
							SDL_SetTextureColorMod(planet28, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet28, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						case 29:
							SDL_SetTextureColorMod(planet29, planetR[i][z], planetG[i][z], planetB[i][z]);
							TextureManager::Draw(planet29, src, dest, NULL, NULL, SDL_FLIP_NONE);
							break;
						}

						int xSide = abs(playerXCoordinate - (planetX[i][z] + (planetDiameter[i][z] / 2)));
						int ySide = abs(playerYCoordinate - (planetY[i][z] - (planetDiameter[i][z] / 2)));

						double sideLength = sqrt((xSide *xSide) + (ySide*ySide));

						//minus 15 is for the ships dimension
						if (collisionCounter > 0) {
							collisionCounter--;
						}

						///////////////////////     COLLISION  DETECTION      //////////////////////////
						if (collisionCounter <= 0) {
							if (sideLength - 20 < ((planetDiameter[i][z] / 2))) {

								//taking away player health based on speed
								playerHealth -= sqrt((xVelocityShip*xVelocityShip) + (yVelocityShip*yVelocityShip)) / 1.5;

								game->sendingUserInput(username2 + '#' + "~dmgtaken:" + to_string(playerHealth) + '~');

								//making sure player doesnt glitch inside planet
								if (playerXCoordinate < (planetX[i][z] + planetDiameter[i][z] / 2)) {
									playerXCoordinate -= 2;
								}
								else {
									playerXCoordinate += 2;
								}

								//making sure player doesnt glitch inside planet
								if (playerYCoordinate < (planetY[i][z] - planetDiameter[i][z] / 2)) {
									playerYCoordinate -= 2;
								}
								else {
									playerYCoordinate += 2;
								}

								collisionCounter = 10;

								if ((sqrt((xVelocityShip *xVelocityShip) + (yVelocityShip*yVelocityShip))) > 3) {

									xVelocityShip = xVelocityShip * -1 / 2;
									yVelocityShip = yVelocityShip * -1 / 2;

								}
								else {

									xVelocityShip = xVelocityShip / abs(xVelocityShip) * -1 * 1.5;
									yVelocityShip = yVelocityShip / abs(yVelocityShip) * -1 * 1.5;

								}
							}
						}

					}


					////////////////////// GRAVITY ///////////////////


					///// gravity on player ship
					double xSide1 = (playerXCoordinate - (planetX[i][z] + (planetDiameter[i][z] / 2)));
					double ySide1 = (playerYCoordinate - (planetY[i][z] - (planetDiameter[i][z] / 2)));

					double sideLength1 = sqrt((xSide1 *xSide1) + (ySide1*ySide1));
					
					if (xSide1 != 0 && ySide1 != 0) {
						
							yVelocityShip += -1 * (pow((planetDiameter[i][z]/2 / sideLength1), 1.5)) / 10 * (sin((((atan2((ySide1), (xSide1)) * 180 / PI)))*PI / 180));
							xVelocityShip += -1 * (pow((planetDiameter[i][z]/2 / sideLength1), 1.5)) / 10 * (cos((((atan2((ySide1), (xSide1)) * 180 / PI)))*PI / 180));

					}

				}
			}
			}
		}

	}

	////////////////////////////    DRAWING MINIMAP /////////////////////

		//drawing mini map backdrop
		drawingMiniMapBackdrop();
	
		for (int z = 0; z < 12; z++) {

			if (chunkActualLoad[z] != "") {

				for (int i = 0; i < 50; i++) {

					if (planetX[i][z] != 0 && planetY[i][z] != 0) {


						miniMapPlanetX[i][z] = (1325 + (((correctingMapPlacementX(planetX[i][z] - planetDiameter[i][z])) * 310 / minimapSize / 150)));
						miniMapPlanetY[i][z] = (865 + (((correctingMapPlacementY(planetY[i][z] + planetDiameter[i][z]/1.5)) * 310 / minimapSize / 150)));

						//testing if planet actually appears on screen
						if (miniMapPlanetX[i][z] > 1150 && miniMapPlanetX[i][z] + (planetDiameter[i][z] / 2 / minimapSize) < 1500) {
							if (miniMapPlanetY[i][z] > 750 && miniMapPlanetY[i][z] - (planetDiameter[i][z] / 2 / minimapSize) < 1000) {

								dest.x = miniMapPlanetX[i][z] * state2resizeImageXVar1;
								dest.y = miniMapPlanetY[i][z] * state2resizeImageYVar1;
								dest.w = planetDiameter[i][z] * state2resizeImageXVar1 / minimapSize * 3;
								dest.h = planetDiameter[i][z] * state2resizeImageYVar1 / minimapSize * 3;


								//which planet to draw
								switch (planetImageNumber[i][z]) {

								case 0:
									SDL_SetTextureColorMod(planet0, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet0, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 1:
									SDL_SetTextureColorMod(planet1, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet1, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 2:
									SDL_SetTextureColorMod(planet2, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet2, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 3:
									SDL_SetTextureColorMod(planet3, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet3, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 4:
									SDL_SetTextureColorMod(planet4, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet4, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 5:
									SDL_SetTextureColorMod(planet5, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet5, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 6:
									SDL_SetTextureColorMod(planet6, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet6, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 7:
									SDL_SetTextureColorMod(planet7, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet7, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 8:
									SDL_SetTextureColorMod(planet8, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet8, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 9:
									SDL_SetTextureColorMod(planet9, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet9, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 10:
									SDL_SetTextureColorMod(planet10, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet10, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 11:
									SDL_SetTextureColorMod(planet11, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet11, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 12:
									SDL_SetTextureColorMod(planet12, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet12, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 13:
									SDL_SetTextureColorMod(planet13, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet13, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 14:
									SDL_SetTextureColorMod(planet14, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet14, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 15:
									SDL_SetTextureColorMod(planet15, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet15, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 16:
									SDL_SetTextureColorMod(planet16, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet16, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 17:
									SDL_SetTextureColorMod(planet17, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet17, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 18:
									SDL_SetTextureColorMod(planet18, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet18, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 19:
									SDL_SetTextureColorMod(planet19, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet19, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 20:
									SDL_SetTextureColorMod(planet20, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet20, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 21:
									SDL_SetTextureColorMod(planet21, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet21, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 22:
									SDL_SetTextureColorMod(planet22, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet22, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 23:
									SDL_SetTextureColorMod(planet23, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet23, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 24:
									SDL_SetTextureColorMod(planet24, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet24, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 25:
									SDL_SetTextureColorMod(planet25, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet25, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 26:
									SDL_SetTextureColorMod(planet26, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet26, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 27:
									SDL_SetTextureColorMod(planet27, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet27, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 28:
									SDL_SetTextureColorMod(planet28, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet28, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;
								case 29:
									SDL_SetTextureColorMod(planet29, planetR[i][z], planetG[i][z], planetB[i][z]);
									TextureManager::Draw(planet29, src, dest, NULL, NULL, SDL_FLIP_NONE);
									break;

								}
							}
						}
					}
				}
			}
		}

		//drawing server players on minimap
		for (int i = 0; i < 50; i++) {
			if (serverPlayers[i] != "") {
				//////////////////  DRAWING POINTER ////////////////////////

				if ((1325 + (((155 + correctingMapPlacementX(serverXCoordinate[i] + 200 - 1325)) * 310 / minimapSize / 150))) > 1150 && (1325 + (((155 + correctingMapPlacementX(serverXCoordinate[i] + 200 - 1325)) * 310 / minimapSize / 150))) < 1500) {
					if ((865 + (((115 + correctingMapPlacementY(serverYCoordinate[i] - 200 + 865)) * 310 / minimapSize / 150))) > 750 && (865 + (((115 + correctingMapPlacementY(serverYCoordinate[i] - 200 + 865)) * 310 / minimapSize / 150))) < 1000) {

						dest.x = state2resizeImageXVar1 * (1325 + (((155 + correctingMapPlacementX(serverXCoordinate[i] + 200 - 1325)) * 310 / minimapSize / 150)));
						dest.y = state2resizeImageYVar1 * (865 + (((115 + correctingMapPlacementY(serverYCoordinate[i] - 200 + 865)) * 310 / minimapSize / 150)));
						dest.w = 200 * state2resizeImageXVar1 / minimapSize * 3.5;
						dest.h = 200 * state2resizeImageYVar1 / minimapSize * 3.5;

						TextureManager::Draw(pointerFoe, src, dest, serverRotation[i], NULL, SDL_FLIP_NONE);

					}
				}
			}
		}
//drawing minimap dorber
drawingMiniMapBorder();

//////////////////  DRAWING POINTER ////////////////////////
	//drawing background
dest.x = state2resizeImageXVar1 * 1315;
dest.y = state2resizeImageYVar1 * 855;
dest.w = state2resizeImageXVar1 * 20;
dest.h = state2resizeImageYVar1 * 20;

TextureManager::Draw(pointer, src, dest, shipRotationAngle, NULL, SDL_FLIP_NONE);

///////////////////////    PLAYER X AND Y POSITION //////////////////

stringstream sstr;
sstr << (int)playerXCoordinate;

string str1 = sstr.str();
str1 = "X: " + str1;
TTF_Font* Arial = TTF_OpenFont("assets/arial.ttf", 15);

////// X COORDINATE //////
SDL_Color Color = { 255,255,255 };

SDL_Surface* surfaceMessageX = TTF_RenderText_Solid(Arial, str1.c_str(), Color);

SDL_Texture* MessageX = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessageX);

SDL_Rect MessageX_rect; //create a rect
MessageX_rect.x = 10 * state2resizeImageXVar1;
MessageX_rect.y = 10 * state2resizeImageYVar1;
MessageX_rect.w = 80 * state2resizeImageXVar1;
MessageX_rect.h = 35 * state2resizeImageYVar1;

SDL_RenderCopy(Game::renderer, MessageX, NULL, &MessageX_rect);

SDL_FreeSurface( surfaceMessageX);
SDL_DestroyTexture(MessageX);



////// Y COORDINATE //////

stringstream sstrY;
sstrY << (int)playerYCoordinate;

string str1Y = sstrY.str();
str1Y = "Y: " + str1Y;

SDL_Surface* surfaceMessageY = TTF_RenderText_Solid(Arial, str1Y.c_str(), Color);

SDL_Texture* MessageY = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessageY);

SDL_Rect MessageY_rect; //create a rect
MessageY_rect.x = 10 * state2resizeImageXVar1;
MessageY_rect.y = 40 * state2resizeImageYVar1;
MessageY_rect.w = 80 * state2resizeImageXVar1;
MessageY_rect.h = 35 * state2resizeImageYVar1;

SDL_RenderCopy(Game::renderer, MessageY, NULL, &MessageY_rect);

SDL_FreeSurface(surfaceMessageY);
SDL_DestroyTexture(MessageY);

//////////////// FPS ////////////////////////

stringstream sstrFPS;
sstrFPS << (int)FPSCurrent;

string str1FPS = sstrFPS.str();
str1FPS = "FPS: " + str1FPS;

SDL_Surface* surfaceMessageFPS = TTF_RenderText_Solid(Arial, str1FPS.c_str(), Color);

SDL_Texture* MessageFPS = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessageFPS);

SDL_Rect MessageFPS_rect; //create a rect
MessageFPS_rect.x = 10 * state2resizeImageXVar1;
MessageFPS_rect.y = 90 * state2resizeImageYVar1;
MessageFPS_rect.w = 80 * state2resizeImageXVar1;
MessageFPS_rect.h = 35 * state2resizeImageYVar1;

SDL_RenderCopy(Game::renderer, MessageFPS, NULL, &MessageFPS_rect);

SDL_FreeSurface(surfaceMessageFPS);
SDL_DestroyTexture(MessageFPS);
TTF_CloseFont(Arial);

//////////////////////  DRAWING SHIP      ///////////////////////////////

dest.x = 710 * state2resizeImageXVar1;
dest.y = 458 * state2resizeImageYVar1;
dest.w = 80 * state2resizeImageXVar1;
dest.h = 84 * state2resizeImageYVar1;

TextureManager::Draw(playerShip, src, dest, shipRotationAngle, NULL, SDL_FLIP_NONE);

////////////////  DRAWING SERVER SHIPS AND EXHAUST /////////////////////
for (int i = 0; i < 50; i++) {
	if (serverPlayers[i] != "") {
		serverXCoordinateHold[i] += serverSpeedX[i];
		serverYCoordinateHold[i] += serverSpeedY[i];

		//////// drawing server exhaust ////////////



//init for random number
		if (spaceKeyPressedServer[i]) {
			exhaustTotalTimeServer[i] = 100;
		}
		if (exhaustTotalTimeServer[i] == 1) {
			for (int abc = 0; abc < 150; abc++) {
				exhaustOnServer[i][abc] = false;
				exhaustTimeServer[i][abc] = 0;
			}
		}

		if (exhaustTotalTimeServer[i] > 0) {
			exhaustTotalTimeServer[i]--;
			if (spaceKeyPressedServer[i]) {
				for (int abc = 0; abc < 150; abc++) {
					if (exhaustOnServer[i][abc] == false) {
						//setting exhaust initial variables
						if (rand() % 15 == 2) {
							exhaustOnServer[i][abc] = true;
							exhaustTimeServer[i][abc] = 28 + (rand() % 3);
							
							//exhaustXHold[i] = sin((shipRotationAngleReal - 90)*3.14159 / 180);
							//exhaustYHold[i] = cos((shipRotationAngleReal - 90)*3.14159 / 180);

							exhaustXHoldServer[i][abc] = -1*cos((serverRotationHold[i] - 90)*3.14159 / 180);
							exhaustYHoldServer[i][abc] = -1*sin((serverRotationHold[i] - 90)*3.14159 / 180);

							exhaustXServer[i][abc] = correctingMapPlacementX(serverXCoordinateHold[i] + 27) + (rand() % 10);
							exhaustYServer[i][abc] = correctingMapPlacementY(serverYCoordinateHold[i] - 47) + (rand() % 10);
						}
					}
				}
			}

		}


		//drawing exhaust
		if (exhaustTotalTimeServer[i] > 0) {
			for (int abc = 0; abc < 150; abc++) {

				if (exhaustTimeServer[i][abc] <= 0) {
					exhaustOnServer[i][abc] = false;
				}

				if (exhaustOnServer[i][abc]) {
					if (exhaustTimeServer[i][abc] > 0) {
						exhaustTimeServer[i][abc]--;
						exhaustXServer[i][abc]   += ((6 * exhaustXHoldServer[i][abc]) - xVelocityShip);
						exhaustYServer[i][abc] += (6 * exhaustYHoldServer[i][abc]) + yVelocityShip;

						double var = sqrt((serverSpeedX[i] * serverSpeedX[i]) + (serverSpeedY[i] * serverSpeedY[i]));

						if (exhaustTimeServer[i][abc] < 22 + ((var/8.8)*2.8) ) {
							SDL_Rect fillRect = { exhaustXServer[i][abc] * state2resizeImageXVar1, exhaustYServer[i][abc] * state2resizeImageYVar1, 2 * state2resizeImageXVar1, 2 * state2resizeImageYVar1 };

							//red, green, blue, opaqueness
							SDL_SetRenderDrawColor(Game::renderer, 255, 255, 0, 255);
							SDL_RenderFillRect(Game::renderer, &fillRect);
						}
					}
				}
			}
		}




		////// drawing server ship stuff ////////////
		//accounting for drag..
		if (serverSpeedX[i] > 0.01) {
			serverSpeedX[i] -= 0.005;
		}
		if (serverSpeedX[i] < -0.01) {
			serverSpeedX[i] += 0.005;
		}

		if (serverSpeedY[i] > 0.01) {
			serverSpeedY[i] -= 0.005;
		}
		if (serverSpeedY[i] < -0.01) {
			serverSpeedY[i] += 0.005;
		}

		//setting x and y coordinate closer to last known xy
		if (serverXCoordinateHold[i] > serverXCoordinate[i] + 50) {
			serverXCoordinateHold[i] -= 7;
		}
		else if (serverXCoordinateHold[i] > serverXCoordinate[i] + 40) {
			serverXCoordinateHold[i] -= 5;
		}
		else if (serverXCoordinateHold[i] > serverXCoordinate[i] + 30) {
			serverXCoordinateHold[i] -= 4;
		}
		else if (serverXCoordinateHold[i] > serverXCoordinate[i] + 15) {
			serverXCoordinateHold[i] -= 3;
		}
		else if (serverXCoordinateHold[i] > serverXCoordinate[i] + 5) {
			serverXCoordinateHold[i] -= 2;
		}
		else if (serverXCoordinateHold[i] > serverXCoordinate[i] + 2) {
			serverXCoordinateHold[i] -= 1;
		}



		if (serverXCoordinateHold[i] < serverXCoordinate[i] - 50) {
			serverXCoordinateHold[i] += 7;
		}
		else if (serverXCoordinateHold[i] < serverXCoordinate[i] - 40) {
			serverXCoordinateHold[i] += 5;
		}
		else if (serverXCoordinateHold[i] < serverXCoordinate[i] - 30) {
			serverXCoordinateHold[i] += 4;
		}
		else if (serverXCoordinateHold[i] < serverXCoordinate[i] - 15) {
			serverXCoordinateHold[i] += 3;
		}
		else if (serverXCoordinateHold[i] < serverXCoordinate[i] - 5) {
			serverXCoordinateHold[i] += 2;
		}
		else if (serverXCoordinateHold[i] < serverXCoordinate[i] - 2) {
			serverXCoordinateHold[i] += 1;
		}

		if (serverYCoordinateHold[i] > serverYCoordinate[i] + 50) {
			serverYCoordinateHold[i] -= 7;
		}
		else if (serverYCoordinateHold[i] > serverYCoordinate[i] + 40) {
			serverYCoordinateHold[i] -= 5;
		}
		else if (serverYCoordinateHold[i] > serverYCoordinate[i] + 30) {
			serverYCoordinateHold[i] -= 4;
		}
		else if (serverYCoordinateHold[i] > serverYCoordinate[i] + 15) {
			serverYCoordinateHold[i] -= 3;
		}
		else if (serverYCoordinateHold[i] > serverYCoordinate[i] + 5) {
			serverYCoordinateHold[i] -= 2;
		}
		else if (serverYCoordinateHold[i] > serverYCoordinate[i] + 2) {
			serverYCoordinateHold[i] -= 1;
		}

		if (serverYCoordinateHold[i] < serverYCoordinate[i] - 50) {
			serverYCoordinateHold[i] += 7;
		}
		else if (serverYCoordinateHold[i] < serverYCoordinate[i] - 40) {
			serverYCoordinateHold[i] += 5;
		}
		else if (serverYCoordinateHold[i] < serverYCoordinate[i] - 30) {
			serverYCoordinateHold[i] += 4;
		}
		else if (serverYCoordinateHold[i] < serverYCoordinate[i] - 15) {
			serverYCoordinateHold[i] += 3;
		}
		else if (serverYCoordinateHold[i] < serverYCoordinate[i] - 5) {
			serverYCoordinateHold[i] += 2;
		}
		else if (serverYCoordinateHold[i] < serverYCoordinate[i] - 2) {
			serverYCoordinateHold[i] += 1;
		}

		//drawing server rotation for server ships

		if (serverRotationHold[i] < serverRotation[i] + 2) {
			serverRotationHold[i] += 4;
		}
		if (serverRotationHold[i] > serverRotation[i] - 2) {
			serverRotationHold[i] -= 4;
		}

		//checking if x and y are too far away
		if (abs(abs(serverXCoordinateHold[i]) - abs(serverXCoordinate[i])) > 65 ){
			serverXCoordinateHold[i] = serverXCoordinate[i];
			serverYCoordinateHold[i] = serverYCoordinate[i];
		}

		if (abs(abs(serverYCoordinateHold[i]) - abs(serverYCoordinate[i])) > 65) {
			serverYCoordinateHold[i] = serverYCoordinate[i];
			serverXCoordinateHold[i] = serverXCoordinate[i];
		}

			dest.x = correctingMapPlacementX(serverXCoordinateHold[i]) * state2resizeImageXVar1;
			dest.y = correctingMapPlacementY(serverYCoordinateHold[i]) * state2resizeImageYVar1;
			dest.w = 80 * state2resizeImageXVar1;
			dest.h = 84 * state2resizeImageYVar1;

			TextureManager::Draw(playerShip, src, dest, serverRotationHold[i], NULL, SDL_FLIP_NONE);
		}
	}

	//////////   drawing speed bar stuff ////////

	//speed bar background 
	SDL_Rect fillRect11 = { 1150 * state2resizeImageXVar1,699 * state2resizeImageYVar1, 175 * state2resizeImageXVar1, 28 * state2resizeImageYVar1 };

	//red, green, blue, opaqueness
	SDL_SetRenderDrawColor(Game::renderer, 62,62,62, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect11);

	currentSpeed = sqrt((xVelocityShip * xVelocityShip) + (yVelocityShip * yVelocityShip));

	//testing if speedbar is at max or not

	////////////////////////////// speedBar /////////////////////////////////////

	if (currentSpeed > maxSpeed) {
		SDL_Rect fillRect10 = { 1150 * state2resizeImageXVar1,699 * state2resizeImageYVar1, 175 * state2resizeImageXVar1, 28 * state2resizeImageYVar1 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 226, 138, 0, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect10);
	}
	else {
	
		SDL_Rect fillRect12 = { 1150 * state2resizeImageXVar1,699 * state2resizeImageYVar1, (175 * currentSpeed / maxSpeed) * state2resizeImageXVar1, 28 * state2resizeImageYVar1 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 200, 165, 38, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect12);

	}


	//overlay
	dest.x = 1150 * state2resizeImageXVar1;
	dest.y = 695 * state2resizeImageYVar1;
	dest.w = 175 * state2resizeImageXVar1;
	dest.h = 35 * state2resizeImageYVar1;

	TextureManager::Draw(speedBar, src, dest, NULL, NULL, SDL_FLIP_NONE);



	//calling f key function
	fKeyActions();

	//updating time things for shots
	updateTimeStuff();

	//drawing shots
	drawShots();

	//making shoot timer go back to zero
	if (shootTimer > 0) {
		shootTimer--;
	}

	////////////////// collision between server players and player ///////////////
	for (int z = 0; z < 50; z++) {
		if (serverPlayers[z] != "") {

			int xSide2 = abs(serverXCoordinateHold[z] - playerXCoordinate + 40);
			int ySide2 = abs(serverYCoordinateHold[z] - playerYCoordinate - 40);

			int sideLength = sqrt((xSide2 *xSide2) + (ySide2*ySide2));

			//minus 15 is for the ships dimension
			if (collisionCounter > 0) {
				collisionCounter--;
			}

			///////////////////////     COLLISION  DETECTION  PLAYERS    //////////////////////////
			if (collisionCounter <= 0) {
				if (sideLength < 55) {

					//making sure player doesnt glitch inside server player
					if (playerXCoordinate < (serverXCoordinateHold[z] + 40)) {
						playerXCoordinate -= 2;
					}
					else {
						playerXCoordinate += 2;
					}

					//making sure player doesnt glitch inside server player
					if (playerYCoordinate < (serverYCoordinateHold[z] - 40)) {
						playerYCoordinate -= 2;
					}
					else {
						playerYCoordinate += 2;
					}

					collisionCounter = 10;

					if ((sqrt((xVelocityShip *xVelocityShip) + (yVelocityShip*yVelocityShip))) > 3) {

						xVelocityShip = xVelocityShip * -1 / 2;
						yVelocityShip = yVelocityShip * -1 / 2;

					}
					else {

						xVelocityShip = xVelocityShip / abs(xVelocityShip) * -1 * 1.5;
						yVelocityShip = yVelocityShip / abs(yVelocityShip) * -1 * 1.5;

					}
				}
			}


		}
	}

	//drawing server health bar
	drawingServerHealthBar();

	//drawing health bar!
	drawingHealthBar();

	//drawing experience bar bg

	dest.x = 300 * state2resizeImageXVar1;
	dest.y = 40 * state2resizeImageYVar1;
	dest.w = state2resizeImageXVar1 * 900;
	dest.h = state2resizeImageYVar1 * 65;

	//currentExperience++;

	TextureManager::Draw(experience_bar_bg, src, dest, NULL, NULL, SDL_FLIP_NONE);

	//drawing experience bar level
	SDL_Rect fillRect22 = { 338 * state2resizeImageXVar1,55 * state2resizeImageYVar1, (839 * currentExperience) / currentMaxExperience * state2resizeImageXVar1, 26 * state2resizeImageYVar1 };

	//red, green, blue, opaqueness
	SDL_SetRenderDrawColor(Game::renderer, 243, 51, 21, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect22);

	//drawing experience bar

	dest.x = 300 * state2resizeImageXVar1;
	dest.y = 40 * state2resizeImageYVar1;
	dest.w = state2resizeImageXVar1 * 900;
	dest.h = state2resizeImageYVar1 * 65;

	TextureManager::Draw(experience_bar, src, dest, NULL, NULL, SDL_FLIP_NONE);

	/////////////// DRAWING CURRENT LEVEL //////////////
	TTF_Font* Arial5 = TTF_OpenFont("assets/arial.ttf", 15);
	SDL_Color Color5 = { 0,0,0 };

	stringstream sstrcurrentLevel;
	sstrcurrentLevel << (int)currentLevel;

	string str1currentLevel = "Level " + sstrcurrentLevel.str();

	SDL_Surface* surfaceMessageExp = TTF_RenderText_Solid(Arial5, str1currentLevel.c_str(), Color5);

	SDL_Texture* MessageExp = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessageExp);

	SDL_Rect MessageExp_rect; //create a rect
	MessageExp_rect.x = 700 * state2resizeImageXVar1;
	MessageExp_rect.y = 52 * state2resizeImageYVar1;
	MessageExp_rect.w = 100 * state2resizeImageXVar1;
	MessageExp_rect.h = 33 * state2resizeImageYVar1;

	SDL_RenderCopy(Game::renderer, MessageExp, NULL, &MessageExp_rect);

	SDL_FreeSurface(surfaceMessageExp);
	SDL_DestroyTexture(MessageExp);
	TTF_CloseFont(Arial5);

	//calculating experience bar level
	if (currentExperience >= currentMaxExperience) {
		currentLevel++;
		currentExperience = 0 + (currentExperience - currentMaxExperience);
		if (currentLevel < 5) {
			currentMaxExperience += 50;
		}
		else if (currentLevel < 10) {
			currentMaxExperience += 100;
		}
		else if (currentLevel < 15) {
			currentMaxExperience += 150;
		}
		else if (currentLevel < 20) {
			currentMaxExperience += 200;
		}
		else if (currentLevel < 25) {
			currentMaxExperience += 250;
		}
		else if (currentLevel < 30) {
			currentMaxExperience += 300;
		}
		else if (currentLevel < 35){
			currentMaxExperience += 350;
		}
		else if (currentLevel < 40) {
			currentMaxExperience += 400;
		}
		else if (currentLevel < 45) {
			currentMaxExperience += 450;
		}
		else {
			currentMaxExperience += 500;
		}
	}

	for (int i = 0; i < 50; i++) {
		if (serverExperienceTimer[i] > 0) {
			serverExperienceTimer[i]--;
		}
	}

}

//getting size of screen

void state2::statetwoResizeX2(int x) {
	state2resizeImageXVar1 = (double)x / 1500;
}

void state2::statetwoResizeY2(int x) {
	state2resizeImageYVar1 = (double)x / 1000;
}


//getting mouse events
void state2::getLeftButton2(bool x) {
	state2isLeftButtonPressed = x;
}

void state2::getMouseX2(int x) {
	state2mouseX = ((double)x*(1500 / (state2resizeImageXVar1 * 1500)));
}

void state2::getMouseY2(int x) {
	state2mouseY = ((double)x*(1000 / (state2resizeImageYVar1 * 1000)));
}

//getting keyboard events
void state2::getUpKeyPressed2(bool b) {
	upKeyPressed2 = b;
}

void state2::getLeftKeyPressed2(bool b) {
	leftKeyPressed2 = b;
}

void state2::getRightKeyPressed2(bool b) {
	rightKeyPressed2 = b;
}

void state2::getDownKeyPressed2(bool b) {
	downKeyPressed2 = b;
}

void state2::getSpaceKeyPressed2(bool b) {
	spaceKeyPressed2 = b;
}

void state2::getFKeyPressed2(bool b) {
	FKeyPressed2 = b;
}

void state2::declaringBackgroundStars() {

	for (int i = 0; i < 100; i++) {

		//random number variable
		int xRand = (rand() % 3000) + 1;
		int yRand = (rand() % 2000) + 1;

		xInitial[i] = xRand;
		yInitial[i] = yRand;
	}
}

//getting right map placement for x
int state2::correctingMapPlacementX(int x) {
	int properX = 0;
	properX = (x - playerXCoordinate) + 750;
	return properX;
}

//getting right map placement for y
int state2::correctingMapPlacementY(int x) {
	int properY = 0;
	properY = (playerYCoordinate - x) + 500;
	return properY;
}

void state2::drawingMiniMapBorder() {

	////// bottom side /////
	SDL_Rect fillRect2 = { 1150 * state2resizeImageXVar1, 980 * state2resizeImageYVar1, 350 * state2resizeImageXVar1, 20 * state2resizeImageYVar1 };

	//red, green, blue, opaqueness
	SDL_SetRenderDrawColor(Game::renderer, 27, 50, 117, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect2);

	////// top side /////
	SDL_Rect fillRect3 = { 1150 * state2resizeImageXVar1, 730 * state2resizeImageYVar1, 350 * state2resizeImageXVar1, 20 * state2resizeImageYVar1 };

	//red, green, blue, opaqueness
	SDL_SetRenderDrawColor(Game::renderer, 27, 50, 117, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect3);

	////// left side /////
	SDL_Rect fillRect4 = { 1150 * state2resizeImageXVar1, 730 * state2resizeImageYVar1, 20 * state2resizeImageXVar1, 350 * state2resizeImageYVar1 };

	//red, green, blue, opaqueness
	SDL_SetRenderDrawColor(Game::renderer, 27, 50, 117, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect4);

	////// right side /////
	SDL_Rect fillRect5 = { 1480 * state2resizeImageXVar1, 730 * state2resizeImageYVar1, 20 * state2resizeImageXVar1, 350 * state2resizeImageYVar1 };

	//red, green, blue, opaqueness
	SDL_SetRenderDrawColor(Game::renderer, 27, 50, 117, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect5);

}

void state2::drawingMiniMapBackdrop() {
	//////  backdrop /////
	SDL_Rect fillRect6 = { 1150 * state2resizeImageXVar1, 730 * state2resizeImageYVar1, 350 * state2resizeImageXVar1, 280 * state2resizeImageYVar1 };

	//red, green, blue, opaqueness
	SDL_SetRenderDrawColor(Game::renderer, 25, 25, 25, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect6);
}

//getting x cordinate of server players
void state2::getServerPlayersX(int x, string s) {

	int z = -1;

	//finding username...
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == s) {
			z = i;
		}
	}

	//if user is not already added..
	if (z == -1) {
		addUser(s);
	}

	if (z > -1) {
		serverXCoordinate[z] = x;
	}

}

//getting y cordinate of server players
void state2::getServerPlayersY(int x, string s) {

	int z = -1;

	//finding username...
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == s) {
			z = i;
		}
	}

	if (z > -1) {
		serverYCoordinate[z] = x;
	}

}
// getting server rotation
void state2::getServerRotation(int x, string s) {

	int z = -1;

	//finding username...
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == s) {
			z = i;
		}
	}

	if(z > -1) {

		serverRotation[z] = x;
	}
}

//adding username to list of players
void state2::addUser(string s) {

	bool variable = false;
	for (int i = 0; i < 50; i++) {

		if (variable == false) {
			if (serverPlayers[i] == "") {
				serverPlayers[i] = s;
				variable = true;
			}
		}
	}

}

//deleting username from list of players
void state2::playerLeft(string s) {

	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == s) {
			serverPlayers[i] = "";
		}
	}
}

//getting x speed of server players
void state2::getServerSpeedX(double x, string s) {

	int z = -1;

	//finding username...
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == s) {
			z = i;
		}
	}
	//if user is not already added..
	if (z == -1) {
		addUser(s);
	}
	else {

		serverSpeedX[z] = x;
	}
}

//getting health of server players
void state2::getServerHealth(int x, string s) {

	int z = -1;

	//finding username...
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == s) {
			z = i;
		}
	}
	//if user is not already added..
	if (z == -1) {
		addUser(s);
	}
	else {

		serverCurrentHealth[z] = x;
	}
}

//getting hits on server players
void state2::getServerHits(string s, string a) {

	int z = -1;

	//finding username...
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == a) {
			z = i;
		}
	}
	//if user is not already added..
	if (z == -1) {
		addUser(s);
	}
	else {

		if(s == username2){

			serverExperienceTimer[z] = 1000;

		}

	}
}

//getting y speed of server players
void state2::getServerSpeedY(double x, string s) {

	int z = -1;

	//finding username...
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == s) {
			z = i;
		}
	}
	//if user is not already added..
	if (z == -1) {
		addUser(s);
	}
	else {

		serverSpeedY[z] = x;
	}
}

//getting space bar pressed
void state2::getServerSpacekey(string x, string s) {

	int z = -1;

	//finding username...
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] == s) {
			z = i;
		}
	}
	//if user is not already added..
	if (z == -1) {
		addUser(s);
	}
	else {
		if (x == "false") {
			spaceKeyPressedServer[z] = false;
		}

		if(x == "true") {
			spaceKeyPressedServer[z] = true;
		}
	}
}

//loading chunks individually
void state2::loadChunks() {

		if (chunkCurrentLoads.size() > 0) {

			game->sendingUserInput("!loadchunk:" + chunkCurrentLoads[0] + "~");
			chunkCurrentLoads.erase(chunkCurrentLoads.begin());
		}
}

void state2::getChunkFromServer(string s) {

	//variable to count down iteration of string
	int counting = 0;

	//deleting "retchunk"
	for (int i = 0; i < 7; i++) {
		s.erase(s.begin());
	}

	vector <string> tempString;

	//pulling out x and y of chunk


	//looping through string input//
	while (s.length() > 2) {

		counting = s.length() - 1;
		bool tempBool = true;

		if (s.length() >= 1) {

			s.erase(s.begin() + counting);
			counting--;

			while (tempBool) {
				if (counting > 0) {
					if (s[counting] != '~') {
						counting--;
					}
					else {
						tempBool = false;
					}
				}
				else {
					tempBool = false;
				}

			}

			//tempString.push_back(s.substr(counting + 1, ((userInput2.length() - 1) - counting + 1)));
			tempString.push_back(s.substr(counting + 1, ((s.length() - 1) - counting + 1)));

			s.erase(counting, ((s.length() - 1) - counting));
		}

	}

	////// reversing string //////
	reverse(tempString.begin(), tempString.end());

	string tempX = "";
	string tempY = "";

	//int for where values are being stored
	int valueStored = 0;

	//int for looping through storing variables
	int valueStoredCounter = 0;

	//ints for loading stuff from chunks into variables
	int planetXCount = 0;
	int planetYCount = 0;
	int planetDiameterCount = 0;
	int planetRCount = 0;
	int planetGCount = 0;
	int planetBCount = 0;
	int planetImageCount = 0;

	///// storing values //////

	for (int i = 0; i < tempString.size(); i++) {

		//storing x
		if (i == 0) {
			tempX = tempString[0];
		}
		//storing y
		if (i == 1) {
			tempY = tempString[1];

			bool chunkFound = false;

			//// finding where chunk will be loaded
			for (int z = 0; z < 12; z++) {

				if (chunkFound == false) {

					if (chunkActualLoad[z] == "") {
						chunkActualLoad[z] = (tempX + "," + tempY);
						chunkFound = true;
						valueStored = z;
					}

				}

			}

		}

		//loading chunks

		if (i > 1) {

			if (valueStoredCounter == 0) {

				planetX[planetXCount][valueStored] = stoi(tempString[i]);
				planetXCount++;

				valueStoredCounter++;
			}
			else if (valueStoredCounter == 1) {
				planetY[planetYCount][valueStored] = stoi(tempString[i]);
				planetYCount++;

				valueStoredCounter++;
			}
			else if (valueStoredCounter == 2) {
				planetDiameter[planetDiameterCount][valueStored] = stoi(tempString[i]);
				planetDiameterCount++;

				valueStoredCounter++;
			}
			else if (valueStoredCounter == 3) {
				planetR[planetRCount][valueStored] = stoi(tempString[i]);
				planetRCount++;

				valueStoredCounter++;
			}
			else if (valueStoredCounter == 4) {
				planetG[planetGCount][valueStored] = stoi(tempString[i]);
				planetGCount++;

				valueStoredCounter++;
			}
			else if (valueStoredCounter == 5) {
				planetB[planetBCount][valueStored] = stoi(tempString[i]);
				planetBCount++;

				valueStoredCounter++;
			}
			else if (valueStoredCounter == 6) {
				planetImageNumber[planetBCount][valueStored] = stoi(tempString[i]);
				planetImageCount++;

				valueStoredCounter = 0;
			}




		}

	}

}

////// default code for shooting right from the front /////////
/*if ((sin((90 - shipRotationAngle)*3.14159 / 180)) > 0) {
	sendMsg += "~xcor:" + to_string((int)playerXCoordinate + ((cos((90 - shipRotationAngle)*3.14159 / 180)) * 40) - ((sin((90 - shipRotationAngle)*3.14159 / 180)) * 13));
}
else {
	sendMsg += "~xcor:" + to_string((int)playerXCoordinate + ((cos((90 - shipRotationAngle)*3.14159 / 180)) * 40) + ((sin((90 - shipRotationAngle)*3.14159 / 180)) * 13));
}

if ((cos((90 - shipRotationAngle)*3.14159 / 180)) > 0) {
	sendMsg += "~ycor:" + to_string((int)playerYCoordinate + ((sin((90 - shipRotationAngle)*3.14159 / 180)) * 40) + ((cos((90 - shipRotationAngle)*3.14159 / 180)) * 25));
}
else {
	sendMsg += "~ycor:" + to_string((int)playerYCoordinate + ((sin((90 - shipRotationAngle)*3.14159 / 180)) * 40) - ((cos((90 - shipRotationAngle)*3.14159 / 180)) * 25));

}*/

//dealing with f key
void state2::fKeyActions() {

	//if the user has pressed 'f' ....
	if (FKeyPressed2) {

		//if shoot timer is ready
		if (shootTimer == 0) {

			//if blaster is selected
			if (typeOfShot == "blaster") {

				shootTimer = 20;
				//we are shooting, username, type of shot, x cordinate, y cordinate, rotation angle

				string sendMsg = "!shoot:";

				sendMsg += "~user:" + username2;
				sendMsg += "~shot:" + typeOfShot;
				sendMsg += "~xvshot:" + to_string(xVelocityShip*1.5);
				sendMsg += "~yvshot:" + to_string(yVelocityShip*1.5);

				//shot 1
				if ((sin((90 - shipRotationAngle)*3.14159 / 180)) > 0) {
					sendMsg += "~xcor1:" + to_string((int)playerXCoordinate + ((cos((90 - shipRotationAngle + 67)*3.14159 / 180)) * 37) - ((sin((90 - shipRotationAngle)*3.14159 / 180)) * 7));
				}
				else {
					sendMsg += "~xcor1:" + to_string((int)playerXCoordinate + ((cos((90 - shipRotationAngle + 67)*3.14159 / 180)) * 37) + ((sin((90 - shipRotationAngle)*3.14159 / 180)) * 7));
				}

				if ((cos((90 - shipRotationAngle)*3.14159 / 180)) > 0) {
					sendMsg += "~ycor1:" + to_string((int)playerYCoordinate + ((sin((90 - shipRotationAngle + 67)*3.14159 / 180)) * 37) + ((cos((90 - shipRotationAngle)*3.14159 / 180)) * 15));
				}
				else {
					sendMsg += "~ycor1:" + to_string((int)playerYCoordinate + ((sin((90 - shipRotationAngle + 67)*3.14159 / 180)) * 37) - ((cos((90 - shipRotationAngle)*3.14159 / 180)) * 15));

				}
				//shot 2
				if ((sin((90 - shipRotationAngle)*3.14159 / 180)) > 0) {
					sendMsg += "~xcor2:" + to_string((int)playerXCoordinate + ((cos((90 - shipRotationAngle - 67)*3.14159 / 180)) * 37) - ((sin((90 - shipRotationAngle)*3.14159 / 180)) * 7));
				}
				else {
					sendMsg += "~xcor2:" + to_string((int)playerXCoordinate + ((cos((90 - shipRotationAngle - 67)*3.14159 / 180)) * 37) + ((sin((90 - shipRotationAngle)*3.14159 / 180)) * 7));
				}

				if ((cos((90 - shipRotationAngle)*3.14159 / 180)) > 0) {
					sendMsg += "~ycor2:" + to_string((int)playerYCoordinate + ((sin((90 - shipRotationAngle - 67)*3.14159 / 180)) * 37) + ((cos((90 - shipRotationAngle)*3.14159 / 180)) * 15));
				}
				else {
					sendMsg += "~ycor2:" + to_string((int)playerYCoordinate + ((sin((90 - shipRotationAngle - 67)*3.14159 / 180)) * 37) - ((cos((90 - shipRotationAngle)*3.14159 / 180)) * 15));

				}

				sendMsg += "~rotat:" + to_string((int)shipRotationAngleReal) + "~";
				game->sendingUserInput(sendMsg);
			}
		}
	}

}

//getting username
void state2::getUsername(string b) {

	username2 = b;

}

void state2::dealWithShooting(string x) {

	//delete beginning
	x.erase(x.begin(), x.begin() + 6);
	//string array for passed in stuff
	vector<string> shootInfo;
	vector<string> shootInfoAll;

	string replacement = x;

	//variable to count down iteration of string
	int counting1 = 0;

	//splitting up shots from multiple into one
	while (replacement.length() > 2) {
		counting1 = replacement.length() - 1;
		bool tempBool = true;

		if (replacement.length() > 2) {

			replacement.erase(replacement.begin() + counting1);
			counting1--;

			while (tempBool) {

				if (replacement[counting1] != '/') {
					counting1--;
				}
				else {
					tempBool = false;
				}
			}

			shootInfoAll.push_back(replacement.substr(counting1 + 1, ((replacement.length() - 1) - counting1 + 1)));
			replacement.erase(counting1, ((replacement.length() - 1) - counting1));
		}
	}

	//looping through all inputs we recieved
	for (int a = 0; a < shootInfoAll.size(); a++) {

		int counting = 0;

		//getting out inputs we need
		while (shootInfoAll[a].length() > 2) {
			counting = shootInfoAll[a].length() - 1;
			bool tempBool = true;

			if (shootInfoAll[a].length() > 2) {

				shootInfoAll[a].erase(shootInfoAll[a].begin() + counting);
				counting--;

				while (tempBool) {

					if (shootInfoAll[a][counting] != '~') {
						counting--;
					}
					else {
						tempBool = false;
					}

				}
				
				shootInfo.push_back(shootInfoAll[a].substr(counting + 1, ((shootInfoAll[a].length() - 1) - counting + 1)));
				shootInfoAll[a].erase(counting, ((shootInfoAll[a].length() - 1) - counting));
			}


		}

		//dealing with shoot inputs

		bool shotExists = false;
		int shotPlaceHolder = 0;
		//seeing if unique name is taken already
		for (int z = 0; z < uniqueName.size(); z++) {
			for (int i = 0; i < shootInfo.size(); i++) {

				if (shootInfo[i] == (("uniname:" + uniqueName[z]))) {
					shotExists = true;
					shotPlaceHolder = z;
				}

			}

		}

		if (shotExists) {
			// if shot already exists
			/*for (int i = 0; i < shootInfo.size(); i++) {

				if (shootInfo[i][0] == 'x' && shootInfo[i][1] == 'c' && shootInfo[i][2] == 'o' && shootInfo[i][3] == 'r') {
					shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 5);
						shotXHold[shotPlaceHolder] = stoi(shootInfo[i]);
				}
				if (shootInfo[i][0] == 'y' && shootInfo[i][1] == 'c' && shootInfo[i][2] == 'o' && shootInfo[i][3] == 'r') {
					shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 5);
						shotYHold[shotPlaceHolder] = stoi(shootInfo[i]);
				}
				if (shootInfo[i][0] == 'r' && shootInfo[i][1] == 'o' && shootInfo[i][2] == 't' && shootInfo[i][3] == 'a') {
					shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 6);
						shotRotation[shotPlaceHolder] = (stoi(shootInfo[i]));
				}
				if (shootInfo[i][0] == 't' && shootInfo[i][1] == 'i' && shootInfo[i][2] == 'm' && shootInfo[i][3] == 'e') {
					shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 9);
					shotTime[shotPlaceHolder] = (stoi(shootInfo[i]));
				}

			}*/

		}
		else {

			//check if everything we need is here//
			int countItems = 0;

			for (int i = 0; i < shootInfo.size(); i++) {
				string shootInfo2 = shootInfo[i];

				if (shootInfo2[0] == 'u' && shootInfo2[1] == 's' && shootInfo2[2] == 'e' && shootInfo2[3] == 'r') {
					countItems++;

				}
					if (shootInfo2[0] == 's' && shootInfo2[1] == 'h' && shootInfo2[2] == 'o' && shootInfo2[3] == 't') {
						countItems++;
					}
						if (shootInfo2[0] == 'x' && shootInfo2[1] == 'c' && shootInfo2[2] == 'o' && shootInfo2[3] == 'r') {
							countItems++;
						}
							if (shootInfo2[0] == 'y' && shootInfo2[1] == 'c' && shootInfo2[2] == 'o' && shootInfo2[3] == 'r') {
								countItems++;
							}
								if (shootInfo2[0] == 'r' && shootInfo2[1] == 'o' && shootInfo2[2] == 't' && shootInfo2[3] == 'a') {
									countItems++;
								}
									if (shootInfo2[0] == 'u' && shootInfo2[1] == 'n' && shootInfo2[2] == 'i' && shootInfo2[3] == 'n') {
										countItems++;
									}
										if (shootInfo2[0] == 'x' && shootInfo2[1] == 'v' && shootInfo2[2] == 's' && shootInfo2[3] == 'h' && shootInfo2[4] == 'o' && shootInfo2[5] == 't') {
											countItems++;
										}
											if (shootInfo2[0] == 'y' && shootInfo2[1] == 'v' && shootInfo2[2] == 's' && shootInfo2[3] == 'h' && shootInfo2[4] == 'o' && shootInfo2[5] == 't') {
												countItems++;
											}
			}

			//if shot is new

			//if shot info contains everything we need
			if (countItems == 8) {
				for (int i = 0; i < shootInfo.size(); i++) {

					if (shootInfo[i][0] == 'u' && shootInfo[i][1] == 's' && shootInfo[i][2] == 'e' && shootInfo[i][3] == 'r') {
						shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 5);
						shotName.push_back(shootInfo[i]);
					}
					if (shootInfo[i][0] == 's' && shootInfo[i][1] == 'h' && shootInfo[i][2] == 'o' && shootInfo[i][3] == 't') {
						shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 5);
						shotType.push_back(shootInfo[i]);
					}
					if (shootInfo[i][0] == 'x' && shootInfo[i][1] == 'c' && shootInfo[i][2] == 'o' && shootInfo[i][3] == 'r') {
						shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 5);
						shotXHold.push_back(stoi(shootInfo[i]));
					}
					if (shootInfo[i][0] == 'y' && shootInfo[i][1] == 'c' && shootInfo[i][2] == 'o' && shootInfo[i][3] == 'r') {
						shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 5);
						shotYHold.push_back(stoi(shootInfo[i]));
					}
					if (shootInfo[i][0] == 'r' && shootInfo[i][1] == 'o' && shootInfo[i][2] == 't' && shootInfo[i][3] == 'a') {
						shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 6);
						shotRotation.push_back(stoi(shootInfo[i]));
					}
					if (shootInfo[i][0] == 'u' && shootInfo[i][1] == 'n' && shootInfo[i][2] == 'i' && shootInfo[i][3] == 'n') {
						shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 8);
						uniqueName.push_back(shootInfo[i]);
					}
					if (shootInfo[i][0] == 'x' && shootInfo[i][1] == 'v' && shootInfo[i][2] == 's' && shootInfo[i][3] == 'h' && shootInfo[i][4] == 'o' && shootInfo[i][5] == 't') {
						shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 7);
						shotStartVelocityX.push_back(stoi(shootInfo[i]));
					}
					if (shootInfo[i][0] == 'y' && shootInfo[i][1] == 'v' && shootInfo[i][2] == 's' && shootInfo[i][3] == 'h' && shootInfo[i][4] == 'o' && shootInfo[i][5] == 't') {
						shootInfo[i].erase(shootInfo[i].begin(), shootInfo[i].begin() + 7);
						shotStartVelocityY.push_back(stoi(shootInfo[i]));
					}

				}
				shotTime.push_back(0);
				shotHit.push_back(false);
			}

		}

		for (int i = 0; i < shootInfo.size(); i++) {
			shootInfo[i] = "";
		}
	}

	for (int i = 0; i < shootInfoAll.size(); i++) {
		shootInfoAll[i] = "";
	}

}

//drawing shots
void state2::drawShots() {

	for (int g = 0; g < uniqueName.size(); g++) {
		//overlay
		//correctingMapPlacementX(shotX[g])
			//correctingMapPlacementY(shotY[g])

		//if shot is not hit
		if (shotHit[g] == false) {

			dest.x = correctingMapPlacementX(shotXHold[g]) * state2resizeImageXVar1;
			dest.y = correctingMapPlacementY(shotYHold[g]) * state2resizeImageYVar1;
			dest.w = 15 * state2resizeImageXVar1;
			dest.h = 30 * state2resizeImageYVar1;

			TextureManager::Draw(bullet1, src, dest, 90 - shotRotation[g], NULL, SDL_FLIP_NONE);
		}
		if (shotTime[g] >= 25) {
			uniqueName.erase(uniqueName.begin() + g);
			shotName.erase(shotName.begin() + g);
			shotRotation.erase(shotRotation.begin() + g);
			shotType.erase(shotType.begin() + g);
			shotTime.erase(shotTime.begin() + g);
			shotHit.erase(shotHit.begin() + g);
			shotXHold.erase(shotXHold.begin() + g);
			shotYHold.erase(shotYHold.begin() + g);
			shotStartVelocityX.erase(shotStartVelocityX.begin() + g);
			shotStartVelocityY.erase(shotStartVelocityY.begin() + g);
		}

	}

}

void state2::updateTimeStuff() {

	//get time passed
	currentTime = std::clock()/ (double)CLOCKS_PER_SEC;
	duration = currentTime - holdTime;

	holdTime = std::clock() / (double)CLOCKS_PER_SEC;

	//getting FPS
	if (FPSCounter < 1) {
		FPSCounter += duration;
		FPSTime++;
	}
	else {
		FPSCurrent = FPSTime;
		FPSCounter = 0;
		FPSTime = 0;
	}

		////// every frame stuff goes here ///////
		for (int i = 0; i < shotXHold.size(); i++) {

			shotTime[i]+= (duration/0.033333);

				shotXHold[i] += ((cos((shotRotation[i])*3.14159 / 180) * 35 ) + shotStartVelocityX[i])*(duration/0.0333333);
				shotYHold[i] += ((sin((shotRotation[i])*3.14159 / 180) * 35 ) + shotStartVelocityY[i])*(duration/0.0333333);
				////////////////// if bullet hits other players ship ////////////////

				//looping through ships
				for (int z = 0; z < 50; z++) {
					if (serverPlayers[z] != "") {
						if (shotName[i] != serverPlayers[z]) {


							int xSide2 = abs(serverXCoordinateHold[z] - shotXHold[i]);
							int ySide2 = abs(serverYCoordinateHold[z] - shotYHold[i]);

							int sideLength = sqrt((xSide2 *xSide2) + (ySide2*ySide2));


							if (sideLength < 70) {

								shotHit[i] = true;
							}

						}

					}
				}

				///////////////// if another players bullet hits our ship ////////////////////
				if (shotName[i] != username2) {
					int xSide3 = abs(playerXCoordinate - shotXHold[i]);
					int ySide3 = abs(playerYCoordinate - shotYHold[i]);

					int sideLength3 = sqrt((xSide3 *xSide3) + (ySide3*ySide3));


					if (sideLength3 < 70) {


						if (shotType[i] == "blaster" && shotHit[i] == false) {
							playerHealth -= 10;

							string msg = "";
							msg = username2 + '#';

							msg += "~dmgtaken:" + to_string(playerHealth);
							//player who hit us
							msg += "~plrhit:" + shotName[i] + '~';

							game->sendingUserInput(msg);
						}

						shotHit[i] = true;

					}
				}

				//////////// if bullet hits a planet ///////////////
				for (int a = 0; a < 12; a++) {

					if (chunkActualLoad[a] != "") {

						for (int b = 0; b < 50; b++) {

							if (planetX[b][a] != 0 || planetY[b][a] != 0) {


								int xSide = abs(shotXHold[i] - (planetX[b][a] + (planetDiameter[b][a] / 2)));
								int ySide = abs(shotYHold[i] - (planetY[b][a] - (planetDiameter[b][a] / 2)));

								double sideLength = sqrt((xSide *xSide) + (ySide*ySide));

								if (sideLength - 20 < ((planetDiameter[b][a] / 2))) {

									shotHit[i] = true;
								}

							}
						}
					}
				}
			
		}


}

void state2::drawingHealthBar() {

	//making health bar above 0 and making sure death is sent to players
	if (playerHealth < 0) {
		playerHealth = 0;

		/*string msg = "";
		msg = username2 + '#';

		msg += "~dmgtaken:" + to_string(playerHealth);
		//player who hit us
		msg += "~plrhit:" + shotName[i] + '~';

		game->sendingUserInput(msg);*/
	}

	//////////   drawing health bar stuff ////////

//health bar background 
	SDL_Rect fillRect15 = { 1325 * state2resizeImageXVar1,699 * state2resizeImageYVar1, 175 * state2resizeImageXVar1, 28 * state2resizeImageYVar1 };

	//red, green, blue, opaqueness
	SDL_SetRenderDrawColor(Game::renderer, 62, 62, 62, 255);
	SDL_RenderFillRect(Game::renderer, &fillRect15);

	////////////////////////////// HEALTH BAR /////////////////////////////////////


		SDL_Rect fillRect12 = { 1325 * state2resizeImageXVar1,699 * state2resizeImageYVar1, (175 * playerHealth / playerMaxHealth) * state2resizeImageXVar1, 28 * state2resizeImageYVar1 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 243, 51, 21, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect12);


		//overlay for health Bar
		dest.x = 1325 * state2resizeImageXVar1;
		dest.y = 695 * state2resizeImageYVar1;
		dest.w = 175 * state2resizeImageXVar1;
		dest.h = 35 * state2resizeImageYVar1;

		TextureManager::Draw(healthBar, src, dest, NULL, NULL, SDL_FLIP_NONE);

		////////////////// HEALTH BAR ON TOP OF PLAYER ///////////////////

		//health bar background 
		SDL_Rect fillRect16 = { 705 * state2resizeImageXVar1,400 * state2resizeImageYVar1, 90 * state2resizeImageXVar1, 22 * state2resizeImageYVar1 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 62, 62, 62, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect16);

		SDL_Rect fillRect17 = { 705 * state2resizeImageXVar1,400 * state2resizeImageYVar1, (90 * playerHealth / playerMaxHealth) * state2resizeImageXVar1, 22 * state2resizeImageYVar1 };

		//red, green, blue, opaqueness
		SDL_SetRenderDrawColor(Game::renderer, 243, 51, 21, 255);
		SDL_RenderFillRect(Game::renderer, &fillRect17);


		//overlay for health Bar
		dest.x = 705 * state2resizeImageXVar1;
		dest.y = 400 * state2resizeImageYVar1;
		dest.w = 90 * state2resizeImageXVar1;
		dest.h = 22 * state2resizeImageYVar1;

		TextureManager::Draw(healthBar, src, dest, NULL, NULL, SDL_FLIP_NONE);


		/////////////// DRAWING NUMBERS FOR HEALTH //////////////
		TTF_Font* Arial = TTF_OpenFont("assets/arial.ttf", 15);
		SDL_Color Color = { 255,255,255 };

		stringstream sstrHealth;
		sstrHealth << (int)playerHealth;

		stringstream sstrHealthMax;
		sstrHealthMax << (int)playerMaxHealth;

		string str1Health = sstrHealth.str();
		string str1HealthMax = sstrHealthMax.str();
		string healthTot = str1Health + " / " + str1HealthMax;

		SDL_Surface* surfaceMessageFPS = TTF_RenderText_Solid(Arial, healthTot.c_str(), Color);

		SDL_Texture* MessageFPS = SDL_CreateTextureFromSurface(Game::renderer, surfaceMessageFPS);

		SDL_Rect MessageFPS_rect; //create a rect
		MessageFPS_rect.x = 1372 * state2resizeImageXVar1;
		MessageFPS_rect.y = 700 * state2resizeImageYVar1;
		MessageFPS_rect.w = 70 * state2resizeImageXVar1;
		MessageFPS_rect.h = 25 * state2resizeImageYVar1;

		SDL_RenderCopy(Game::renderer, MessageFPS, NULL, &MessageFPS_rect);

		SDL_FreeSurface(surfaceMessageFPS);
		SDL_DestroyTexture(MessageFPS);
		TTF_CloseFont(Arial);

}

void state2::drawingServerHealthBar() {
	for (int i = 0; i < 50; i++) {
		if (serverPlayers[i] != "") {

			if (serverCurrentHealth[i] < 0) {
				serverCurrentHealth[i] = 0;
			}

			//health bar background 
			SDL_Rect fillRect16 = { correctingMapPlacementX(serverXCoordinateHold[i]) * state2resizeImageXVar1,correctingMapPlacementY(serverYCoordinateHold[i] + 50) * state2resizeImageYVar1, 90 * state2resizeImageXVar1, 22 * state2resizeImageYVar1 };

			//red, green, blue, opaqueness
			SDL_SetRenderDrawColor(Game::renderer, 62, 62, 62, 255);
			SDL_RenderFillRect(Game::renderer, &fillRect16);



			SDL_Rect fillRect17 = { correctingMapPlacementX(serverXCoordinateHold[i]) * state2resizeImageXVar1,			correctingMapPlacementY(serverYCoordinateHold[i] + 50) * state2resizeImageYVar1, (90 * serverCurrentHealth[i]/ serverMaxHealth[i]) * state2resizeImageXVar1, 22 * state2resizeImageYVar1 };

			//red, green, blue, opaqueness
			SDL_SetRenderDrawColor(Game::renderer, 243, 51, 21, 255);
			SDL_RenderFillRect(Game::renderer, &fillRect17);

			//overlay for health Bar
			dest.x = correctingMapPlacementX(serverXCoordinateHold[i]) * state2resizeImageXVar1;
			dest.y = correctingMapPlacementY(serverYCoordinateHold[i] + 50) * state2resizeImageYVar1;
			dest.w = 90 * state2resizeImageXVar1;
			dest.h = 22 * state2resizeImageYVar1;

			TextureManager::Draw(healthBar, src, dest, NULL, NULL, SDL_FLIP_NONE);


		}
	}


}