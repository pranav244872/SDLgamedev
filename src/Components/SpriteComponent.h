#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct SpriteComponent
{
	std::string assetId;
	int width;
	int height;
	int zIndex;
	SDL_RendererFlip flip;
	SDL_Rect srcRect;
	bool isFixed;

	SpriteComponent
	(
		const std::string& assetId = "", 
		int width = 0, int height = 0,
		int srcRectX = 0, int srcRectY = 0,
		int zIndex = 0, bool isFixed = false
	)
	{
		this->assetId = assetId;
		this->width = width;
		this->height= height;
		this->srcRect = { srcRectX, srcRectY, width, height };
		this->zIndex = zIndex;
		this->flip = SDL_FLIP_NONE;
		this->isFixed = isFixed;
	}
};

#endif
