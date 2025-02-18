#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"
#include "../Events/CollisionEvent.h"

typedef std::unordered_map
<std::type_index,std::vector<std::unique_ptr<Event>>> EventMap;

class DamageSystem: public System
{
	private:
		std::shared_ptr<EventMap> eventMap;

	public:
		DamageSystem(std::shared_ptr<EventMap> eventMap)
		{
			this->eventMap = eventMap;
		}
		
		void OnProjectileHitsPlayer
		(
			std::shared_ptr<Entity> projectile, std::shared_ptr<Entity> player
		)
		{
			const auto projectileComponent = projectile->
				GetComponent<ProjectileComponent>();
			if (!projectileComponent.isFriendly)
			{
				// Reduce the health of the player by the projectile hit percentage
				auto& health = player->GetComponent<HealthComponent>();

				// Subtract the health of the player
				health.healthPercentage -= projectileComponent.hitPercentDamage;

				// Kills the player if health reaches 0
				if (health.healthPercentage <= 0)
				{
					player->Kill();
				}

				// Kill the projectile
				projectile->Kill();
			}
		}

		void OnPorjectileHitsEnemy
		(
			std::shared_ptr<Entity> projectile, std::shared_ptr<Entity> enemy
		)
		{
			auto projectileComponent = projectile->
				GetComponent<ProjectileComponent>();
			if (projectileComponent.isFriendly)
			{
				// Reduce the health of the enemy
				auto& health = enemy->GetComponent<HealthComponent>();
				// Subtract the health of the enemy
				health.healthPercentage -= projectileComponent.hitPercentDamage;
				//Kills the enemy if health reaches 0
				if (health.healthPercentage<= 0) enemy->Kill();
				projectile->Kill();
			}
		}

		void Update()
		{
			auto it = eventMap->find(typeid(CollisionEvent));
			if (it != eventMap->end())
			{
				for (const auto& event : it->second)
				{
					// Cast the raw pointer from the unique_ptr to CollisionEvent*
					CollisionEvent* collisionEvent = static_cast<CollisionEvent*>(event.get());
					// Check if the entity is involved in the event
					Logger::Log
					(
						"Collision event emitted between: " +
						std::to_string(collisionEvent->a->getId()) +
						" and " +
						std::to_string(collisionEvent->b->getId())

					);

					if
					(
						collisionEvent->a->BelongsToGroup("projectiles")
						&&
						collisionEvent->b->HasTag("player")
					)
					{
						OnProjectileHitsPlayer
						(collisionEvent->a,collisionEvent->b);
					}

					if
					(
						collisionEvent->b->BelongsToGroup("projectiles")
						&&
						collisionEvent->a->HasTag("player")
					)
					{
						OnProjectileHitsPlayer
						(collisionEvent->b,collisionEvent->a);
					}

					if 
					(
						collisionEvent->a->BelongsToGroup("projectiles")
						&&
						collisionEvent->b->BelongsToGroup("enemies")
					)
					{
						OnPorjectileHitsEnemy
						(collisionEvent->a, collisionEvent->b);
					}

					if 
					(
						collisionEvent->b->BelongsToGroup("projectiles")
						&&
						collisionEvent->a->BelongsToGroup("enemies")
					)
					{
						OnPorjectileHitsEnemy
						(collisionEvent->b, collisionEvent->a);
					}
				}
			}
		}

};
#endif
