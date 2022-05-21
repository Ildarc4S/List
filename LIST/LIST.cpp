#include "list.hpp"
#include <iostream>

int main()
{
	srand(time(NULL));
	List<int> list;

	for (int i{}; i < 20; i++)
	{
		list.push_back(rand() % 100 + 20);
	}

	auto listAB = list.begin();
	auto listAE = list.end();

	for (listAB; listAB != listAE; listAB++)
	{
		std::cout << *listAB << " ";
	}

	std::cout << "\n";

	//test, ne trogai biliet!hhh
	list.sort();

	auto listB = list.begin();
	auto listE = list.end();

	for (listB; listB != listE; listB++)
	{
		std::cout << *listB << " ";
	}
	return 0;
}
