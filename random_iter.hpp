#include "vector.hpp"
#include <iostream>

namespace ft {

	template<class Iterator> 
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;

		typedef typename Iterator::value_type value_type;

		typedef typename Iterator::pointer pointer;

		typedef typename Iterator::reference reference;

		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T> 
	struct iterator_traits<T*> {
		typedef     ptrdiff_t difference_type;
		typedef     T value_type;
		typedef     T* pointer;
		typedef     T& reference;
		typedef     std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	class My_iter : public ft::iterator_traits<T*>
	{
		My_iter(pointer	iter): _iter(iter)
		{

		}

		My_iter(const	My_iter &other)
		{
			this->_iter = other._iter;
		}

		My_iter	&operator=(const My_iter &rhs)
		{
			if (this != &rhs)
			{
				this->_iter = other._iter;
			}
			return (*this);
		}

		bool	operator==(const My_iter &other)
		{
			return (this->_iter == other._iter);
		}

		bool	operator!=(const My_iter	&other)
		{
			return(this->_iter != other._iter);
		}

		reference	ConvertToType(pointer	ptr)
		{
			return (*ptr);
		}

		My_iter*	operator->(){return this->_iter;}

	 	const My_iter	&operator++(int)
		{
			My_iter		temp(*this);

			++this->_iter;
			return	temp;
		}

		My_iter	&operator++()
		{
			++this->_iter;
			return	*this;
		}

		const My_iter	&operator--(int)
		{
			My_iter		temp(*this);

			--this->_iter;
			return	temp;
		}

		My_iter	&operator--()
		{
			--this->_iter;
			return	*this;
		}

		My_iter	&operator+=(const difference_type	&m)
		{
			if (m >= 0 )
				while(m--)
					++_iter;
			else
				while(m++)
					--_iter;
			return *this;		
		}

		My_iter	&operator-=(const difference_type	&m)
		{
			_iter -= m;
			return *this;		
		}

		My_iter	operator+(const difference_type	&m)
		{
			pointer	store;
			
			store = _iter;
			_iter += m;
			My_iter	temp(*this);
			_iter = old;
			return	temp;
		}

		My_iter	operator-(const difference_type	&m)
		{
			pointer	store;

			store = _iter;
			_iter -= m;
			My_iter	temp(*this);
			_iter = old;
			return	temp;
		}

	<template class Input>
	value_type	distance(Input first, Input last)
	{
		iterator_traits<Input>::value_type result = (*last - *first);

		return((result > 0) ? result : -result);
	}

	value_type	operator[](size_t	index)
	{
		return ConvertToType(_iter + index);
	}

	bool	operator>(const My_iter &othr)
	{
		return	(_iter > othr._iter);
	}

	bool	operator>=(const My_iter &othr)
	{
		return	(_iter >= othr._iter);
	}

	bool	operator<(const My_iter &othr)
	{
		return	(_iter < othr._iter);
	}
	
	bool	operator<=(const My_iter &othr)
	{
		return	(_iter <= othr._iter);
	}

	private:
		pointer		_iter;
	};


	
}