#pragma once
template<typename T>
class unique_ptr
{
	T* ptr;
public:
	 unique_ptr() :ptr(nullptr) {  }
	 unique_ptr(std::nullptr_t resource) :ptr(resource) {  }
	explicit unique_ptr(T* const ptr) : ptr(ptr){}
	~unique_ptr() { delete ptr; }
	void reset(T* p = nullptr) noexcept 
	{
		auto temp = ptr;
		ptr = p;
		if (temp)
			delete temp;
	}
	unique_ptr(const unique_ptr& rhs) = delete;
	unique_ptr& operator=(const unique_ptr& rhs) = delete;
	unique_ptr(unique_ptr &&rhs) noexcept : ptr(rhs.ptr)
	{
		rhs.ptr = nullptr;
	}
	unique_ptr& operator=(unique_ptr&& rhs) noexcept
	{
		if (rhs == *this)
			return *this;
		reset(rhs.release());
		return *this;
	}
	T* release() noexcept
	{
		auto ptr = (*this).ptr;
		(this) -> ptr = nullptr;
		return ptr;
	}
	void swap(unique_ptr& resource) noexcept
	{
		T* temp = release();
		*this = std::move(resource);
		resource.ptr = temp;
	}
	T* get() const noexcept
	{
		if ((this)->ptr == nullptr)
			return nullptr;
		else
			return (this)->ptr;
	}
	explicit operator bool() const noexcept
	{
		if (ptr == nullptr)
			return false;
		else
			return true;
	}
	T* operator->() const noexcept
	{
		return get();
	}
	T& operator*() const
	{
		return *ptr;
	}
};
template <typename T1,typename T2>
bool operator == (const unique_ptr<T1>& lhs,  const unique_ptr<T2>& rhs) noexcept
{
	return lhs.get() == rhs.get();
}
template <typename T1, typename T2>
bool operator!=(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs) noexcept
{
	return !(lhs.get() == rhs.get());
}
template <typename T1, typename T2>
bool operator<(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs)
{
	if (lhs.get() == nullptr || rhs.get() == nullptr)
		throw"Comparing with nullptr pointer!";
	if (lhs.get() < rhs.get())
		return true;
	else
		return false;
}
template <typename T1, typename T2>
bool operator<=(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs)
{
	if (lhs.get() == nullptr || rhs.get() == nullptr)
		throw"Comparing with nullptr pointer!";
	return !(rhs.get() < lhs.get());
}
template <typename T1, typename T2>
bool operator>(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs)
{
	if (lhs.get() == nullptr || rhs.get() == nullptr)
		throw"Comparing with nullptr pointer!";
	return rhs.get() < lhs.get();
}
template <typename T1, typename T2>
bool operator>=(const unique_ptr<T1>& lhs, const unique_ptr<T2>& rhs)
{
	if (lhs.get() == nullptr || rhs.get() == nullptr)
		throw"Comparing with nullptr pointer!";
	return !(lhs.get() < rhs.get());
}