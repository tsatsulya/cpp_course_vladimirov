#include <iostream>
#include <string>
#include "cachelet/cachelet.hpp"
#include "random_generator/random_generator.hpp"
#include "user_data/user_data.hpp"

using namespace rand_gen;
using namespace user_data;
using namespace cache;

using cachelet_t = typename cache::cachelet<int, std::string>;

template <typename data_t, typename key_t>
data_t slow_get_item(key_t key) {
	user_item ud = user_item(key);
	ud.print_user_item_info();
	return ud.unnecessary_value_;
}

int main() {
	cachelet_t cache = cachelet<int, std::string>(2);
	std::cout << cache.lookup_update("aaaa", &slow_get_item<int, std::string>) << std::endl;
	std::cout << cache.lookup_update("aaaa", &slow_get_item<int, std::string>) << std::endl;
	std::cout << cache.lookup_update("aaaa", &slow_get_item<int, std::string>) << std::endl;
	std::cout << cache.lookup_update("aaaa", &slow_get_item<int, std::string>) << std::endl;

	return 0;
}