#include "ECS.h"

int IComponent::nextId = 0;

long unsigned int Entity::getId() const 
{
	return id;
}

void Entity::Kill()
{
    // Create a shared_ptr from 'this' to pass to other parts of the system
    std::shared_ptr<Entity> sharedThis = shared_from_this();

    // Now, you can use the shared pointer to pass it around
    registry->KillEntity(sharedThis);

    // Additional logic for killing the entity (e.g., removing from systems, cleaning up)
    Logger::Log("Entity with id " + std::to_string(id) + " has been killed.");
}

void System::AddEntityToSystem(std::shared_ptr<Entity> entity)
{
	entities.push_back(entity);

}

void System::RemoveEntityFromSystem(std::shared_ptr<Entity> entity)
{
	entities.erase(
		std::remove_if(
			entities.begin(), 
			entities.end(),
			[&entity](std::shared_ptr<Entity> other)
			{
				return *entity == *other;
			}
		), 
		entities.end()
	);
}

const std::vector<std::shared_ptr<Entity>>& System::GetSystemEntities() const
{
	return entities;
}

const Signature& System::GetComponentSignature() const
{
	return componentSignature;
}

std::shared_ptr<Entity> Registry::CreateEntity()
{
	long unsigned int entityId;
	if (freeIds.empty())
	{
		entityId = numEntities++;
		if (entityId >= entityComponentSignatures.size())
		{
			entityComponentSignatures.resize(entityId + 1);
		}
	}
	else
	{
		// Reuse an id from the list of previously removed entities
		entityId = freeIds.front();
		freeIds.pop_front();
	}

	std::shared_ptr<Entity> entity = std::make_shared<Entity>(entityId);
	entity->registry = this;
	entitiesToBeAdded.insert(entity);
	Logger::Log("Entity created with id = " + std::to_string(entityId));
	return entity;
}

void Registry::KillEntity(std::shared_ptr<Entity> entity)
{
	entitiesToBeKilled.insert(entity);
}

void Registry::AddEntityToSystems(std::shared_ptr<Entity> entity)
{
	const auto entityId = entity->getId();
	const auto& entityComponentSignature = entityComponentSignatures[entityId];

	// Loop all the systems
	for (auto& system: systems)
	{
		const auto& systemComponentSignature = system.second->GetComponentSignature();
		bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;
		if (isInterested)
		{
			system.second->AddEntityToSystem(entity);
		}
	}
}

void Registry::RemoveEntityFromSystems(std::shared_ptr<Entity> entity)
{
	for (auto system: systems)
	{
		system.second->RemoveEntityFromSystem(entity);
	}
}

void Registry::Update()
{
	// Add the entites that are waiting to be created to the active Systems
	for (auto entity: entitiesToBeAdded)
	{
		AddEntityToSystems(entity);
	}
	entitiesToBeAdded.clear();

	// Remove the entities that are waiting to be removed
	for (auto entity: entitiesToBeKilled)
	{
		RemoveEntityFromSystems(entity);
		entityComponentSignatures[entity->getId()].reset();
		// Make the entity id available to be reused
		freeIds.push_back(entity->getId());
	}
	entitiesToBeKilled.clear();
}
