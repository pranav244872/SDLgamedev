#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "../ECS/ECS.h"
#include "../Events/CollisionEvent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

typedef std::unordered_map
<std::type_index,std::vector<std::unique_ptr<Event>>> EventMap;

class CollisionSystem: public System
{
	private:
		std::shared_ptr<EventMap> eventMap;

		void emitCollisionEvent
		(
			std::shared_ptr<Entity> a, std::shared_ptr<Entity> b,
			double overlapX, double overlapY
		)
		{
			std::unique_ptr<CollisionEvent> event = 
			std::make_unique<CollisionEvent>(a, b, overlapX, overlapY);
			(*eventMap)[typeid(CollisionEvent)].push_back(std::move(event));
		}

		void clearAndEraseCollisionEvents()
		{
			auto it = eventMap->find(typeid(CollisionEvent));
			
			if (it != eventMap->end()) {
				it->second.clear();
				eventMap->erase(it);
			}
		}

		// Function to calculate overlap in X and Y directions
		std::pair<double, double> CalculateOverlap(
			double aX, double aY, double aW, double aH,
			double bX, double bY, double bW, double bH
		)
		{
			// Calculate the X and Y overlaps between the two AABBs
			double overlapX = std::min(aX + aW, bX + bW) - std::max(aX, bX);
			double overlapY = std::min(aY + aH, bY + bH) - std::max(aY, bY);

			// If there is no overlap in either direction, return zero
			if (overlapX < 0) overlapX = 0;
			if (overlapY < 0) overlapY = 0;

			return {overlapX, overlapY};
		}

	public:
		CollisionSystem(std::shared_ptr<EventMap> eventMap)
		{
			this->eventMap = eventMap;
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
			// Check if A's rectangle intersects B's rectangle
			return 
			(
				aX < bX + bW &&   // Check if A's left is less than B's right
				aX + aW > bX &&   // Check if A's right is greater than B's left
				aY < bY + bH &&   // Check if A's top is less than B's bottom
				aY + aH > bY      // Check if A's bottom is greater than B's top
			);       
		}

		void Update()
		{
			// Clear the eventMaps CollisionEvent values before adding new entities for the current frame
			clearAndEraseCollisionEvents();
				
			auto entities = GetSystemEntities();
			// Loop through all entities this system is interested in
			for (size_t i = 0; i < entities.size(); i++)
			{
				auto a = entities[i]; // a is now a shared_ptr<Entity>
				auto aTransform = a->GetComponent<TransformComponent>();
				auto aCollider = a->GetComponent<BoxColliderComponent>();

				// Precompute the width and height for entity A
				double aWidth = aCollider.width * aTransform.scale.x;
				double aHeight = aCollider.height * aTransform.scale.y;

				// Loop through all entities to check for collisions with entity A
				for (size_t j = i + 1; j < entities.size(); j++) 
				// Start from i+1 to avoid checking the same pair twice
				{
					auto b = entities[j]; // b is now a shared_ptr<Entity>
					auto bTransform = b->GetComponent<TransformComponent>();
					auto bCollider = b->GetComponent<BoxColliderComponent>();

					// Precompute the width and height for entity B
					double bWidth = bCollider.width * bTransform.scale.x;
					double bHeight = bCollider.height * bTransform.scale.y;

					// Check for collision between entity A and entity B
					bool collisionHappened = CheckAABBCollision
					(
						aTransform.position.x,
						aTransform.position.y,
						aWidth,
						aHeight,
						bTransform.position.x,
						bTransform.position.y,
						bWidth,
						bHeight 
					);

					// If a collision occurred, log it
					if (collisionHappened)
					{
						// Calculate overlap in X and Y directions
						auto [overlapX, overlapY] = 
						CalculateOverlap
						(
							aTransform.position.x, aTransform.position.y, 
							aWidth, aHeight,
							bTransform.position.x, bTransform.position.y, 
							bWidth, bHeight
						);

						emitCollisionEvent(a, b, overlapX, overlapY);

						// Here, you can log the overlap or store it as needed
						// For now, we just print the overlap values to the console
						Logger::Log
						(
							"Collision between entities " 
							+ std::to_string(a->getId()) + " and " 
							+ std::to_string(b->getId()) 
							+ " with overlap (X, Y): (" 
							+ std::to_string(overlapX) + ", " 
							+ std::to_string(overlapY) + ")"
						);
					}
				}
			}
		}
};

#endif
