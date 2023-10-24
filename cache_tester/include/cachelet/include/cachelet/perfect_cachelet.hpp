#pragma once

#include <unordered_map>
#include <list>
#include <algorithm>
#include <iostream>

namespace perfect_cache {
template <typename data_t, typename key_t>
class perfect_cachelet 
{
	std::list<data_t> stream_;
	size_t capasity_;
	size_t size_;

	using iterator_t = typename std::list<data_t>::const_iterator;
	std::unordered_map<key_t, iterator_t> cache_;
	std::unordered_map<key_t, unsigned int> counts_;
	std::unordered_map<key_t, unsigned int> predicted_element_counts_ = {};

public:
	perfect_cachelet(size_t capasity, std::list<key_t> requests) : capasity_(capasity) {
		for (auto *key = requests.begin(), *end = requests.end(); key != end; ++key ) {
			if ( predicted_element_counts_.find(key) ) 
				++predicted_element_counts_[key];
			else
				predicted_element_counts_[key] = 1;
		}
	}

	bool lookup_update(key_t key, data_t (*slow_get_item)(key_t)) {
		auto hit = cache_.find(key);
		if (hit == cache_.end()) {
			data_t new_item = slow_get_item(key);
			return update_cache_miss(key, new_item);
		}
		return update_cache_hit(key);
	}
};
}