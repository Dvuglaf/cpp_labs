#include<ctime>
#include "set.h"
#include "unordered_set.h"
#include <set>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include "ordered_vector.h"
#include "vector.h"
int main() {
	srand(time(NULL));
	//ordered_vector<int> test(1);
	unordered_set<int> test(5);
	int start = clock();
	for (size_t i = 0; i < 20; ++i) {
		test.insert(rand() % 50);
	}
	int end = clock();
	test.print();
//	std::cout << end - start << "ms";
	/*test.insert(0);
	for (int n : test) {
		std::cout << n << " ";
	}*/
}