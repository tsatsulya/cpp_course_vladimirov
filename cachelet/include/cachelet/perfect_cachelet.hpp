#pragma once

#include <unordered_map>
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
namespace perfect_cache {
template <typename data_t, typename key_t>
class perfect_cachelet
{
	std::list<data_t> stream_;
	size_t capacity_;
	size_t size_;

	using iterator_t = typename std::list<data_t>::const_iterator;
	std::unordered_map<key_t, iterator_t> cache_;
	std::unordered_map<key_t, unsigned int> counts_;

	std::unordered_map<key_t, unsigned int> predicted_element_counts_;

	key_t find_first_minimal_count(std::unordered_map<key_t, unsigned int> map) const {
		std::unordered_map<key_t, unsigned int> reverse_map;
		for (auto &pair : map) {
			reverse_map.insert(std::make_pair(pair.first, pair.second));
		}

		std::pair<key_t, unsigned int> min_pair = *min_element(reverse_map.begin(), reverse_map.end(),
			[&](std::pair<key_t, unsigned int> i, std::pair<key_t, unsigned int> j)
			{ return i.second < j.second; });

		return min_pair.first; // still O(N) just like un_map.find :ъ
	}

	void erase_elem(key_t key) {
		cache_.erase(key);
	}

	void erase_if_last_occurrence(key_t key) {
		if (predicted_element_counts_[key] == 0) {
			erase_elem(key);
		}
	}

	bool update_cache_hit(key_t key) {
		erase_if_last_occurrence(key);
		return true;
	}

	bool update_cache_miss(key_t key, data_t new_item) {
		erase_if_last_occurrence(key);

		if (size_ == capacity_) {
			key_t key_of_min_occurrence = find_first_minimal_count(predicted_element_counts_);
			cache_.erase(key_of_min_occurrence);
		}
		iterator_t new_iterator = stream_.begin();
		new_iterator = stream_.insert(new_iterator, new_item);
		cache_[key] = new_iterator;
		return false;
	}


public:

	explicit perfect_cachelet(size_t capacity) : capacity_(capacity) {}
	
	perfect_cachelet(size_t capacity, std::vector<key_t> requests) : capacity_(capacity) {
		for (auto key = requests.begin(), end = requests.end(); key != end; ++key) {
			std::cout << *key << std::endl;
			if (predicted_element_counts_.find(*key) == predicted_element_counts_.end()) 
				predicted_element_counts_[*key] = 1;
			else 
				predicted_element_counts_[*key]++;
		}
	}
	
	data_t *get_item(key_t key, data_t (*slow_get_item)(key_t)) {
		lookup_update(key, slow_get_item);
		return cache_;
	}

	bool lookup_update(key_t key, data_t (*slow_get_item)(key_t)) {
		auto hit = cache_.find(key);
		predicted_element_counts_[key]--;
		if (hit == cache_.end()) {
			data_t new_item = slow_get_item(key);
			return update_cache_miss(key, new_item);
		}
		return update_cache_hit(key);
	}
private:

};
}