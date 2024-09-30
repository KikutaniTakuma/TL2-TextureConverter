#include <iostream>
#include <cstdlib>

#include <string>

int main(int32_t args, char* argv[]) {
	std::string argStr;

	for (int32_t i = 0; i < args; i++) {
		argStr += argv[i];
	}

	std::cout << argStr << std::endl;

	system("pause");

	return 0;
}