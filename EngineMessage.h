#ifndef _ENGINE_MESSAGE_H_
#define _ENGINE_MESSAGE_H_

#include "Color.h"

enum class EngineMessageType
{
	WINDOW_SIZE_CHANGE,
	LINE_RENDER
};

struct EngineMessage
{
	EngineMessageType myType;

	union 
	{
		struct WindowSizeChange 
		{
			int myWindowSize[2];
		} windowSizeChange;

		struct LineRender
		{
			int myVertices[4];
			Color myColor;
		} lineRender;
	};
};


#endif