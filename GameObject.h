#pragma once
#include "Game.h"
class GameObject {

public:

	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void Update();
	void Render();

	//resized x var
	void setresizeImageXVar(int x);
	//resized y var
	void setresizeImageYVar(int x);

private:

	int xpos;
	int ypos;

	int height;
	int width;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;

};