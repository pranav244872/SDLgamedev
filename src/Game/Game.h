#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

const int FPS = 30;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
	private:
		bool isRunning;
		SDL_Window* window;
		int millisecsPreviousFrame = 0;
		SDL_Renderer* renderer;
		
		std::unique_ptr<Registry> registry;
		std::unique_ptr<AssetStore> assetStore;
	public:
		Game();
		~Game();
		void Initialize();
		void Run();
		void ProcessInput();
		void Setup();
		void Update();
		void Render();
		void Destroy();
	
		int windowWidth;
		int windowHeight;
};

#endif
