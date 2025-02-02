#ifndef COLLISIONEVENT_H
#define COLLISIONEVENT_H

#include <memory>
#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class CollisionEvent: public Event
{
public:
	std::shared_ptr<Entity> a;
	std::shared_ptr<Entity> b;
	CollisionEvent(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b):
		a(a), b(b) {}

};

#endif
