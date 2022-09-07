#include <iostream>
#include "libutils/bool_func.h"
#include "unique_ptr.h"
#include "shared_ptr.h"
#include "vector.h"
#include"list.h"
#include <vector>
#include <list>
#include <iostream>
#include <memory>
template <class T> using unique_ptr_type = unique_ptr<T>;	// std::unique_ptr<T>;
template <class T> using shared_ptr_type = shared_ptr<T>;//shared_ptr<T>;		 /*std::shared_ptr<T>;*/
template <class T> using collection_type = vector<T>;	//	 std::vector<T>;
//List<T>;	//	   std::list<T>;
/*int main()
{
	std::cout << "unique_ptr: \n" << std::endl;
	{/////////////////////////////////////////
		unique_ptr_type<BoolFunc> unique_ptr_first(new BoolFunc(2, true));
		unique_ptr_type<BoolFunc> unique_ptr_second(new BoolFunc(1, false));
		std::cout << "unique_ptr_first: " << *unique_ptr_first << std::endl;
		std::cout << "unique_ptr_second: " << *unique_ptr_second << std::endl;
		std::cout << "unique_ptr_second.swap(unique_ptr_first)\n";
		unique_ptr_second.swap(unique_ptr_first);
		std::cout << "unique_ptr_first: " << *unique_ptr_first << std::endl;
		std::cout << "unique_ptr_second: " << *unique_ptr_second << std::endl;
		std::cout << "unique_ptr_first.reset()\n";
		unique_ptr_first.reset();
		std::cout << "pointer=unique_ptr_second.release()\n";
		BoolFunc* pointer= unique_ptr_second.release();
		if (unique_ptr_second)
			std::cout << *unique_ptr_second;
		else
			std::cout << "unique_ptr_second does not exist\n";
		std::cout << "pointer " << *pointer<<std::endl;
		unique_ptr_first.reset(pointer);
		std::cout << "unique_ptr_first.reset(pointer)\n";
		std::cout << "unique_ptr_first: " << *unique_ptr_first << std::endl;
		unique_ptr_type<BoolFunc> unique_ptr_third(new BoolFunc(4, true));
		bool value = (unique_ptr_first == unique_ptr_third);
		std::cout << "unique_ptr_third: " << *unique_ptr_third << std::endl;
		std::cout << "unique_ptr_first == unique_ptr_third: " << value << std::endl;
	}/////////////////////////////////////////

	{/////////////////////////////////////////
		std::cout << "\nshared_ptr: \n" << std::endl;
		shared_ptr_type<BoolFunc>shared_ptr_first(new BoolFunc(2, true));
		shared_ptr_type<BoolFunc>shared_ptr_second(new BoolFunc(1, false));
		shared_ptr_type<BoolFunc>shared_ptr_third(shared_ptr_first);
		std::cout << "shared_ptr_first: " << *shared_ptr_first << std::endl;
		std::cout << "shared_ptr_second: " << *shared_ptr_second << std::endl;
		std::cout << "shared_ptr_third: " << *shared_ptr_third << std::endl;
		std::cout << "shared_ptr_third = shared_ptr_first\n";
		shared_ptr_third = shared_ptr_first;
		std::cout << "shared_ptr_third: " << *shared_ptr_third << std::endl;
		std::cout << "shared_ptr_first: " << shared_ptr_first.use_count() << " ptrs\n";
		std::cout << "shared_ptr_third.reset()\n";
		shared_ptr_third.reset();
		std::cout << "shared_ptr_first: " << shared_ptr_first.use_count() << " ptrs\n";
		std::cout << "shared_ptr_first.swap(shared_ptr_second)\n";
		shared_ptr_first.swap(shared_ptr_second);
		std::cout << "shared_ptr_first: " << *shared_ptr_first << std::endl;
		std::cout << "shared_ptr_second: " << *shared_ptr_second << std::endl;
		if (shared_ptr_third)
			std::cout << "shared_ptr_third: " << *shared_ptr_third << std::endl;
	}/////////////////////////////////////////

	{/////////////////////////////////////////
		std::cout << "\ncollection_type:\n\n";
		collection_type<BoolFunc>collection_first(2, BoolFunc(2, true));
		collection_type<BoolFunc>collection_second(3, BoolFunc(2, false));
		std::cout << "collection_first: ";

		for (BoolFunc n : collection_first)
			std::cout << n;

		auto beg = collection_first.begin();
		auto en = collection_first.end();
		while (beg != en)
		{
			std::cout << *beg << " ";
			++beg;
		}


		std::cout << "\ncollection_second: ";
		for (BoolFunc n : collection_second)
			std::cout << n;
		std::cout << "\ncollection_first: " << collection_first.size() << " elements\n";
		std::cout << "collection_first.insert(collection_first.begin(), BoolFunc(2, false))";
		collection_first.insert(collection_first.begin(), BoolFunc(2, false));
		std::cout << "\ncollection_first: ";
		for (BoolFunc n : collection_first)
			std::cout << n;
		std::cout << std::endl << "\ncollection_first: " << collection_first.size() << " elements";
		std::cout << std::endl;
		std::cout << "collection_first.erase(begin())";
		//iterator_list<BoolFunc> en = c1.end();
		collection_first.erase(collection_first.begin());
		std::cout << std::endl << "collection_first: " << collection_first.size() << " elements";
		std::cout << "\ncollection_first: ";
		for (BoolFunc n : collection_first)
			std::cout << n;
	}/////////////////////////////////////////
	{/////////////////////////////////////////
		std::cout <<"\n\ncollection_type<shared_ptr_type<BoolFunc>>\n\n";
		shared_ptr_type<BoolFunc> shared_ptr_first(new BoolFunc(2, true));
		collection_type<shared_ptr_type<BoolFunc>> collection_shared_first(4,shared_ptr_first);
		collection_type<shared_ptr_type<BoolFunc>> collection_shared_second(2,shared_ptr_type<BoolFunc>(new BoolFunc(1, false)));
		collection_type<shared_ptr_type<BoolFunc>> collection_shared_third(collection_shared_second);
		std::cout << "collection_shared_first: " ;
		for (shared_ptr_type<BoolFunc> n : collection_shared_first)
		{
			std::cout << *n;
			std::cout << " ";
		}
		std::cout << "\ncollection_shared_first: " << shared_ptr_first.use_count() << " pointers\n";

		std::cout << std::endl;
		std::cout << "\ncollection_shared_second: ";
		for (shared_ptr_type<BoolFunc> n : collection_shared_second)
		{
			std::cout << *n;
			std::cout << " ";
		}
		std::cout << std::endl;
		std::cout << "collection_shared_third: " ;
		for (shared_ptr_type<BoolFunc> n : collection_shared_third)
		{
			std::cout << *n;
			std::cout << " ";
		}
		std::cout << std::endl;
		std::cout << "\ncollection_shared_first: " << collection_shared_first.size() << " elements\n";
		std::cout << "\ncollection_shared_first.insert(collection_shared_first.begin(), BoolFunc(2, false))";

		collection_shared_first.insert(collection_shared_first.begin(), shared_ptr_type<BoolFunc>(new BoolFunc(2, false)));
		std::cout << "\ncollection_shared_first: ";
		for (shared_ptr_type<BoolFunc> n : collection_shared_first)
		{
			std::cout << *n;
			std::cout << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl << "collection_shared_first: " << collection_shared_first.size() << " elements";
		std::cout << std::endl;
		std::cout << "collection_shared_first.erase(collection_shared_first.begin())";
		//iterator_list<BoolFunc> en = c1.end();
		collection_shared_first.erase(collection_shared_first.begin());
		std::cout << "collection_shared_first: " << collection_shared_first.size() << " elements";
		std::cout << "\ncollection_shared_first: ";
		for (shared_ptr_type<BoolFunc> n : collection_shared_first)
		{
			std::cout << *n;
			std::cout << " ";
		}
		std::cout << std::endl;
	}/////////////////////////////////////////
	return 0;
}*/