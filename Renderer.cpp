#include "Renderer.h"
#include "SDL\SDL_render.h"
#include "SDL\SDL_image.h"
#include "Color.h"
#include <cassert>

Renderer::Renderer(void) {
}


Renderer::~Renderer(void) {
}

void Renderer::Init(SDL_Window* aWindow, SDL_Renderer* aRenderer, SpriteFactory* aSpriteFactory) {
	myWindow = aWindow;
	myRenderer = aRenderer;
	mySpriteFactory = aSpriteFactory;
}
 
void Renderer::Render() { 
	SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
	SDL_RenderClear(myRenderer); 
	while(myRenderStacks.Size() > 0) {
		auto message = myRenderStacks.Pop();
		SDL_Rect srcRect = {0,0,static_cast<int>(message.size.x),static_cast<int>(message.size.y)};
		SDL_Rect dstRect = {static_cast<int>(message.pos.x), static_cast<int>(message.pos.y), static_cast<int>(message.size.x), static_cast<int>(message.size.y)};

		const SpriteRenderingData data = mySpriteFactory->Get(message.textureIndex); 
		SDL_Point hotspot = {message.hotspot.x, message.hotspot.y}; 
		SDL_SetTextureColorMod(data.myTexture, message.color.r, message.color.g, message.color.b);
		SDL_SetTextureAlphaMod(data.myTexture, message.color.a);
		SDL_SetTextureBlendMode(data.myTexture, message.blendMode);
		SDL_RenderCopyEx(myRenderer, data.myTexture, &srcRect, &dstRect, message.angle, &hotspot, message.flip);
	}
	SDL_RenderPresent(myRenderer);
}

void Renderer::RenderSprite(const RenderMessage aRenderMessage) {
	myRenderStacks.Push(aRenderMessage);
}

void Renderer::EndFrame() {
	myRenderStacks.Switch();
}