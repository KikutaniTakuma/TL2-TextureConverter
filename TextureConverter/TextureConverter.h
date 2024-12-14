#pragma once

#include <filesystem>
#include <vector>

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
	void ConvertTextureWICToDDS(
		const std::filesystem::path& filePath,
		int numOpotions = 0,
		char* options[] = nullptr
	);
	static void OutputUsage();

private:
	void LoadWICTextureFromFile_(
		const std::filesystem::path& filePath
	);
	void SaveDDSTextureToFile_(const std::vector<std::string>& options);

private:
	DirectX::TexMetadata metaData_ = {};
	DirectX::ScratchImage scratchImage_;

	std::filesystem::path filePath_;
};