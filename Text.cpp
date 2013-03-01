#include "Text.h"
#include "Engine.h"

Text::Text(void) {
	memset(&myRenderMessage, 0, sizeof(myRenderMessage));
}


Text::~Text(void) {
}


void Text::Load(const std::string& aText, const std::string& anID) {
	myString = aText;
	myID = anID;

	if(myRenderMessage.textureIndex != 0) { // Reload.
		RenderMessage newMessage = Engine::GetInstance()->LoadText(aText, anID);
		myRenderMessage.textureIndex = newMessage.textureIndex;
		myRenderMessage.size = newMessage.size;
	}
	else {
		myRenderMessage = Engine::GetInstance()->LoadText(aText, anID);	
	}
}

RenderMessage& Text::Data() {
	return myRenderMessage;
}

void Text::Render() {
	Engine::GetInstance()->RenderSprite(myRenderMessage);
}