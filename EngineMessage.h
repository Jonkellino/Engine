#ifndef _ENGINE_MESSAGE_H_
#define _ENGINE_MESSAGE_H_

#include "Color.h"
#include "SDL\SDL.h"

enum class EngineMessageType
{
	WINDOW_SIZE_CHANGE,
	LINE_RENDER,
	LINE_ARRAY_RENDER
};

struct EngineMessage
{
	EngineMessageType myType;

	union 
	{ 
		struct LineArrayRender
		{
			int verticeCount;
			SDL_Point* myVertices;
			Color myColor;
		} lineArrayRender;
	};
};


#endif