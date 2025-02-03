#ifndef KEYPRESSEVENT_H
#define KEYPRESSEVENT_H

#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "./Event.h"

struct KeyPressEvent: public Event
{
	public:
		SDL_Keycode symbol;
		KeyPressEvent(SDL_Keycode symbol): symbol(symbol) {}
};

#endif
