#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <memory>
#include <deque>
#include "../Logger/Logger.h"

////////////////////////////////////////////////////////////////////////////////
/// Signature
////////////////////////////////////////////////////////////////////////////////
/// We use bitset (1s and 0s) to keep track of which components an entity has,
/// also jelps keep track of which entities a system is interested in
////////////////////////////////////////////////////////////////////////////////
const int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

////////////////////////////////////////////////////////////////////////////////
/// Component Class
////////////////////////////////////////////////////////////////////////////////
struct IComponent
{
protected:
	static int nextId;
};

// Used to assign a unique id to a component type
template <typename T>
class Component: public IComponent
{
public:
	// Returns the unique id of Component<T>
	static int GetId()
	{
		static auto id = nextId++;
		return id;
	}
};

////////////////////////////////////////////////////////////////////////////////
/// Entity Class
////////////////////////////////////////////////////////////////////////////////
class Entity : public std::enable_shared_from_this<Entity>
{
private:
	long unsigned int id;
public:
	Entity(int id): id(id) {};
	Entity(const Entity& entity) = default;
	void Kill();
	long unsigned int getId() const;

	Entity& operator = (const Entity& other) = default;
	bool operator == (const Entity& other) const { return id == other.id; }
	bool operator != (const Entity& other) const { return id != other.id; }
	bool operator > (const Entity& other) const { return id > other.id; }
	bool operator < (const Entity& other) const { return id < other.id; }
	
	class Registry* registry;

	// Manage entity tags and groups
	void Tag(const std::string& tag);
	bool HasTag(const std::string& tag);
	void Group(const std::string& group);
	bool BelongsToGroup(const std::string& group);
	
	// Manage entity components
	template <typename TComponent, typename ...TArgs>
	void AddComponent(TArgs&& ...args);
	template <typename TComponent>
	void RemoveComponent();
	template <typename TComponent>
	bool HasComponent() const;
	template <typename TComponent>
	TComponent& GetComponent() const;
};

////////////////////////////////////////////////////////////////////////////////
// System Class
////////////////////////////////////////////////////////////////////////////////
// The system processes entities that contain a specific signature
////////////////////////////////////////////////////////////////////////////////
class System
{
private:
	Signature componentSignature;
	std::vector<std::shared_ptr<Entity>> entities;
public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(std::shared_ptr<Entity> entity);
	void RemoveEntityFromSystem(std::shared_ptr<Entity> entity);
	const std::vector<std::shared_ptr<Entity>>& GetSystemEntities() const;
	const Signature& GetComponentSignature() const;

	// Defines the component type that entities must have to be considered by
	// the system
	template <typename TComponent> void RequireComponent();
};

////////////////////////////////////////////////////////////////////////////////
/// Pool Class
////////////////////////////////////////////////////////////////////////////////
/// A pool is just a vector (contiguous data) of objects of type T
////////////////////////////////////////////////////////////////////////////////
class IPool
{
public:
	virtual ~IPool() = default;
	virtual void RemoveEntityFromPool(int entityId) = 0;
};

template <typename T>
class Pool : public IPool
{
private:
	std::vector<T> data;
	int size;
	
	// Helper maps to keep track of entity ids per index, so the vector is always packed
	std::unordered_map<int, int> entityIdToIndex;
	std::unordered_map<int, int> indexToEntityId;

public:
	Pool(int capacity = 100) 
	{ 
		size = 0;
		data.resize(capacity); 
	}
	virtual ~Pool() = default;

	bool isEmpty() const { return size == 0; }
	int GetSize() const { return size; }
	void Resize(int n) { data.resize(n); }
	void Clear() { data.clear(); size = 0; }

	void Add(T object) 
	{ 
		data.push_back(object); 
	}

	void Set(int entityId, T object) 
	{
		if (entityIdToIndex.find(entityId)!= entityIdToIndex.end())
		{
			// If the element already exists, simply replace the component object
			int index = entityIdToIndex[entityId];
			data[index] = object;
		}
		else
		{
			// When adding a new object, we keep track of the entity ids and 
			// their vector index
			int index = size;
			entityIdToIndex.emplace(index, entityId);
			if (static_cast<long unsigned int>(index) >= data.capacity())
			{
				// If necessary, we resize by always doubling the current capacity
				data.resize(size * 2);
			}
			data[index] = object;
			size++;
		}
	}
	
	void Remove(int entityId)
	{
		// Copy the last element to the deleted position to keep the array packed		
		int indexOfRemoved = entityIdToIndex[entityId];
		int indexOfLast = size - 1;
		data[indexOfRemoved] = data[indexOfLast];
		
		// Update the index-entity maps to point to the correct elements
		int entityIdOfLastElement = indexToEntityId[indexOfLast];
		entityIdToIndex[entityIdOfLastElement] = indexOfRemoved;
		indexToEntityId[indexOfRemoved] = entityIdOfLastElement;

		entityIdToIndex.erase(entityId);
		indexToEntityId.erase(indexOfLast);

		size--;
	}
	
	void RemoveEntityFromPool(int entityId) override
	{
		if (entityIdToIndex.find(entityId) != entityIdToIndex.end())
		{
			Remove(entityId);
		}
	}

	T& Get(int entityId) 
	{ 
		int index = entityIdToIndex[entityId];
		return static_cast<T&>(data[index]); 
	}

	T& operator [] (int index) { return data[index]; }
};

////////////////////////////////////////////////////////////////////////////////
/// Registry Class
////////////////////////////////////////////////////////////////////////////////
/// The Registry manages the creation and destruction of entities, as well as
/// adding systems and adding components to entities
////////////////////////////////////////////////////////////////////////////////

class Registry
{
private:
	// Keep track of how many entities were added to the screen
	long unsigned int numEntities = 0;
	std::set<std::shared_ptr<Entity>> entitiesToBeAdded;
	std::set<std::shared_ptr<Entity>> entitiesToBeKilled;
	
	// Entity tags (one tag per entity)
	std::unordered_map<std::string, std::shared_ptr<Entity>> entityPerTag;
	std::unordered_map<int, std::string> tagPerEntity;

	// Entity groups (a set of entites per group name)
	std::unordered_map<std::string, std::set<std::shared_ptr<Entity>>> entitiesPerGroup;
	std::unordered_map<int, std::string> groupPerEntity;

	// Vector of component pools, each pool contains all the data for a certain
	// component type
	// Vector index = component type id
	// Pool index = entity id
	std::vector<std::shared_ptr<IPool>> componentPools;
	
	// Vector of component signatures
	// The signature lets us know which components are turned "on" for an entity
	// [vector index = entity id]
	std::vector<Signature> entityComponentSignatures;

	// Map of active system [index = system typeId]
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

	// List of free entity ids that were previously removed
	std::deque<long unsigned int> freeIds;

public:
	Registry() = default;

	// The registry Update() finally processes the entities that are waiting to
	// be added or killed
	void Update();
	
	// Entity Management
	std::shared_ptr<Entity> CreateEntity();	
	void KillEntity(std::shared_ptr<Entity> entity);
	
	// Tag management
	void TagEntity(std::shared_ptr<Entity> entity, const std::string& tag);
	bool EntityHasTag(std::shared_ptr<Entity> entity, const std::string& tag) const;
	std::shared_ptr<Entity> GetEntityByTag(const std::string& tag) const;
	void RemoveEntityTag(std::shared_ptr<Entity> entity);

	// Group management
	void GroupEntity(std::shared_ptr<Entity> entity, const std::string& group);
	bool EntityBelongsToGroup(std::shared_ptr<Entity> entity, const std::string& group) const;
	std::vector<std::shared_ptr<Entity>> GetEntitiesByGroup(const std::string& group) const;
	void RemoveEntityGroup(std::shared_ptr<Entity> entity);

	// Component Management
	// Adds a Component<T> to an entity
	template <typename TComponent, typename ...TArgs> 
	void AddComponent(Entity entity, TArgs&& ...args);

	// Ask to RemoveComponent<T> from an entity
	template <typename TComponent>
	void RemoveComponent(Entity entity);

	// Checks if an entity HasComponent<T>()
	template <typename TComponent> bool HasComponent(Entity entity);

	// Returns the component
	template <typename TComponent> TComponent& GetComponent(Entity entity) const;

	// System management
	template <typename TSystem, typename ...TArgs> 
	void AddSystem(TArgs&& ...args);

	template <typename TSystem> 
	void RemoveSystem();

	template <typename TSystem> 
	bool HasSystem() const;

	template <typename TSystem>
	TSystem& GetSystem() const;

	// Checks the component signature of an entity and add the entity to the systems
	// that are interested in it
	void AddEntityToSystems(std::shared_ptr<Entity> entity);
	void RemoveEntityFromSystems(std::shared_ptr<Entity> entity);
};

////////////////////////////////////////////////////////////////////////////////
/// System Templates
////////////////////////////////////////////////////////////////////////////////

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

////////////////////////////////////////////////////////////////////////////////
/// Registry Templates
////////////////////////////////////////////////////////////////////////////////

template <typename TSystem, typename ...TArgs> 
void Registry::AddSystem(TArgs&& ...args)
{
	std::shared_ptr<TSystem> newSystem 
		= std::make_shared<TSystem>(std::forward<TArgs>(args)...);
	
	systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem()
{
	auto system = systems.find(std::type_index(typeid(TSystem)));
	systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const
{
	return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem>
TSystem& Registry::GetSystem() const
{
	auto system = systems.find(std::type_index(typeid(TSystem)));
	return *std::static_pointer_cast<TSystem>(system->second);
}

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.getId();

	// If the component id is greater than the current size of the componentPools,
	// then resize the vector
	if 
	(
		static_cast<long unsigned int>(componentId) >= 
		static_cast<long unsigned int>(componentPools.size())
	)
	{	
		componentPools.resize(componentId + 1, nullptr);
	}

	// If we still dont have a pool for that component type
	if (!componentPools[componentId])
	{
		std::shared_ptr<Pool<TComponent>> newComponentPool 
			= std::make_shared<Pool<TComponent>>();
		componentPools[componentId] = newComponentPool;
	}

	// Get the pool of component values for that component type
	std::shared_ptr<Pool<TComponent>> componentPool 
		= std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

	// Create a new Component object of the type T, and forward the various paramenters
	// to the constructor
	TComponent newComponent(std::forward<TArgs>(args)...);
	
	// Add the new component to the component pool list, using the entity id as index
	componentPool->Set(entityId, newComponent);
	
    // Update the entity's signature to indicate that it now has this component.
    entityComponentSignatures[entityId].set(componentId, true);

	Logger::Log
	(
		"Component id = " 
		+ std::to_string(componentId) + 
		" was added to entityid " + 
		std::to_string(entityId)
	);

	std::cout << "COMPONENT ID = " << componentId 
		<< " --> POOL SIZE: " << componentPool->GetSize() << std::endl;
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.getId();

	
	// Remove the component from the component list for that entity
	std::shared_ptr<Pool<TComponent>> componentPool 
		= std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
	componentPool->Remove(entityId);

	// Set this component signature for that entity to false
	entityComponentSignatures[entityId].set(componentId, false);

	Logger::Log
	(
		"Component id = " 
		+ std::to_string(componentId) + 
		" was removed to entityid " + 
		std::to_string(entityId)
	);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.getId();

	return entityComponentSignatures[entityId].test(componentId);
}

template <typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.getId();
	auto componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
	return componentPool->Get(entityId);
}

////////////////////////////////////////////////////////////////////////////////
// Entity Templates
////////////////////////////////////////////////////////////////////////////////
template <typename TComponent, typename ...TArgs>
void Entity::AddComponent(TArgs&& ...args)
{
	registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);  
}

template <typename TComponent>
void Entity::RemoveComponent()
{
	registry->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::HasComponent() const
{
	return registry->HasComponent<TComponent>(*this);
}

template <typename TComponent>
TComponent& Entity::GetComponent() const
{
	return registry->GetComponent<TComponent>(*this);
}
////////////////////////////////////////////////////////////////////////////////

#endif
