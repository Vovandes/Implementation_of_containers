#pragma once

#include <iostream>
#include <algorithm>
#include <initializer_list>

namespace mtd {
	template <typename Q>
	class list {
		template <typename Q>
		class Node;
	public:
		//-------------------------------------------------------------------------------------------------
		// Class Iterator:
		class iterator {
		public:
			iterator(Node<Q>* elem = nullptr) : elem_{ elem } {}
			iterator(const iterator& it) : iterator{ it.elem_ } {}
			~iterator() = default;
			bool operator==(const iterator& rhs) const { return (elem_ == rhs.elem_); }
			bool operator!=(const iterator& rhs) const { return !(*this == rhs); }
			iterator& operator++() {
				elem_ = elem_->pNext;
				return *this;
			}
			iterator& operator++(int) {
				auto tmp = this;
				elem_ = elem_->pNext;
				return *tmp;
			}
			iterator operator +(std::size_t index) {
				while (index) {
					elem_ = elem_->pNext;
					--index;
				}
				return *this;
			}
			Q& operator*() { return elem_->data; }
		private:
			Node<Q>* elem_;
		};
		iterator begin() { return iterator(head_); }
		iterator end() { return iterator(nullptr); }
		const iterator begin() const { return iterator(head_); }
		const iterator end() const { return iterator(nullptr); }
		//-------------------------------------------------------------------------------------------------
		// Class Const_Iterator:
		class const_iterator {
		public:
			const_iterator(Node<Q>* elem = nullptr) : elem_{ elem } {}
			const_iterator(const const_iterator& it) : const_iterator{ it.elem_ } {}
			~const_iterator() = default;
			bool operator==(const const_iterator& rhs) const { return (elem_ == rhs.elem_); }
			bool operator!=(const const_iterator& rhs) const { return !(*this == rhs); }
			const_iterator& operator++() {
				elem_ = elem_->pNext;
				return *this;
			}
			const_iterator& operator++(int) {
				auto tmp = this;
				elem_ = elem_->pNext;
				return *tmp;
			}
			const_iterator operator +(std::size_t index) {
				while (index) {
					elem_ = elem_->pNext;
					--index;
				}
				return *this;
			}
			const Q& operator*() const { return elem_->data; }
		private:
			Node<Q>* elem_;
		};
		const_iterator cbegin() const { return const_iterator(head_); }
		const_iterator cend() const { return const_iterator(nullptr); }
		//-------------------------------------------------------------------------------------------------
		list();
		list(const Q value);
		list(const std::initializer_list<Q> l);

		list(const list& rhs);
		list(list&& rhs) noexcept;

		// Copy Assignment:
		list<Q>& operator = (const list<Q>& rhs);
		// Move Assignment:
		list<Q>& operator = (list<Q>&& rhs) noexcept;

		~list();
		//-------------------------------------------------------------------------------------------------
		// Add
		void push_back(const Q& value);
		void push_front(const Q& value);
		void insert(const std::size_t index, const Q& value);
		//-------------------------------------------------------------------------------------------------
		// Sub
		void pop_front();
		void pop_back();
		void erase(const std::size_t index);
		void clear();

		const Q& at(const std::size_t index) const;
		Q& at(const std::size_t index);

		std::size_t size() const { return size_; }
		bool empty() const { return !size_; }

		const Q& operator [](const std::size_t index) const;
		Q& operator [](const std::size_t index);
	private:
		//-------------------------------------------------------------------------------------------------
		template <typename Q>
		class Node {
		public:
			Node* pNext;
			Q data;
			Node(const Q data = Q{}, Node* pNext = nullptr) : data{ data }, pNext{ pNext } {};
			Node(const Node& node) : Node(node.data, node.pNext) {};
		};
		//-------------------------------------------------------------------------------------------------

		bool if_index_large_size(const std::size_t index) const;

		std::size_t size_;
		Node<Q>* head_;
	};
	//-------------------------------------------------------------------------------------------------
	// Constructors:
	template <typename Q>
	inline list<Q>::list()
		:head_{ nullptr }
		, size_{ 0 }
	{};
	template <typename Q>
	inline list<Q>::list(const Q value)
		: head_{ new Node<Q>{value} }
		, size_{ 1 }
	{};
	template <typename Q>
	inline list<Q>::list(const std::initializer_list<Q> l)
		: list()
	{
		for (const auto& elem : l) {
			push_back(elem);
		}
	};
	//-------------------------------------------------------------------------------------------------
	// Copy Constructor:
	template <typename Q>
	inline list<Q>::list(const list& rhs)
		: list()
	{
		auto tmp = rhs.head_;
		while (tmp) {
			push_back(tmp->data);
			tmp = tmp->pNext;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Move Constructor:
	template <typename Q>
	inline list<Q>::list(list&& rhs) noexcept
		: head_{ rhs.head_ }
		, size_{ rhs.size_ }
	{
		rhs.head_ = nullptr;
	}
	//-------------------------------------------------------------------------------------------------
	// Copy Assignment:
	template<typename Q>
	inline list<Q>& list<Q>::operator=(const list<Q>& rhs) {
		clear();
		auto tmp = rhs.head_;
		while (tmp) {
			push_back(tmp->data);
			tmp = tmp->pNext;
		}
		return *this;
	}
	//-------------------------------------------------------------------------------------------------
	// Move Assignment:
	template<typename Q>
	inline list<Q>& list<Q>::operator=(list<Q>&& rhs) noexcept {
		size_ = std::move(rhs.size_);
		head_ = std::move(rhs.head_);
		rhs.head_ = nullptr;
		return *this;
	}
	//-------------------------------------------------------------------------------------------------
	// Destructor:
	template <typename Q>
	inline list<Q>::~list() {
		if (head_) {
			clear();
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method push_back:
	template <typename Q>
	inline void list<Q>::push_back(const Q& value) {
		if (!head_) {
			head_ = new Node<Q>{ value };
		}
		else {
			Node<Q>* new_current = head_;
			while (new_current->pNext) {
				new_current = new_current->pNext;
			}
			new_current->pNext = new Node<Q>{ value };
			new_current = new_current->pNext;
		}
		++size_;
	}
	//-------------------------------------------------------------------------------------------------
	// Method push_front:
	template <typename Q>
	inline void list<Q>::push_front(const Q& value) {
		head_ = new Node<Q>{ value, head_ };
		++size_;
	}
	//-------------------------------------------------------------------------------------------------
	// Method insert:
	template <typename Q>
	inline void list<Q>::insert(const std::size_t index, const Q& value) {
		if (if_index_large_size(index)) {
			std::cout << "Error! Incorrect Index!" << std::endl;
			return;
		}
		if (index == 0) {
			push_front(value);
		}
		else {
			std::size_t count{ 1 };
			Node<Q>* new_current = head_;
			while (count < index) {
				new_current = new_current->pNext;
				++count;
			}
			new_current->pNext = new Node<Q>{ value, new_current->pNext };
			++size_;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method pop_front:
	template <typename Q>
	inline void list<Q>::pop_front() {
		if (empty()) {
			std::cout << "Error! Container is empty! Removal is not possible!" << std::endl;
			return;
		}
		Node<Q>* tmp = head_;
		head_ = head_->pNext;
		delete tmp;
		--size_;
	}
	//-------------------------------------------------------------------------------------------------
	// Method pop_back:
	template <typename Q>
	inline void list<Q>::pop_back() {
		if (empty()) {
			return;
		}
		else {
			erase(size_);
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method erase:
	template <typename Q>
	inline void list<Q>::erase(const std::size_t index) {
		if (empty()) {
			std::cout << "Error! Container is empty! Removal is not possible!" << std::endl;
			return;
		}
		if (!index) {
			pop_front();
		}
		else {
			if (if_index_large_size(index)) {
				std::cout << "Error! " << index << " is incorrect Index!" << std::endl;
				return;
			}
			else {
				Node<Q>* new_current = head_;
				std::size_t count{ 1 };
				while (count < index - 1) {
					new_current = new_current->pNext;
					++count;
				}
				Node<Q>* past_current = new_current->pNext;
				new_current->pNext = past_current->pNext;
				delete past_current;
				--size_;
			}
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method clear:
	template <typename Q>
	inline void list<Q>::clear() {
		if (!empty()) {
			while (size_) {
				pop_front();
			}
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Function bool if index larger than size return true
	template <typename Q>
	inline bool list<Q>::if_index_large_size(const std::size_t index) const {
		return index >= size_;
	}
	template<typename Q>
	inline const Q& list<Q>::at(const std::size_t index) const {
		try {
			if (if_index_large_size(index)) {
				throw std::runtime_error("error(1): going beyond the array limit. return first element");
			}
			if (empty()) {
				throw "error(2): container is empty. exit(1)";
			}
			return this->operator[](index);
		}
		catch (const std::exception& ex) {
			std::cerr << "main(exception): " << ex.what() << ": ";
			return head_->data;
		}
		catch (const char* msg) {
			std::cerr << "main(exception): " << msg << std::endl;
			std::exit(1);
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Functions at() with check index
	template <typename Q>
	inline Q& list<Q>::at(const std::size_t index) {
		return const_cast<Q&>(static_cast<const list<Q>&>(*this).at(index));
	}
	//-------------------------------------------------------------------------------------------------
	// Overload operator []() const:
	template <typename Q>
	inline const Q& list<Q>::operator[](const std::size_t index) const {
		Node<Q>* new_current = head_;
		std::size_t count{ 0 };
		while (new_current) {
			if (count == index) {
				return new_current->data;
			}
			new_current = new_current->pNext;
			++count;
		}
		return head_->data;
	}
	//-------------------------------------------------------------------------------------------------
	// Overload operator []():
	template <typename Q>
	inline Q& list<Q>::operator[](const std::size_t index) {
		return const_cast<Q&>(static_cast<const list<Q>&>(*this)[index]);
	}
}
