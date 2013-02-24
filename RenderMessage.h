#ifndef _RENDERMESSAGE_H_
#define _RENDERMESSAGE_H_

#include "Vector.h"
#include "SDL\sdl_render.h"
#include "Color.h"

struct RenderMessage
{
	Vector2i			topLeft;
	Vector2i			pos;
	Vector2i			size;
	Vector2f			hotspot;
	Vector2f			scale;
	Color				color;
	unsigned			textureIndex;
	SDL_RendererFlip	flip;
	SDL_BlendMode		blendMode;
	double				angle;
};

#endif