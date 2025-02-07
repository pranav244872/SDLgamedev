#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/KeyBoardControlledComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Events/KeyPressEvent.h"

typedef std::unordered_map<std::type_index, std::vector<std::unique_ptr<Event>>>
    EventMap;

class MovementSystem: public System
{
public:
	MovementSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
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

	// Update method where we handle both cases: with and 
	// without KeyBoardControlledComponent
	void Update(double deltaTime, std::shared_ptr<EventMap> eventMap)
	{
		// Loop through all entities the system is interested in
		for (auto entity : GetSystemEntities())
		{
			// Always retrieve common components
			auto &rigidbody = entity->GetComponent<RigidBodyComponent>();
			auto &transform = entity->GetComponent<TransformComponent>();

			// Check if the entity has a KeyBoardControlledComponent
			if (entity->HasComponent<KeyBoardControlledComponent>())
			{
				// Retrieve components related to keyboard control and sprite
				auto &keyboardcontrol = entity->GetComponent
					<KeyBoardControlledComponent>();
				auto &sprite = entity->GetComponent<SpriteComponent>();

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
		}
	}
};

#endif
