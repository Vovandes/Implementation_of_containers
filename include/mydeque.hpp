#pragma once

#include <iostream>
#include <algorithm>
#include <initializer_list>

namespace mtd {
	template <typename Q>
	class deque {
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
			bool operator!=(const iterator& rhs) const { return (elem_ != rhs.elem_); }
			iterator& operator++() {
				elem_ = elem_->pNext;
				return *this;
			}
			iterator& operator++(int) {
				auto tmp = this;
				elem_ = elem_->pNext;
				return *tmp;
			}
			iterator& operator--() {
				elem_ = elem_->pPrev;
				return *this;
			}
			iterator& operator--(int) {
				auto tmp = this;
				elem_ = elem_->pPrev;
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
		iterator end() { return iterator(tail_->pNext); }
		iterator begin() const { return iterator(head_); }
		iterator end() const { return iterator(tail_->pNext); }
		//-------------------------------------------------------------------------------------------------
		// Class Reverse_Iterator:
		class reverse_iterator {
		public:
			reverse_iterator(Node<Q>* elem = nullptr) : elem_{ elem } {}
			reverse_iterator(const reverse_iterator& it) : reverse_iterator{ it.elem_ } {}
			~reverse_iterator() = default;
			bool operator==(const reverse_iterator& rhs) const { return (elem_ == rhs.elem_); }
			bool operator!=(const reverse_iterator& rhs) const { return (elem_ != rhs.elem_); }
			reverse_iterator& operator++() {
				elem_ = elem_->pPrev;
				return *this;
			}
			reverse_iterator& operator++(int) {
				auto tmp = this;
				elem_ = elem_->pPrev;
				return *tmp;
			}
			reverse_iterator& operator--() {
				elem_ = elem_->pNext;
				return *this;
			}
			reverse_iterator& operator--(int) {
				auto tmp = this;
				elem_ = elem_->pNext;
				return *tmp;
			}
			reverse_iterator operator +(std::size_t index) {
				while (index) {
					elem_ = elem_->pPrev;
					--index;
				}
				return *this;
			}
			Q& operator*() { return elem_->data; }
		private:
			Node<Q>* elem_;
		};
		reverse_iterator rbegin() { return reverse_iterator(tail_); }
		reverse_iterator rend() { return reverse_iterator(head_->pPrev); }
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
			const_iterator& operator--() {
				elem_ = elem_->pPrev;
				return *this;
			}
			const_iterator& operator--(int) {
				auto tmp = this;
				elem_ = elem_->pPrev;
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
		const_iterator cend() const { return const_iterator(tail_->pNext); }
		//-------------------------------------------------------------------------------------------------
		// Class Const Reverse_Iterator:
		class const_reverse_iterator {
		public:
			const_reverse_iterator(Node<Q>* elem = nullptr) : elem_{ elem } {}
			const_reverse_iterator(const const_reverse_iterator& it) : const_reverse_iterator{ it.elem_ } {}
			~const_reverse_iterator() = default;
			bool operator==(const const_reverse_iterator& rhs) const { return (elem_ == rhs.elem_); }
			bool operator!=(const const_reverse_iterator& rhs) const { return (elem_ != rhs.elem_); }
			const_reverse_iterator& operator++() {
				elem_ = elem_->pPrev;
				return *this;
			}
			const_reverse_iterator& operator++(int) {
				auto tmp = this;
				elem_ = elem_->pPrev;
				return *tmp;
			}
			const_reverse_iterator& operator--() {
				elem_ = elem_->pNext;
				return *this;
			}
			const_reverse_iterator& operator--(int) {
				auto tmp = this;
				elem_ = elem_->pNext;
				return *tmp;
			}
			const_reverse_iterator operator +(std::size_t index) {
				while (index) {
					elem_ = elem_->pPrev;
					--index;
				}
				return *this;
			}
			Q& operator*() const { return elem_->data; }
		private:
			Node<Q>* elem_;
		};
		const_reverse_iterator crbegin() const { return const_reverse_iterator(tail_); }
		const_reverse_iterator crend() const { return const_reverse_iterator(head_->pPrev); }
		//-------------------------------------------------------------------------------------------------
		deque();
		deque(const Q value);
		deque(const std::initializer_list<Q> l);

		deque(const deque& rhs);
		deque(deque&& rhs) noexcept;

		~deque();
		//-------------------------------------------------------------------------------------------------
		// Copy Assignment:
		deque<Q>& operator = (const deque<Q>& rhs);
		// Move Assignment:
		deque<Q>& operator = (deque<Q>&& rhs) noexcept;
		//-------------------------------------------------------------------------------------------------
		// Add
		void push_back(const Q value);
		void push_front(const Q value);
		void insert(std::size_t index, const Q value);
		//-------------------------------------------------------------------------------------------------
		// Sub
		void pop_front();
		void pop_back();
		void erase(std::size_t index);
		void clear();
		//-------------------------------------------------------------------------------------------------
		Q& at(std::size_t index);
		const Q& at(std::size_t index) const;
		//void PrintDeque();
		//-------------------------------------------------------------------------------------------------
		std::size_t size() const { return size_; }
		bool empty() const { return !size_; }
		//-------------------------------------------------------------------------------------------------
		const Q& operator [](std::size_t index) const;
		Q& operator [](std::size_t index);
		//-------------------------------------------------------------------------------------------------
	private:
		//-------------------------------------------------------------------------------------------------
		template <typename Q>
		class Node {
		public:
			Node* pPrev;
			Node* pNext;
			Q data;
			Node(const Q data = Q{}, Node* pPrev = nullptr, Node* pNext = nullptr) : data{ data }, pPrev{ pPrev }, pNext{ pNext } {};
			Node(const Node& node) : Node(node.data, node.pPrev, node.pNext) {};
		};
		//-------------------------------------------------------------------------------------------------
		bool if_index_large_size(const std::size_t index) const;
		//-------------------------------------------------------------------------------------------------
		std::size_t size_;
		Node<Q>* head_;
		Node<Q>* tail_;
	};
	//-------------------------------------------------------------------------------------------------
	// Constructors:
	// #1 +
	template <typename Q>
	inline deque<Q>::deque()
		:head_{ nullptr }
		, tail_{ nullptr }
		, size_{ 0 } {}
	//-------------------------------------------------------------------------------------------------
	// #2 +
	template <typename Q>
	inline deque<Q>::deque(const Q value)
		: head_{ new Node<Q>{value} }
		, tail_{ head_ }
		, size_{ 1 }
	{ }
	//-------------------------------------------------------------------------------------------------
	// #3 +
	template <typename Q>
	inline deque<Q>::deque(const std::initializer_list<Q> l)
		: deque()
	{
		for (const auto& elem : l) {
			push_back(elem);
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Copy Constructor:
	template <typename Q>
	inline deque<Q>::deque(const deque& rhs)
		: deque()
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
	inline deque<Q>::deque(deque&& rhs) noexcept
		: head_{ rhs.head_ }
		, tail_{ rhs.tail_ }
		, size_{ rhs.size_ }
	{
		rhs.head_ = nullptr;
		rhs.tail_ = nullptr;
	}
	//-------------------------------------------------------------------------------------------------
	// Copy Assignment:
	template<typename Q>
	inline deque<Q>& deque<Q>::operator=(const deque<Q>& rhs) {
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
	inline deque<Q>& deque<Q>::operator=(deque<Q>&& rhs) noexcept {
		size_ = std::move(rhs.size_);
		head_ = std::move(rhs.head_);
		tail_ = std::move(rhs.tail_);
		rhs.head_ = nullptr;
		rhs.tail_ = nullptr;
		return *this;
	}
	//-------------------------------------------------------------------------------------------------
	// Destructor:
	template <typename Q>
	inline deque<Q>::~deque() {
		if (head_) {
			clear();
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method push_back:
	template <typename Q>
	inline void deque<Q>::push_back(const Q value) {
		if (empty()) {
			head_ = new Node<Q>{ value };
			tail_ = head_;
			++size_;
		}
		else {
			auto new_current = tail_;
			new_current->pPrev = tail_->pPrev;
			new_current->pNext = new Node<Q>{ value };
			tail_ = new_current->pNext;
			tail_->pPrev = new_current;
			++size_;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method push_front:
	template <typename Q>
	inline void deque<Q>::push_front(const Q value) {
		if (empty()) {
			head_ = new Node<Q>{ value };
			tail_ = head_;
			++size_;
		}
		else {
			head_ = new Node<Q>{ value, nullptr, head_ };
			auto tmp = head_->pNext;
			tmp->pPrev = head_;
			tmp = nullptr;
			++size_;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method insert:
	template <typename Q>
	inline void deque<Q>::insert(std::size_t index, const Q value) {
		if (if_index_large_size(index)) {
			std::cout << "Error! Incorrect Index!" << std::endl;
			return;
		}
		if (!index) {
			push_front(value);
		}
		else if (index == size_) {
			push_back(value);
		}
		else if (index > size_ / 2) {
			index = size_ - index;
			auto new_current = tail_;
			while (index--) {
				new_current = new_current->pPrev;
			}
			auto tmp = new_current;
			auto tmp2 = new_current->pNext;
			new_current->pNext = new Node<Q>{ value };
			new_current = new_current->pNext;
			new_current->pNext = tmp2;
			tmp2->pPrev = new_current;
			new_current->pPrev = tmp;

			++size_;
		}
		else {
			auto new_current = head_;
			while (--index) {
				new_current = new_current->pNext;
			}
			auto tmp = new_current;
			auto tmp2 = new_current->pNext;
			new_current->pNext = new Node<Q>{ value };
			new_current = new_current->pNext;
			new_current->pNext = tmp2;
			tmp2->pPrev = new_current;
			new_current->pPrev = tmp;

			++size_;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method pop_front:
	template <typename Q>
	inline void deque<Q>::pop_front() {
		if (empty()) {
			std::cout << "Error! Container is empty! Removal is not possible!" << std::endl;
			return;
		}
		Node<Q>* tmp = head_;
		head_ = head_->pNext;
		delete tmp;
		--size_;
		size_ ? head_->pPrev = nullptr : (head_ = nullptr, tail_ = nullptr);
	}
	//-------------------------------------------------------------------------------------------------
	// Method pop_back:
	template <typename Q>
	inline void deque<Q>::pop_back() {
		if (empty()) {
			std::cout << "Error! Container is empty! Removal is not possible!" << std::endl;
			return;
		}
		Node<Q>* tmp = tail_;
		tail_ = tail_->pPrev;
		delete tmp;
		--size_;
		size_ ? tail_->pNext = nullptr : (head_ = nullptr, tail_ = nullptr);
	}
	//-------------------------------------------------------------------------------------------------
	// Method erase:
	template <typename Q>
	inline void deque<Q>::erase(std::size_t index) {
		if (empty()) {
			std::cout << "Error! Container is empty! Removal is not possible!" << std::endl;
			return;
		}
		if (if_index_large_size(index)) {
			std::cout << "Error! " << index << " is incorrect Index!" << std::endl;
			return;
		}
		if (!index) {
			pop_front();
		}
		else if (index == size_) {
			pop_back();
		}
		else if (index > size_ / 2) {
			index = size_ - index;
			auto new_current = tail_;
			while (index--) {
				new_current = new_current->pPrev;
			}
			auto tmp = new_current->pPrev;
			auto tmp2 = new_current->pNext;
			tmp->pNext = tmp2;
			tmp2->pPrev = tmp;
			delete new_current;
			--size_;
		}
		else {
			auto new_current = head_;
			while (--index) {
				new_current = new_current->pNext;
			}
			auto tmp = new_current->pPrev;
			auto tmp2 = new_current->pNext;
			tmp->pNext = tmp2;
			tmp2->pPrev = tmp;
			delete new_current;
			--size_;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Method clear:
	template <typename Q>
	inline void deque<Q>::clear() {
		if (!empty()) {
			while (size_) {
				pop_back();
			}
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Function bool if index larger than size return true
	template <typename Q>
	inline bool deque<Q>::if_index_large_size(const std::size_t index) const {
		return index > size_;
	}
	//-------------------------------------------------------------------------------------------------
	// Functions at() with check index
	template <typename Q>
	inline Q& deque<Q>::at(std::size_t index) {
		return const_cast<Q&>(static_cast<const deque<Q>&>(*this).at(index));
	}
	template<typename Q>
	inline const Q& deque<Q>::at(std::size_t index) const {
		if (empty()) {
			std::cout << "Error! Container is empty!" << std::endl;
			std::exit(1);
		}
		else if (if_index_large_size(index)) {
			std::cout << "Error! Incorrect Index! Return first element" << std::endl;
			return head_->data;
		}
		else if (index > size_ / 2) {
			index = size_ - 1 - index;
			Node<Q>* new_current = tail_;
			while (index--) {
				new_current = new_current->pPrev;
			}
			return new_current->data;
		}
		else {
			Node<Q>* new_current = head_;
			while (index--) {
				new_current = new_current->pNext;
			}
			return new_current->data;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Overload operator []() const:
	template <typename Q>
	inline const Q& deque<Q>::operator[](std::size_t index) const {
		if (index > size_ / 2) {
			index = size_ - 1 - index;
			Node<Q>* new_current = tail_;
			while (index--) {
				new_current = new_current->pPrev;
			}
			return new_current->data;
		}
		else {
			Node<Q>* new_current = head_;
			while (index--) {
				new_current = new_current->pNext;
			}
			return new_current->data;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Overload operator []():
	template <typename Q>
	inline Q& deque<Q>::operator[](std::size_t index) {
		return const_cast<Q&>(static_cast<const deque<Q>&>(*this)[index]);
	}
}
