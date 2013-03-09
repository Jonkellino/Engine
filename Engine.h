#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <array>
#include <vector>
#include "Renderer.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Sprite.h"
#include "SpriteFactory.h"
#include "EngineMessage.h"
#include "DoubleThreadingStack.h"
#include "Text.h"


class Engine
{
	friend class Sprite;
	friend class Text;
public:
	static void				Create();
	static void				Destroy();
	static Engine*			GetInstance();
	void					Render();
	void					EndFrame();
	void					NotifyMessage(EngineMessage aMessage);
	const Vector2i			GetWindowSize() const;

private:
							Engine();
							~Engine();

	void					RenderSprite(const RenderMessage aMessage);
	void					RenderText(const RenderMessage aMessage);
	RenderMessage			LoadSprite(const std::string& aSprite);
	RenderMessage			LoadText(const std::string& aText, const std::string& aTextureID);
	void					RenderSurfaceToTexture(SDL_Surface* aSurface, const unsigned aTexture);
	
	void					Init();

private:
	static Engine*			ourInstance; 
	SDL_Window*				myWindow;
	SDL_Renderer*			mySDLRenderer;
	TTF_Font*				myFont;
	Vector2i				myWindowSize;
	Renderer				myRenderer;
	SpriteFactory			mySpriteFactory;
	
	bool					myLoadMutex;
	DoubleThreadingStack
		<EngineMessage>		myMessageStack;


	std::vector
		<std::string>		myErrorMessages;
};


#endif