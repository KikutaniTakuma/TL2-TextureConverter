#pragma once

#include <filesystem>

#include "external/DirectXTex/DirectXTex.h"

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
	void SaveDDSTextureToFile_();

private:
	DirectX::TexMetadata metaData_;
	DirectX::ScratchImage scratchImage_;

	std::filesystem::path filePath_;
};