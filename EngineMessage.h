#ifndef _ENGINE_MESSAGE_H_
#define _ENGINE_MESSAGE_H_

enum class EngineMessageType
{
	WINDOW_SIZE_CHANGE
};

struct EngineMessage
{
	EngineMessageType myType;

	union 
	{
		struct WindowSizeChangeData 
		{
			int myWindowSize[2];
		} windowSizeChange;
	};
};


#endif