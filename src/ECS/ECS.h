#ifndef ECS_H
#define ECS_H

#include "../Logger/Logger.h"
#include <bitset>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <typeindex>
#include <set>
////////////////////////////////////////////////////////////////////////////////
/// Signature
////////////////////////////////////////////////////////////////////////////////
/// We use bitset (1s and 0s) to keep track of which components an entity has,
/// also jelps keep track of which entities a system is interested in
////////////////////////////////////////////////////////////////////////////////
const int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent
{
protected:
	static int nextId;
};

// Used to assign a unique id to a component type
template <typename T>
class Component: public IComponent
{
	// Returns the unique id of Component<T>
	static int GetId()
	{
		static auto id = nextId++;
		return id;
	}
};

class Entity
{
private:
	long unsigned int id;
public:
	Entity(int id): id(id) {};
	Entity(const Entity& entity) = default;
	long unsigned int getId() const;

	Entity& operator = (const Entity& other) = default;
	bool operator == (const Entity& other) const { return id == other.id; }
	bool operator != (const Entity& other) const { return id != other.id; }

};

////////////////////////////////////////////////////////////////////////////////
// Systems
////////////////////////////////////////////////////////////////////////////////
// The system processes entities that contain a specific signature
////////////////////////////////////////////////////////////////////////////////
class System
{
private:
	Signature componentSignature;
	std::vector<Entity*> entities;
public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(Entity* entity);
	void RemoveEntityFromSystem(Entity* entity);
	const std::vector<Entity*>& GetSystemEntities() const;
	const Signature& GetComponentSignature() const;

	// Defines the component type that entities must have to be considered by
	// the system
	template <typename TComponent> void RequireComponent();
};

////////////////////////////////////////////////////////////////////////////////
/// Pool 
////////////////////////////////////////////////////////////////////////////////
/// A pool is just a vector (contiguous data) of objects of type T
////////////////////////////////////////////////////////////////////////////////
class IPool
{
public:
	virtual ~IPool() {}
};

template <typename T>
class Pool : public IPool
{
private:
	std::vector<T> data;

public:
	Pool(int size = 100) { data.resize(size); }
	~Pool() = default;

	bool isEmpty() const { return data.empty(); }
	int GetSize() const { return data.size(); }
	void Resize(int n) { data.resize(n); }
	void Clear() { data.clear(); }
	void Add(T object) { data.push_back(object); }
	void Set(int index, T object) { data[index] = object; }
	T& Get(int index) { return static_cast<T&>(data[index]); }
	T& operator [] (int index) { return data[index]; }
};

////////////////////////////////////////////////////////////////////////////////
/// Registry
////////////////////////////////////////////////////////////////////////////////
/// The Registry manages the creation and destruction of entities, as well as
/// adding systems and adding components to entities
////////////////////////////////////////////////////////////////////////////////
class Registry
{
private:
	// Keep track of how many entities were added to the screen
	long unsigned int numEntities = 0;
	std::set<Entity*> entitiesToBeAdded;
	std::set<Entity*> entitiesToBeKilled;

	// Vector of component pools, each pool contains all the data for a certain
	// component type
	// Vector index = component type id
	// Pool index = entity id
	std::vector<IPool*> componentPools;
	
	// Vector of component signatures
	// The signature lets us know which components are turned "on" for an entity
	// [vector index = entity id]
	std::vector<Signature> entityComponentSignatures;

	// Map of active system [index = system typeId]
	std::unordered_map<std::type_index, System*> systems;

public:
	Registry() = default;

	// The registry Update() finally processes the entities that are waiting to
	// be added or killed
	void Update();
	
	// Entity Management
	Entity& CreateEntity();	
	void KillEntity(Entity& entity);

	// Component Management
	// Adds a Component<T> to an entity
	template <typename TComponent, typename ...TArgs> 
	void AddComponent(Entity entity, TArgs&& ...args);

	// Ask to RemoveComponent<T> from an entity
	template <typename TComponent>
	void RemoveComponent(Entity entity);

	// Checks if an entity HasComponent<T>()
	template <typename T> bool HasComponent(Entity entity);



	void AddEntityToSystem(Entity entity);
	// void AddSystem(...);
	// void AddComponent();
	// void RemoveComponent();
	// HasComponent(Entity entity)
	// AddSystem()
	// RemoveSystem()
	// HasSystem()
	// GetSystem()
};

template <typename TComponent>
void System::RequireComponent()
{
	const auto componentId = Component<TComponent>::GetId();
	componentSignature.set(componentId);
}

template <typename TComponent, typename ...TArgs>
void Registry::AddComponent(Entity entity, TArgs&& ...args)
{
	const auto componentId = Component<TComponent>::GetId();
	const auto entityId = entity.getId();

	// If the component id is greater than the current size of the componentPools,
	// then resize the vector
	if (componentId >= componentPools.size())
	{	
		componentPools.resize(componentId + 1, nullptr);
	}

	// If we still dont have a pool for that component type
	if (!componentPools[componentId])
	{
		Pool<TComponent>* newComponentPool = new Pool<TComponent>();
		componentPools[componentId] = newComponentPool;
	}

	// Get the pool of component values for that component type
	Pool<TComponent>* componentPool = Pool<TComponent>(componentPools[componentId]);

	// If the entity id is greater than the current size of the component pool,
	// then resize the pool
	if (entityId >= componentPool->getSize())
	{
		componentPool->Resize(numEntities);
	}
	
	// Create a new Component object of the type T, and forward the various paramenters
	// to the constructor
	TComponent newComponent(std::forward<TArgs>(args)...);
	
	// Add the new component to the component pool list, using the entity id as index
	componentPool->Set(entityId, newComponent);
	
    // Update the entity's signature to indicate that it now has this component.
    entityComponentSignatures[entityId].set(componentId, true);
}

template <typename T>
void Registry::RemoveComponent(Entity entity)
{
	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.getId();

	entityComponentSignatures[entityId].set(componentId, false);
}

template <typename T>
bool Registry::HasComponent(Entity entity)
{
	const auto componentId = Component<T>::GetId();
	const auto entityId = entity.getId();

	return entityComponentSignatures[entityId].test(componentId);
}
#endif
