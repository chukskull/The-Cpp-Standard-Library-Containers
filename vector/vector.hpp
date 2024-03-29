
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <vector>
#include "random_iter.hpp"
#include "lexicographical.hpp"
#include "is_integral.hpp"
#include <type_traits>
#include <algorithm>
#include <map>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{

	public:
		// types:ß
		template <bool B, class Tp = void>
		struct enable_if
		{
		};

		template <class Tp>
		struct enable_if<true, Tp>
		{
			typedef Tp type;
		};
		typedef T value_type;
		typedef typename Allocator::reference reference;

		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		typedef size_t size_type;
		typedef My_iter<value_type> iterator;
		typedef My_iter<const value_type> const_iterator;
		typedef typename My_iter<value_type>::difference_type difference_type;
		typedef Allocator allocator_type;

		typedef reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const iterator> const_reverse_iterator;
		explicit vector(const Allocator &alloc = Allocator()) : _alloc(alloc)
		{
			this->arr = NULL;
			this->Capacity = 0;
			this->Size = 0;
		}

		explicit vector(size_type n, const value_type &value = value_type(),
						const Allocator &alloc = Allocator()) : _alloc(alloc)
		{
			this->arr = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
			{
				this->_alloc.construct(&arr[i], value);
			}
			this->Size = n;
			this->Capacity = n;
		}
		template <class InputIterator>
		vector(typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
			   const Allocator & = Allocator())
		{
			difference_type length;

			length = TheDistance(first, last);
			this->arr = _alloc.allocate(abs(length));
			for (size_t i = 0; i < static_cast<size_t>(length); i++)
			{
				this->_alloc.construct(&arr[i], *first);
				first++;
			}
			this->Size = abs(length);
			this->Capacity = abs(length);
		}

		vector(const vector<T, Allocator> &x)
		{
			this->_alloc = Allocator();
			this->arr = this->_alloc.allocate(x.size());
			this->Size = x.size();
			this->Capacity = x.capacity();
			for (size_type i = 0; i < x.size(); i++)
			{
				this->_alloc.construct(&arr[i], x.arr[i]);
			}
		}
		~vector()
		{
			if (size() && capacity())
			{
				for (size_t i = 0; i < this->size(); i++)
				{
					_alloc.destroy(&arr[i]);
				}
				if (this->arr != NULL)
					_alloc.deallocate(arr, this->capacity());
			}
		}
		vector<T, Allocator> &operator=(const vector<T, Allocator> &x)
		{
			if (this != &x)
			{
				_alloc.deallocate(arr, this->capacity());
				_alloc = x._alloc;
				arr = this->_alloc.allocate(x.size());
				Capacity = x.Capacity;
				Size = x.Size;
				for (size_type i = 0; i < x.size(); i++)
				{
					this->_alloc.construct(&arr[i], x.arr[i]);
				}
			}
			return *this;
		}

		template <class InputIterator>
		void assign(typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			size_type tmp;
			size_type old_cap;

			tmp = this->Size;
			old_cap = this->Capacity;
			difference_type distanc_;

			distanc_ = TheDistance(first, last);
			if (capacity() < static_cast<size_type>(distanc_))
			{
				this->Capacity = distanc_;
			}
			this->Size = distanc_;
			for (size_t i = 0; i < tmp; i++)
			{
				this->_alloc.destroy(&arr[i]);
			}
			_alloc.deallocate(arr, old_cap);
			arr = _alloc.allocate(distanc_);
			for (size_t i = 0; i < size(); i++)
			{
				this->_alloc.construct(&arr[i], *first);
				first++;
			}
		}

		void assign(size_type n, const T &u)
		{
			size_type tmp;
			size_type old_cap;

			old_cap = capacity();
			tmp = this->Size;
			if (capacity() < n)
				this->Capacity = n;
			this->Size = n;
			for (size_t i = 0; i < tmp; i++)
			{
				_alloc.destroy(&arr[i]);
			}
			_alloc.deallocate(arr, old_cap);
			arr = _alloc.allocate(capacity());
			for (size_t i = 0; i < size(); i++)
			{
				_alloc.construct(&arr[i], u);
			}
		}

		allocator_type get_allocator() const
		{
			return this->_alloc;
		}
		value_type *get_array()
		{
			return this->arr;
		}
		// iterators:
		iterator begin()
		{
			return iterator(&this->arr[0]);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(&this->arr[0]);
		}

		const_iterator begin() const
		{
			return const_iterator(&this->arr[0]);
		}

		iterator end()
		{
			return iterator(&this->arr[this->size()]);
		}

		const_iterator end() const
		{
			return const_iterator(&this->arr[size()]);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(&this->arr[size()]);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(&this->arr[size()]);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(&this->arr[0]);
		}
		// 23.2.4.2 capacity:
		size_type size() const
		{
			return (this->Size);
		}

		size_type max_size() const
		{
			return this->_alloc.max_size();
		}

		void resize(size_type sz, T c = T())
		{
			if (sz < size())
			{
				for (size_type i = sz - 1; i < size(); i++)
				{
					_alloc.destroy(&arr[i]);
				}
				this->Size = sz;
			}
			else if (sz < capacity() && sz > size())
			{
				for (size_type i = size() - 1; i < sz; i++)
				{
					if (i >= sz)
					{
						_alloc.construct(&arr[i], c);
					}
				}
				this->Size = sz;
			}
			else if (sz > capacity())
			{
				value_type *tmp = arr;
				arr = _alloc.allocate(sz);
				for (size_type i = 0; i < sz; i++)
				{
					if (i >= size())
					{
						_alloc.construct(&arr[i], c);
					}
					else
						_alloc.construct(&arr[i], tmp[i]);
				}
				// arr = new_arr;
				_alloc.deallocate(tmp, size());
				Capacity = sz;
				Size = sz;
			}
			// Size = sz;
		}

		size_type capacity() const
		{
			return (this->Capacity);
		}

		bool empty() const
		{
			return (!(this->size()));
		}

		void reserve(size_type n)
		{
			if (n < size())
				return;
			value_type *tmp = arr;

			arr = _alloc.allocate(n);
			for (size_type i = 0; i < size(); i++)
			{
				_alloc.destroy(&arr[i]);
				_alloc.construct(&arr[i], tmp[i]);
			}
			_alloc.deallocate(tmp, size());
			this->Capacity = n;
		}
		// element access:
		reference operator[](size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("out of range");
			return (this->arr[n]);
		}

		const_reference operator[](size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("out of range");
			return (this->arr[n]);
		}

		const_reference at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("out of range");
			return (this->arr[n]);
		}

		reference at(size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("out of range");
			return (this->arr[n]);
		}

		reference front()
		{
			return (this->arr[0]);
		}

		const_reference front() const;

		reference back()
		{
			return (this->arr[this->size() - 1]);
		}

		const_reference back() const;
		// 23.2.4.3 modifiers:
		void push_back(const T &x)
		{
			size_type old_ca = capacity();
			if (capacity() == 0)
			{
				this->Capacity = 1;
				if (arr == NULL)
					arr = _alloc.allocate(1);
			}
			else if (size() >= capacity())
			{
				this->Capacity = this->Capacity * 2;
				value_type *temp;
				temp = arr;
				arr = _alloc.allocate(capacity());
				for (size_type i = 0; i < size(); i++)
				{
					_alloc.construct(&arr[i], temp[i]);
				}
				for (size_t i = 0; i < size(); i++)
				{
					_alloc.destroy(&temp[i]);
				}
				_alloc.deallocate(temp, old_ca);
			}
			if (this->Capacity > 0)
				_alloc.construct(&arr[this->size()], x);
			this->Size++;
		}
		void pop_back()
		{
			_alloc.destroy(&arr[size()]);
			this->Size--;
		}

		// if size + 1 > capacity reallocate(capacity * 2)
		iterator insert(iterator position, const T &x)
		{
			size_type count = 0;
			size_type old_cp = this->capacity();
			iterator it = this->begin();
			while (it != position)
			{
				count++;
				it++;
			}
			size_type i = 0;
			if (size() + 1 > capacity())
				resize(size() + 1);
			else
				this->Size++;
			i = size();
			while (i > count)
			{
				arr[i] = arr[i - 1];
				i--;
			}
			iterator lol = iterator(&arr[i]);
			arr[i] = x;
			this->Capacity = old_cp * 2;
			return lol;

			// resize()
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			difference_type count = TheDistance(this->begin(), position);
			size_type s = 0;
			size_t curr_size = this->size();
			if (size() + n > capacity())
				resize(size() + n);
			else
				this->Size += n;
			s = curr_size - 1;
			while (s >= static_cast<size_type>(count))
			{
				arr[s + (n)] = arr[s];
				s--;
			}
			// getchar();
			size_type count_2 = 0;
			while (count_2 < n)
			{
				arr[count] = val;
				count_2++;
				count++;
			}
		}
		template <class InputIterator>
		void insert(iterator position, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			difference_type count = abs(TheDistance(this->begin(), position));
			difference_type distance = first - last;
			size_type curr_size = this->size();
			size_type s = 0;
			if (size() + distance > capacity())
				resize(size() + distance);
			else
				this->Size += distance;
			s = curr_size - 1;
			while (s >= static_cast<size_type>(count))
			{
				arr[s + distance] = arr[s];
				s--;
			}
			size_type count_2 = 0;
			while (count_2 < static_cast<size_type>(distance) && first != last)
			{
				arr[count] = *first;
				count_2++;
				count++;
				first++;
			}
		}

		iterator erase(iterator position)
		{
			size_type curr_pos = abs(this->begin() - position);
			resize(size() - 1);
			while (curr_pos < size())
			{
				arr[curr_pos] = arr[curr_pos + 1];
				curr_pos++;
			}
			return position;
		}
		iterator erase(iterator first, iterator last)
		{
			size_type count = 0;
			difference_type d = abs(TheDistance(last, first));
			iterator it = this->begin();
			while (it != first)
			{
				count++;
				it++;
			}
			resize(size() - d);
			while (count < size())
			{
				arr[count] = arr[count + d];
				count++;
			}
			return it;
		}
		void clear()
		{
			for (size_type i = 0; i < size(); i++)
			{
				_alloc.destroy(&arr[i]);
			}
			this->Size = 0;
		}

		void swap(vector<T, Allocator> &x)
		{
			size_type c_temp = x.capacity();
			size_type s_temp = x.size();
			Allocator _alloc_temp = x._alloc;
			value_type *temp = x.arr;

			x.Capacity = this->Capacity;
			x.Size = this->Size;
			x._alloc = this->_alloc;
			x.arr = this->arr;

			this->Capacity = c_temp;
			this->Size = s_temp;
			this->_alloc = _alloc_temp;
			this->arr = temp;
		}

	private:
		value_type *arr;
		size_type Capacity;
		size_type Size;
		Allocator _alloc;
	};

	template <class _Tp, class _Allocator>
	bool
	operator==(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
	{
		return __x.size() == __y.size() && std::equal(__x.begin(), __x.end(), __y.begin());
	}

	template <class _Tp, class _Allocator>
	bool
	operator!=(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
	{
		return !(__x == __y);
	}

	template <class _Tp, class _Allocator>
	bool
	operator<(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
	{
		return ft::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
	}

	template <class _Tp, class _Allocator>
	bool operator>(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
	{
		return __y < __x;
	}

	template <class _Tp, class _Allocator>
	bool
	operator>=(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
	{
		return !(__x < __y);
	}

	template <class _Tp, class _Allocator>
	bool
	operator<=(const vector<_Tp, _Allocator> &__x, const vector<_Tp, _Allocator> &__y)
	{
		return !(__y < __x);
	}
	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		vector<T, Alloc> tmp(x);
		x.swap(y);
		y.swap(tmp);
	}
}

#endif