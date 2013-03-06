#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "SDL\SDL_keyboard.h"



class Keyboard
{
public:

	static void Create();
	static void Destroy();
	static Keyboard* GetInstance();

	void Update();

	const bool KeyReleased(const SDL_Scancode aKey) const;
	const bool KeyPressed(const SDL_Scancode aKey) const;
	const bool KeyDown(const SDL_Scancode aKey) const;
	const bool KeyUp(const SDL_Scancode aKey) const;
	

private:
	Keyboard(void);
	~Keyboard(void);

	static Keyboard* ourInstance;

	uint8_t* myState;
	uint8_t* myPreviousState;
	uint8_t* myCurrentState;

	int myNumberOfKeys;
	

};

#define KeyboardInput Keyboard::GetInstance()

#endif