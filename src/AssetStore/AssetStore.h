#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "../Logger/Logger.h"

class AssetStore
{
private:
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;

public:
	AssetStore();
	~AssetStore();

	void ClearAssets();
	void AddTexture
	(
		SDL_Renderer* renderer, 
		const std::string& assetId, 
		const std::string& filePath
	);
	void AddFont
	(const std::string& assetId, const std::string& filePath, int fontSize);

	SDL_Texture* GetTexture(const std::string& assetId);
	TTF_Font* GetFont(const std::string& assetId);

	// Function to get the list of texture names
	std::vector<std::string> GetTextureNames() const;
	std::vector<std::string> GetFontNames() const;
};
#endif
