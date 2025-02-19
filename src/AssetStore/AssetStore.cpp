#include "AssetStore.h"

AssetStore::AssetStore()
{
	Logger::Log("AssetStore constructor called!");
}

AssetStore::~AssetStore()
{
	ClearAssets();
	Logger::Log("AssetStore destructor called!");
}

void AssetStore::ClearAssets()
{
	for (auto texture: textures)
	{
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();

	for (auto font: fonts)
	{
		TTF_CloseFont(font.second);
	}
	fonts.clear();
}

void AssetStore::AddTexture
(
	SDL_Renderer* renderer, 
	const std::string& assetId, 
	const std::string& filepath
)
{
	SDL_Surface* surface = IMG_Load(filepath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Add the texture to the map
	textures.emplace(assetId, texture);

	Logger::Log("New texture added to the Asset Store with id = " + assetId);
}

void AssetStore::AddFont
(const std::string& assetId, const std::string& filePath, int fontSize)
{
	fonts.emplace(assetId, TTF_OpenFont(filePath.c_str(), fontSize));
}

TTF_Font* AssetStore::GetFont(const std::string& assetId)
{
	return fonts[assetId];
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId)
{
	return textures[assetId];
}

std::vector<std::string> AssetStore::GetFontNames() const
{
	std::vector<std::string> names;
	for (const auto& pair : fonts)
	{
		names.push_back(pair.first);
	}
	return names;
}

std::vector<std::string> AssetStore::GetTextureNames() const
{
	std::vector<std::string> names;
	for (const auto& pair : textures)
	{
		names.push_back(pair.first);
	}
	return names;
}

