#ifndef SCRIPTSYSTEM_H
#define SCRIPTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/ScriptComponent.h"
#include "../Components/TransformComponent.h"

// Declare the function
void SetEntityPosition(std::shared_ptr<Entity> entity, double x, double y);

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
			lua.set_function("set_position", SetEntityPosition);
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
