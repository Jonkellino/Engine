#ifndef _RENDERMESSAGE_H_
#define _RENDERMESSAGE_H_

#include "Vector.h"
#include "SDL\sdl_render.h"
#include "Color.h"

struct RenderMessage
{
	Vector2i pos;
	Vector2i size;
	Vector2i hotspot;
	Color color;
	unsigned textureIndex;
	SDL_RendererFlip flip;
	SDL_BlendMode blendMode;
	double angle;
};

#endif