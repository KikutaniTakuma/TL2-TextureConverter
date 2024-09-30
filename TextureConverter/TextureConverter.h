#pragma once

#include <filesystem>

class TextureConverter {
public:
	TextureConverter() = default;
	TextureConverter(const TextureConverter&) = delete;
	TextureConverter(TextureConverter&&) = delete;
	~TextureConverter() = default;

	TextureConverter& operator=(const TextureConverter&) = delete;
	TextureConverter& operator=(TextureConverter&&) = delete;

public:
	void ConvertTextureWICToDDS(const std::filesystem::path& filePath);

private:
	void LoadWICTextureFromFile_(const std::filesystem::path& filePath);
};