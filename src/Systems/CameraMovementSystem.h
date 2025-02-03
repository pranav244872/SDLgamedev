#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../Game/Game.h"

class CameraMovementSystem: public System
{
	public:	
		CameraMovementSystem()
		{
			RequireComponent<CameraFollowComponent>();
			RequireComponent<TransformComponent>();
		}
		
		void Update(SDL_Rect& camera)
		{
			for (auto entity: GetSystemEntities())
			{
				auto transform = entity->GetComponent<TransformComponent>();
				if (transform.position.x < Game::mapWidth)
				{
					camera.x = transform.position.x;
				}
				if (transform.position.y < Game::mapHeight)
				{
					camera.y = transform.position.y;
				}
				
				// Keep the camera rectangle view inside the screen limits
				camera.x = camera.x < 0 ? 0 : camera.x;
				camera.y = camera.y < 0 ? 0 : camera.y;
				camera.x = camera.x > camera.w ? camera.w : camera.x;
				camera.y = camera.y > camera.h ? camera.h : camera.y;
			}
		}
	
};

#endif
