#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "Sprite.h"
#include <vector>


enum class AnimationPlayState 
{
	PLAY_ONCE,
	LOOP
};

class Animation
{
public:
	Animation(void);
	~Animation(void);

	void Load(const std::string& aTexture, const Vector2i aFrameSize, const float aTimePerFrame, const AnimationPlayState aPlayState = AnimationPlayState::LOOP);
	void Update(const float aDelta);
	void Render();

	RenderMessage& Data(); 

private:

	void PlayOnceUpdate(const float aDelta);
	void LoopUpdate(const float aDelta);
	Sprite mySprite;
	float myTimePerFrame; // FIX LATER: Specific times per frame? XML perhaps. Maybe. Maybemaybemaybenotnowfuckyou.
	float myCurrentFrameTime;

	std::vector<Vector2i> myFrames;
	unsigned myFrame;
	AnimationPlayState myPlayState;
};



#endif