#pragma once
#include <cstddef>
template<typename T>
void selection_sort(T* array, const std::size_t N)
{
	for (std::size_t i = 0; i < N; ++i) {
		std::size_t i_min = i;
		for (size_t j = i + 1; j < N; ++j) {

			if (array[i_min] > array[j])
			{
				i_min = j;
			}
		}

		T temp = array[i];
		array[i] = array[i_min];
		array[i_min] = temp;


	}
}
template<class T>
void bubble_sort(T* array, const size_t N) {
	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < N - i - 1; ++j) {

			if (array[j] > array[j + 1]) {
				T temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}

		}
	}
}
template<class T>
void shell_sort(T* array, const size_t N) {
	size_t d = N / 2;
	while (d > 0) {
		for (size_t i = 0; i < N - d; ++i) {
			for (int j = i; j >= 0 && array[j] > array[j+d]; j-=d) {
				
				T temp = array[j];
				array[j] = array[j + d];
				array[j + d] = temp;

			}
		}
		d = d / 2;
	}
}
template<class T>
void quick_sort(T* array, const size_t left, const size_t right) {
	if (left < right) {
		size_t i = left;
		size_t j = right;
		T pivot = array[(left + right) / 2];
		while (i <= j) {
		    while (array[i] < pivot){
		        ++i;
		    }
            while (array[j] > pivot){
                --j;
            }
			if (i >= j)
				break;
			T temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			++i;
			--j;
		}
		quick_sort<T>(array, left, j);
		quick_sort<T>(array, j + 1, right);
	}
	else
		return;
}
template<class T>
void merge_sort(T* array, const size_t N) {
	int s = 0, d = 1, f = 1;
	T* t_array = new T[2 * N];
	for (size_t c = 0; c < N; ++c)
		t_array[c] = array[c];
	size_t i, j, k, l;
	while (true) {
		if (!s) {
			i = 0;
			j = N - 1;
			k = N;
			l = 2 * N - 1;
		}
		else {
			k = 0;
			l = N - 1;
			i = N;
			j = 2 * N - 1;
		}
		d = f = 1;
		while (true) {
			if (t_array[i] <= t_array[j]) {
				if (i == j) {
					t_array[k] = t_array[i];
					if (!f) {
						s = 1 - s;
						break;
					}
					else {
						if(!s)
							for (size_t c = 0; c < N; ++c) {
								array[c] = t_array[c + N];
							}
						else
							for (size_t c = 0; c < N; ++c) {
								array[c] = t_array[c];
							}
						return;
					}
				}
				else {
					t_array[k] = t_array[i];
					k += d;
				}

				++i;
				if (t_array[i - 1] <= t_array[i])
					continue;

				while (true){
					t_array[k] = t_array[j];
					k += d;

					--j;
					if (t_array[i - 1] <= t_array[i])
						continue;
					else {
						f = 0;
						d = -d;
						int temp = k;
						k = l;
						l = temp;
						break;
					}
				}
				continue;
			}
			else {
				t_array[k] = t_array[j];
				k += d;
			}

			--j;
			if (t_array[j + 1] <= t_array[j])
				continue;

			while (true){

				t_array[k] = t_array[i];
				k += d;

				++i;
				if (t_array[i - 1] <= t_array[i])
					continue;
				break;
			}

			f = 0;
			d = -d;
			int temp = k;
			k = l;
			l = temp;
			continue;
		}
	}
}