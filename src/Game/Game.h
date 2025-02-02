#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../AssetStore/AssetStore.h"
#include "../EventBus/EventBus.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/CollisionDebug.h"
#include "../Systems/DamageSystem.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
	private:
		bool isRunning;
		bool isDebugMode;
		SDL_Window* window;
		int millisecsPreviousFrame = 0;
		SDL_Renderer* renderer;
		
		std::unique_ptr<Registry> registry;
		std::unique_ptr<AssetStore> assetStore;
		std::unique_ptr<EventBus> eventBus;
	public:
		Game();
		~Game();
		void Initialize();
		void Run();
		void ProcessInput();
		void LoadLevel(int level);
		void Setup();
		void Update();
		void Render();
		void Destroy();
	
		int windowWidth;
		int windowHeight;
};

#endif
