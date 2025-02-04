#ifndef PROJECTILEEMITYSYSTEM_H
#define PROJECTILEEMITYSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"

class ProjectileEmitSystem: public System
{
	public:
		ProjectileEmitSystem()
		{
			RequireComponent<ProjectileEmitterComponent>();
			RequireComponent<TransformComponent>();
		}
		void Update(std::unique_ptr<Registry>& registry)	
		{
			for (auto entity: GetSystemEntities())
			{
				auto& projectileEmitter = 
					entity->GetComponent<ProjectileEmitterComponent>();
				auto transform = entity->GetComponent<TransformComponent>();

				// Check if its time to re-emit a new projectile
				if 
				(
					SDL_GetTicks() - projectileEmitter.lastEmissionTime > 
					static_cast<unsigned int>(projectileEmitter.repeatFrequency)
				)
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
					projectile->AddComponent<TransformComponent>
						(projectilePosition, glm::vec2(2.0, 2.0), 0);
					projectile->AddComponent<RigidBodyComponent>	
						(projectileEmitter.projectileVelocity);
					projectile->AddComponent<SpriteComponent>	
						("bullet-image", 4, 4, 2, false);
					projectile->AddComponent<BoxColliderComponent>	
						(4, 4);
					projectile->AddComponent<ProjectileComponent>
						(
							projectileEmitter.isFriendly, projectileEmitter.hitPercentDamage,
							projectileEmitter.projectileDuration
						);
					// Update the projectile emitter component
					projectileEmitter.lastEmissionTime = SDL_GetTicks();
				}

			}
		}
};

#endif
