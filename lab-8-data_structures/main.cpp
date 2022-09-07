#include <chrono>
#include "set.h"
#include "unordered_set.h"
#include <algorithm>
#include <iostream>
#include "ordered_vector.h"



int main() {
	const int size = 30000;
	int begin = 5000;
	std::cout << "SET: \n";
	for(size_t j=0;j<3;++j){
		set<int> test_1;
		for (int i = 0; i < begin; ++i)
			test_1.insert(i);
		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_1.insert(rand() % 40000);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "insert: " << diff.count() / size << std::endl;
		std::cout << std::endl;

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_1.find(rand() % 40000);
		end = std::chrono::steady_clock::now();
		diff = end - start;
		std::cout << "find: " << diff.count() / size << std::endl;
		std::cout << std::endl;

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_1.erase(rand() % 40000);
		end = std::chrono::steady_clock::now();
		diff = end - start;
		std::cout << "erase: " << diff.count() / size << std::endl;
		std::cout << std::endl;
		if (begin == 5000) {
			begin = 10000;
			continue;
		}
		begin = 12000;
	}


	std::cout << "UNORDERED_SET: \n";
	for (size_t j = 0; j < 3; ++j) {
		begin = 5000;
		unordered_set<int> test_2(10000);
		for (int i = 0; i < begin; ++i)
			test_2.insert(i);

		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_2.insert(rand() % 40000);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "insert: " << diff.count() / size << std::endl;
		std::cout << std::endl;

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_2.find(rand() % 40000);
		end = std::chrono::steady_clock::now();
		diff = end - start;
		std::cout << "find: " << diff.count() / size << std::endl;
		std::cout << std::endl;

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_2.erase(rand() % 40000);
		end = std::chrono::steady_clock::now();
		diff = end - start;
		std::cout << "erase: " << diff.count() / size << std::endl;
		std::cout << std::endl;
		if (begin == 5000) {
			begin = 10000;
			continue;
		}
		begin = 100000;
	}

	std::cout << "ORDERED_VECTOR: \n";
	for (size_t j = 0; j < 3; ++j) {
		int begin = 5000;
		ordered_vector<int> test_3(20000);
		for (int i = 0; i < begin; ++i)
			test_3.insert(i);

		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_3.insert(rand() % 40000);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "insert: " << diff.count() / size << std::endl;
		std::cout << std::endl;

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_3.find(rand() % 40000);
		end = std::chrono::steady_clock::now();
		diff = end - start;
		std::cout << "find: " << diff.count() / size << std::endl;
		std::cout << std::endl;

		start = std::chrono::steady_clock::now();
		for (int i = 0; i < size; ++i)
			test_3.erase(rand() % 40000);
		end = std::chrono::steady_clock::now();
		diff = end - start;
		std::cout << "erase: " << diff.count() / size << std::endl;
		std::cout << std::endl;
		if (begin == 5000) {
			begin = 10000;
			continue;
		}
		begin = 20000;
	}

}