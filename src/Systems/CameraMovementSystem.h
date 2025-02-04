#ifndef CAMERAMOVEMENTSYSTEM_H
#define CAMERAMOVEMENTSYSTEM_H

#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"

class CameraMovementSystem: public System
{
	public:	
		CameraMovementSystem()
		{
			RequireComponent<CameraFollowComponent>();
			RequireComponent<TransformComponent>();
		}
		
		void Update
		(
			SDL_Rect& camera, 
			int mapWidth, int mapHeight, 
			int windowWidth, int windowHeight
		)
		{
			for (auto entity: GetSystemEntities())
			{
				auto transform = entity->GetComponent<TransformComponent>();
				if (transform.position.x + (camera.w / 2) < mapWidth)
				{
					camera.x = transform.position.x - (windowWidth / 2);
				}
				if (transform.position.y + (camera.h / 2) < mapHeight)
				{
					camera.y = transform.position.y - (windowHeight / 2);
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
