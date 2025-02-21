#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../ECS/ECS.h"
#include "Event.h"

struct CollisionEvent: public Event
{
    public:
        std::shared_ptr<Entity> a;
        std::shared_ptr<Entity> b;
        double overlapX;  // The overlap in the X direction
        double overlapY;  // The overlap in the Y direction

        // Constructor modified to accept overlap values
        CollisionEvent
		(
			std::shared_ptr<Entity> a, std::shared_ptr<Entity> b, 
			double overlapX, double overlapY
		)
        {
            this->a = a;
            this->b = b;
            this->overlapX = overlapX;
            this->overlapY = overlapY;
        }

        ~CollisionEvent() = default;
};

#endif
