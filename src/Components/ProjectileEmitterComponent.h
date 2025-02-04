#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

struct ProjectileEmitterComponent
{
	glm::vec2 projectileVelocity;
	int repeatFrequency; // in ms
	int projectileDuration;
	int hitPercentDamage;
	bool isFriendly;
	int lastEmissionTime;

	ProjectileEmitterComponent
	(
		glm::vec2 projectileVelocity = glm::vec2(0),
		int repeatFrequency = 1000,
		int projectileDuration = 10000,
		int hitPercentDamage = 10,
		bool isFriendly = false
	)
	:
	projectileVelocity(projectileVelocity),
	repeatFrequency(repeatFrequency),
	projectileDuration(projectileDuration),
	hitPercentDamage(hitPercentDamage),
	isFriendly(isFriendly)
	{
		lastEmissionTime = SDL_GetTicks();
	}
};

#endif
