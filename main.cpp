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


int main(int32_t argc, char* argv[]) {
	assert(argc <= kNumArgument);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	TextureConverter converter;

	converter.ConvertTextureWICToDDS(argv[kFilePath]);

	CoUninitialize();

	system("pause");
	return 0;
}