#pragma once

#include <iostream>
#include <string>
#include "random_generator/random_generator.hpp"

namespace user_data{
class user_item {

	rand_gen::generator user_generator = rand_gen::generator();

public:
	int key_;
	int unnecessary_value_;

	user_item() {
		key_ = user_generator.generate_random_int();
		unnecessary_value_ = user_generator.generate_random_int();
	}
	user_item(int string_key, int unnecessary_value) : key_(string_key), 
		unnecessary_value_(unnecessary_value) {}
	
	explicit user_item(int string_key) : key_(string_key) {
		unnecessary_value_ = user_generator.generate_random_int();
	}

	void print_user_item_info() {
		std::cout << "key: " << key_ << std::endl;
		std::cout << "value: " << unnecessary_value_ << std::endl;
	}
	
	// user_item slow_get_item(std::string key) { return user_item(); } // return not a user_item *, but a user_item, because it’s slower
};
}