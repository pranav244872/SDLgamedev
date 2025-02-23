#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>
#include <sol/sol.hpp>

class LevelLoader
{
	private:
		std::vector<std::vector<int>> ParseTilemapFile(const std::string &filePath);
		void CreateTileEntities
		(
			std::unique_ptr<Registry> &registry,
			const std::vector<std::vector<int>> &tilemap,
			std::string textureAssetId,
			int scale,
			int tileSize
		);

	public:
		LevelLoader();
		~LevelLoader();

		void LoadLevel
		(
			sol::state& lua,
			std::unique_ptr<Registry>& registry,
			std::unique_ptr<AssetStore>& assetStore,
			SDL_Renderer* renderer, int levelNumber
		);
};

#endif
