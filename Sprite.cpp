#include "Sprite.h"
#include "Engine.h"


Sprite::Sprite(void) {
	memset(&myRenderMessage, 0, sizeof(RenderMessage)); 
}


Sprite::~Sprite(void) {
}

void Sprite::Load(const std::string& aSprite) {
	myRenderMessage = Engine::GetInstance()->LoadSprite(aSprite);
}

void Sprite::Render() {
	Engine::GetInstance()->RenderSprite(myRenderMessage);
}

RenderMessage& Sprite::Data() {
	return myRenderMessage;
}