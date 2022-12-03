/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:20:08 by snagat            #+#    #+#             */
/*   Updated: 2022/12/03 17:54:35 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <vector>
#include <iterator>
#include "random_iter.hpp"

namespace ft {
template <class T, class Allocator = std::allocator<T> >
class vector {

public:
// types:

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
		this->arr = get_allocator().allocate(1);
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
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
	const Allocator& = Allocator())
	{
		difference_type	length;

		length = TheDistance(first, last);
		this->arr = _alloc.allocate(length);
		for(int i = 0; i < length; i++)
		{
			this->_alloc.construct(&arr[i], *first);
			first++;
		}
		this->Size = length;
		this->Capacity = length;
		
		
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
		_alloc.deallocate(arr, this->size());
	}
	vector<T,Allocator>& operator=(const vector<T,Allocator>& x);
	
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last);
	void assign(size_type n, const T& u);
	
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
	
	size_type max_size() const;
	
	void resize(size_type sz, T c = T());
	
	size_type capacity() const
	{
		return (this->Capacity);
	}
	
	bool empty() const
	{
		return(this->size());
	}
	
	void reserve(size_type n);
	// element access:
	reference operator[](size_type n);
	
	const_reference operator[](size_type n) const;
	
	const_reference at(size_type n) const;
	
	reference at(size_type n);
	
	reference front();
	
	const_reference front() const;
	
	reference back();
	
	const_reference back() const;
	// 23.2.4.3 modifiers:
	void push_back(const T& x);
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