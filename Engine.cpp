#include "Engine.h"
#include <cassert>
#include <string>
#include "SDL\SDL_image.h"
#include "SDL\SDL_ttf.h"

Engine* Engine::ourInstance = nullptr;

void Engine::Create() {
	ourInstance = new Engine();
	ourInstance->Init(); 
}

void Engine::Destroy() {
	delete ourInstance;
}

Engine* Engine::GetInstance() {
	return ourInstance;
}

void Engine::Render() {
	while(myLoadMutex){
		SDL_Delay(1);
	}
	myLoadMutex = true;

	SDL_UpdateWindowSurface(myWindow); 
	myRenderer.Render();
	for(auto index = 0U; index < myMessageStack.Size(); ++index) {
		EngineMessage& message = myMessageStack[index];
		if(message.myType == EngineMessageType::LINE_RENDER) {
			SDL_SetRenderDrawColor(mySDLRenderer, message.lineRender.myColor.r, message.lineRender.myColor.g, message.lineRender.myColor.b, message.lineRender.myColor.a);
			SDL_RenderDrawLine(mySDLRenderer, message.lineRender.myVertices[0], message.lineRender.myVertices[1], message.lineRender.myVertices[2], message.lineRender.myVertices[3]);
		}
	}
	
	SDL_RenderPresent(mySDLRenderer);
	myLoadMutex = false;
}

void Engine::EndFrame() {
	myRenderer.EndFrame();
	myMessageStack.Switch();
}

void Engine::NotifyMessage(EngineMessage aMessage) {
	myMessageStack.Push(aMessage);
}

void Engine::RenderSprite(const RenderMessage aMessage) {
	myRenderer.RenderSprite(aMessage);
}

RenderMessage Engine::LoadSprite(const std::string& aSprite) {
	while(myLoadMutex){
		SDL_Delay(1);
	}
	myLoadMutex = true;
	RenderMessage output = mySpriteFactory.LoadSprite(aSprite);
	myLoadMutex = false;
	return output;
}

RenderMessage Engine::LoadText(const std::string& aText, const std::string& aTextureID) {
	while(myLoadMutex) {
		SDL_Delay(1);
	}
	myLoadMutex = true;
	SDL_Color WTF;
	memset(&WTF, 255, sizeof(WTF));
	
	SDL_Surface* temp = TTF_RenderText_Blended(myFont, aText.c_str(), WTF);
	RenderMessage output = mySpriteFactory.LoadSprite(aTextureID, temp); 
	myLoadMutex = false;
	return output;
}

Engine::Engine() {
}

Engine::~Engine() {
	IMG_Quit();
	SDL_Quit();
}

void Engine::Init() {
	myLoadMutex = true;
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::string output = "Couldn't initialize SDL, err: ";
		output += SDL_GetError();
		assert(0 && output.c_str());
	}
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	myFont = TTF_OpenFont("font.ttf", 20);
	myWindow = SDL_CreateWindow("I am a hat, AMA", 0,0,1680,1024, SDL_WINDOW_BORDERLESS);
	mySDLRenderer = SDL_CreateRenderer(myWindow, -1, ::SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	myRenderer.Init(myWindow, mySDLRenderer, &mySpriteFactory);
	mySpriteFactory.Init(mySDLRenderer);
	myLoadMutex = false;
}