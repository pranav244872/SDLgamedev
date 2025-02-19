#ifndef RENDERGUISYSTEM_H
#define RENDERGUISYSTEM_H

#include "../AssetStore/AssetStore.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <cmath>

class RenderGUISystem : public System {
public:
    RenderGUISystem() = default;

    void Update
	(
        const std::unique_ptr<Registry>& registry,
        const std::unique_ptr<AssetStore>& assetStore
    ) 
	{
        // Start new ImGui frame
        ImGui::NewFrame();

        if (ImGui::Begin("Spawn Enemies")) 
		{

            // ----- TransformComponent -----
            static int enemyXPos, enemyYPos;
			static int enemyXScale, enemyYScale, enemyAngleDegrees;
            if (ImGui::CollapsingHeader("TransformComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::InputInt("X Position", &enemyXPos);
                ImGui::InputInt("Y Position", &enemyYPos);
                ImGui::InputInt("X Scale", &enemyXScale);
                ImGui::InputInt("Y Scale", &enemyYScale);
                ImGui::SliderInt("Angle (degrees)", &enemyAngleDegrees, 0, 359);
            }

            // ----- RigidBodyComponent -----
            static int enemyVelX, enemyVelY;
            if (ImGui::CollapsingHeader("RigidBodyComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::InputInt("X Velocity", &enemyVelX);
                ImGui::InputInt("Y Velocity", &enemyVelY);
            }

            // ----- SpriteComponent -----
            static std::string enemySprite;
            static int enemySpriteWidth, enemySpriteHeight;
            static int enemySpriteSourceX, enemySpriteSourceY, enemySpriteZIndex;
            static int current_item = 0;
            if 
			(
				ImGui::CollapsingHeader
				("SpriteComponent", ImGuiTreeNodeFlags_DefaultOpen)
			) 
			{
                static const std::vector<std::string> textureNames 
					= assetStore->GetTextureNames();
                std::vector<const char*> textureNamesCStr;
                for (const auto& name : textureNames)
				{
                    textureNamesCStr.push_back(name.c_str());
                }
                if 
				(
					ImGui::Combo
					(
						"Select Texture", &current_item, textureNamesCStr.data(), 
						textureNames.size()
					)
				) 
				{
                    enemySprite = textureNames[current_item];
                }
                ImGui::InputInt("Sprite Width", &enemySpriteWidth);
                ImGui::InputInt("Sprite Height", &enemySpriteHeight);
                ImGui::InputInt("Sprite Source X", &enemySpriteSourceX);
                ImGui::InputInt("Sprite Source Y", &enemySpriteSourceY);
                ImGui::InputInt("Sprite zIndex", &enemySpriteZIndex);
            }

            // ----- BoxColliderComponent -----
            static int enemyColliderWidth, enemyColliderHeight;
            static int enemyColliderOffsetX, enemyColliderOffsetY;
            if (ImGui::CollapsingHeader("BoxColliderComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::InputInt("Collider Width", &enemyColliderWidth);
                ImGui::InputInt("Collider Height", &enemyColliderHeight);
                ImGui::InputInt("Collider Offset X", &enemyColliderOffsetX);
                ImGui::InputInt("Collider Offset Y", &enemyColliderOffsetY);
            }

            // ----- HealthComponent -----
            static int enemyHealth;
            if (ImGui::CollapsingHeader("HealthComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::InputInt("Health", &enemyHealth);
            }

            // ----- ProjectileEmitterComponent -----
            static int bulletSpeed;
            static int bulletIntervalSec, bulletLifetimeSec, bulletDamage;
            static const char* directions[] = { "Up", "Right", "Down", "Left" };
            static int currentDirection = 0;
            glm::vec2 bulletVelocity;

            if (ImGui::CollapsingHeader("ProjectileEmitterComponent", ImGuiTreeNodeFlags_DefaultOpen)) {
                ImGui::Combo("Bullet Direction", &currentDirection, directions, IM_ARRAYSIZE(directions));
                ImGui::InputInt("Bullet Speed", &bulletSpeed);
                ImGui::InputInt("Interval Between Bullets (sec)", &bulletIntervalSec);
                ImGui::InputInt("Bullet Lifetime (sec)", &bulletLifetimeSec);
                ImGui::InputInt("Bullet Damage", &bulletDamage);

                // Mapping direction to SDL coordinates
                switch (currentDirection) {
                    case 0: bulletVelocity = glm::vec2(0, -bulletSpeed); break; // Up
                    case 1: bulletVelocity = glm::vec2(bulletSpeed, 0); break;  // Right
                    case 2: bulletVelocity = glm::vec2(0, bulletSpeed); break;  // Down
                    case 3: bulletVelocity = glm::vec2(-bulletSpeed, 0); break; // Left
                }
            }

            // ----- Button: Create New Enemy -----
            if (ImGui::Button("Create New Enemy")) {
                std::shared_ptr<Entity> enemy = registry->CreateEntity();
                enemy->Group("enemies");
                enemy->AddComponent<TransformComponent>(
                    glm::vec2(enemyXPos, enemyYPos),
                    glm::vec2(enemyXScale, enemyYScale),
                    enemyAngleDegrees * (M_PI / 180.0f)
                );
                enemy->AddComponent<RigidBodyComponent>(
                    glm::vec2(enemyVelX, enemyVelY)
                );
                enemy->AddComponent<SpriteComponent>(
                    enemySprite,
                    enemySpriteWidth, enemySpriteHeight,
                    enemySpriteSourceX, enemySpriteSourceY,
                    enemySpriteZIndex, false
                );
                enemy->AddComponent<BoxColliderComponent>(
                    enemyColliderWidth, enemyColliderHeight,
                    glm::vec2(enemyColliderOffsetX, enemyColliderOffsetY)
                );
                enemy->AddComponent<HealthComponent>(enemyHealth);

                enemy->AddComponent<ProjectileEmitterComponent>(
                    bulletVelocity,
                    bulletIntervalSec * 1000,    // Convert sec to ms
                    bulletLifetimeSec * 1000,   // Convert sec to ms
                    bulletDamage,
                    false                       // Keep 5th param as is
                );
            }
        }

        ImGui::End();

        // Render ImGui frame
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
    }
};

#endif
