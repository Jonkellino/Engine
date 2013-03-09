#include "Keyboard.h"


Keyboard* Keyboard::ourInstance = nullptr;


Keyboard::Keyboard(void)
{
	uint8_t* currentState = SDL_GetKeyboardState(&myNumberOfKeys);
	myState = new uint8_t[myNumberOfKeys*2];
	myPreviousState = myState;
	myCurrentState = &myState[myNumberOfKeys];

	SDL_memcpy(currentState, myCurrentState, sizeof(uint8_t)*myNumberOfKeys);
	SDL_memcpy(currentState, myPreviousState, sizeof(uint8_t)*myNumberOfKeys);
}

Keyboard::~Keyboard(void)
{
	delete myState;
}

void Keyboard::Create()
{
	ourInstance = new Keyboard();
}

void Keyboard::Destroy()
{
	delete ourInstance;
}

Keyboard* Keyboard::GetInstance()
{
	return ourInstance;
}

void Keyboard::Update()
{
	SDL_memcpy(myPreviousState, myCurrentState, sizeof(uint8_t)*myNumberOfKeys);
	uint8_t* currentState = SDL_GetKeyboardState(NULL);	
	SDL_memcpy(myCurrentState, currentState, sizeof(uint8_t)*myNumberOfKeys);
}

#pragma warning(push)

const bool Keyboard::KeyReleased(const SDL_Scancode aKey) const
{
	return myCurrentState[aKey] == false && myPreviousState[aKey] != false;
}

const bool Keyboard::KeyPressed(const SDL_Scancode aKey) const
{
	return myCurrentState[aKey] == true && myPreviousState[aKey] == false;
}

const bool Keyboard::KeyDown(const SDL_Scancode aKey) const
{
	return myCurrentState[aKey] == true;
}

const bool Keyboard::KeyUp(const SDL_Scancode aKey) const
{
	return myCurrentState[aKey] == false;
}

#pragma warning( pop )