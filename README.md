# Warhammer: A Game Built on a Custom Game Engine

**Warhammer** is a fast-paced **game** developed using a **custom game engine** built from scratch using an **Entity-Component-System (ECS)** architecture. The game is designed to showcase how this engine operates, and it features dynamic gameplay where players must clear the map of enemy entities that are actively shooting at them.

This project is primarily focused on the **game engine** itself, highlighting the use of an ECS architecture for efficient management of game entities and interactions. Warhammer is a demonstration of how to build a game using this custom engine, but the engine is flexible enough to be used for a wide variety of games.

## Features
- **Entity-Component-System (ECS)**: The game engine is built on an ECS design, where entities are combined with components, and systems manage the behavior of entities.
- **Custom Game Engine**: Warhammer is built using a custom game engine developed in **C++** with **Lua** for level scripting. The engine offers high flexibility and scalability.
- **Dynamic Gameplay**: The gameplay involves clearing the map, where multiple enemy entities are shooting at the player. As the player navigates the map, they must strategically avoid enemies while shooting back to eliminate threats.
- **Cross-Platform**: The engine and game are designed to work on both **Windows** and **Linux** platforms.
- **Lua for Level Scripting**: Game levels are designed using Lua scripts, providing an easy way to dynamically create and modify levels.
- **Customizability**: The game engine is designed to be modular, with an emphasis on flexibility. You can create new components, systems, and game mechanics easily.
- **Asset Management**: The engine manages assets like textures and sound files, which can be easily referenced in Lua scripts.
- **Performance**: The engine is optimized for real-time performance, making it suitable for games with many interactive entities.  
- **Debug Mode (ImGui)**: Users can enter debug mode by pressing the D key, enabling them to see hitboxes and spawn enemies while the game is running for testing and experimentation.   
  
## About the Game Engine

The **Warhammer Game Engine** is a custom-built engine designed to provide flexibility and scalability for real-time games. At its core, the engine uses the **Entity-Component-System (ECS)** design pattern, which separates the data (components), the entities (game objects), and the logic (systems) to ensure that the game runs efficiently, even with large numbers of interactive objects.

### What is ECS?

**Entity-Component-System (ECS)** is a software architecture pattern used in game development that separates game objects into three distinct categories:

- **Entities**: Unique identifiers for game objects (such as a player, an enemy, or a bullet).
- **Components**: Data containers that hold specific information about an entity (like position, velocity, health, etc.).
- **Systems**: Logic that operates on entities with specific components (such as a movement system that processes entities with a position and velocity component).

By using ECS, the game engine is able to efficiently handle complex interactions and a large number of entities without sacrificing performance. The modular design also makes it easier to extend and modify the engine as needed.

---

## Level Design and Lua Scripting

The game engine provides an easy way to create and modify levels through **Lua scripting**. Lua is a lightweight scripting language that allows developers to define game logic, entities, and behaviors dynamically.

### Example: Level 1 Lua Script

```lua
Level = {
    assets = {
        { type = "texture", id = "jungle-tilemap", file = "../assets/tilemaps/jungle.png" },
        { type = "texture", id = "chopper-texture", file = "../assets/images/chopper-spritesheet.png" },
        -- More assets as needed
    },
    tilemap = {
        map_file = "../assets/tilemaps/jungle.map",
        texture_asset_id = "jungle-tilemap",
        tile_size = 32,
        scale = 3.0
    },
    entities = {
        {
            tag = "player",
            components = {
                transform = { position = {x = 355, y = 160}, scale = {x = 2.0, y = 2.0}, rotation = 0.0 },
                rigidbody = { velocity = {x = 0.0, y = 0.0} },
                sprite = { texture_asset_id = "chopper-texture", width = 32, height = 32, z_index = 2 },
                animation = { num_frames = 2, speed_rate = 10 },
                health = { health_percentage = 100 },
                -- More components as needed
            }
        },
        -- More entities as needed
    }
}
```
### Example: Level 2 (Day-Night Cycle)
```lua
local current_system_hour = os.date("*t").hour
local map_texture_asset_id = current_system_hour >= 9 and current_system_hour <= 18 and "tilemap-texture-day" or "tilemap-texture-night"

Level = {
    assets = {
        { type = "texture", id = "tilemap-texture-day", file = "../assets/tilemaps/jungle-day.png" },
        { type = "texture", id = "chopper-texture", file = "../assets/images/chopper-green-spritesheet.png" },
        -- More assets as needed
    },
    tilemap = {
        map_file = "../assets/tilemaps/jungle.map",
        texture_asset_id = map_texture_asset_id,
        tile_size = 32,
        scale = 3.0
    },
    entities = {
        {
            tag = "player",
            components = {
                transform = { position = {x = 355, y = 160}, scale = {x = 2.0, y = 2.0}, rotation = 0.0 },
                sprite = { texture_asset_id = "chopper-texture", width = 32, height = 32, z_index = 4 },
                -- More components as needed
            }
        },
        -- More entities as needed
    }
}
```

This example demonstrates how you can change the level dynamically based on the time of day, adding a day-night cycle effect to the map.
This Lua script defines the first level of the game, including the assets (textures), the tilemap, and the player entity, along with its various components such as transform, sprite, and health.

---

## Game Description

In **Warhammer**, players are tasked with **clearing the map** of enemy entities that are actively shooting at them. The game uses a combination of **ECS** for entity management, **C++** for performance, and **Lua** for level scripting, allowing the creation of complex interactions and dynamic levels.

The gameplay requires strategic thinking as players navigate the map, avoid enemy fire, and eliminate enemy entities to succeed. The engine also allows for easy modification and extension, so you can create entirely new gameplay experiences with the same underlying framework.

---

## Controls

- **Arrow Keys**: Move the player character (up, down, left, right).
- **Spacebar**: Shoot projectiles.
- **Health**: The player has a health bar. Once your health reaches 0, you lose the game.
---
## Debug Mode (ImGui)

To help with testing and experimentation, the game includes a debug mode accessible by pressing the *D* key while playing. Once in debug mode, you can see the hitboxes of the player and entities and spawn enemies dynamically in the game world as the game is running. This is useful for testing different enemy configurations, behaviors, or creating custom scenarios.

The ImGui interface allows for easy interaction with the game, making it simple to modify the game world and spawn enemies on the fly.

---

## Building and Running the Game

Since **Warhammer** is released as a fully compiled game, you can simply download and run the pre-compiled version for your platform.

### On Windows

1. **Download** the Windows version of the game from the release section.
2. **Extract** the files to a directory of your choice.
3. Run `gameengine.exe` to start playing.

### On Linux

1. **Download** the Linux version of the game from the release section.
2. **Extract** the files to a directory of your choice.
3. Run the following in your terminal:
   ```bash
   ./gameengine
   ```
---
## Create Your Own Levels

The Warhammer Game Engine is designed to be flexible, and we encourage users to create and share their own levels. Since levels are defined using Lua scripting, creating a custom level is as simple as editing the Lua files.  
  
**How to Contribute:**
- Create a New Level: Modify or create your own Lua scripts to define new levels.
- Share Your Level: Push your levels to the repository.
- Review and Merge: If your level is well-crafted and aligns with the project’s goals, it will be considered for merging into the main project.

---

## Demo


https://github.com/user-attachments/assets/aba24a71-0471-4db6-bbd4-7dcecb1633c3


---

