#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/KeyBoardControlledComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Events/KeyPressEvent.h"
#include "../Events/CollisionEvent.h"

typedef std::unordered_map<std::type_index, std::vector<std::unique_ptr<Event>>>
    EventMap;

class MovementSystem: public System
{
	private: 

		// Handles collision response for enemy and obstacle collisions
		void ifEnemyCollidingWithObstacle(std::shared_ptr<EventMap> eventMap)
		{
			// Check for CollisionEvent
			auto it = eventMap->find(typeid(CollisionEvent));
			if (it != eventMap->end())
			{
				// Process each collision event
				for (const auto& event : it->second)
				{
					// Cast the raw pointer from the unique_ptr to CollisionEvent*
					CollisionEvent* collisionEvent = 
						static_cast<CollisionEvent*>(event.get());

					// Check if collision involves "enemies" and "obstacles"
					if 
					(
						(
							collisionEvent->a->BelongsToGroup("enemies") && 
							collisionEvent->b->BelongsToGroup("obstacles")
						) 
						||
						(
							collisionEvent->a->BelongsToGroup("obstacles") && 
							collisionEvent->b->BelongsToGroup("enemies")
						)
					)
					{
						// Determine which entity was hit and reverse its velocity
						auto& entity = 
							(collisionEvent->a->BelongsToGroup("enemies")) ?
							collisionEvent->a : collisionEvent->b;
						auto& rigidbody = 
							entity->GetComponent<RigidBodyComponent>();
						auto& sprite = 
							entity->GetComponent<SpriteComponent>();
						rigidbody.velocity = -(rigidbody.velocity);
						if (rigidbody.velocity.x != 0)
						{
							sprite.flip = 
								(
									sprite.flip == SDL_FLIP_NONE ? 
									SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
								);
						} 
						else
						{
							sprite.flip = 
								(
									sprite.flip == SDL_FLIP_NONE ? 
									SDL_FLIP_VERTICAL : SDL_FLIP_NONE
								);
						}
					}
				}
			}
		}

		// Handle key press for entities with KeyBoardControlledComponent
		void onKeyPressed
		(
			const std::unique_ptr<Event> &event, std::shared_ptr<Entity> entity,
			TransformComponent &transform, RigidBodyComponent &rigidbody, 
			SpriteComponent &sprite, KeyBoardControlledComponent &keyboardcontrol
		)
		{
			KeyPressEvent *keyPressEvent =
				static_cast<KeyPressEvent *>(event.get());

			switch (keyPressEvent->symbol)
			{
				case SDLK_UP:
					rigidbody.velocity = keyboardcontrol.upVelocity;
					sprite.srcRect.y = sprite.height * 0;
					break;
				case SDLK_RIGHT:
					rigidbody.velocity = keyboardcontrol.rightVelocity;
					sprite.srcRect.y = sprite.height * 1;
					break;
				case SDLK_DOWN:
					rigidbody.velocity = keyboardcontrol.downVelocity;
					sprite.srcRect.y = sprite.height * 2;
					break;
				case SDLK_LEFT:
					rigidbody.velocity = keyboardcontrol.leftVelocity;
					sprite.srcRect.y = sprite.height * 3;
					break;
			}
		}

	public:
		MovementSystem()
		{
			RequireComponent<TransformComponent>();
			RequireComponent<RigidBodyComponent>();
		}

		// Update method: handles movement and collision detection for each entity
		void Update
		(
			double deltaTime, std::shared_ptr<EventMap> eventMap,
			int mapWidth, int mapHeight
		)
		{
			// Handle collisions between enemies and obstacles
			ifEnemyCollidingWithObstacle(eventMap);

			// Loop through all entities the system is interested in
			for (auto entity : GetSystemEntities())
			{
				// retrieve common components for each entity
				auto& rigidbody = entity->GetComponent<RigidBodyComponent>();
				auto& transform = entity->GetComponent<TransformComponent>();
				auto& sprite = entity->GetComponent<SpriteComponent>();

				// Check if the entity has a KeyBoardControlledComponent
				if (entity->HasComponent<KeyBoardControlledComponent>())
				{
					// Retrieve components related to keyboard control and sprite
					auto &keyboardcontrol = entity->GetComponent
						<KeyBoardControlledComponent>();

					// Process key press events if any exist
					auto it = eventMap->find(typeid(KeyPressEvent));
					if (it != eventMap->end())
					{
						for (const auto &event : it->second)
						{
							onKeyPressed
							(
								event, entity, transform, 
								rigidbody, sprite, keyboardcontrol
							);
						}
					}
				}

				// Update position based on the velocity
				transform.position.x += rigidbody.velocity.x * deltaTime;
				transform.position.y += rigidbody.velocity.y * deltaTime;

				// Check if entity is outside map boundaries
				bool isEntityOutsideMap = 
				(
					transform.position.x < 0 ||
					transform.position.x > mapWidth ||
					transform.position.y < 0 ||
					transform.position.y > mapHeight
				);

				// Kill entities which go outside map except player
				if (isEntityOutsideMap && !entity->HasTag("player"))
				{
					entity->Kill();
				}
				
				// Handle player entity specific logic if its outside the map
				if (entity->HasTag("player"))
				{
					// If out of map in x direction
					if ( transform.position.x < 0 )
					{
						rigidbody.velocity.x = 0;
						transform.position.x = 0;
					}
					if 
					(
						transform.position.x + (transform.scale.x*sprite.width) 
						> mapWidth
					)
					{
						rigidbody.velocity.x = 0;
						transform.position.x = 
							mapWidth - (transform.scale.x*sprite.width);
					}
					// If out of map in y direction
					if ( transform.position.y < 0 )
					{
						rigidbody.velocity.y = 0;
						transform.position.y = 0;
					}
					if 
					(
						transform.position.y + (transform.scale.y*sprite.height) 
						> mapHeight
					)
					{
						rigidbody.velocity.y = 0;
						transform.position.y = 
							mapHeight - (transform.scale.y*sprite.height);
					}
				}
			}
		}
};

#endif
