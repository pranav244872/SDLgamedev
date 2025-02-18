#include "Game.h"

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

    // Handle Key presses
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
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

// Parse the .map file into a 2D vector of tile numbers
std::vector<std::vector<int>> ParseTilemapFile(const std::string &filePath)
{
    std::vector<std::vector<int>> tilemap;
    std::ifstream file(filePath);

    if (!file)
    {
        Logger::Err("Unable to open the .map file: " + filePath);
        return tilemap; // Return empty if error occurs
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string number;
        std::vector<int> row;

        // Extract numbers separated by commas and convert to integers
        while (std::getline(ss, number, ','))
        {
            row.push_back(std::stoi(number));
        }

        tilemap.push_back(row);
    }
    file.close();
    return tilemap;
}

// Create entities for each tile in the map
void CreateTileEntities(
    std::unique_ptr<Registry> &registry,
    const std::vector<std::vector<int>> &tilemap, int scale
)
{
    int tileSize = 32;
    int transformPosX = 0;
    int transformPosY = 0;

    for (const auto &row : tilemap)
    {
        for (int num : row)
        {
            int sourceX = (num % 10) * tileSize;
            int sourceY = (num / 10) * tileSize;

            std::shared_ptr<Entity> tile = registry->CreateEntity();
			tile->Group("tile");
            tile->AddComponent<TransformComponent>(
                glm::vec2(transformPosX * scale, transformPosY * scale),
                glm::vec2(scale, scale), 0.0f
            );
            tile->AddComponent<SpriteComponent>(
                "jungle-tilemap", tileSize, tileSize, sourceX, sourceY, 0, false
            );

            transformPosX += tileSize; // Move to next tile in row
        }

        transformPosY += tileSize; // Move to next row
        transformPosX = 0;         // Reset X for next row

        int mapNumRows = tilemap.size();
        int mapNumCols = tilemap[0].size();
        Game::mapWidth = mapNumCols * tileSize * scale;
        Game::mapHeight = mapNumRows * tileSize * scale;
    }
}

void Game::LoadLevel(int level)
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

    // Adding assets to the asset store
    assetStore->AddTexture(
        renderer, "tank-image",
        "/home/pranav/del/SDLgamedev/assets/images/tank-tiger-left.png"
    );
    assetStore->AddTexture(
        renderer, "jungle-tilemap",
        "/home/pranav/del/SDLgamedev/assets/tilemaps/jungle.png"
    );
    assetStore->AddTexture(
        renderer, "chopper-image",
        "/home/pranav/del/SDLgamedev/assets/images/chopper-spritesheet.png"
    );
    assetStore->AddTexture(
        renderer, "radar-image",
        "/home/pranav/del/SDLgamedev/assets/images/radar.png"
    );
    assetStore->AddTexture(
        renderer, "truck-image",
        "/home/pranav/del/SDLgamedev/assets/images/truck-ford-right.png"
    );
    assetStore->AddTexture(
        renderer, "bullet-image",
        "/home/pranav/del/SDLgamedev/assets/images/bullet.png"
    );

    // create entities

    auto tilemap = ParseTilemapFile
	(
        "/home/pranav/del/SDLgamedev/assets/tilemaps/jungle.map"
    );
    if (!tilemap.empty())
    { // Only create entities if tilemap is valid
        CreateTileEntities(registry, tilemap, 3);
    }

    std::shared_ptr<Entity> chopper = registry->CreateEntity();
	chopper->Tag("player");
    chopper->AddComponent<TransformComponent>
	(
        glm::vec2(10.0, 500.0), glm::vec2(2.0, 2.0), 0.0
    );
    chopper->AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    chopper->AddComponent<SpriteComponent>
	("chopper-image", 32, 32, 0, 0, 2, false);
    chopper->AddComponent<AnimationComponent>(2, 20, true);
    chopper->AddComponent<KeyBoardControlledComponent>
	(
		glm::vec2(0, -150), glm::vec2(150, 0), glm::vec2(0, 150),
		glm::vec2(-150, 0)
	);
    chopper->AddComponent<CameraFollowComponent>();
    chopper->AddComponent<HealthComponent>(100);
	chopper->AddComponent<ProjectileEmitterComponent>
	(glm::vec2(200, 0), 1000, 10000, 10, true);

    std::shared_ptr<Entity> radar = registry->CreateEntity();
    radar->AddComponent<TransformComponent>
	(glm::vec2(windowWidth - 74, 10), glm::vec2(1.0, 1.0), 0.0);
    radar->AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
    radar->AddComponent<SpriteComponent>("radar-image", 64, 64, 0, 0, 3, true);
    radar->AddComponent<AnimationComponent>(8, 5, true);

    std::shared_ptr<Entity> tank = registry->CreateEntity();
	tank->Group("enemies");
    tank->AddComponent<TransformComponent>
	(glm::vec2(500.0, 30.0), glm::vec2(2.0, 2.0), 0.0);
    tank->AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0));
    tank->AddComponent<SpriteComponent>("tank-image", 32, 32, 0, 0, 1, false);
    tank->AddComponent<BoxColliderComponent>(32, 32, glm::vec2(0, 0));
    tank->AddComponent<HealthComponent>(100);
	tank->AddComponent<ProjectileEmitterComponent>
	(glm::vec2(200, 0), 1000, 10000, 10, false);

    std::shared_ptr<Entity> truck = registry->CreateEntity();
	truck->Group("enemies");
    truck->AddComponent<TransformComponent>	
	(glm::vec2(10.0, 30.0), glm::vec2(2.0, 2.0), 0.0);
    truck->AddComponent<RigidBodyComponent>(glm::vec2(0, 0));
    truck->AddComponent<SpriteComponent>("truck-image", 32, 32, 0, 0, 1, false);
    truck->AddComponent<BoxColliderComponent>(32, 32, glm::vec2(0, 0));
    truck->AddComponent<HealthComponent>(100);
	truck->AddComponent<ProjectileEmitterComponent>
	(glm::vec2(200, 0), 1000, 10000, 10, false);
}

void Game::Setup() { LoadLevel(1); }

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
    registry->GetSystem<MovementSystem>().Update(deltaTime, events);
    registry->GetSystem<CameraMovementSystem>().Update(
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
    registry->GetSystem<CollisionDebug>().Update(renderer, isDebugMode, camera);

    SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
