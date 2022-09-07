#pragma once
#include <iostream>
template <class T>
struct u_node {
	T data;
	u_node* next;
};
template <class T>
class unordered_set {
	u_node<T>** table;
	size_t size;
public:
	unordered_set(size_t n) {
		table = new u_node<T>* [n];
		for (size_t i = 0; i < n; ++i) {
			table[i] = new u_node<T>;
			table[i]->next = nullptr;
		}
		size = n;                                                                                                         
	}
	unordered_set(const unordered_set& other) = delete;
	unordered_set& operator=(const unordered_set& other) = delete;
	~unordered_set() {
		if (size != 0) {
			for (size_t i = 0; i < size; ++i) {
				delete[] table[i];
			}
			delete[] table;
			size = 0;
		}
	}
	void insert(const T& obj) {
		std::hash<T> hash_fn;
		auto h = hash_fn(obj);
		auto index = h % size;

		auto element = new u_node<T>;
		if (table[index]->next == nullptr) {//���� ��� ��������
			table[index]->next = element;
			element->data = obj;
			element->next = nullptr;
		}
		else if (table[index]->next != nullptr)
		{
			auto ptr = table[index];
			while (ptr->next != nullptr) {//�� ����� ������
				ptr = ptr->next;
			}
			ptr->next = element;
			element->data = obj;
			element->next = nullptr;
		}
		else
			throw "Insertion error";
	}
	void print() const {
		if (size!=0) {
			for (size_t i = 0; i < size; ++i) {
				std::cout << "|--->";
				auto ptr = table[i]->next;
				while (ptr != nullptr) {
					std::cout << ptr->data << "--->";
					ptr = ptr->next;
				}
				std::cout << std::endl;
			}
		}
		else
			std::cout << "Empty!" << std::endl;
	}
	void erase(const T& key) {
		std::hash<T> hash_fn;
		auto h = hash_fn(key);
		auto index = h % size;

		auto ptr = table[index];
		if (ptr->next != nullptr) {
			while (ptr->next->data != key) {//�������� ��������� �� �������, ������� �� ����������
				ptr = ptr->next;
				if (ptr->next == nullptr)
					return;
			}
		}
		else
			return;

		auto temp = ptr->next->next;
		delete ptr->next;
		ptr->next = temp;
		
	}
	void clear() {
		
		this->~unordered_set();
	}
	u_node<T>* find(const T& key) const {
		std::hash<T> hash_fn;
		auto h = hash_fn(key);
		auto index = h % size;

		auto ptr = table[index];
		while (ptr->next != nullptr && ptr->next->data != key) {//�� �����, ���� �� key
			ptr = ptr->next;
		}
		if (ptr->next != nullptr && ptr->next->data == key)
			return ptr->next;
		return nullptr;
	}
};