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

void Entity::Tag(const std::string& tag)
{
    std::shared_ptr<Entity> sharedThis = shared_from_this();
	registry->TagEntity(sharedThis, tag);
}

bool Entity::HasTag(const std::string& tag) 
{
    std::shared_ptr<Entity> sharedThis = shared_from_this();
	return registry->EntityHasTag(sharedThis, tag);
}

void Entity::Group(const std::string &group)
{
    std::shared_ptr<Entity> sharedThis = shared_from_this();
	registry->GroupEntity(sharedThis, group);
}

bool Entity::BelongsToGroup(const std::string &group)
{
    std::shared_ptr<Entity> sharedThis = shared_from_this();
	return registry->EntityBelongsToGroup(sharedThis, group);
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

void Registry::TagEntity(std::shared_ptr<Entity> entity, const std::string &tag)
{
	entityPerTag.emplace(tag, entity);
	tagPerEntity.emplace(entity->getId(), tag);
}

bool Registry::EntityHasTag
(std::shared_ptr<Entity> entity, const std::string& tag) const
{
	if (tagPerEntity.find(entity->getId()) == tagPerEntity.end())
	{
		return false;
	}
	return entityPerTag.find(tag)->second == entity;
}

std::shared_ptr<Entity> Registry::GetEntityByTag(const std::string& tag) const
{
	return entityPerTag.at(tag);
}

void Registry::RemoveEntityTag(std::shared_ptr<Entity> entity)
{
	auto taggedEntity = tagPerEntity.find(entity->getId());
	if (taggedEntity != tagPerEntity.end())
	{
		auto tag = taggedEntity->second;
		entityPerTag.erase(tag);
		tagPerEntity.erase(taggedEntity);
	}
}

void Registry::GroupEntity(std::shared_ptr<Entity> entity, const std::string& group)
{
	entitiesPerGroup.emplace(group, std::set<std::shared_ptr<Entity>>());
	entitiesPerGroup[group].emplace(entity);
	groupPerEntity.emplace(entity->getId(), group);
}

bool Registry::EntityBelongsToGroup
(std::shared_ptr<Entity> entity, const std::string& group) const
{
    auto groupEntities = entitiesPerGroup.at(group);
    
    // Instead of checking the entity ID, check the shared_ptr directly
    return groupEntities.find(entity) != groupEntities.end();
}

std::vector<std::shared_ptr<Entity>> Registry::GetEntitiesByGroup
(const std::string& group) const
{
	auto &setOfEntities = entitiesPerGroup.at(group);
	return std::vector<std::shared_ptr<Entity>>(setOfEntities.begin(), setOfEntities.end());
}

void Registry::RemoveEntityGroup(std::shared_ptr<Entity> entity) {
    auto groupedEntity = groupPerEntity.find(entity->getId());
    if (groupedEntity != groupPerEntity.end()) {
        auto group = entitiesPerGroup.find(groupedEntity->second);
        if (group != entitiesPerGroup.end()) {
            auto entityInGroup = group->second.find(entity); // Correct: entity is a shared_ptr
            if (entityInGroup != group->second.end()) {
                group->second.erase(entityInGroup);
            }
        }
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
