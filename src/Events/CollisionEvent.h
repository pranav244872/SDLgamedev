#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include "../ECS/ECS.h"
#include "Event.h"

struct CollisionEvent: public Event
{
	public:
		std::shared_ptr<Entity> a;
		std::shared_ptr<Entity> b;
		CollisionEvent(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
		{
			this->a = a;
			this->b = b;
		}
		~CollisionEvent() = default;
};

#endif
