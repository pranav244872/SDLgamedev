-- Load a different tilemap image depending on the current system time
local current_system_hour = os.date("*t").hour

local map_texture_asset_id

if current_system_hour  >= 9 and current_system_hour <= 18 then
		map_texture_asset_id = "tilemap-texture-day"
else
		map_texture_asset_id = "tilemap-texture-night"
end

-- Define a table with the start values of the first level
Level = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] =
        { type = "texture", id = "tilemap-texture-night",             file = "/home/pranav/del/SDLgamedev/assets/tilemaps/jungle-night.png" },
        { type = "texture", id = "tilemap-texture-day",             file = "/home/pranav/del/SDLgamedev/assets/tilemaps/jungle-night.png" },
        { type = "texture", id = "chopper-texture",             file = "/home/pranav/del/SDLgamedev/assets/images/chopper-green-spritesheet.png" },
        { type = "texture", id = "su27-texture",                file = "/home/pranav/del/SDLgamedev/assets/images/su27-spritesheet.png" },
        { type = "texture", id = "f22-texture",                 file = "/home/pranav/del/SDLgamedev/assets/images/f22-spritesheet.png" },
        { type = "texture", id = "fw190-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/fw190-spritesheet.png" },
        { type = "texture", id = "upf7-texture",                file = "/home/pranav/del/SDLgamedev/assets/images/upf7-spritesheet.png" },
        { type = "texture", id = "bf109-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/bf109-spritesheet.png" },
        { type = "texture", id = "bomber-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/bomber-spritesheet.png" },
        { type = "texture", id = "carrier-texture",             file = "/home/pranav/del/SDLgamedev/assets/images/carrier.png" },
        { type = "texture", id = "boat-texture",                file = "/home/pranav/del/SDLgamedev/assets/images/boat.png" },
        { type = "texture", id = "tank-tiger-up-texture",       file = "/home/pranav/del/SDLgamedev/assets/images/tank-tiger-up.png" },
        { type = "texture", id = "tank-tiger-right-texture",    file = "/home/pranav/del/SDLgamedev/assets/images/tank-tiger-right.png" },
        { type = "texture", id = "tank-tiger-down-texture",     file = "/home/pranav/del/SDLgamedev/assets/images/tank-tiger-down.png" },
        { type = "texture", id = "tank-tiger-left-texture",     file = "/home/pranav/del/SDLgamedev/assets/images/tank-tiger-left.png" },
        { type = "texture", id = "tank-tiger-killed-texture",   file = "/home/pranav/del/SDLgamedev/assets/images/tank-tiger-killed.png" },
        { type = "texture", id = "tank-panther-up-texture",     file = "/home/pranav/del/SDLgamedev/assets/images/tank-panther-up.png" },
        { type = "texture", id = "tank-panther-right-texture",  file = "/home/pranav/del/SDLgamedev/assets/images/tank-panther-right.png" },
        { type = "texture", id = "tank-panther-down-texture",   file = "/home/pranav/del/SDLgamedev/assets/images/tank-panther-down.png" },
        { type = "texture", id = "tank-panther-left-texture",   file = "/home/pranav/del/SDLgamedev/assets/images/tank-panther-left.png" },
        { type = "texture", id = "tank-panther-killed-texture", file = "/home/pranav/del/SDLgamedev/assets/images/tank-panther-killed.png" },
        { type = "texture", id = "truck-ford-up-texture",       file = "/home/pranav/del/SDLgamedev/assets/images/truck-ford-up.png" },
        { type = "texture", id = "truck-ford-right-texture",    file = "/home/pranav/del/SDLgamedev/assets/images/truck-ford-right.png" },
        { type = "texture", id = "truck-ford-down-texture",     file = "/home/pranav/del/SDLgamedev/assets/images/truck-ford-down.png" },
        { type = "texture", id = "truck-ford-left-texture",     file = "/home/pranav/del/SDLgamedev/assets/images/truck-ford-left.png" },
        { type = "texture", id = "truck-ford-killed-texture",   file = "/home/pranav/del/SDLgamedev/assets/images/truck-ford-killed.png" },
        { type = "texture", id = "army-walk-up-texture",        file = "/home/pranav/del/SDLgamedev/assets/images/army-walk-up.png" },
        { type = "texture", id = "army-walk-right-texture",     file = "/home/pranav/del/SDLgamedev/assets/images/army-walk-right.png" },
        { type = "texture", id = "army-walk-down-texture",      file = "/home/pranav/del/SDLgamedev/assets/images/army-walk-down.png" },
        { type = "texture", id = "army-walk-left-texture",      file = "/home/pranav/del/SDLgamedev/assets/images/army-walk-left.png" },
        { type = "texture", id = "army-walk-killed-texture",    file = "/home/pranav/del/SDLgamedev/assets/images/army-walk-killed.png" },
        { type = "texture", id = "army-gun-up-texture",         file = "/home/pranav/del/SDLgamedev/assets/images/army-gun-up.png" },
        { type = "texture", id = "army-gun-right-texture",      file = "/home/pranav/del/SDLgamedev/assets/images/army-gun-right.png" },
        { type = "texture", id = "army-gun-down-texture",       file = "/home/pranav/del/SDLgamedev/assets/images/army-gun-down.png" },
        { type = "texture", id = "army-gun-left-texture",       file = "/home/pranav/del/SDLgamedev/assets/images/army-gun-left.png" },
        { type = "texture", id = "army-gun-killed-texture",     file = "/home/pranav/del/SDLgamedev/assets/images/army-gun-killed.png" },
        { type = "texture", id = "sam-truck-right-texture",     file = "/home/pranav/del/SDLgamedev/assets/images/sam-truck-right.png" },
        { type = "texture", id = "sam-tank-left-texture",       file = "/home/pranav/del/SDLgamedev/assets/images/sam-tank-left-spritesheet.png" },
        { type = "texture", id = "sam-tank-right-texture",      file = "/home/pranav/del/SDLgamedev/assets/images/sam-tank-right-spritesheet.png" },
        { type = "texture", id = "takeoff-base-texture",        file = "/home/pranav/del/SDLgamedev/assets/images/takeoff-base.png" },
        { type = "texture", id = "landing-base-texture",        file = "/home/pranav/del/SDLgamedev/assets/images/landing-base.png" },
        { type = "texture", id = "runway-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/runway.png" },
        { type = "texture", id = "obstacles1-texture",          file = "/home/pranav/del/SDLgamedev/assets/images/obstacles-1.png" },
        { type = "texture", id = "obstacles2-texture",          file = "/home/pranav/del/SDLgamedev/assets/images/obstacles-2.png" },
        { type = "texture", id = "obstacles3-texture",          file = "/home/pranav/del/SDLgamedev/assets/images/obstacles-3.png" },
        { type = "texture", id = "obstacles4-texture",          file = "/home/pranav/del/SDLgamedev/assets/images/obstacles-4.png" },
        { type = "texture", id = "obstacles5-texture",          file = "/home/pranav/del/SDLgamedev/assets/images/obstacles-5.png" },
        { type = "texture", id = "obstacles6-texture",          file = "/home/pranav/del/SDLgamedev/assets/images/obstacles-6.png" },
        { type = "texture", id = "obstacles7-texture",          file = "/home/pranav/del/SDLgamedev/assets/images/obstacles-7.png" },
        { type = "texture", id = "tree1-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-1.png" },
        { type = "texture", id = "tree2-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-2.png" },
        { type = "texture", id = "tree3-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-3.png" },
        { type = "texture", id = "tree4-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-4.png" },
        { type = "texture", id = "tree5-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-5.png" },
        { type = "texture", id = "tree6-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-6.png" },
        { type = "texture", id = "tree7-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-7.png" },
        { type = "texture", id = "tree8-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-8.png" },
        { type = "texture", id = "tree9-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/tree-9.png" },
        { type = "texture", id = "tree10-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-10.png" },
        { type = "texture", id = "tree11-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-11.png" },
        { type = "texture", id = "tree12-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-12.png" },
        { type = "texture", id = "tree13-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-13.png" },
        { type = "texture", id = "tree14-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-14.png" },
        { type = "texture", id = "tree15-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-15.png" },
        { type = "texture", id = "tree16-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-16.png" },
        { type = "texture", id = "tree17-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-17.png" },
        { type = "texture", id = "tree18-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-18.png" },
        { type = "texture", id = "tree19-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-19.png" },
        { type = "texture", id = "tree20-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/tree-20.png" },
        { type = "texture", id = "bullet-texture",              file = "/home/pranav/del/SDLgamedev/assets/images/bullet.png" },
        { type = "texture", id = "radar-texture",               file = "/home/pranav/del/SDLgamedev/assets/images/radar-spritesheet.png" },
        { type = "font"   , id = "pico8-font-5",                file = "/home/pranav/del/SDLgamedev/assets/fonts/pico8.ttf", font_size = 5 },
        { type = "font"   , id = "pico8-font-10",               file = "/home/pranav/del/SDLgamedev/assets/fonts/pico8.ttf", font_size = 10 },
        { type = "font"	, id = "chariot-font", file = "/home/pranav/del/SDLgamedev/assets/fonts/charriot.ttf", font_size = 14 }
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    tilemap = {
        map_file = "/home/pranav/del/SDLgamedev/assets/tilemaps/jungle.map",
        texture_asset_id = map_texture_asset_id,
        num_rows = 20,
        num_cols = 25,
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
                    z_index = 4,
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
            -- Takeoff base
            components = {
                transform = {
                    position = { x = 355, y = 165 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "takeoff-base-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Landing base
            components = {
                transform = {
                    position = { x = 2084, y = 735},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "landing-base-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Radar UI animation
            group = "ui",
            components = {
                transform = {
                    position = { x = 10, y = 10 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "radar-texture",
                    width = 64,
                    height = 64,
                    z_index = 10,
                    fixed = true
                },
                animation = {
                    num_frames = 8,
                    speed_rate = 7 -- fps
                }
            }
        },
        {
            -- Runway
            components = {
                transform = {
                    position = { x = 1410, y = 58 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 270.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "runway-texture",
                    width = 21,
                    height = 191,
                    z_index = 0
                }
            }
        },
        {
            -- Runway
            components = {
                transform = {
                    position = { x = 705, y = 578 },
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "runway-texture",
                    width = 21,
                    height = 191,
                    z_index = 0
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform = {
                    position = { x = 300, y = 736},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-tiger-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
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
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 20,
                    friendly = false
                }
            }
        },
        {
            -- Tank 2
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1160, y = 225 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
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
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 3
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1160, y = 310 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-tiger-down-texture",
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
                    projectile_velocity = { x = 0, y = 200 },
                    projectile_duration = 3, -- seconds
                    repeat_frequency = 3, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 4
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1160, y = 395 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-left-texture",
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
                    projectile_velocity = { x = -200, y = 0 },
                    projectile_duration = 3, -- seconds
                    repeat_frequency = 3, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 5
            group = "enemies",
            components = {
                transform = {
                    position = { x = 780, y = 770 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-right-texture",
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
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 6
            group = "enemies",
            components = {
                transform = {
                    position = { x = 780, y = 835 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-left-texture",
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
                    projectile_velocity = { x = -200, y = 0 },
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 7
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1560, y = 260 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-right-texture",
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
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 4, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 8
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1735, y = 165 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-down-texture",
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
                    projectile_velocity = { x = 0, y = 200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 9
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2050, y = 165 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-down-texture",
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
                    projectile_velocity = { x = 0, y = 200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 10
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1905, y = 350 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-killed-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Tank 11
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1905, y = 400 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-left-texture",
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
                    projectile_velocity = { x = -200 , y = 0 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 12
            group = "enemies",
            components = {
                transform = {
                    position = { x = 755, y = 1005 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-tiger-down-texture",
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
                    projectile_velocity = { x = 0, y = 200 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 5, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 13
            group = "enemies",
            components = {
                transform = {
                    position = { x = 945, y = 960},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-tiger-left-texture",
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
                    projectile_velocity = { x = -200 , y = 0 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 14
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1050, y = 1005 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-tiger-right-texture",
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
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 15
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1600 , y = 1280 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0 , y = 0}
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 0, y = 100 },
                    projectile_duration = 4, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 16
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1160, y = 1005},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
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
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 17
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1200, y = 1005},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
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
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 18
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1240, y = 1005},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
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
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 19
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1280, y = 1005},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
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
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 20
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1495 , y = 660 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-up-texture",
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
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 21
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2250 , y = 1100 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-right-texture",
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
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 22
            group = "enemies",
            components = {
                transform = {
					position = { x = 2250 , y = 1200 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-tiger-left-texture",
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
                    projectile_velocity = { x = -200, y = 0 },
                    projectile_duration = 1, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 23
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2155, y = 420},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-tiger-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 6, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 0, y = 300 },
                    projectile_duration = 1, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 24
            group = "enemies",
            components = {
                transform = {
                    position = { x = 290, y = 1495},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-tiger-up-texture",
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
                    projectile_velocity = { x = 0, y = -200 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 25
            group = "enemies",
            components = {
                transform = {
                    position = { x = 150, y = 1685 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "tank-panther-down-texture",
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
                    projectile_velocity = { x = 0, y = 300 },
                    projectile_duration = 1, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                }
            }
        },
        {
            -- Tank 26
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2095 , y = 820},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-panther-killed-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                }
            }
        },
        {
            -- Truck 1
            group = "enemies",
            components = {
                transform = {
                    position = { x = 160, y = 985},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 0}
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 2
            group = "enemies",
            components = {
                transform = {
                    position = { x = 75, y = 1505 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
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
                }
            }
        },
        {
            -- Truck 3
            group = "enemies",
            components = {
                transform = {
                    position = { x = 145, y = 1505 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 32}
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 4
            group = "enemies",
            components = {
                transform = {
                    position = { x = 215, y = 1505 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
                boxcollider = {
                    width = 12,
                    height = 25,
                    offset = { x = 10, y = 2 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- Truck 5
            group = "enemies",
            components = {
                transform = {
                    position = { x = 740, y = 950},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
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
                }
            }
        },
        {
            -- Truck 6
            group = "enemies",
            components = {
                transform = {
                    position = { x = 790, y = 980},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-down-texture",
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
                }
            }
        },
        {
            -- Truck 7
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2000, y = 1280 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-up-texture",
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
                }
            }
        },
        {
            -- Truck 8
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2040, y = 1280 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-up-texture",
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
                }
            }
        },
        {
            -- Truck 9
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2080, y = 1280 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-up-texture",
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
                }
            }
        },
        {
            -- Truck 10
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2160, y = 685},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-left-texture",
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
                }
            }
        },
        {
            -- Truck 11
            group = "enemies",
            components = {
                transform = {
                    position = { x = 2160, y = 740 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "truck-ford-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 0 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- SAM Tank 1
            group = "enemies",
            components = {
                transform = {
                    position = { x = 745, y = 580},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-tank-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 2 -- fps
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
                    projectile_velocity = { x = -200, y = -200 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Tank 2
            group = "enemies",
            components = {
                transform = {
                    position = { x = 745, y = 640},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "sam-tank-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 2 -- fps
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
                    projectile_velocity = { x = -200, y = -200 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Tank 3
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1900, y = 300},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "sam-tank-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 2 -- fps
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
                    projectile_velocity = { x = -150, y = -125 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Tank 4
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1410, y = 835},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "sam-tank-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 2 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 32 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = -200, y = -120 },
                    projectile_duration = 1, -- seconds
                    repeat_frequency = 2, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 1
            group = "enemies",
            components = {
                transform = {
                    position = { x = 160, y = 1120},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
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
                    projectile_velocity = { x = 150, y = -150 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 2 
            group = "enemies",
            components = {
                transform = {
                    position = { x = 160, y = 1170},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
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
                    projectile_velocity = { x = 150, y = -150 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 3
            group = "enemies",
            components = {
                transform = {
                    position = { x = 160, y = 750},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
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
                    projectile_velocity = { x = 150, y = -170 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 4
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1690, y = 735},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
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
                    projectile_velocity = { x = 150, y = -170 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
            }
        },
        {
            -- SAM Truck 5
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1690, y = 775},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
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
                    projectile_velocity = { x = 150, y = -170 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
			}
        },
        {
            -- SAM Truck 5
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1690, y = 815},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "sam-truck-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
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
                    projectile_velocity = { x = 150, y = -170 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 5,
                    friendly = false
                }
			}
        },
        {
            -- Vegetation
            components = {
                transform = {
                    position = { x = 234, y = 746},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree6-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform = {
                    position = { x = 655, y = 606},
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree14-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform = {
                    position = { x = 1018, y = 738 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree17-texture",
                    width = 17,
                    height = 20,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform = {
                    position = { x = 1034, y = 738 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree17-texture",
                    width = 17,
                    height = 20,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform = {
                    position = { x = 1028, y = 745 },
                    scale = { x = 3.0, y = 3.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree18-texture",
                    width = 17,
                    height = 20,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform = {
                    position = { x = 1278, y = 528},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree10-texture",
                    width = 31,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform = {
                    position = { x = 1301, y = 621},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree10-texture",
                    width = 31,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Vegetation
            components = {
                transform = {
                    position = { x = 1276, y = 275},
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tree14-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform = {
                    position = { x = 669, y = 549 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform = {
                    position = { x = 685, y = 549 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform = {
                    position = { x = 527, y = 754},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 3
                },
            }
        },
        {
            -- Obstacles
            components = {
                transform = {
                    position = { x = 520, y = 745},
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "obstacles7-texture",
                    width = 16,
                    height = 16,
                    z_index = 2
                },
            }
        },
		{
            -- Army
            components = {
                transform = {
                    position = { x = 947, y = 569},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform = {
                    position = { x = 955, y = 652},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform = {
                    position = { x = 1018, y = 833},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-gun-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform = {
                    position = { x = 1332, y = 727},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-up-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform = {
                    position = { x = 943, y = 1196},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-down-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform = {
                    position = { x = 1495, y = 1144},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-walk-left-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Army
            components = {
                transform = {
                    position = { x = 278, y = 1662},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "army-gun-right-texture",
                    width = 32,
                    height = 32,
                    z_index = 1
                },
            }
        },
        {
            -- Boat
            components = {
                transform = {
                    position = { x = 267, y = 573},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 90.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "boat-texture",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Boat
            components = {
                transform = {
                    position = { x = 80, y = 790 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "boat-texture",
                    width = 21,
                    height = 126,
                    z_index = 1
                },
            }
        },
        {
            -- Carrier
            components = {
                transform = {
                    position = { x = 970, y = 150 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "carrier-texture",
                    width = 59,
                    height = 191,
                    z_index = 1
                },
            }
        },
        {
            -- Carrier
            components = {
                transform = {
                    position = { x = 300, y = 975 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "carrier-texture",
                    width = 59,
                    height = 191,
                    z_index = 1
                },
            }
        },
        {
            -- F-22 fighter jet
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1018, y = 265 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "f22-texture",
                    width = 32,
                    height = 32,
                    z_index = 4
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 32,
                    offset = { x = 0, y = 0}
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- SU-27 fighter jet
            group = "enemies",
            components = {
                transform = {
                    position = { x = 975, y = 300 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = -10.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = -5.5 , y = -35.0 }
                },
                sprite = {
                    texture_asset_id = "su27-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
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
                }
            }
        },
        {
            -- Bomber plane
            group = "enemies",
            components = {
                transform = {
                    position = { x = 571, y = 664},
                    scale = { x = 2.0, y = 2.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "bomber-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
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
                }
            }
        },
        {
            -- FW190 plane
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1000, y = 143 },
                    scale = { x = 2.0, y = 2.0 },
                    rotation = -90.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = -50.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "fw190-texture",
                    width = 32,
                    height = 32,
                    z_index = 6
                },
                animation = {
                    num_frames = 3,
                    speed_rate = 15 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 30,
                    offset = { x = 0, y = 0 }
                },
                health = {
                    health_percentage = 100
                }
            }
        },
        {
            -- UPF7 plane
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1052, y = 600},
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "upf7-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                }
            }
        },
        {
            -- UPF7 plane
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1112, y = 600},
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "upf7-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                }
            }
        },
        {
            -- UPF7 plane
            group = "enemies",
            components = {
                transform = {
                    position = { x = 1172, y = 600},
                    scale = { x = 1.5, y = 1.5 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "upf7-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                }
            }
        },
        {
            -- SU-27 fighter jet
            group = "enemies",
            components = {
                transform = {
                    position = { x = 317, y = 985 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = -50.0 }
                },
                sprite = {
                    texture_asset_id = "su27-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 32
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 0, y = -100 },
                    projectile_duration = 5, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                },
                on_update_script = {
                    [0] =
                    function(entity, delta_time, ellapsed_time)
                        -- this function makes the fighter jet move up and down the map shooting projectiles
                        local current_position_x, current_position_y = get_position(entity)
                        local current_velocity_x, current_velocity_y = get_velocity(entity)

                        -- if it reaches the top or the bottom of the map
                        if current_position_y < 10  or current_position_y > map_height - 32 then
                            set_velocity(entity, 0, current_velocity_y * -1); -- flip the entity y-velocity
                        else
                            set_velocity(entity, 0, current_velocity_y); -- do not flip y-velocity
                        end

                        -- set the transform rotation to match going up or down
                        if (current_velocity_y < 0) then
                            set_rotation(entity, 0) -- point up
                            set_projectile_velocity(entity, 0, -200) -- shoot projectiles up
                        else
                            set_rotation(entity, 180) -- point down
                            set_projectile_velocity(entity, 0, 200) -- shoot projectiles down
                        end
                    end
                }
            }
        },
        {
            -- F-22 fighter jet
            group = "enemies",
            components = {
                transform = {
                    position = { x = 10, y = 10 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 90.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "f22-texture",
                    width = 32,
                    height = 32,
                    z_index = 5
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 32
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 400, y = 0 },
                    projectile_duration = 1, -- secondsm
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 10,
                    friendly = false
                },
                on_update_script = {
                    [0] =
                    function(entity, delta_time, ellapsed_time)
                        -- change the position of the the airplane to follow a sine wave movement
                        local new_x = ellapsed_time * 0.09
                        local new_y = 200 + (math.sin(ellapsed_time * 0.001) * 50)
                        set_position(entity, new_x, new_y) -- set the new position
                    end
                }
            }
        }
    }
}

-- Define some useful global variables
map_width = Level.tilemap.num_cols * Level.tilemap.tile_size * Level.tilemap.scale
map_height = Level.tilemap.num_rows * Level.tilemap.tile_size * Level.tilemap.scale
