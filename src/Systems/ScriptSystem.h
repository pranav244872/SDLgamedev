#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/AnimationComponent.h"

// Declare the function
std::tuple<double, double> GetEntityPosition(std::shared_ptr<Entity> entity);
std::tuple<double, double> GetEntityVelocity(std::shared_ptr<Entity> entity);
void SetEntityPosition(std::shared_ptr<Entity> entity, double x, double y);
void SetEntityVelocity(std::shared_ptr<Entity> entity, double x, double y);
void SetEntityRotation(std::shared_ptr<Entity> entity, double angle);
void SetProjectileVelocity(std::shared_ptr<Entity> entity, double x, double y);
void SetEntityAnimationFrame(std::shared_ptr<Entity> entity, int frame);

class ScriptSystem: public System
{
	public:
		ScriptSystem()
		{
			RequireComponent<ScriptComponent>();
		}

		void CreateLuaBindings(sol::state& lua)
		{
			// Create the entity usertype so lua knows what an entity is
			lua.new_usertype<Entity>
			(
				"entity"
			);
			lua.set_function("get_position", GetEntityPosition);
			lua.set_function("get_velocity", GetEntityVelocity);
			lua.set_function("set_position", SetEntityPosition);
			lua.set_function("set_velocity", SetEntityVelocity);
			lua.set_function("set_rotation", SetEntityRotation);
			lua.set_function("set_projectile_velocity", SetProjectileVelocity);
			lua.set_function("set_animation_frame", SetEntityAnimationFrame);
		}

		void Update(double deltaTime, int ellapsedTime)
		{
			for (auto entity: GetSystemEntities())
			{
				const auto script = entity->GetComponent<ScriptComponent>();
				script.func(entity, deltaTime, ellapsedTime); // here is where we invoke a sol::function
			}
		}
};
#endif
