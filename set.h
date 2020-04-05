#pragma once
template<class T>
struct node {
	T data;
	node* left;
	node* right;
	size_t height;
	node<T>(const T& key) :data(key), left(nullptr), right(nullptr), height(1) { }
	node(const node& other) = delete;
	node& operator=(const node& other) = delete;
};
template<class T>
class set {
	node<T>* root;
	size_t get_height(node<T>* ptr) const {
		return ptr != nullptr ? ptr->height : 0;
	}
	int get_balance(node<T>* ptr) const {
		return get_height(ptr->right) - get_height(ptr->left);
	}
	void update_height(node<T>* ptr) {
		ptr->height = std::max(get_height(ptr->left), get_height(ptr->right));
	}
	node<T>* rotate_right(node<T>* ptr) {
		auto temp = ptr->left;
		ptr->left = temp->right;
		temp->right = ptr;
		update_height(ptr);
		update_height(temp);
		return temp;
	}
	node<T>* rotate_left(node<T>* ptr) {
		auto temp = ptr->right;
		ptr->right = temp->left;
		temp->left = ptr;
		update_height(ptr);
		update_height(temp);
		return temp;
	}
	node<T>* balance(node<T>* ptr) {
		update_height(ptr);
		auto value = get_balance(ptr);
		if (value == -2) {
			if (get_balance(ptr->left) > 0)
				ptr->left = rotate_left(ptr->left);
			return rotate_right(ptr);
		}
		else if (value == 2) {
			if (get_balance(ptr->right) > 0)
				ptr->right = rotate_right(ptr->right);
			return rotate_left(ptr);
		}
		return ptr;
	}
	node<T>* insert(node<T>* ptr, const T& key) {
		if (ptr == nullptr)
			return new node<T>(key);
		if (key < ptr->data) {
			ptr->left = insert(ptr->left, key);
		}
		else if (ptr->data < key) {
			ptr->right = insert(ptr->right, key);
		}
		return balance(ptr);

	}
	void print(node<T>* ptr, size_t offset) const {
		std::string temp(offset,' ');
		std::cout << temp;
		if (ptr==nullptr) {
			std::cout << "null" << std::endl;
			return;
		}
		std::cout << ptr->data << std::endl;
		print(ptr->left, offset + 2);
		print(ptr->right, offset + 2);
	}
	node<T>* search(node<T>* ptr, const T& key) const {
		if (!ptr)
			return nullptr;
		if (key < ptr->data)
			return search(ptr->left, key);
		if (key > ptr->data)
			return search(ptr->right, key);
		return ptr;
	}
	node<T>* find_min(node<T>* ptr) const {
			return ptr->left?find_min(ptr->left):ptr;
	}
	node<T>* remove_min(node<T>* ptr) {
		if (!ptr->left) {
			return ptr->right;
		}
		ptr->left = remove_min(ptr->left);
		return balance(ptr);
	}
	node<T>* erase(node<T>* ptr, const T& key) {
		if (!ptr)
			return nullptr;
		if (key < ptr->data)
			ptr->left = erase(ptr->left, key);
		else if (key > ptr->data)
			ptr->right = erase(ptr->right, key);
		else {
			node<T>* root_left = ptr->left;//запоминаем поддеревья
			node<T>* root_right = ptr->right;
			delete ptr;
			if (!root_right)
				return root_left;
			node<T>* min = find_min(root_right);//минимальный в пр.поддереве
			min->right = remove_min(root_right);
			min->left = root_left;
			return balance(min);
		}
		return balance(ptr);
	}

public:
	set() :root(nullptr) { }
	~set() {
		clear();
	}
	set(const set& other) = delete;
	set& operator=(const set& other) = delete;
	void insert(const T& key) {
		root = insert(root, key);
	}
	void print() {
		print(root, 0);
	}
	void erase(const T& key) {
		root = erase(root, key);
	}
	node<T>* find(const T& key) {
		return search(root, key);
	}
	void clear() {
		while (root) {
			node<T>* min = find_min(root);
			erase(min->data);
		}

	}
};
