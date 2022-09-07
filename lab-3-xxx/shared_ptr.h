#pragma once
template<typename T>
class shared_ptr
{
	T* ptr;
	unsigned long int* count;
public:
	shared_ptr()
	{
		count = nullptr;
		ptr = nullptr;
	}
	explicit shared_ptr(T* const pointer) : ptr(pointer)
	{
		 count = new unsigned long int(1);
	}
	 ~shared_ptr() 
	 {
		 if (ptr)
		 {
			 if (*count > 1)
				 (*count)--;
			 else if (*count == 1)
			 {
				delete ptr;
				delete count;
			 }
		 }
	 }
	shared_ptr(std::nullptr_t p) :ptr(p), count( nullptr) {}
	shared_ptr(const shared_ptr<T>& rs)
	{
		ptr = rs.ptr;
		count = rs.count;
		if(count)
			(*count) ++;
	}
	shared_ptr& operator= (const shared_ptr& rhs) noexcept
	{
		shared_ptr<T>(rhs).swap(*this);
		return *this;
	}
	shared_ptr(shared_ptr&& rhs) : ptr(rhs.ptr), count(rhs.count)
	{
		rhs.ptr = nullptr;
		rhs.count = nullptr;
	}
	shared_ptr& operator=(shared_ptr&& rhs) noexcept
	{
		if (rhs == *this)
			return *this;
		delete ptr;
		delete count;
		ptr = new T;
		count = new unsigned long int;
		ptr = rhs.ptr;
		count = rhs.count;
	}
	T* operator->() const noexcept
	{
		return get();
	}
	T& operator*() const
	{
		return *ptr;
	}
	T* get() const noexcept
	{
		if (ptr == nullptr)
			return nullptr;
		else
			return ptr;
	}
	unsigned long int use_count() const noexcept
	{
		if (count)
			return *count;
		else
			return 0;
	}
	void reset() noexcept
	{
		shared_ptr<T>().swap(*this);
	}
	void swap(shared_ptr& resource) noexcept
	{
		auto ptr_temp = ptr;
		ptr = resource.ptr ;
		resource.ptr = ptr_temp;
		auto count_temp = count;
		count = resource.count;
		resource.count = count_temp;
	}
	operator bool() const 
	{
		return get() != 0;
	}
};
template <typename T1, typename T2>
bool operator == (const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) noexcept
{
	return lhs.get() == rhs.get();
}
template <typename T1, typename T2>
bool operator!=(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs) noexcept
{
	return !(lhs.get() == rhs.get());
}
template <typename T1, typename T2>
bool operator<(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs)
{
	if (lhs.get() == nullptr || rhs.get() == nullptr)
		throw"Comparing with nullptr pointer!";
	if (lhs.get() < rhs.get())
		return true;
	else
		return false;
}
template <typename T1, typename T2>
bool operator<=(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs)
{
	if (lhs.get() == nullptr || rhs.get() == nullptr)
		throw"Comparing with nullptr pointer!";
	return !(rhs.get() < lhs.get());
}
template <typename T1, typename T2>
bool operator>(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs)
{
	if (lhs.get() == nullptr || rhs.get() == nullptr)
		throw"Comparing with nullptr pointer!";
	return rhs.get() < lhs.get();
}
template <typename T1, typename T2>
bool operator>=(const shared_ptr<T1>& lhs, const shared_ptr<T2>& rhs)
{
	if (lhs.get() == nullptr || rhs.get() == nullptr)
		throw"Comparing with nullptr pointer!";
	return !(lhs.get() < rhs.get());
}