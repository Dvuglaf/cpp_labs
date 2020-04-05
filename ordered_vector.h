#pragma once
#include "vector.h"
template <class T>
class ordered_vector{
	vector<T> array;

	iterator<T> binary_search(vector<T> array, size_t size, const T& key) {
		int left = 0, right = size - 1;
		while (true) {
			size_t middle = (left + right) / 2;
			if (array[middle] < key)
				left = middle + 1;
			else if (array[middle] > key) {
				right = middle - 1;
			}
			else return iterator<T>(begin().operator->() + middle);
			if (left > right)
				return iterator<T>(begin().operator->() + left);
		}
	}
public:
	ordered_vector(size_t size) {
		vector<T> temp(size);
		array = temp;
	}
	ordered_vector(size_t size, const T& key){
		vector<T> temp(size,key);
		array = temp;
	}
	~ordered_vector() {
		array.~vector();
	}
	ordered_vector(const ordered_vector& other) = delete;
	ordered_vector& operator=(const ordered_vector& other) = delete;
	iterator<T> begin()
	{
		return array.begin();
	}
	const iterator<T> begin() const
	{
		return array.begin();
	}
	iterator<T> end()
	{
		return array.end();
	}
	const iterator<T> end() const
	{
		return array.end();
	}
	void insert(const T& key) {
		auto it = binary_search(array, array.size(), key);
		array.insert(it, key);
	}
	void erase(const T& key) {
		auto it = binary_search(array, array.size(), key);
		if (it == end()) {
			return;
		}
		it = array.erase(it);		
	}
	iterator<T> find(const T& key)  {
		auto it = binary_search(array, array.size(), key);
		if (*it != key)
			return end();
		return it;
	}
	void clear() {
		array.clear();
	}
};