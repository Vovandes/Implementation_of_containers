//#include <iostream>
//#include <vector>

#include "myvector.hpp"
#include "mylist.hpp"
#include "mydeque.hpp"

#include "module_test.hpp"

int main() {
	std::setlocale(LC_ALL, "");
	//-------------------------------------------------------------------------------------------------
	// MyVector
	mtd::vector<int> vect;
	ModulTest("vect", vect);
	//-------------------------------------------------------------------------------------------------
	// MyList
	mtd::list<int> ml;
	ModulTest("list", ml);
	//-------------------------------------------------------------------------------------------------
	// MyDeque
	mtd::deque<int> d;
	ModulTest("deque", d);
	//-------------------------------------------------------------------------------------------------
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << std::endl << "Push Enter key..." << std::cin.get();

	return 0;
}