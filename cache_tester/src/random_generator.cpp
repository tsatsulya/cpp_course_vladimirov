#include "random_generator/random_generator.hpp"
#include <random>
#include <iostream>

namespace gtor {
	std::random_device random_device;
	std::mt19937 generator(random_device());
}


int rand_gen::generator::generate_random_int(int max_value) const {	

	std::uniform_int_distribution<> distribution(0, max_value);
	return distribution(gtor::generator);
}


int rand_gen::generator::generate_random_int() const {
	return generate_random_int(random_max_value_);	
}

std::string rand_gen::generator::generate_random_string(int length) const {

	const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int num_of_char = CHARACTERS.size();
	std::string random_string;

	for (std::size_t i = 0; i < length; ++i) {
		random_string += CHARACTERS[generate_random_int(num_of_char - 1)];
	}
	return random_string;
} 

std::string rand_gen::generator::generate_random_string() const {
	return generate_random_string(random_string_length_);
}

