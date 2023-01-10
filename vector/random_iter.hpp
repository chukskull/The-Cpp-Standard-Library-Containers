
#ifndef	RANDOM_VECTOR_HPP
# define RANDOM_VECTOR_HPP

#include "vector.hpp"
#include <iostream>
#include <cmath>

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


	template<class T, class Category, class Distance = ptrdiff_t,
		 class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         	value_type;
		typedef Distance  	difference_type;
		typedef Pointer   	pointer;
		typedef Reference			reference;
		typedef Category  	iterator_category;
	};

template <class T,
		class Category = std::random_access_iterator_tag,
		class Distance = ptrdiff_t,
		class Pointer = T*,
		class Reference = T&>
class My_iter
	{
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference			reference;
			typedef Category	iterator_category;
		My_iter(pointer	iter): _iter(iter)
		{

		}
		My_iter()
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
				this->_iter = rhs._iter;
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

	 	My_iter	operator++(int)
		{
			const My_iter		temp(*this);

			++this->_iter;
			return	temp;
		}

		My_iter	&operator++()
		{
			++this->_iter;
			return	*this;
		}

		My_iter	operator--(int)
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

		reference	operator+=(const difference_type	&m)
		{
			if (m >= 0 )
				while(m--)
					++this->_iter;
			else
				while(m++)
					--this->_iter;
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
			_iter = store;
			return	temp;
		}

		My_iter	operator-(const difference_type	&m)
		{
			pointer	store;

			store = this->_iter;
			this->_iter -= m;
			My_iter	temp(*this);
			this->_iter = store;
			return	temp;
		}
		difference_type	operator-(const My_iter &obj)
		{
			return (obj.getPointer() - this->getPointer());
		}
		reference	operator*(){return *_iter;}

	value_type	operator[](size_t	index)
	{
		return ConvertToType(this->_iter + index);
	}

	bool	operator>(const My_iter &othr)
	{
		return	(this->_iter > othr._iter);
	}

	bool	operator>=(const My_iter &othr)
	{
		return	(this->_iter >= othr._iter);
	}

	bool	operator<(const My_iter &othr)
	{
		return	(this->_iter < othr._iter);
	}
	
	bool	operator<=(const My_iter &othr)
	{
		return	(this->_iter <= othr._iter);
	}

	pointer		getPointer()const
	{
		return this->_iter;
	}

	protected:
		pointer		_iter;
	};
}
	// template<class Iterator>
	// typename iterator_traits<Iterator>::difference_type difference_type;
	// template <class InputIterator>
	// typename iterator_traits<InputIterator>::difference_type
	// difference_s(InputIterator first, InputIterator last) {
	//   typename iterator_traits<InputIterator>::difference_type	result = last - first;
	//   return result;}    	
	namespace disc
	{
		template<class iter>
		typename ft::iterator_traits<iter>::difference_type
		TheDistance_(iter first, iter last, std::random_access_iterator_tag)
		{
			typename ft::iterator_traits<iter>::difference_type result;
			result = last - first;
			return	abs(result);
		}
		template <class iter>
		typename ft::iterator_traits<iter>::difference_type
		TheDistance_(iter first, iter last, std::input_iterator_tag)
		{
			typename ft::iterator_traits<iter>::difference_type result;
			while(first < last)
			{
				first++;
				result++;
			}
			return	result;
		}
	} // namespace name
	
	template<class iter>
	typename ft::iterator_traits<iter>::difference_type	 TheDistance(iter first, iter last)
		{
			return disc::TheDistance_(first, last, typename ft::iterator_traits<iter>::iterator_category());
		}


#endif