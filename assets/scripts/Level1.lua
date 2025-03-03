-- Define a table with the values of the first level
Level = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] =
        { type = "texture", id = "jungle-tilemap", file = "../assets/tilemaps/jungle.png" },
        { type = "texture", id = "chopper-texture", file = "../assets/images/chopper-spritesheet.png" },
        { type = "texture", id = "tank-texture", file = "../assets/images/tank-tiger-right.png" },
        { type = "texture", id = "bullet-texture", file = "../assets/images/bullet.png" },
        { type = "font", id = "pico8-font-5", file = "../assets/fonts/pico8.ttf", font_size = 5 },
        { type = "font", id = "pico8-font-10", file = "../assets/fonts/pico8.ttf", font_size = 10 },
        { type = "font", id = "chariot-font", file = "../assets/fonts/charriot.ttf", font_size = 14 }
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    tilemap = {
        map_file = "../assets/tilemaps/jungle.map",
        texture_asset_id = "jungle-tilemap",
        tile_size = 32,
        scale = 3.0
    },

    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
        [0] =
        {
            -- Player
            tag = "player",
            components = {
                transform = {
                    position = { x = 355, y = 160 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "chopper-texture",
                    width = 32,
                    height = 32,
                    z_index = 2,
                    fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 0 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 200, y = 200 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 0, -- seconds
                    hit_percentage_damage = 10,
                    friendly = true
                },
                keyboard_controller = {
                    up_velocity = { x = 0, y = -150 },
                    right_velocity = { x = 150, y = 0 },
                    down_velocity = { x = 0, y = 150 },
                    left_velocity = { x = -150, y = 0 }
                },
                camera_follow = {
                    follow = true
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform = {
                    position = { x = 290, y = 735 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 0 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 200, y = 0 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        }
    }
}
