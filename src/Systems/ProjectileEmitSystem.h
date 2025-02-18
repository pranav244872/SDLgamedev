#ifndef PROJECTILEEMITYSYSTEM_H
#define PROJECTILEEMITYSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/KeyBoardControlledComponent.h"
#include "../Events/KeyPressEvent.h"

typedef std::unordered_map<std::type_index, std::vector<std::unique_ptr<Event>>>
EventMap;

class ProjectileEmitSystem : public System
{
	private:
		// Handle spacebar press for entities with KeyBoardControlledComponent
		void onSpacePressed
		(
		 std::unique_ptr<Registry>& registry,
		 const std::unique_ptr<Event>& event,
		 std::shared_ptr<Entity> entity,
		 const TransformComponent& transform,
		 const ProjectileEmitterComponent& projectileEmitter,
		 const SpriteComponent& sprite,
		 const RigidBodyComponent& rigidbody
		)
		{
			KeyPressEvent* keyPressEvent = 
				static_cast<KeyPressEvent*>(event.get());

			if (keyPressEvent->symbol == SDLK_SPACE)
			{
				glm::vec2 projectilePosition = transform.position;
				projectilePosition.x += (transform.scale.x * sprite.width / 2);
				projectilePosition.y += (transform.scale.y * sprite.height / 2);

				// Determine projectile velocity
				glm::vec2 projectileVelocity = projectileEmitter.projectileVelocity;

				// If the entity is moving, normalize its velocity and adjust the projectile speed accordingly
				if (glm::length(rigidbody.velocity) > 0.1f)  // Check if entity is moving
				{
					// Normalize the direction of movement and apply the desired speed
					glm::vec2 direction = glm::normalize(rigidbody.velocity);
					projectileVelocity = direction * glm::length(projectileEmitter.projectileVelocity);  // Maintain magnitude

					// Add the emitter's velocity to the projectile's velocity
					projectileVelocity += rigidbody.velocity;
				}

				// Calculate angle based on movement direction (emitter's velocity)
				float angle = 0.0f;
				if (glm::length(rigidbody.velocity) > 0.1f)
				{
					angle = glm::atan(rigidbody.velocity.y, rigidbody.velocity.x);  // Angle in radians
					angle = glm::degrees(angle);  // Convert to degrees
				}

				// Create projectile
				std::shared_ptr<Entity> projectile = registry->CreateEntity();
				projectile->Group("projectiles");
				projectile->AddComponent<TransformComponent>
				(projectilePosition, glm::vec2(2.0, 2.0), angle);  // Set angle based on velocity direction
				projectile->AddComponent<RigidBodyComponent>(projectileVelocity);  // Add emitter's velocity to projectile
				projectile->AddComponent<SpriteComponent>("bullet-image", 4, 4, 2, false);
				projectile->AddComponent<BoxColliderComponent>(4, 4);
				projectile->AddComponent<ProjectileComponent>
				(
					 projectileEmitter.isFriendly,
					 projectileEmitter.hitPercentDamage,
					 projectileEmitter.projectileDuration
				);
			}
		}
	public:
		ProjectileEmitSystem()
		{
			RequireComponent<ProjectileEmitterComponent>();
			RequireComponent<TransformComponent>();
			RequireComponent<RigidBodyComponent>();  // Ensure we can get velocity for projectiles
		}

		void Update(std::unique_ptr<Registry>& registry, std::shared_ptr<EventMap> eventMap)
		{
			for (auto entity : GetSystemEntities())
			{
				auto &projectileEmitter = entity->GetComponent<ProjectileEmitterComponent>();
				auto &transform = entity->GetComponent<TransformComponent>();
				auto &rigidbody = entity->GetComponent<RigidBodyComponent>();

				// Check if the entity has KeyBoardControlledComponent for direct space press control
				if (entity->HasComponent<KeyBoardControlledComponent>())
				{
					// Check for spacebar press and spawn projectile immediately
					auto it = eventMap->find(typeid(KeyPressEvent));
					if (it != eventMap->end())
					{
						for (const auto &event : it->second)
						{
							onSpacePressed(registry, event, entity, transform, projectileEmitter, 
									entity->GetComponent<SpriteComponent>(), rigidbody);
						}
					}
				}
				else
				{
					// Normal emission logic with cooldown for entities without KeyBoardControlledComponent
					if (SDL_GetTicks() - projectileEmitter.lastEmissionTime >
							static_cast<unsigned int>(projectileEmitter.repeatFrequency))
					{
						glm::vec2 projectilePosition = transform.position;
						if (entity->HasComponent<SpriteComponent>())
						{
							auto sprite = entity->GetComponent<SpriteComponent>();
							projectilePosition.x += (transform.scale.x * sprite.width / 2);
							projectilePosition.y += (transform.scale.y * sprite.height / 2);
						}
						// Add a new projectile entity to the registry
						std::shared_ptr<Entity> projectile = registry->CreateEntity();
						projectile->Group("projectiles");
						projectile->AddComponent<TransformComponent>
						(projectilePosition, glm::vec2(2.0, 2.0), 0);
						projectile->AddComponent<RigidBodyComponent>
						(projectileEmitter.projectileVelocity);
						projectile->AddComponent<SpriteComponent>("bullet-image", 4, 4, 2, false);
						projectile->AddComponent<BoxColliderComponent>(4, 4);
						projectile->AddComponent<ProjectileComponent>
						(
							projectileEmitter.isFriendly,
							projectileEmitter.hitPercentDamage,
							projectileEmitter.projectileDuration
						);
						// Update the projectile emitter component's last emission time
						projectileEmitter.lastEmissionTime = SDL_GetTicks();
					}
				}
			}
		}
};

#endif
