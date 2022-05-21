#include "list.hpp"
#include <iostream>

int main()
{
	List<int> list;

	for (int i{}; i < 10; i++)
	{
		list.push_back(rand() % 100 + 20);
	}


	//tests, ne trogai biliet!
	//list.partition();

	auto listB = list.begin();
	auto listE = list.end();

	for (listB; listB != listE; listB++)
	{
		std::cout << *listB << " ";
	}
	return 0;
}
