#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "../ECS/ECS.h"
#include "../Events/KeyPressEvent.h"
#include "../Components/KeyBoardControlledComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

typedef std::unordered_map
<std::type_index,std::vector<std::unique_ptr<Event>>> EventMap;

class KeyboardControlSystem: public System
{
	private:
		std::shared_ptr<EventMap> eventMap;
		void onKeyPressed(const std::unique_ptr<Event>& event)
		{
			KeyPressEvent* keyPressEvent = static_cast<KeyPressEvent*>(event.get());
			for (auto entity: GetSystemEntities())
			{
				const auto keyboardcontrol = entity->GetComponent<KeyBoardControlledComponent>();
				auto& sprite = entity->GetComponent<SpriteComponent>();
				auto& rigidbody = entity->GetComponent<RigidBodyComponent>();
				
				switch (keyPressEvent->symbol)
				{
					case SDLK_UP:
						rigidbody.velocity = keyboardcontrol.upVelocity;
						sprite.srcRect.y = sprite.height * 0;
						break;
					case SDLK_RIGHT:
						rigidbody.velocity = keyboardcontrol.rightVelocity;
						sprite.srcRect.y = sprite.height * 1;
						break;
					case SDLK_DOWN:
						rigidbody.velocity = keyboardcontrol.downVelocity;
						sprite.srcRect.y = sprite.height * 2;
						break;
					case SDLK_LEFT:
						rigidbody.velocity = keyboardcontrol.leftVelocity;
						sprite.srcRect.y = sprite.height * 3;
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
				for (const auto& event : it->second)
				{
					onKeyPressed(event);
				}
			}
		}
};
#endif
