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

const bool renderMessageSortCompare(const RenderMessage& first, const RenderMessage& second) 
{
	return first.depth < second.depth;
}
 
void Renderer::Render() { 
	myActiveRender = true;
	SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255);
	SDL_RenderClear(myRenderer); 

	std::sort(myRenderStacks.begin(), myRenderStacks.end(), &renderMessageSortCompare);
	while(myRenderStacks.Size() > 0) {
		auto message = myRenderStacks.Pop();
		SDL_Rect srcRect = {message.topLeft.x,message.topLeft.y, 
							message.size.x, message.size.y};
		Vector2i fullScale(static_cast<int>(static_cast<float>(message.size.x)*message.scale.x), static_cast<int>(static_cast<float>(message.size.y)*message.scale.y));
		SDL_Point hotspot = {static_cast<int>(message.hotspot.x*fullScale.x),
							static_cast<int>(message.hotspot.y*fullScale.y)};
		Vector2i destTopLeft(message.pos.x - hotspot.x, message.pos.y - hotspot.y);
		SDL_Rect dstRect = {destTopLeft.x, destTopLeft.y, fullScale.x, fullScale.y}; 

		const SpriteRenderingData data = mySpriteFactory->Get(message.textureIndex); 
		
		SDL_SetTextureColorMod(data.myTexture, message.color.r, message.color.g, message.color.b);
		SDL_SetTextureAlphaMod(data.myTexture, message.color.a);
		SDL_SetTextureBlendMode(data.myTexture, message.blendMode);
		SDL_RenderCopyEx(myRenderer, data.myTexture, &srcRect, &dstRect, message.angle, &hotspot, message.flip);
	}
	myActiveRender = false;
}

void Renderer::RenderSprite(const RenderMessage aRenderMessage) {
	myRenderStacks.Push(aRenderMessage);
}

void Renderer::EndFrame() { 
	while(myActiveRender){
		SDL_Delay(1);
	}
	myRenderStacks.Switch();
}