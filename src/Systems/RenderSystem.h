#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <SDL2/SDL.h>
#include "../ECS/ECS.h"
#include "../Logger/Logger.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../AssetStore/AssetStore.h"

class RenderSystem: public System
{
public:
	RenderSystem()
	{
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update
	(
		SDL_Renderer* renderer, 
		std::unique_ptr<AssetStore>& assetStore, 
		SDL_Rect& camera
	)
	{
		// Sort all the entities of our system by z-index
		struct RenderableEntity
		{

			TransformComponent transformComponent;
			SpriteComponent spriteComponent;
		};

		std::vector<RenderableEntity> renderableEntities;
		for (auto entity: GetSystemEntities())
		{
			RenderableEntity renderableEntity;
			renderableEntity.spriteComponent = 
				entity->GetComponent<SpriteComponent>();
			renderableEntity.transformComponent = 
				entity->GetComponent<TransformComponent>();

			// Bypass rendering entities if they are outside the camera view
			bool isEntityOutsideCameraView = 
			(
				renderableEntity.transformComponent.position.x + 
				( 
					renderableEntity.transformComponent.scale.x * 
					renderableEntity.spriteComponent.width
				) < camera.x ||
				renderableEntity.transformComponent.position.x 
				> camera.x + camera.w ||
				renderableEntity.transformComponent.position.y +
				( 
					renderableEntity.transformComponent.scale.y * 
					renderableEntity.spriteComponent.height
				) < camera.y ||
				renderableEntity.transformComponent.position.y 
				> camera.y + camera.h
			);
			
			// cull sprites that are outside the camera view (and are not fixed)
			if 
			(
				isEntityOutsideCameraView && 
				!renderableEntity.spriteComponent.isFixed
			) continue;

			renderableEntities.emplace_back(renderableEntity);  
		}

		std::stable_sort(renderableEntities.begin(), renderableEntities.end(),
			[](const RenderableEntity& a, const RenderableEntity& b)
			{
				return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
			}
		);

		// Loop all entities that the system is interested in
		for (auto entity: renderableEntities)
		{
			const auto transform = entity.transformComponent;
			const auto sprite = entity.spriteComponent;

			// Set the source rectangle of our original sprite texture
			SDL_Rect srcRect = sprite.srcRect;
			
			// Set the destination rectangle with the x, y position to be rendered
			SDL_Rect dstRect = 
			{
				static_cast<int>(transform.position.x - (sprite.isFixed ? 0 : camera.x)),
				static_cast<int>(transform.position.y - (sprite.isFixed ? 0 : camera.y)),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height * transform.scale.y),
			};
			
			SDL_RenderCopyEx
			(
				renderer, 
				assetStore->GetTexture(sprite.assetId),
				&srcRect,
				&dstRect,
				transform.rotation,
				nullptr,
				sprite.flip
			);
		}
	}
};
#endif
