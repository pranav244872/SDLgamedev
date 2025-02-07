#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "../Components/KeyBoardControlledComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../ECS/ECS.h"
#include "../Events/KeyPressEvent.h"

typedef std::unordered_map<std::type_index, std::vector<std::unique_ptr<Event>>>
    EventMap;

class KeyboardControlSystem : public System
{
    private:
        std::shared_ptr<EventMap> eventMap;
        void onKeyPressed(const std::unique_ptr<Event> &event)
        {
            KeyPressEvent *keyPressEvent =
                static_cast<KeyPressEvent *>(event.get());
            for (auto entity : GetSystemEntities())
            {
                switch (keyPressEvent->symbol)
                {
                case SDLK_UP:
					Logger::Log("Up pressed");
                    break;
                case SDLK_RIGHT:
					Logger::Log("Right pressed");
                    break;
                case SDLK_DOWN:
					Logger::Log("Down pressed");
                    break;
                case SDLK_LEFT:
					Logger::Log("Left pressed");
                    break;
                }
            }
        }

    public:
        KeyboardControlSystem(std::shared_ptr<EventMap> eventMap)
            : eventMap(eventMap)
        {
            RequireComponent<KeyBoardControlledComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void Update()
        {
            auto it = eventMap->find(typeid(KeyPressEvent));
            if (it != eventMap->end())
            {
                for (const auto &event : it->second)
                {
                    onKeyPressed(event);
                }
            }
        }
};
#endif
