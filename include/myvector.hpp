#pragma once

#include <iostream>
#include <algorithm>
#include <initializer_list>

namespace mtd {
	template <typename Q>
	class vector {
	public:
		//-------------------------------------------------------------------------------------------------		
		// Class Iterator:
		class iterator {
		public:
			iterator(Q* elem) : elem_{ elem } {}
			iterator(const iterator& it) : iterator{ it.elem_ } {}
			~iterator() = default;

			iterator operator +(std::size_t ind) { return elem_ + ind; }
			iterator operator -(std::size_t ind) { return elem_ - ind; }
			iterator& operator ++(int) {
				auto tmp = elem_;
				++elem_;
				return *tmp;
			}
			iterator& operator --(int) {
				auto tmp = elem_;
				--elem_;
				return *tmp;
			}
			iterator& operator ++() {
				++elem_;
				return *this;
			}
			iterator& operator --() {
				--elem_;
				return *this;
			}

			bool operator ==(const iterator& iter) const { return elem_ == iter.elem_; }
			bool operator !=(const iterator& iter) const { return !(elem_ == iter.elem_); }

			Q& operator *() { return *elem_; }
		private:
			Q* elem_;
		};
		iterator begin() { return iterator(data_); }
		iterator end() { return iterator(data_ + size_); }
		const iterator begin() const { return iterator(data_); }
		const iterator end() const { return iterator(data_ + size_); }
		//-------------------------------------------------------------------------------------------------
		// Class Const_Iterator:
		class const_iterator {
		public:
			const_iterator(Q* elem) : elem_{ elem } {}
			const_iterator(const const_iterator& it) : const_iterator{ it.elem_ } {}
			~const_iterator() = default;

			const_iterator operator +(std::size_t ind) { return elem_ + ind; }
			const_iterator operator -(std::size_t ind) { return elem_ - ind; }
			const_iterator& operator ++(int) {
				auto tmp = elem_;
				++elem_;
				return *tmp;
			}
			const_iterator& operator --(int) {
				auto tmp = elem_;
				--elem_;
				return *tmp;
			}
			const_iterator& operator ++() {
				++elem_;
				return *this;
			}
			const_iterator& operator --() {
				--elem_;
				return *this;
			}

			bool operator ==(const const_iterator& iter) const { return elem_ == iter.elem_; }
			bool operator !=(const const_iterator& iter) const { return !(elem_ == iter.elem_); }

			const Q& operator *() const { return *elem_; }
		private:
			Q* elem_;
		};
		const_iterator cbegin() const { return const_iterator(data_); }
		const_iterator cend() const { return const_iterator(data_ + size_); }
		//-------------------------------------------------------------------------------------------------
		// Constructors:
		vector();
		vector(std::initializer_list<Q> l);
		// Destructor:
		~vector();
		// Copy Constructor:
		vector(const vector& rhs);
		// Move Constructor:
		vector(vector&& rhs) noexcept;
		//-------------------------------------------------------------------------------------------------
		// Copy Assignment:
		vector<Q>& operator = (const vector<Q>& rhs);
		// Move Assignment:
		vector<Q>& operator = (vector<Q>&& rhs) noexcept;
		//-------------------------------------------------------------------------------------------------
		// Overload operator *()
		Q& operator *() const { return *data_; }

		// Overload operator []()
		const Q& operator[](std::size_t index) const;
		Q& operator[](std::size_t index);
		//-------------------------------------------------------------------------------------------------
		// Functions with check Out of array
		const Q& at(std::size_t index) const;
		Q& at(std::size_t index);
		//-------------------------------------------------------------------------------------------------
		void push_back(const Q& value);
		void push_front(const Q& value);
		void insert(const std::size_t index, const Q& value);
		void erase(const std::size_t index);
		void clear();
		//-------------------------------------------------------------------------------------------------
		std::size_t size() const { return size_; }
		bool empty() const { return !size_; }
		//-------------------------------------------------------------------------------------------------
		static constexpr void CinGet() {
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cout << "Push Enter key..." << std::cin.get();
		}
	private:
		std::size_t size_;
		std::size_t capacity_;
		Q* data_;
		//-------------------------------------------------------------------------------------------------
		bool out_of_array(std::size_t value) const;
		bool capacity_is_small() const;
		void swap(vector<Q>& rhs) noexcept;
	};
	//-------------------------------------------------------------------------------------------------
	// Constructors:
	template <typename Q>
	inline vector<Q>::vector()
		: size_{ 0 }
		, capacity_{ 0 }
		, data_{ nullptr } {}
	template <typename Q>
	inline vector<Q>::vector(std::initializer_list<Q> l)
		: vector() {
		for (const auto& elem : l) {
			push_back(elem);
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Destructor:
	template <typename Q>
	inline vector<Q>::~vector() {
		clear();
	}
	//-------------------------------------------------------------------------------------------------
	// Copy Constructor:
	template <typename Q>
	inline vector<Q>::vector(const vector& rhs) : vector() {
		if (this != &rhs) {
			size_ = rhs.size_;
			capacity_ = rhs.capacity_;
			data_ = new Q[capacity_];
			std::copy(rhs.data_, rhs.data_ + rhs.size_, data_);
			//std::cout << "Copy ctor" << std::endl;
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Move Constructor:
	template <typename Q>
	inline vector<Q>::vector(vector&& rhs) noexcept
		:size_{ rhs.size_ }
		, capacity_{ rhs.capacity_ }
		, data_{ rhs.data_ ? rhs.data_ : nullptr } {
		rhs.data_ = nullptr;
	}
	//-------------------------------------------------------------------------------------------------
	// Copy Assignment:
	template <typename Q>
	inline vector<Q>& vector<Q>::operator=(const vector<Q>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		auto tmp{ rhs };
		swap(tmp);
		//std::cout << "Copy Assignment" << std::endl;
		return *this;
	}
	//-------------------------------------------------------------------------------------------------
	// Move Assignment:
	template <typename Q>
	inline vector<Q>& vector<Q>::operator=(vector<Q>&& rhs) noexcept {
		swap(rhs);
		rhs.data_ = nullptr;
		return *this;
	}
	//-------------------------------------------------------------------------------------------------
	// Overload operator []() const:
	template <typename Q>
	inline const Q& vector<Q>::operator[](std::size_t index) const {
		return data_[index];
	}
	// Overload operator []():
	template <typename Q>
	inline Q& vector<Q>::operator[](std::size_t index) {
		return const_cast<Q&>(static_cast<const vector<Q>&>(*this)[index]);
	}
	//-------------------------------------------------------------------------------------------------
	// Functions with check Out of array at() for const objects:
	template <typename Q>
	inline const Q& vector<Q>::at(std::size_t index) const {
		try {
			if (out_of_array(index)) {
				throw std::runtime_error("error(1): going beyond the array limit. return first element");
			}
			if (empty()) {
				throw "error(2): container is empty. exit(1)";
			}
			return this->operator[](index);
		}
		catch (const std::exception& ex) {
			std::cerr << "main(exception): " << ex.what() << ": ";
			return *data_;
		}
		catch (const char* msg) {
			std::cerr << "main(exception): " << msg << std::endl;
			std::exit(1);
		}
	}
	//-------------------------------------------------------------------------------------------------
	// Functions with check Out of array at():
	template <typename Q>
	inline Q& vector<Q>::at(std::size_t index) {
		return const_cast<Q&>(static_cast<const vector<Q>&>(*this).at(index));
	}
	//-------------------------------------------------------------------------------------------------
	// Method push_back:
	template <typename Q>
	inline void vector<Q>::push_back(const Q& value) {
		if (!data_ || capacity_is_small()) {
			capacity_ = (size_ + 1) * 2;
			auto new_region = new Q[capacity_];
			std::copy(data_, data_ + size_, new_region);
			new_region[size_] = value;
			delete[] data_;
			data_ = new_region;
		}
		else {
			data_[size_] = value;
		}
		++size_;
	}
	//-------------------------------------------------------------------------------------------------
	// Method push_front:
	template <typename Q>
	inline void vector<Q>::push_front(const Q& value) {
		if (capacity_is_small()) {
			capacity_ = (size_ + 1) * 2;
		}
		auto new_region = new Q[capacity_];
		new_region[0] = value;
		std::copy(data_, data_ + size_++, new_region + 1);
		delete[] data_;
		data_ = new_region;
	}
	//-------------------------------------------------------------------------------------------------
	// Method insert:
	template <typename Q>
	inline void vector<Q>::insert(const std::size_t index, const Q& value) {
		if (out_of_array(index)) {
			std::cout << "Error! Out of array!" << std::endl;
			return;
		}
		if (capacity_is_small()) {
			capacity_ = (size_ + 1) * 2;
		}
		auto new_region = new Q[capacity_];
		std::copy_n(data_, index, new_region);
		new_region[index] = value;
		std::copy_n(data_ + index, size_, new_region + index + 1);
		delete[] data_;
		data_ = new_region;
		++size_;
	}
	//-------------------------------------------------------------------------------------------------
	// Method erase:
	template <typename Q>
	inline void vector<Q>::erase(const std::size_t index) {
		if (out_of_array(index)) {
			std::cout << "Error! Out of array!" << std::endl;
			return;
		}
		if (size_ == 1) {
			delete[] data_;
			data_ = nullptr;
			--size_;
			capacity_ = 0;
			return;
		}
		auto new_region = new Q[size_];
		std::copy_n(data_, index - 1, new_region);
		std::copy_n(data_ + index, size_ - index, new_region + index - 1);
		std::copy(new_region, new_region + (--size_), data_);
		delete[] new_region;
		new_region = nullptr;
	}
	//-------------------------------------------------------------------------------------------------
	// Method clear:
	template <typename Q>
	inline void vector<Q>::clear() {
		if (data_) {
			delete[] data_;
			data_ = nullptr;
		}
		size_ = 0;
		capacity_ = 0;
	}
	//-------------------------------------------------------------------------------------------------
	// Out of array:
	template <typename Q>
	inline bool vector<Q>::out_of_array(std::size_t value) const {
		return value >= size_;
	}
	//-------------------------------------------------------------------------------------------------
	// Checking capacity:
	template <typename Q>
	inline bool vector<Q>::capacity_is_small() const {
		return capacity_ <= size_ || !data_;
	}
	//-------------------------------------------------------------------------------------------------
	// Swap Functions:
	template <typename Q>
	inline void vector<Q>::swap(vector<Q>& rhs) noexcept {
		std::swap(size_, rhs.size_);
		std::swap(capacity_, rhs.capacity_);
		std::swap(data_, rhs.data_);
	}
}