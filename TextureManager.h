#pragma once

#include "Game.h"
#include "SDL_ttf.h"
#include <string>

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* filename);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, double angle, SDL_Point* center, SDL_RendererFlip flip);

private:
	

};
