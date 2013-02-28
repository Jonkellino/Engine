#include "Animation.h"
#include <cassert>


Animation::Animation(void){
	myFrame = 0U;
	myTimePerFrame = 0.f;
	myCurrentFrameTime = 0.f;
}


Animation::~Animation(void){
}

void Animation::Load(const std::string& aTexture, const Vector2i aFrameSize, const float aTimePerFrame, const AnimationPlayState aPlayState) {
	mySprite.Load(aTexture);
	RenderMessage& spriteData = mySprite.Data();
	myPlayState = aPlayState;
	myTimePerFrame = aTimePerFrame;

	Vector2i numberOfFrames = spriteData.size / aFrameSize;
	myFrames.resize(numberOfFrames.x*numberOfFrames.y);
	

	spriteData.size = aFrameSize;
	for(int y = 0; y < numberOfFrames.y; ++y) {
		for(int x = 0; x < numberOfFrames.x; ++x) {
			myFrames[ x + y * numberOfFrames.x ] = Vector2i(x,y) * aFrameSize;
		}
	}
}

void Animation::Update(const float aDelta) {
	switch(myPlayState) {
	case AnimationPlayState::LOOP:
		LoopUpdate(aDelta);
		break;
	case AnimationPlayState::PLAY_ONCE:
		PlayOnceUpdate(aDelta);
		break;
	default:
		assert(0 && "Faulty state");
		break;
	}
}

void Animation::Render() {
	mySprite.Data().topLeft = myFrames[myFrame];
	mySprite.Render();
}

RenderMessage& Animation::Data() {
	return mySprite.Data();
}

void Animation::PlayOnceUpdate(const float aDelta) {
	if(myFrame < myFrames.size()) {
		myCurrentFrameTime += aDelta;
		if(myCurrentFrameTime > myTimePerFrame) {
			myCurrentFrameTime -= myTimePerFrame;
			++myFrame;
		}
	}
	
	if(myFrame >= myFrames.size()) {
		myFrame = myFrames.size()-1;
	}

}

void Animation::LoopUpdate(const float aDelta) {
	myCurrentFrameTime += aDelta;
	if(myCurrentFrameTime > myTimePerFrame) {
		myCurrentFrameTime -= myTimePerFrame;
		++myFrame;
		if(myFrame >= myFrames.size()) {
			myFrame = 0;
		}
	}
}