#include "GameObject.h"
#include "TextureManager.h"

#include "Game.h"

GameObject::~GameObject()
{
}

//variables

//resizing x variable to scale of window
int resizeImageYVar = 1;

GameObject::GameObject(const char* texturesheet, int x, int y) {

	if (texturesheet != NULL) {
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

}

//settings xvar scale
void GameObject::setresizeImageXVar(int x) {
	//resizeImageXVar = x;
}

//settings yvar scale
void GameObject::setresizeImageYVar(int x) {
	resizeImageYVar = x;
}

void GameObject::Update() {

	xpos = 10;
	ypos = 10;

	srcRect.h = height;
	srcRect.w = width;
	srcRect.x = 0;
	srcRect.y = 0;

	//destRect.x = xpos * (((double)resizeImageXVar)/1500);
	destRect.y = ypos * (((double)resizeImageYVar)/1000);
	//destRect.w = srcRect.w * (((double)resizeImageXVar) / 1500);
	destRect.h = srcRect.h* (((double)resizeImageYVar) / 1000);
}

void GameObject::Render() {
	
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
	
}

