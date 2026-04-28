#include <iostream>
#include <ctime>
#include <cstdlib>
#include "functions.hpp"

int main() {
	std::srand(std::time(NULL));

	for (int i = 0; i < 5; i++) {
		std::cout << "--- Test " << i + 1 << " ---" << std::endl;
		Base* obj = generate();

		std::cout << "identify(ptr): ";
		identify(obj);

		std::cout << "identify(ref): ";
		identify(*obj);

		delete obj;
		std::cout << std::endl;
	}

	return 0;
}
