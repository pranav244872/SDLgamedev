#ifndef RENDERHEALTHSTATUS_H
#define RENDERHEALTHSTATUS_H

#include "../ECS/ECS.h"
#include <SDL2/SDL.h>
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../AssetStore/AssetStore.h"

class RenderHealthStatus : public System
{
public:
    // Constructor that ensures entities must have a HealthComponent
    RenderHealthStatus()
    {
        RequireComponent<HealthComponent>();
    }

    void Update(
        SDL_Renderer* renderer, // Renderer to draw on
        std::unique_ptr<AssetStore>& assetStore, // Asset store for fonts
        const SDL_Rect& camera // Camera viewport to handle rendering
    )
    {
        // Loop through all entities that require a HealthComponent
        for (auto entity : GetSystemEntities())
        {
            // Get the necessary components for rendering
            const auto& transform = entity->GetComponent<TransformComponent>();
            const auto& health = entity->GetComponent<HealthComponent>();

            // Determine the health bar color based on health percentage
            SDL_Color healthColor = GetHealthBarColor(health.healthPercentage);

            // Define the health bar dimensions, considering the camera offset
            SDL_Rect healthBar = GetHealthBarRect(transform, health, camera);

            // Render the health bar
            SDL_SetRenderDrawColor(renderer, healthColor.r, healthColor.g, healthColor.b, healthColor.a);
            SDL_RenderFillRect(renderer, &healthBar);

            // Render the health percentage text, considering the camera offset
            RenderHealthText(renderer, assetStore, transform, health, camera);
        }
    }

private:
    // Function to determine the color of the health bar based on the health percentage
    SDL_Color GetHealthBarColor(int healthPercentage) const
    {
        if (healthPercentage > 70)
        {
            return {0, 255, 0, 255}; // Green
        }
        else if (healthPercentage > 20)
        {
            return {255, 255, 0, 255}; // Yellow
        }
        else
        {
            return {255, 0, 0, 255}; // Red
        }
    }

    // Function to compute the dimensions of the health bar rectangle, considering camera offset
    SDL_Rect GetHealthBarRect(
        const TransformComponent& transform, const HealthComponent& health, const SDL_Rect& camera) const
    {
        // Health bar width is proportional to the health percentage
        int width = static_cast<int>((health.healthPercentage * 32 * transform.scale.x) / 100);
        int height = static_cast<int>(0.1 * 32 * transform.scale.y);

        // Apply camera offset for the x and y positions
        return {
            static_cast<int>(transform.position.x - camera.x),
            static_cast<int>(transform.position.y + (transform.scale.y * 32) - camera.y + 5),
            width,
            height
        };
    }

    // Function to render the health percentage text, considering camera offset
    void RenderHealthText(
        SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore, 
        const TransformComponent& transform, const HealthComponent& health, const SDL_Rect& camera) const
    {
        // Create the health percentage text
        std::string healthText = std::to_string(health.healthPercentage) + " %";

        // Choose the color for the text based on health
        SDL_Color textColor = GetHealthBarColor(health.healthPercentage);

        // Render the text to a surface and create a texture from it
        SDL_Surface* textSurface = TTF_RenderText_Blended(
            assetStore->GetFont("chariot-font"), healthText.c_str(), textColor);
        
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface); // Free the surface after creating the texture

        // Get the dimensions of the rendered text
        int labelWidth, labelHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &labelWidth, &labelHeight);

        // Define the destination rectangle for the text, considering camera offset
        SDL_Rect textRect = {
            static_cast<int>(transform.position.x - camera.x), 
            static_cast<int>(transform.position.y + (transform.scale.y * 32) - camera.y - 10),
            labelWidth,
            labelHeight
        };

        // Render the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        // Cleanup the texture after use
        SDL_DestroyTexture(textTexture);
    }
};

#endif
