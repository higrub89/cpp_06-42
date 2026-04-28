#include "Serializer.hpp"

int main() {
	Data original;
	original.name = "Ruben";
	original.value = 42;

	std::cout << "=== Original ===" << std::endl;
	std::cout << "Address: " << &original << std::endl;
	std::cout << "Name:    " << original.name << std::endl;
	std::cout << "Value:   " << original.value << std::endl;

	// Serialize: pointer → integer
	uintptr_t raw = Serializer::serialize(&original);
	std::cout << std::endl << "=== Serialized ===" << std::endl;
	std::cout << "Raw:     " << raw << std::endl;

	// Deserialize: integer → pointer
	Data* restored = Serializer::deserialize(raw);
	std::cout << std::endl << "=== Deserialized ===" << std::endl;
	std::cout << "Address: " << restored << std::endl;
	std::cout << "Name:    " << restored->name << std::endl;
	std::cout << "Value:   " << restored->value << std::endl;

	// Proof: same pointer
	std::cout << std::endl << "=== Verification ===" << std::endl;
	if (restored == &original)
		std::cout << "✅ Pointers match!" << std::endl;
	else
		std::cout << "❌ Pointers DON'T match!" << std::endl;

	return 0;
}
