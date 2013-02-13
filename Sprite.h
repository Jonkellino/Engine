#ifndef _SPRITE_H_
#define _SPRITE_H_


#include "RenderMessage.h"
#include <string>

class Sprite
{
public:
	Sprite(void);
	~Sprite(void);

	void Load(const std::string& aSprite);
	void Render();

	RenderMessage& Data();

private:

	RenderMessage myRenderMessage;

};

#endif