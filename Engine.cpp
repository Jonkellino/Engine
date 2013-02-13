#include "Engine.h"
#include <cassert>
#include <string>
#include "SDL\SDL_image.h"

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
	SDL_UpdateWindowSurface(myWindow); 
	myRenderer.Render();
}

void Engine::EndFrame() {
	myRenderer.EndFrame();
	myMessageQueue.Switch();
}

void Engine::NotifyMessage(EngineMessage aMessage) {
	myMessageQueue.Push(aMessage);
}

void Engine::RenderSprite(const RenderMessage aMessage) {
	myRenderer.RenderSprite(aMessage);
}

RenderMessage Engine::LoadSprite(const std::string& aSprite) {
	return mySpriteFactory.LoadSprite(aSprite);
}

Engine::Engine() {
}

Engine::~Engine() {
	IMG_Quit();
	SDL_Quit();
}

void Engine::Init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::string output = "Couldn't initialize SDL, err: ";
		output += SDL_GetError();
		assert(0 && output.c_str());
	}
	IMG_Init(IMG_INIT_PNG);
	myWindow = SDL_CreateWindow("I am a hat, AMA", 256,100,1024,768, 0);
	mySDLRenderer = SDL_CreateRenderer(myWindow, -1, ::SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	myRenderer.Init(myWindow, mySDLRenderer, &mySpriteFactory);
	mySpriteFactory.Init(mySDLRenderer);
}