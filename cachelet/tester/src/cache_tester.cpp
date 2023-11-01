#include <iostream>
#include <string>
#include <vector>
#include "random_generator/random_generator.hpp"
#include "user_data/user_data.hpp"
#include "cachelet/perfect_cachelet.hpp"
#include "cachelet/cachelet.hpp"
using namespace rand_gen;
using namespace user_data;
using namespace perfect_cache;
using namespace cache;
using p_cachelet_t = typename perfect_cache::perfect_cachelet<int, int>;
using cachelet_t = typename cache::cachelet<int, int>;

template <typename data_t, typename key_t>
data_t slow_get_item(key_t key) {
	user_item ud = user_item(key);
	// ud.print_user_item_info();
	return ud.unnecessary_value_;
}

int main() {
	int hits = 0;

	size_t capacity = 10;
	// std::cin >> capacity >> requests;
	cachelet_t tt = cachelet<int, int>(capacity);
	std::vector<int> v = {1, 2, 3, 4, 5};
	p_cachelet_t cache = perfect_cachelet<int, int>(capacity, v);
	// for (int i = 0; i < requests; i++) {
	// 	int key;
	// 	std::cin >> key;
	// 	hits += cache.lookup_update(key, &slow_get_item<int, int>);
	// 	std::cout << std::endl;
	// 	cache.print_cache_state();
	// 	std::cout << hits << std::endl;
	// }
	// std::cout << hits << std::endl;

	return 0;
}

// 4 12 1 2 3 4 1 2 5 1 2 4 3 4

// Hits statistics:
// - LFU:3
// - PCA (Perfect Caching Algorithm): 5

// Тут при знании будущего должно быть 7 а не 5.