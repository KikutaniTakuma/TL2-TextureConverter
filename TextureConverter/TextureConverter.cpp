#include "TextureConverter.h"
#include <cassert>

#include <iostream>

void TextureConverter::ConvertTextureWICToDDS(const std::filesystem::path& filePath) {
	filePath_ = filePath;

	if (not std::filesystem::exists(filePath)) {
		throw std::exception(("This file is not exist -> " + filePath_.string()).c_str());
	}

	std::cout << "Convert file : " << filePath_ << std::endl;

	LoadWICTextureFromFile_(filePath_);

	SaveDDSTextureToFile_();

	std::cout << "Convert completed" << std::endl;
}

void TextureConverter::LoadWICTextureFromFile_(const std::filesystem::path& filePath) {
	[[maybe_unused]] auto hr = DirectX::LoadFromWICFile(filePath.wstring().c_str(), DirectX::WIC_FLAGS_NONE, &metaData_, scratchImage_);
	if (FAILED(hr)) {
		throw std::exception("DirectX::LoadFromWICFile failed");
	}
	assert(SUCCEEDED(hr));
}

void TextureConverter::SaveDDSTextureToFile_() {
	DirectX::ScratchImage mipChain;
	auto result = DirectX::GenerateMipMaps(
		scratchImage_.GetImages(),
		scratchImage_.GetImageCount(),
		scratchImage_.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT,
		0,
		mipChain
	);

	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(mipChain);
		metaData_ = scratchImage_.GetMetadata();
	}
	else {
		throw std::exception("DirectX::GenerateMipMaps failed");
	}

	DirectX::ScratchImage converted;
	result = DirectX::Compress(
		scratchImage_.GetImages(), scratchImage_.GetImageCount(),
		metaData_,
		DXGI_FORMAT_BC7_UNORM_SRGB, 
		DirectX::TEX_COMPRESS_BC7_QUICK | DirectX::TEX_COMPRESS_SRGB_OUT | DirectX::TEX_COMPRESS_PARALLEL,
		1.0f, converted
	);

	if (SUCCEEDED(result)) {
		scratchImage_ = std::move(converted);
		metaData_ = scratchImage_.GetMetadata();
	}
	else {
		throw std::exception("DirectX::Compress failed");
	}

	metaData_.format = DirectX::MakeSRGB(metaData_.format);
	
	std::wstring outputFilePath = std::filesystem::current_path().wstring() + L"/" + filePath_.stem().wstring() + L".dds";

	[[maybe_unused]] auto hr = DirectX::SaveToDDSFile(
		scratchImage_.GetImages(),
		scratchImage_.GetImageCount(),
		metaData_,
		DirectX::DDS_FLAGS_NONE,
		outputFilePath.c_str()
	);

	if (FAILED(hr)) {
		throw std::exception("DirectX::SaveToDDSFile failed");
	}
}
