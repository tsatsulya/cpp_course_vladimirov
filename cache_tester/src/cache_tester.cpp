#include <iostream>
#include <string>
#include "cachelet/cachelet.hpp"
#include "cachelet/perfect_cachelet.hpp"
#include "random_generator/random_generator.hpp"
#include "user_data/user_data.hpp"

using namespace rand_gen;
using namespace user_data;
using namespace cache;

using cachelet_t = typename cache::cachelet<int, int>;

template <typename data_t, typename key_t>
data_t slow_get_item(key_t key) {
	user_item ud = user_item(key);
	// ud.print_user_item_info();
	return ud.unnecessary_value_;
}

int main() {
	int hits = 0;

	int capasity, requests;
	std::cin >> capasity >> requests;
	cachelet_t cache = cachelet<int, int>(capasity);

	for (int i = 0; i < requests; i++) {
		int key;
		std::cin >> key;
		hits += cache.lookup_update(key, &slow_get_item<int, int>);
		std::cout << std::endl;
		cache.print_cache_state();
		std::cout << hits << std::endl;
	}
	std::cout << hits << std::endl;

	return 0;
}

// 4 12 1 2 3 4 1 2 5 1 2 4 3 4

// Hits statistics:
// - LFU:3
// - PCA (Perfect Caching Algorithm): 5

// Тут при знании будущего должно быть 7 а не 5.