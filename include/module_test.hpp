#pragma once

#include <iostream>
#include <ctime>
#include <string_view>

#include "myvector.hpp"
#include "mylist.hpp"
#include "mydeque.hpp"

//-------------------------------------------------------------------------------------------------
template <typename Q>
void PrintOneContainer(const std::string_view& name_container, const Q& object) {
	if (object.empty()) {
		std::cout << "Container is empty!" << std::endl;
	}
	else {
		// Output with rfor cycle:
		std::cout << "Output with rfor cycle:\t\t";
		std::cout << "Container " << name_container << ":\t";
		for (const auto& elem : object) {
			std::cout << elem << "   ";
		}
		std::cout << std::endl;
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Q>
void PrintContainers(const std::string_view& name_container, const Q& object) {
	if (object.empty()) {
		std::cout << "Container is empty!" << std::endl;
	}
	else {
		// Output with rfor cycle:
		std::cout << "Output with rfor cycle:\t\t";
		std::cout << "Container " << name_container << ":\t";
		for (const auto& elem : object) {
			std::cout << elem << "   ";
		}
		std::cout << std::endl;

		// Output with class iterator:
		std::cout << "Output with class iterator:\t";
		std::cout << "Container " << name_container << ":\t";
		for (auto it = object.cbegin(); it != object.cend(); ++it) {
			std::cout << *it << "   ";
		}
		std::cout << std::endl;

		// Output with operator []:
		std::cout << "Output with operator []:\t";
		std::cout << "Container " << name_container << ":\t";
		for (std::size_t i = 0; i < object.size(); ++i) {
			std::cout << object[i] << "   ";
		}
	}
	std::cout << std::endl;
}
//-------------------------------------------------------------------------------------------------
template <typename Q>
void FillRandomValuesContainer(Q& object) {
	std::srand(static_cast<std::size_t>(std::time(nullptr)));
	for (std::size_t i = 0; i < 10; ++i) {
		auto x = -10 + std::rand() % 21;
		object.push_back(x);
	}
}
//-------------------------------------------------------------------------------------------------
template <typename Q>
void ModulTest(const std::string_view& name_container, Q& object) {
	std::cout << "//////////////////////////////////////////////////////////////////////////" << std::endl;
	// Если контейнер пустой заполняем:
	if (object.empty()) {
		std::cout << "Container " << name_container << " is empty!" << std::endl;
		std::cout << "Fill container " << name_container << std::endl;
		//FillRandomValuesContainer(object);
		for (auto i = 0; i < 10; ++i) {
			object.push_back(i);
		}
	}
	PrintContainers(name_container, object);

	std::cout << std::endl << "Container size is " << object.size() << std::endl;

	std::cout << std::endl << "Удаление третьего (по счёту), пятого и седьмого элементов method erase()" << std::endl;
	object.erase(7);
	object.erase(5);
	object.erase(3);
	PrintOneContainer(name_container, object);
	std::cout << std::endl << "Container size is " << object.size() << std::endl;

	std::cout << std::endl << "Добавление элемента 10 в начало контейнера method push_front()" << std::endl;
	object.push_front(10);
	PrintOneContainer(name_container, object);
	std::cout << std::endl << "Container size is " << object.size() << std::endl;

	std::cout << std::endl << "Добавление элемента 20 в середину контейнера method insert()" << std::endl;
	object.insert(object.size() / 2, 20);
	PrintOneContainer(name_container, object);
	std::cout << std::endl << "Container size is " << object.size() << std::endl;

	std::cout << std::endl << "Добавление элемента 30 в конец контейнера method push_back()" << std::endl;
	object.push_back(30);
	PrintOneContainer(name_container, object);
	std::cout << std::endl << "Container size is " << object.size() << std::endl;

	std::cout << std::endl << "method at()" << std::endl;
	std::cout << object.at(object.size() + 1) << std::endl;

	std::cout << "//////////////////////////////////////////////////////////////////////////" << std::endl;
}
//-------------------------------------------------------------------------------------------------