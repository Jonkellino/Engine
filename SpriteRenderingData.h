#ifndef _SPRITE_RENDERING_DATA_H_
#define _SPRITE_RENDERING_DATA_H_

#include "SDL\SDL.h"
#include "RenderMessage.h"

struct SpriteRenderingData
{
	SDL_Texture* myTexture;
	RenderMessage myBaseRenderMessage;
};


#endif