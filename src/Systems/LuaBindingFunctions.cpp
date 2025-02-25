#include "ScriptSystem.h"
#include "../Logger/Logger.h"

void SetEntityPosition(std::shared_ptr<Entity> entity, double x, double y)
{
    if (entity->HasComponent<TransformComponent>())
    {
        auto& transform = entity->GetComponent<TransformComponent>();
        transform.position.x = x;
        transform.position.y = y;
    }
    else
    {
        Logger::Err("Trying to set the position of an entity that has no transform component");
    }
}

std::tuple<double, double> GetEntityPosition(std::shared_ptr<Entity> entity)
{
	if (entity->HasComponent<TransformComponent>())
	{
		const auto transform = entity->GetComponent<TransformComponent>();
		return std::make_tuple(transform.position.x, transform.position.y);
	}
	else
	{
		Logger::Err
		("Trying to get the position of an entity that has no transform component");
		return std::make_tuple(0.0, 0.0);
	}
}

std::tuple<double, double> GetEntityVelocity(std::shared_ptr<Entity> entity)
{
	if (entity->HasComponent<RigidBodyComponent>())
	{
		const auto rigidbody = entity->GetComponent<RigidBodyComponent>();
		return std::make_tuple(rigidbody.velocity.x, rigidbody.velocity.y);
	}
	else
	{
		Logger::Err
		("Trying to get the position of an entity that has no transform component");
		return std::make_tuple(0.0, 0.0);
	}
}

void SetEntityVelocity(std::shared_ptr<Entity> entity, double x, double y)
{
	if (entity->HasComponent<RigidBodyComponent>())
	{
		auto& rigidbody = entity->GetComponent<RigidBodyComponent>();
		rigidbody.velocity.x = x;
		rigidbody.velocity.y = y;
	}
	else 
	{
		Logger::Err
		("Trying to set the velocity of an entity that has no rigidbody component");
	}
}

void SetEntityRotation(std::shared_ptr<Entity> entity, double angle)
{
	if (entity->HasComponent<TransformComponent>())
	{
		auto& transform = entity->GetComponent<TransformComponent>();
		transform.rotation = angle;
	}
	else 
	{
		Logger::Err
		("Trying to set the rotation of an entity that has no Transform component");
	}
}

void SetProjectileVelocity(std::shared_ptr<Entity> entity, double x, double y)
{
	if (entity->HasComponent<ProjectileEmitterComponent>())
	{
		auto& projectileEmitter = entity->GetComponent<ProjectileEmitterComponent>();
		projectileEmitter.projectileVelocity.x = x;
		projectileEmitter.projectileVelocity.y = y;
	}
	else
	{
		Logger::Err
		("Trying to set the projectile velocity of an entity that has no projectileEmitter component");
	}
}

void SetEntityAnimationFrame(std::shared_ptr<Entity> entity, int frame)
{
	if (entity->HasComponent<AnimationComponent>())
	{
		auto& animation = entity->GetComponent<AnimationComponent>();
		animation.currentFrame = frame;
	}
	else
	{
		Logger::Err
		("Trying to set the animation frame of an entity that has no animation component");
	}
}

