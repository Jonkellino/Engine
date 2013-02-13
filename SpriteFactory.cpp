#include "SpriteFactory.h"
#include "SDL\SDL_image.h"


SpriteFactory::SpriteFactory(void) {
	myRenderData.reserve(10);
}


SpriteFactory::~SpriteFactory(void) {
}

void SpriteFactory::Init(SDL_Renderer* aRenderer) {
	myRenderer = aRenderer;
}

const SpriteRenderingData SpriteFactory::Get(const int anIndex) const {
	return myRenderData[anIndex];
}

RenderMessage SpriteFactory::LoadSprite(std::string aSprite) {
	for( auto character : aSprite ) {
		character = tolower(character);
	}
	auto indexIterator = mySpriteIndexMap.find(aSprite);
	if(indexIterator == mySpriteIndexMap.end()) {
		indexIterator = NewSprite(aSprite);
	}
	return myRenderData[(*indexIterator).second].myBaseRenderMessage;
}

std::map<std::string, unsigned>::iterator SpriteFactory::NewSprite(const std::string& aSprite) {
	myRenderData.emplace_back();
	const unsigned targetIndex = myRenderData.size()-1;
	mySpriteIndexMap.insert(std::pair<std::string, unsigned>(aSprite, targetIndex));
	std::map<std::string, unsigned>::iterator iter = mySpriteIndexMap.find(aSprite);

	SpriteRenderingData& newData = myRenderData[targetIndex];
	newData.myTexture = IMG_LoadTexture(myRenderer, aSprite.c_str());
	memset(&newData.myBaseRenderMessage, 0, sizeof(RenderMessage));
	SDL_QueryTexture(newData.myTexture, NULL, NULL, &newData.myBaseRenderMessage.size.x, &newData.myBaseRenderMessage.size.y);
	newData.myBaseRenderMessage.textureIndex = targetIndex;
	newData.myBaseRenderMessage.hotspot = newData.myBaseRenderMessage.size / 2;
	newData.myBaseRenderMessage.blendMode = SDL_BlendMode::SDL_BLENDMODE_ADD;
	return iter;
}