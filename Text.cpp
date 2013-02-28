#include "Text.h"
#include "Engine.h"

Text::Text(void) {
}


Text::~Text(void) {
}


void Text::Load(const std::string& aText, const std::string& anID) {
	myString = aText;
	myID = anID;

	myRenderMessage = Engine::GetInstance()->LoadText(aText, anID);
}

RenderMessage& Text::Data() {
	return myRenderMessage;
}

void Text::Render() {
	Engine::GetInstance()->RenderSprite(myRenderMessage);
}