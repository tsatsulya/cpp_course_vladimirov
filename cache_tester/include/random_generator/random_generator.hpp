#pragma once

#include <string>
#include <random>

namespace rand_gen {

class generator {
	int random_string_length_ = 20;
	int random_max_value_ = 1024;
public:
	std::string generate_random_string(int length) const;
	std::string generate_random_string() const;

	int generate_random_int(int max_value) const;
	int generate_random_int() const;

	void set_random_string_length(int length) {
		random_string_length_ = length;
	}
	void set_random_max_value_(int max_value) {
		random_max_value_ = max_value;
	}

	generator() {};
	generator(int max_value, int string_length) : 
		random_max_value_(max_value), 
		random_string_length_(string_length) {}
};
}