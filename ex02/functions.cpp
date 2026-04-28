#include <iostream>
#include <cstdlib>
#include "functions.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

// Genera aleatoriamente una instancia de A, B o C
Base* generate(void) {
	int random = std::rand() % 3;
	if (random == 0) {
		std::cout << "Generated: A" << std::endl;
		return new A();
	} else if (random == 1) {
		std::cout << "Generated: B" << std::endl;
		return new B();
	} else {
		std::cout << "Generated: C" << std::endl;
		return new C();
	}
}

// Identifica el tipo real usando PUNTERO
// dynamic_cast con puntero retorna NULL si falla
void identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

// Identifica el tipo real usando REFERENCIA
// dynamic_cast con referencia lanza std::bad_cast si falla
void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	} catch (...) {}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	} catch (...) {}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	} catch (...) {}
	std::cout << "Unknown type" << std::endl;
}
