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
