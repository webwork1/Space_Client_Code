#pragma once
#include <iostream>
#include "Game.h"
#include <vector>

class state2 {

public:
	state2();
	~state2();

	//setting state
	void setState2(int x);

	//getting current state
	int getState2();

	//get player cords and rotation angle
	int getPlayerX();
	int getPlayerY();
	int getPlayerR();
	double getPlayerSpeedX();
	double getPlayerSpeedY();
	string getPlayerSpacebar();

	//when player leaves server
	void playerLeft(string s);

	//drawing state2 stuff
	void drawImagesState2();


	//getting other players' coordinates
	void getServerPlayersX(int x, string s);
	//getting other players' coordinates
	void getServerPlayersY(int x, string s);
	//getting other players' speed
	void getServerSpeedX(double x, string s);
	//getting other players' speed
	void getServerSpeedY(double x, string s);
	//getting other players rotation angle
	void getServerRotation(int x,string s);
	//getting space bar pressed by other players
	void getServerSpacekey(string x, string s);
	//getting other players' health
	void getServerHealth(int x, string s);
	//getting hits on other players
	void getServerHits(string s, string a);
	//adding username
	void addUser(string s);

	//resized x var
	void statetwoResizeX2(int x);
	void statetwoResizeY2(int x);

	//mouse stuff
	void getLeftButton2(bool x);
	void getMouseX2(int x);
	void getMouseY2(int x);

	//keyboard stuff
	void getUpKeyPressed2(bool b);
	void getLeftKeyPressed2(bool b);
	void getRightKeyPressed2(bool b);
	void getDownKeyPressed2(bool b);
	void getSpaceKeyPressed2(bool b);
	void getFKeyPressed2(bool b);

	void fKeyActions();

	//dealing with shooting function
	void dealWithShooting(string x);

	//getting username of player
	void getUsername(string b);

	//loading chunks individually
	void loadChunks();

	//getting chunks from server
	void getChunkFromServer(string s);

	//drawing shots
	void drawShots();

	void updateTimeStuff();


	void drawingHealthBar();
	void drawingServerHealthBar();
private:
	//player x and y coordinate
	double playerXCoordinate = 0;
	double playerYCoordinate = 0;

	void declaringBackgroundStars();

	Game *game = new Game();
	SDL_Rect src, dest;

	//used for generating stars
	bool tempBoolean = true;
	//array for x and y variables
	double xInitial[50];
	double yInitial[50];

	//variables for exhaust
	int exhaustTime[150];
	int exhaustX[150];
	int exhaustY[150];

	int exhaustOn[150];
	double exhaustXHold[150];
	double exhaustYHold[150];

	//to stop lag from exhaust
	int exhaustTotalTime = 0;

	/////////////exhaust variables for server players///////////////
		//variables for exhaust
	int exhaustTimeServer[50][150];
	int exhaustXServer[50][150];
	int exhaustYServer[50][150];

	int exhaustOnServer[50][150];
	double exhaustXHoldServer[50][150];
	double exhaustYHoldServer[50][150];

	//to stop lag from exhaust
	int exhaustTotalTimeServer[50];


	////end exhaust variables for server..... /////////////

	//these two functions are for getting proper placement of planets
	int correctingMapPlacementX(int x);
	int correctingMapPlacementY(int x);

	//drawing mini map border
	void drawingMiniMapBorder();
	void drawingMiniMapBackdrop();

	/// minimap ////
	//minimap size
	int minimapSize = 50;
	double miniMapPlanetY[50][12];
	double miniMapPlanetX[50][12];

	// int for making collision detection work
	int collisionCounter = 0;

	//images

	SDL_Texture* background;
	SDL_Texture* playerShip;
	SDL_Texture* pointer;
	SDL_Texture* pointerFoe;
	SDL_Texture* speedBar;
	SDL_Texture* healthBar;
	SDL_Texture* star_Background;
	SDL_Texture* experience_bar;
	SDL_Texture* experience_bar_bg;

	//bullets
	SDL_Texture* bullet1;

	//planet images
	SDL_Texture* planet0;
	SDL_Texture* planet1;
	SDL_Texture* planet2;
	SDL_Texture* planet3;
	SDL_Texture* planet4;
	SDL_Texture* planet5;
	SDL_Texture* planet6;
	SDL_Texture* planet7;
	SDL_Texture* planet8;
	SDL_Texture* planet9;
	SDL_Texture* planet10;
	SDL_Texture* planet11;
	SDL_Texture* planet12;
	SDL_Texture* planet13;
	SDL_Texture* planet14;
	SDL_Texture* planet15;
	SDL_Texture* planet16;
	SDL_Texture* planet17;
	SDL_Texture* planet18;
	SDL_Texture* planet19;
	SDL_Texture* planet20;
	SDL_Texture* planet21;
	SDL_Texture* planet22;
	SDL_Texture* planet23;
	SDL_Texture* planet24;
	SDL_Texture* planet25;
	SDL_Texture* planet26;
	SDL_Texture* planet27;
	SDL_Texture* planet28;
	SDL_Texture* planet29;

};