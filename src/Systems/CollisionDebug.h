#ifndef COLLISIONDEBUG_H
#define COLLISIONDEBUG_H

#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"

class CollisionDebug: public System
{
public:
    CollisionDebug()
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
        return 
		(
			aX < bX + bW &&   // Check if A's left is less than B's right
			aX + aW > bX &&   // Check if A's right is greater than B's left
			aY < bY + bH &&   // Check if A's top is less than B's bottom
			aY + aH > bY	 // Check if A's bottom is greater than B's top
		);       
	}
    
    void Update(SDL_Renderer* renderer, bool debugMode)
    {
        if (debugMode)
        {
            auto entities = GetSystemEntities();
            // Loop all the entities that the system is interested in
            for (size_t i = 0; i < entities.size(); i++)
            {
                auto a = entities[i]; // a is a shared_ptr<Entity>
                auto aTransform = a->GetComponent<TransformComponent>();
                auto aCollider = a->GetComponent<BoxColliderComponent>();

                // Precompute width and height with scale for entity A
                double aWidth = aCollider.width * aTransform.scale.x;
                double aHeight = aCollider.height * aTransform.scale.y;

                // Loop all the entities that still need to be checked
                for (size_t j = i + 1; j < entities.size(); j++)  
                {
                    auto b = entities[j]; // b is a shared_ptr<Entity>
                    auto bTransform = b->GetComponent<TransformComponent>();
                    auto bCollider = b->GetComponent<BoxColliderComponent>();

                    // Precompute width and height with scale for entity B
                    double bWidth = bCollider.width * bTransform.scale.x;
                    double bHeight = bCollider.height * bTransform.scale.y;

                    // Get transformed rectangle for entity A
                    SDL_Rect rectA = 
                    { 
                        static_cast<int>(aTransform.position.x),
                        static_cast<int>(aTransform.position.y),
                        static_cast<int>(aWidth),
                        static_cast<int>(aHeight)
                    };

                    // Get transformed rectangle for entity B
                    SDL_Rect rectB = 
                    { 
                        static_cast<int>(bTransform.position.x),
                        static_cast<int>(bTransform.position.y),
                        static_cast<int>(bWidth),
                        static_cast<int>(bHeight)
                    };

                    // Check for the collision between entity A and entity B
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

                    // Set color based on collision detection result using if-else
                    if (collisionHappened)
                    {
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
						// Red for collision
                    }
                    else
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); 
						// Blue for no collision
                    }

                    // Draw both rectangles
                    SDL_RenderDrawRect(renderer, &rectA);
                    SDL_RenderDrawRect(renderer, &rectB);
                }
            }
        }
    }
};

#endif
