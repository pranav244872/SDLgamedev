#ifndef COLLISIONDEBUG_H
#define COLLISIONDEBUG_H

#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../Events/CollisionEvent.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"

typedef std::unordered_map
<std::type_index,std::vector<std::unique_ptr<Event>>> EventMap;

class CollisionDebug: public System
{
	private: 
		std::shared_ptr<EventMap> eventMap;
		bool isEntityInCollisionEvents(std::shared_ptr<Entity> entity)
		{
			auto it = eventMap->find(typeid(CollisionEvent));
			if (it != eventMap->end())
			{
				for (const auto& event : it->second)
				{
					// Cast the raw pointer from the unique_ptr to CollisionEvent*
					CollisionEvent* collisionEvent = static_cast<CollisionEvent*>(event.get());
					// Check if the entity is involved in the event
					if (collisionEvent->a == entity || collisionEvent->b == entity)
					{
						return true; // Entity is involved in a collision event
					}
				}
			}

			return false; // Entity is not involved in any collision event
		}

	public:
		CollisionDebug(std::shared_ptr<EventMap> eventMap)
		{
			this->eventMap = eventMap;
			RequireComponent<BoxColliderComponent>();
			RequireComponent<TransformComponent>();
		}

		void Update(SDL_Renderer* renderer, bool debugMode, SDL_Rect& camera)
		{
			if (debugMode)
			{
				auto entities = GetSystemEntities();
				for (unsigned long int i = 0; i < entities.size(); i++)
				{
					auto a = entities[i];
					auto aTransform = a->GetComponent<TransformComponent>();
					auto aCollider = a->GetComponent<BoxColliderComponent>();

					// Precompute width and height with scale for entity A
					double aWidth = aCollider.width * aTransform.scale.x;
					double aHeight = aCollider.height * aTransform.scale.y;
					
                    // Get transformed rectangle for entity A
                    SDL_Rect rectA = 
                    { 
                        static_cast<int>(aTransform.position.x - camera.x),
                        static_cast<int>(aTransform.position.y - camera.y),
                        static_cast<int>(aWidth),
                        static_cast<int>(aHeight)
                    };
					
					if (isEntityInCollisionEvents(a))
					{
						SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for collision
					}
					else
					{
						SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for no collision
					}
					SDL_RenderDrawRect(renderer, &rectA);
				}
			}
		}
};

#endif
