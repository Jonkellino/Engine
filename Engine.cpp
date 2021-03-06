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
	while(myMessageStack.Size() > 0) {
		auto message = myMessageStack.Pop();
		if(message.myType == EngineMessageType::LINE_ARRAY_RENDER) {
			SDL_SetRenderDrawColor(mySDLRenderer, message.lineArrayRender.myColor.r, message.lineArrayRender.myColor.g, message.lineArrayRender.myColor.b, message.lineArrayRender.myColor.a);
			SDL_RenderDrawLines(mySDLRenderer, message.lineArrayRender.myVertices, message.lineArrayRender.verticeCount);
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

const Vector2i Engine::GetWindowSize() const {
	return myWindowSize;
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
	SDL_Color col;
	memset(&col, 255, sizeof(col));

	SDL_Surface* temp = TTF_RenderText_Blended(myFont, aText.c_str(), col);
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

	myFont = TTF_OpenFont("data/fonts/consolas.ttf", 20);
	myWindow = SDL_CreateWindow("I am a hat, AMA", 0,0,1366,768, SDL_WINDOW_BORDERLESS);
	
	mySDLRenderer = SDL_CreateRenderer(myWindow, -1, ::SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(mySDLRenderer, 1366, 768);

	myRenderer.Init(myWindow, mySDLRenderer, &mySpriteFactory);
	mySpriteFactory.Init(mySDLRenderer);
	SDL_RenderGetLogicalSize(mySDLRenderer, &myWindowSize.x, &myWindowSize.y);
	myLoadMutex = false;
}