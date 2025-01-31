#ifndef	COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

class CollisionSystem: public System
{
public:
	CollisionSystem()
	{
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	bool CheckAABBCollision
	(
		double aX, double aY, 
		double aW, double aH,
		double bX, double bY,
		double bW, double bH
	)
	{
		bool collision = 
			(
			aX < bX + bW &&   // Check if A's left is less than B's right
			aX + aW > bX &&   // Check if A's right is greater than B's left
			aY < bY + bH &&   // Check if A's top is less than B's bottom
			aY + aH > bY      // Check if A's bottom is greater than B's top
		);

		return collision;
	}

	void Update()
	{
		auto entities = GetSystemEntities();
		// Loop all the entities that the system is interested in
		for (long unsigned int i = 0; i < entities.size(); i++)
		{
			Entity a = *entities[i];
			auto aTransform = a.GetComponent<TransformComponent>();
			auto aCollider = a.GetComponent<BoxColliderComponent>();
			// Loop all the entities that still need to be checked
			for (long unsigned int j = i; j < entities.size(); j++)
			{
				Entity b = *entities[j];
				if (a == b) continue;

				auto bTransform = b.GetComponent<TransformComponent>();
				auto bCollider = b.GetComponent<BoxColliderComponent>();

				// Check for the collision between a and b
				bool collisionHappened = CheckAABBCollision
					(
						aTransform.position.x,
						aTransform.position.y,
						aCollider.width,
						aCollider.height,
						bTransform.position.x,
						bTransform.position.y,
						bCollider.width,
						bCollider.height
					);
				if (collisionHappened)
				{
					Logger::Log("Collision occurred between Entity A with ID " + std::to_string(a.getId()) + " and Entity B with ID " + std::to_string(b.getId()));
				}
			}
		}
	}
};

#endif
