/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:20:08 by snagat            #+#    #+#             */
/*   Updated: 2022/12/07 16:45:02 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include "random_iter.hpp"
#include <type_traits>
#include <algorithm>

namespace ft {
template <class T, class Allocator = std::allocator<T> >
class vector {

public:
// types:
	template<bool B, class Tp = void>
	struct enable_if {};
	
	template<class Tp>
	struct enable_if<true, Tp> { typedef Tp type; };
	
	
	typedef T value_type;
	typedef typename Allocator::reference reference;
	
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer     pointer;
	
	typedef size_t          			size_type;
	typedef My_iter<value_type>		iterator;
	// typedef implementation defined iterator; 
	// typedef implementation defined const_iterator; 
	// typedef implementation defined size_type;
	typedef typename	My_iter<value_type>::difference_type	difference_type;
	
	typedef Allocator allocator_type;
	
	typedef typename Allocator::const_pointer const_pointer;
	
	// typedef std::reverse_iterator<iterator> reverse_iterator;
	
	// typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	
	explicit vector(const Allocator& alloc = Allocator())
	{
		this->arr = NULL;
		this->Capacity = 0;
		this->Size = 0;
	}
	
	explicit vector(size_type n, const value_type& value = value_type(),
	const Allocator& alloc = Allocator())
	{
		this->arr = _alloc.allocate(n);
		for(size_type i = 0; i < n; i++)
		{
			this->_alloc.construct(&arr[i], value);
		}
		this->Size = n;
		this->Capacity = n;
	}
	template<class InputIterator>
  	vector(typename enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
	const Allocator& = Allocator())
	{
		difference_type	length;

		length = TheDistance(first, last);
		this->arr = _alloc.allocate(abs(length));
		for(int i = 0; i < length; i++)
		{
			this->_alloc.construct(&arr[i], *first);
			first++;
		}
		this->Size = abs(length);
		this->Capacity = abs(length);
	}
	
	vector(const vector<T,Allocator>& x)
	{
		this->_alloc = Allocator();
		this->arr = this->_alloc.allocate(x.size());
		this->Size = x.size();
		this->Capacity = x.capacity();
		for(size_type i = 0; i < x.size(); i++)
		{
			this->_alloc.construct(&arr[i], x.arr[i]);
		}
	}
	~vector()
	{
		for (size_t i = 0; i < this->size(); i++)
		{
			_alloc.destroy(&arr[i]);
		}
		_alloc.deallocate(arr, this->capacity());
	}
	vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
	
	template <class InputIterator>
	void assign(typename enable_if<!std::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
	{
		size_type	tmp;
		size_type	old_cap;

		tmp = this->Size;
		difference_type	distanc_;

		distanc_ = TheDistance(first, last);
		if (capacity() < distanc_)
		{
			this->Capacity = distanc_;
		}
		this->Size = distanc_;
		for (size_t i = 0; i < tmp; i++)
		{
			this->_alloc.destroy(&arr[i]);
		}
		_alloc.deallocate(arr,old_cap);
		arr = _alloc.allocate(distanc_);
		for (size_t i = 0; i < size(); i++)
		{
			this->_alloc.construct(&arr[i], *first);
			first++;
		}	
	}
	void assign(size_type n, const T& u)
	{
		size_type	tmp;
		size_type	old_cap;

		old_cap = capacity();
		tmp = this->Size;
		if (capacity() < n)
			this->Capacity = n;
		this->Size = n;
		for (size_t i; i < tmp; i++)
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
	value_type	*get_array()
	{
		return this->arr;
	}
	// iterators:
	iterator begin(){
		return iterator(&this->arr[0]);
	}
	
	// const_iterator begin() const;
	
	iterator end(){
		return iterator(&this->arr[this->size()]);
	}
	
	// const_iterator end() const;
	
	// reverse_iterator rbegin();
	
	// const_reverse_iterator rbegin() const;
	
	// reverse_iterator rend();
	
	// const_reverse_iterator rend() const;
	// 23.2.4.2 capacity:
	size_type size() const
	{
		return (this->Size);
	}
	
	size_type max_size() const
	{
		return std::numeric_limits<std::size_t>::max();
	}
	
	// void resize(size_type sz, T c = T())
	// {
	// 	if (sz > capacity())
	// 	{
	// 		Allocator	new_arr;
	// 		arr = new_arr.allocate(sz);
	// 		std::copy(begin(), end(), begin());
	// 		_alloc.deallocate(arr, size());
	// 		for (int i = 0; i < size(); i++)
	// 		{
	// 			_alloc.destroy(&arr[i]);
	// 		}
	// 		// arr = new_arr;
	// 		Capacity = sz;
	// 	}
	// 	Size = sz;
	// }
	
	size_type capacity() const
	{
		return (this->Capacity);
	}
	
	bool empty() const
	{
		return(this->size());
	}
	
	void reserve(size_type n){
		_alloc.deallocate(size());
		_alloc.allocate(n);
	}
	// element access:
	reference operator[](size_type n){
		return (this->arr[n]);
	}
	
	const_reference operator[](size_type n) const;
	
	const_reference at(size_type n) const;
	
	reference at(size_type n){
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
		return (this->arr[this->size() -1]);	
	}
	
	const_reference back() const;
	// 23.2.4.3 modifiers:
	void push_back(const T& x)
	{
		if (capacity() == 0)
		{
			this->Capacity = 1;
			this->arr = _alloc.allocate(1);

		}
		if (size() == capacity())
		{
			this->Capacity = this->Capacity * 2;
			value_type		*temp;
			temp = arr;
			arr = _alloc.allocate(capacity());
			for(int i = 0; i < size(); i++)
			{
				_alloc.construct(&arr[i], temp[i]);
			}
			for (size_t i = 0; i < size(); i++)
			{
				_alloc.destroy(&temp[i]);
			}
			_alloc.deallocate(temp, this->capacity());
		}
		_alloc.construct(&arr[this->size()], x);
		this->Size++;
	}
	void pop_back();
	
	// iterator insert(iterator position, const T& x);
	
	// void insert(iterator position, size_type n, const T& x);
	
	// template <class InputIterator>
	// void insert(iterator position,
	// InputIterator first, InputIterator last);
	// iterator erase(iterator position);
	
	// iterator erase(iterator first, iterator last);
	
	void swap(vector<T,Allocator>&);
	
	void clear();
private:
	value_type			*arr;
	size_type			Capacity;
	size_type			Size;
	Allocator			_alloc;
};
}

#endif