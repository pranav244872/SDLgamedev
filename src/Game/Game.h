#ifndef GAME_H
#define GAME_H

#include "../AssetStore/AssetStore.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/KeyBoardControlledComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/TextLabelComponent.h"
#include "../ECS/ECS.h"
#include "../Events/Event.h"
#include "../Logger/Logger.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/CollisionDebug.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/ProjectileEmitSystem.h"
#include "../Systems/ProjectileLifecycleSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../Systems/RenderHealthStatus.h"
#include "../Systems/RenderGUISystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <imgui/imgui_impl_sdl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <sol/sol.hpp>

typedef std::unordered_map<std::type_index, std::vector<std::unique_ptr<Event>>>
    EventMap;

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
    private:
        bool isRunning;
        bool isDebugMode;
        SDL_Window *window;
        int millisecsPreviousFrame = 0;
        SDL_Renderer *renderer;
        SDL_Rect camera;

		sol::state lua;

        std::unique_ptr<Registry> registry;
        std::unique_ptr<AssetStore> assetStore;
        std::shared_ptr<EventMap> events;

    public:
        static int windowWidth;
        static int windowHeight;
        static int mapWidth;
        static int mapHeight;
        Game();
        ~Game();
        void Initialize();
        void Run();
        void ProcessInput();
        void Setup();
        void Update();
        void Render();
        void Destroy();
};

#endif
