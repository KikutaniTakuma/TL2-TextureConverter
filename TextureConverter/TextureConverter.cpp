#include "TextureConverter.h"

void TextureConverter::ConvertTextureWICToDDS(const std::filesystem::path& filePath) {
	LoadWICTextureFromFile_(filePath);


}

void TextureConverter::LoadWICTextureFromFile_(const std::filesystem::path& filePath) {
	std::wstring wfilePath = filePath.wstring();


}
