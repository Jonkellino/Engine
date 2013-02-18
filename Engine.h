#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <array>
#include <vector>
#include "Renderer.h"
#include "SDL/SDL.h"
#include "Sprite.h"
#include "SpriteFactory.h"
#include "EngineMessage.h"
#include "DoubleThreadingStack.h"


class Engine
{
	friend class Sprite;
	friend class Line;
public:
	static void				Create();
	static void				Destroy();
	static Engine*			GetInstance();
	void					Render();
	void					EndFrame();
	void					NotifyMessage(EngineMessage aMessage);

private:
							Engine();
							~Engine();

	void					RenderSprite(const RenderMessage aMessage);
	RenderMessage			LoadSprite(const std::string& aSprite);
	void					Init();

private:
	static Engine*			ourInstance; 
	SDL_Window*				myWindow;
	SDL_Renderer*			mySDLRenderer;
	Renderer				myRenderer;
	SpriteFactory			mySpriteFactory;

	DoubleThreadingStack
		<EngineMessage>		myMessageStack;
};


#endif