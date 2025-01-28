#include "ECS.h"

int IComponent::nextId = 0;

long unsigned int Entity::getId() const 
{
	return id;
}

void System::AddEntityToSystem(Entity* entity)
{
	entities.push_back(entity);

}

void System::RemoveEntityFromSystem(Entity* entity)
{
	entities.erase(
		std::remove_if(
			entities.begin(), 
			entities.end(),
			[&entity](Entity* other)
			{
				return *entity == *other;
			}
		), 
		entities.end()
	);
}

const std::vector<Entity*>& System::GetSystemEntities() const
{
	return entities;
}

const Signature& System::GetComponentSignature() const
{
	return componentSignature;
}

Entity& Registry::CreateEntity()
{
	long unsigned int entityId = numEntities++;
	if (entityId >= entityComponentSignatures.size())
	{
		entityComponentSignatures.resize(entityId + 1);
	}
	Entity* entity = new Entity(entityId);
	entitiesToBeAdded.insert(entity);
	Logger::Log("Entity created with id = " + std::to_string(entityId));
	return *entity;
}
