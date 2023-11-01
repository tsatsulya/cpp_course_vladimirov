#pragma once

#include <unordered_map>
#include <list>
#include <algorithm>
#include <iostream>

namespace cache
{
	template <typename data_t, typename key_t>
	class cachelet
	{
		std::list<data_t> stream_;
		size_t capacity_;
		size_t size_;

		using iterator_t = typename std::list<data_t>::const_iterator;
		std::unordered_map<key_t, iterator_t> cache_;
		std::unordered_map<key_t, unsigned int> counts_;

		key_t find_first_minimal_count(std::unordered_map<key_t, unsigned int> map) const { // still O(N) just like un_map.find :ъ
			std::unordered_map<key_t, unsigned int> reverse_map;
			for (auto &pair : map) {
				reverse_map.insert(std::make_pair(pair.first, pair.second));
			}

			std::pair<key_t, unsigned int> min_pair = *min_element(reverse_map.begin(), reverse_map.end(),
				[&](std::pair<key_t, unsigned int> i, std::pair<key_t, unsigned int> j)
				{ return i.second < j.second; });

			return min_pair.first;
		}

		bool update_cache_miss(key_t key, data_t new_item) {
			if (cache_.size() >= capacity_) {
				key_t key_of_minimal_count = find_first_minimal_count(counts_);
				iterator_t it_min = cache_[key_of_minimal_count];cache_.erase(key_of_minimal_count);
				counts_.erase(key_of_minimal_count);
			}

			iterator_t new_iterator = stream_.begin();
			new_iterator = stream_.insert(new_iterator, new_item);
			cache_[key] = new_iterator;
			counts_[key] = 1;
			return false; // miss
		}

		void update_item_count(key_t key) {
			unsigned int count = counts_[key];
			counts_.erase(key);
			counts_.insert(std::make_pair(key, ++count)); // insert to the head oh map
		}

		bool update_cache_hit(key_t key) {
			update_item_count(key);
			return true; // hit
		}

	public:
		explicit cachelet(size_t capacity) : capacity_(capacity) {}

		bool lookup_update(key_t key, data_t (*slow_get_item)(key_t)) {
			auto hit = cache_.find(key);
			if (hit == cache_.end()) {
				data_t new_item = slow_get_item(key);
				return update_cache_miss(key, new_item);
			}
			return update_cache_hit(key);
		}

		data_t get_item(key_t key, data_t (*slow_get_item)(key_t)) {
			lookup_update(key, slow_get_item);
			return cache_[key];
		}

		void clear() {
			cache_.clear();
			counts_.clear();
			stream_.clear();
			size_ = 0;
		}

		void print_cache_state() const {
			std::cout << "size: " << cache_.size() << "/" << capacity_ << std::endl;
			for (auto &pair : cache_)
			{
				std::cout << *pair.second << "\t";
			}
			std::cout << std::endl;
		}
	};
}
