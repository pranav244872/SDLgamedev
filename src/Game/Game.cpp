#include "Game.h"
#include "LevelLoader.h"

int Game::windowWidth = 0;
int Game::windowHeight = 0;
int Game::mapWidth = 0;
int Game::mapHeight = 0;

Game::Game()
{
    isRunning = false;
    isDebugMode = false;
    registry = std::make_unique<Registry>();
    assetStore = std::make_unique<AssetStore>();
    events = std::make_shared<EventMap>();
    Logger::Log("Game Constructor Called");
}

Game::~Game() { Logger::Log("Game Destructor called"); }

void Game::Initialize()
{
    // If failed then Error
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Err("Error Initializing SDL.");
        return;
    }

	if (TTF_Init() != 0)
	{
		Logger::Err("Error Initializing SDL TTF");
		return;
	}

    // Here we are getting our computers display width and display height
    // through SDL function
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;
    window = SDL_CreateWindow(
        NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth,
        windowHeight, SDL_WINDOW_FULLSCREEN
    );
    if (!window)
    {
        Logger::Err("Error creating SDL window");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) { Logger::Err("Error creating SDL renderer"); }

	// Initialize the imgui context
	ImGui::CreateContext();
	ImGuiSDL::Initialize(renderer, windowWidth, windowHeight);
    // Initialize the camera view with the entire screen area
    camera.x = 0;
    camera.y = 0;
    camera.w = Game::windowWidth;
    camera.h = Game::windowHeight;
    isRunning = true;
}

void Game::Run()
{
    Setup();
    while (isRunning)
    {
        ProcessInput();
        Update();
        Render();
    }
}

// Checking for inputs
void Game::ProcessInput()
{

    // Clear all the key press events from previous frame
    auto it = events->find(typeid(KeyPressEvent));
    if (it != events->end())
    {
        it->second.clear();
        events->erase(it);
    }

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
		// ImGui SDL input
		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
		ImGuiIO& io = ImGui::GetIO();

		int mouseX, mouseY;
		const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

		io.MousePos = ImVec2(mouseX, mouseY);
		io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
		io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);

		// Handle core SDL events (close window, key pressed, etc.)
        switch (sdlEvent.type)
        {
			case SDL_QUIT: isRunning = false; break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) { isRunning = false; }
				else if (sdlEvent.key.keysym.sym == SDLK_d)
				{
					isDebugMode = !isDebugMode;
				}
				// Emit a key press event
				std::unique_ptr<KeyPressEvent> event =
					std::make_unique<KeyPressEvent>(sdlEvent.key.keysym.sym);
				(*events)[typeid(KeyPressEvent)].push_back(std::move(event));
				break;
        }
    }
}

void Game::Setup() 
{ 
    // Add the systems that need to be processed in our game
    registry->AddSystem<MovementSystem>();
    registry->AddSystem<RenderSystem>();
    registry->AddSystem<AnimationSystem>();
    registry->AddSystem<CollisionSystem>(events);
    registry->AddSystem<CollisionDebug>(events);
    registry->AddSystem<DamageSystem>(events);
    registry->AddSystem<KeyboardControlSystem>(events);
    registry->AddSystem<CameraMovementSystem>();
    registry->AddSystem<ProjectileEmitSystem>();
    registry->AddSystem<ProjectileLifecycleSystem>();
	registry->AddSystem<RenderTextSystem>();
	registry->AddSystem<RenderHealthStatus>();
	registry->AddSystem<RenderGUISystem>();

	// Load the first level
	LevelLoader loader;
	lua.open_libraries(sol::lib::base, sol::lib::math);
	loader.LoadLevel(lua, registry, assetStore, renderer, 2);

}

void Game::Update()
{
    // If we are too fast, waste some time until we reach the
    // MILLISECS_PER_FRAME
    int timeToWait =
        MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME)
    {
        SDL_Delay(timeToWait);
    }

    // The difference in ticks since the last frame, converted to seconds
    double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0f;

    // Store the current frame time
    millisecsPreviousFrame = SDL_GetTicks();

    // Perform the subscription of the events for all systems

    // Update the registry to process the entities that are waiting to be
    // created/deleted
    registry->Update();

    // Ask all the systems to update
    registry->GetSystem<KeyboardControlSystem>().Update();
    registry->GetSystem<MovementSystem>().Update
	(deltaTime, events, Game::mapWidth, Game::mapHeight);
    registry->GetSystem<CameraMovementSystem>().Update
	(
        camera, Game::mapWidth, Game::mapHeight, Game::windowWidth,
        Game::windowHeight
    );
    registry->GetSystem<ProjectileEmitSystem>().Update(registry, events);
    registry->GetSystem<AnimationSystem>().Update();
    registry->GetSystem<CollisionSystem>().Update();
    registry->GetSystem<ProjectileLifecycleSystem>().Update();
    registry->GetSystem<DamageSystem>().Update();
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Invoke all the systems that need to render
    registry->GetSystem<RenderSystem>().Update(renderer, assetStore, camera);
	registry->GetSystem<RenderTextSystem>().Update(renderer, assetStore, camera);
	registry->GetSystem<RenderHealthStatus>().Update(renderer, assetStore, camera);
    registry->GetSystem<CollisionDebug>().Update(renderer, isDebugMode, camera);
	if (isDebugMode)
	{
		registry->GetSystem<RenderGUISystem>().Update(registry, assetStore, camera);
	}

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	ImGuiSDL::Deinitialize();
	ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
