#ifndef DAMAGESYSTEM_H
#define DAMAGESYSTEM_H

#include "../ECS/ECS.h"
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
		
		void Update()
		{
			/*auto it = eventMap->find(typeid(CollisionEvent));*/
			/*if (it != eventMap->end())*/
			/*{*/
			/*	for (const auto& event : it->second)*/
			/*	{*/
			/*		// Cast the raw pointer from the unique_ptr to CollisionEvent**/
			/*		CollisionEvent* collisionEvent = static_cast<CollisionEvent*>(event.get());*/
			/*		// Check if the entity is involved in the event*/
			/*	}*/
			/*}*/
		}

};
#endif
