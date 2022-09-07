#pragma once
typedef unsigned long int ulint;
template<typename T>
struct node
{
	T data;
	node* next;
	node* prev;
};
template<typename T>
class iterator_list
{
	node<T>* obj;
public:
	iterator_list() :obj(nullptr) {}
	iterator_list(node<T>* const resource):obj(resource) {}
	iterator_list& operator++()
	{
		obj = obj->next;
		return *this;
	}
	iterator_list& operator++(int)
	{
		iterator_list<T> temp(*this);
		++temp;
		return temp;
	}
	iterator_list& operator--()
	{
		/*iterator_list<T> temp = std::prev((*this).operator->());
		return temp;*/
		obj = obj->prev;
		return *this;
	}
	iterator_list& operator--(int)
	{
		iterator_list<T> temp(*this);
		--temp;
		return temp;
	}
	bool operator==(const iterator_list<T>& rhs) const
	{
		return obj == rhs.obj;
	}
	bool operator!=(const iterator_list<T>& rhs) const
	{
		return !(obj == rhs.obj);
	}
	node<T>* operator->() const
	{
		return obj;
	}
	T operator*() const
	{
		return obj->data;
	}
};
template<typename T>
class list
{
	node<T>* obj;
	ulint count;

public:
	list()
	{
		obj = new node<T>;
		count = 0;
		obj->next = nullptr;
		obj->prev = nullptr;
	}
	explicit list(ulint size) : count(size), obj(create_list(size)) {}
	explicit list(ulint size, const T& value ) : count(size) { obj = create_list(size, value); }
	list(const list& resource) : count(resource.count) { obj = copy_list(resource); }
	list(list&& resource) :count(resource.count), obj(resource.obj)
	{
		resource.obj = nullptr;
		resource.count = 0;
	}
	list& operator=(const list& rhs)
	{
		clear();
		obj = copy_list(rhs);
		count = rhs.count;
		return *this;
	}
	list& operator=(list&& rhs)
	{
		clear();
		obj = rhs.obj;
		count = rhs.count;
		rhs.obj = nullptr;
		rhs.count = 0;
	}
	~list() { clear(); delete obj; }
	ulint size() const noexcept
	{
		return count;
	}
	iterator_list<T> begin() noexcept
	{
		return iterator_list<T>(obj);
	}
	const iterator_list<T> begin()  const noexcept
	{
		return iterator_list<T>(obj);
	}
	iterator_list<T> end() noexcept
	{
		iterator_list<T> ret = begin();
		for (ulint i = 0; i < count ; ++i)
			++ret;
		return ret;
	}
	const iterator_list<T> end() const noexcept
	{
		auto ret = obj;
		while (ret->next)
			++ret;
		return iterator_list<T>(ret);
	}
	iterator_list<T> insert(const iterator_list<T>& it, const T& key)
	{
		auto temp = new node<T>;
		temp->data = key;
		if (it == begin())
		{
			temp->prev = nullptr;
			temp->next = it.operator->();
			obj = temp;
		}
		else
		{
			temp->prev = (it.operator->())->prev;
			temp->next = it.operator->();
			temp->prev->next = temp;
		}
		it.operator->()->prev = temp;
		++count;
		return iterator_list<T>(temp);
	}
	iterator_list<T> erase(iterator_list <T>& it)
	{
		if (it == begin())
		{
			auto temp = obj;
			obj = obj->next;
			obj->prev = nullptr;
			delete temp;
			--count;
			return begin();
		}
		else
		{
			it.operator->()->next->prev = it.operator->()->prev;
			it.operator->()->prev->next = it.operator->()->next;
			auto ret = it.operator->()->next;
			delete it.operator->();
			--count;
			return iterator_list<T>(ret);
		}
	}
	node<T>* create_list( ulint count, const T& value=T())
	{
		auto head = new node<T>;
		head->data = value;
		head->next = nullptr;
		head->prev = nullptr;
		auto ret = head;
		for (ulint i = 0; i < count; ++i)
		{
			auto temp = new node<T>;
			temp->data = value;
			head->next = temp;
			temp->next = nullptr;
			temp->prev = head;
			head = head->next;
		}
		return ret;
	}
	node<T>* copy_list(const list<T>& resource)
	{
		auto head = new node<T>;
		iterator_list<T> it = resource.begin();
		iterator_list<T> en = resource.end();
		++en;
		head->data = *it;
		head->next = nullptr;
		head->prev = nullptr;
		auto ret = head;
		++it;
		while(it!=en)
		{
			auto temp = new node<T>;
			temp->data = *it;
			temp->prev = head;
			temp->next = nullptr;
			head->next = temp;
			head = head->next;
			++it;
		}
		return ret;
	}		
	void clear() noexcept 
	{
		while (begin() != end())
		{
			erase(begin());
		}
	}
};