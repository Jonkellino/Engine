#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <vector>
#include <array>
#include <stdint.h>
#include "SDL\SDL.h"
#include "RenderMessage.h"
#include "SpriteFactory.h"
#include "DoubleThreadingStack.h"


class Renderer
{
public:
			Renderer(void);
			~Renderer(void);
	void	Init(SDL_Window* aWindow, SDL_Renderer* aRenderer, SpriteFactory* aSpriteFactory );
	void	Render();
	void	RenderSprite(const RenderMessage aMessage);
	void	EndFrame();

private:
	SDL_Window*				myWindow;
	SDL_Renderer*			myRenderer;

	DoubleThreadingStack<
		RenderMessage>		myRenderStacks;

	SpriteFactory*			mySpriteFactory;
	bool					myActiveRender;
};

#endif