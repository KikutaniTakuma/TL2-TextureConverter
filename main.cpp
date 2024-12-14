#include <iostream>
#include <cstdlib>

#include "TextureConverter/TextureConverter.h"

#include <cassert>

#include <Windows.h>
#undef max
#undef min

enum Argument {
	kApplicationPath,
	kFilePath,

	kNumArgument
};


int main([[maybe_unused]] int32_t argc, char* argv[]) {
	if (argc < kNumArgument) {
		TextureConverter::OutputUsage();
		system("pause");
		return 0;
	}

	int numOptions = argc - kNumArgument;
	char** options = argv + kNumArgument;

	[[maybe_unused]] HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;

	try {
		converter.ConvertTextureWICToDDS(argv[kFilePath], numOptions, options);
	}
	catch (std::exception err) {
		CoUninitialize();
		std::cerr << err.what() << std::endl;
		system("pause");
		return -1;
	}
	CoUninitialize();

	return 0;
}