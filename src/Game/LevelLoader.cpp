#include "./LevelLoader.h"
#include "../Game/Game.h"
#include <fstream>
#include <string>

std::vector<std::vector<int>> LevelLoader::ParseTilemapFile
(
	const std::string &filePath
)
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

void LevelLoader::CreateTileEntities
(
	 std::unique_ptr<Registry> &registry,
	 const std::vector<std::vector<int>> &tilemap, 
	 std::string textureAssetId,
	 int scale, 
	 int tileSize
)
{
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

            tile->AddComponent<TransformComponent>
			(
                glm::vec2(transformPosX * scale, transformPosY * scale),
                glm::vec2(scale, scale), 0.0f
            );

            tile->AddComponent<SpriteComponent>
			(
                textureAssetId, tileSize, tileSize, sourceX, sourceY, -1, false
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

LevelLoader::LevelLoader()
{
	Logger::Log("LevelLoader Constructor called!");
}

LevelLoader::~LevelLoader()
{
	Logger::Log("LevelLoader Destructor called!");
}

void LevelLoader::LoadLevel
(
    sol::state& lua,
    std::unique_ptr<Registry>& registry,
    std::unique_ptr<AssetStore>& assetStore,
    SDL_Renderer* renderer, int levelNumber
)
{
    ////////////////////////////////////////////////////////////////////////////////
    // Load and validate the Lua script
    ////////////////////////////////////////////////////////////////////////////////
    std::string scriptPath = "../assets/scripts/Level" + std::to_string(levelNumber) + ".lua";
    Logger::Log("Loading Lua script: " + scriptPath);

    sol::load_result script = lua.load_file(scriptPath);
    if (!script.valid())
    {
        sol::error err = script;
        std::string errorMessage = err.what();
        Logger::Err("Error loading the Lua script: " + errorMessage);
        return;
    }

    // Execute the Lua script
    lua.script_file(scriptPath);
    Logger::Log("Lua script executed successfully: " + scriptPath);

    ////////////////////////////////////////////////////////////////////////////////
    // Read the level table
    ////////////////////////////////////////////////////////////////////////////////
    sol::table level = lua["Level"];
    if (!level.valid())
    {
        Logger::Err("Level table not found in Lua script");
        return;
    }
    Logger::Log("Level table loaded successfully");

    ////////////////////////////////////////////////////////////////////////////////
    // Read the level assets
    ////////////////////////////////////////////////////////////////////////////////
    sol::table assets = level["assets"];
    if (!assets.valid())
    {
        Logger::Err("Assets table not found in Level table");
    }
    else
    {
        Logger::Log("Assets table found with " + std::to_string(assets.size() + 1) + " entries");

        for (size_t i = 0; i < assets.size() + 1; i++)
        {
            sol::optional<sol::table> asset = assets[i];
            if (asset == sol::nullopt)
            {
                Logger::Err("Asset at index " + std::to_string(i) + " is missing or invalid");
                continue;
            }

            std::string assetType = asset.value()["type"];
            std::string assetId = asset.value()["id"];
            Logger::Log("Processing asset: id = " + assetId + ", type = " + assetType);

            if (assetType == "texture")
            {
                std::string filePath = asset.value()["file"];
                assetStore->AddTexture(renderer, assetId, filePath);
                Logger::Log("Added texture to asset store: id = " + assetId + ", file = " + filePath);
            }
            else if (assetType == "font")
            {
                std::string filePath = asset.value()["file"];
                int fontSize = asset.value()["font_size"];
                assetStore->AddFont(assetId, filePath, fontSize);
                Logger::Log("Added font to asset store: id = " + assetId + ", file = " + filePath + ", size = " + std::to_string(fontSize));
            }
            else
            {
                Logger::Err("Unknown asset type: " + assetType);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    // Read the level tilemap information
    ////////////////////////////////////////////////////////////////////////////////
    sol::table tilemapTable = level["tilemap"];
    if (!tilemapTable.valid())
    {
        Logger::Err("Tilemap table not found in Level table");
    }
    else
    {
        std::string mapPath = tilemapTable["map_file"];
        Logger::Log("Loading tilemap from file: " + mapPath);

        auto tilemap = ParseTilemapFile(mapPath);
        if (tilemap.empty())
        {
            Logger::Err("Tilemap is empty or could not be parsed");
        }
        else
        {
            std::string tilemapAssetId = tilemapTable["texture_asset_id"];
            double scale = tilemapTable["scale"];
            int tileSize = tilemapTable["tile_size"];
            Logger::Log("Creating tile entities with assetId = " + tilemapAssetId + ", scale = " + std::to_string(scale) + ", tileSize = " + std::to_string(tileSize));

            CreateTileEntities(registry, tilemap, tilemapAssetId, scale, tileSize);
            Logger::Log("Tile entities created successfully");
        }
    }
	
    ////////////////////////////////////////////////////////////////////////////////
    // Read the level entities and components
    ////////////////////////////////////////////////////////////////////////////////
    sol::table entities = level["entities"];
    if (!entities.valid())
    {
        Logger::Err("Entities table not found in Level table");
    }
    else
    {
        Logger::Log("Entities table found with " + std::to_string(entities.size() + 1) + " entries");

        for (size_t i = 0; i < entities.size() + 1; i++)
        {
            sol::optional<sol::table> entity = entities[i];
            if (entity == sol::nullopt)
            {
                Logger::Err("Entity at index " + std::to_string(i) + " is missing or invalid");
                continue;
            }

            std::shared_ptr<Entity> newEntity = registry->CreateEntity();
            Logger::Log("Created entity with id = " + std::to_string(newEntity->getId()));

            // Tag
            sol::optional<std::string> tag = entity.value()["tag"];
            if (tag != sol::nullopt)
            {
                newEntity->Tag(tag.value());
                Logger::Log("Added tag to entity: " + tag.value());
            }

            // Group
            sol::optional<std::string> group = entity.value()["group"];
            if (group != sol::nullopt)
            {
                newEntity->Group(group.value());
                Logger::Log("Added group to entity: " + group.value());
            }

            // Components
            sol::optional<sol::table> components = entity.value()["components"];
            if (components != sol::nullopt)
            {
                Logger::Log("Processing components for entity " + std::to_string(newEntity->getId()));

                // Transform
                sol::optional<sol::table> transform = components.value()["transform"];
                if (transform != sol::nullopt)
                {
                    double posX = transform.value()["position"]["x"];
                    double posY = transform.value()["position"]["y"];
                    double scaleX = transform.value()["scale"]["x"].get_or(1.0);
                    double scaleY = transform.value()["scale"]["y"].get_or(1.0);
                    double rotation = transform.value()["rotation"].get_or(0.0);

                    newEntity->AddComponent<TransformComponent>(glm::vec2(posX, posY), glm::vec2(scaleX, scaleY), rotation);
                    Logger::Log("Added TransformComponent: pos = (" + std::to_string(posX) + ", " + std::to_string(posY) + "), scale = (" + std::to_string(scaleX) + ", " + std::to_string(scaleY) + "), rotation = " + std::to_string(rotation));
                }

                // RigidBody
                sol::optional<sol::table> rigidbody = components.value()["rigidbody"];
                if (rigidbody != sol::nullopt)
                {
                    double velX = rigidbody.value()["velocity"]["x"];
                    double velY = rigidbody.value()["velocity"]["y"];

                    newEntity->AddComponent<RigidBodyComponent>(glm::vec2(velX, velY));
                    Logger::Log("Added RigidBodyComponent: velocity = (" + std::to_string(velX) + ", " + std::to_string(velY) + ")");
                }

                // Sprite
                sol::optional<sol::table> sprite = components.value()["sprite"];
                if (sprite != sol::nullopt)
                {
                    std::string textureAssetId = sprite.value()["texture_asset_id"];
                    int width = sprite.value()["width"];
                    int height = sprite.value()["height"];
                    int zIndex = sprite.value()["z_index"].get_or(1);
                    bool fixed = sprite.value()["fixed"].get_or(false);
                    int srcRectX = sprite.value()["src_rect_x"].get_or(0);
                    int srcRectY = sprite.value()["src_rect_y"].get_or(0);

                    newEntity->AddComponent<SpriteComponent>(textureAssetId, width, height, srcRectX, srcRectY, zIndex, fixed);
                    Logger::Log("Added SpriteComponent: textureAssetId = " + textureAssetId + ", width = " + std::to_string(width) + ", height = " + std::to_string(height) + ", zIndex = " + std::to_string(zIndex) + ", fixed = " + std::to_string(fixed) + ", srcRect = (" + std::to_string(srcRectX) + ", " + std::to_string(srcRectY) + ")");
                }

                // Animation
                sol::optional<sol::table> animation = components.value()["animation"];
                if (animation != sol::nullopt)
                {
                    int numFrames = animation.value()["num_frames"].get_or(1);
                    int speedRate = animation.value()["speed_rate"].get_or(1);

                    newEntity->AddComponent<AnimationComponent>(numFrames, speedRate);
                    Logger::Log("Added AnimationComponent: numFrames = " + std::to_string(numFrames) + ", speedRate = " + std::to_string(speedRate));
                }

                // BoxCollider
                sol::optional<sol::table> collider = components.value()["boxcollider"];
                if (collider != sol::nullopt)
                {
                    int width = collider.value()["width"];
                    int height = collider.value()["height"];
                    double offsetX = collider.value()["offset"]["x"].get_or(0.0);
                    double offsetY = collider.value()["offset"]["y"].get_or(0.0);

                    newEntity->AddComponent<BoxColliderComponent>(width, height, glm::vec2(offsetX, offsetY));
                    Logger::Log("Added BoxColliderComponent: width = " + std::to_string(width) + ", height = " + std::to_string(height) + ", offset = (" + std::to_string(offsetX) + ", " + std::to_string(offsetY) + ")");
                }

                // Health
                sol::optional<sol::table> health = components.value()["health"];
                if (health != sol::nullopt)
                {
                    int healthPercentage = health.value()["health_percentage"].get_or(100);

                    newEntity->AddComponent<HealthComponent>(healthPercentage);
                    Logger::Log("Added HealthComponent: healthPercentage = " + std::to_string(healthPercentage));
                }

                // ProjectileEmitter
                sol::optional<sol::table> projectileEmitter = components.value()["projectile_emitter"];
                if (projectileEmitter != sol::nullopt)
                {
                    double velX = projectileEmitter.value()["projectile_velocity"]["x"];
                    double velY = projectileEmitter.value()["projectile_velocity"]["y"];
                    int repeatFrequency = projectileEmitter.value()["repeat_frequency"].get_or(1) * 1000;
                    int projectileDuration = projectileEmitter.value()["projectile_duration"].get_or(10) * 1000;
                    int hitPercentageDamage = projectileEmitter.value()["hit_percentage_damage"].get_or(10);
                    bool friendly = projectileEmitter.value()["friendly"].get_or(false);

                    newEntity->AddComponent<ProjectileEmitterComponent>(glm::vec2(velX, velY), repeatFrequency, projectileDuration, hitPercentageDamage, friendly);
                    Logger::Log("Added ProjectileEmitterComponent: velocity = (" + std::to_string(velX) + ", " + std::to_string(velY) + "), repeatFrequency = " + std::to_string(repeatFrequency) + ", projectileDuration = " + std::to_string(projectileDuration) + ", hitPercentageDamage = " + std::to_string(hitPercentageDamage) + ", friendly = " + std::to_string(friendly));
                }

                // CameraFollow
                sol::optional<sol::table> cameraFollow = components.value()["camera_follow"];
                if (cameraFollow != sol::nullopt)
                {
                    newEntity->AddComponent<CameraFollowComponent>();
                    Logger::Log("Added CameraFollowComponent");
                }

                // KeyboardControlled
                sol::optional<sol::table> keyboardControlled = components.value()["keyboard_controller"];
                if (keyboardControlled != sol::nullopt)
                {
                    double upVelX = keyboardControlled.value()["up_velocity"]["x"];
                    double upVelY = keyboardControlled.value()["up_velocity"]["y"];
                    double rightVelX = keyboardControlled.value()["right_velocity"]["x"];
                    double rightVelY = keyboardControlled.value()["right_velocity"]["y"];
                    double downVelX = keyboardControlled.value()["down_velocity"]["x"];
                    double downVelY = keyboardControlled.value()["down_velocity"]["y"];
                    double leftVelX = keyboardControlled.value()["left_velocity"]["x"];
                    double leftVelY = keyboardControlled.value()["left_velocity"]["y"];

                    newEntity->AddComponent<KeyBoardControlledComponent>(
                        glm::vec2(upVelX, upVelY),
                        glm::vec2(rightVelX, rightVelY),
                        glm::vec2(downVelX, downVelY),
                        glm::vec2(leftVelX, leftVelY)
                    );
                    Logger::Log("Added KeyBoardControlledComponent: upVel = (" + std::to_string(upVelX) + ", " + std::to_string(upVelY) + "), rightVel = (" + std::to_string(rightVelX) + ", " + std::to_string(rightVelY) + "), downVel = (" + std::to_string(downVelX) + ", " + std::to_string(downVelY) + "), leftVel = (" + std::to_string(leftVelX) + ", " + std::to_string(leftVelY) + ")");
                }

				// Script
				sol::optional<sol::table> script = components.value()["on_update_script"];
				if (script != sol::nullopt)
				{
					sol::function func = components.value()["on_update_script"][0];
					newEntity->AddComponent<ScriptComponent>(func);
				}
            }
        }
    }
}
