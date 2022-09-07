#include "sort.h"
#include <iostream>
#include <ctime>
#include <cmath>
int main() {
	srand(time(NULL));

	size_t N;
	std::cout<<"Insert number of elements: ";
	std::cin >> N;
	int* arr = new int[N];

	for (size_t i = 0; i < N; ++i) {
		arr[i] = rand() % 1000000;
	}

	
	int start = clock();
	//bubble_sort<int>(arr, N);
    //selection_sort<int>(arr, N);
    //shell_sort<int>(arr, N);
    //quick_sort<int>(arr,0, N-1);
    merge_sort<int>(arr,N);
	int end = clock();
	std::cout << "\nTime: " << end - start<<"mсs";
	return 0;
}

