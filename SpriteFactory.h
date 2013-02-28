#ifndef _SPRITE_FACTORY_H_
#define _SPRITE_FACTORY_H_

#include <string>
#include <vector>
#include <map>
#include "SpriteRenderingData.h"
#include "SDL\SDL.h"



class SpriteFactory
{
public:
										SpriteFactory(void);
										~SpriteFactory(void);
	void								Init(SDL_Renderer* aRenderer);
	const SpriteRenderingData			Get(const int anIndex) const;
	RenderMessage						LoadSprite(std::string aSprite, SDL_Surface* aSurface = NULL);
private:

	std::map<std::string, unsigned>
		::iterator						NewSprite(const std::string& aSprite, SDL_Surface* aSurface);

private:

	SDL_Renderer*						myRenderer;
	std::map<std::string, unsigned>		mySpriteIndexMap;
	std::vector<SpriteRenderingData>	myRenderData;

};

#endif