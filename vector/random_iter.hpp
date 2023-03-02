
#ifndef	RANDOM_VECTOR_HPP
# define RANDOM_VECTOR_HPP

#include "vector.hpp"
#include "traits.hpp"
#include <iostream>
#include <map>
#include <cmath>

namespace ft {
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

			My_iter(const	My_iter &other)
			{
				this->_iter = other._iter;
			}
		My_iter(pointer	iter): _iter(iter)
		{

		}
		My_iter()
		{

		}
		public:
			operator My_iter<const T>() const 
			{
        		return My_iter<const	T>(_iter);
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

		reference	operator->(){return &*this->_iter;}

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

		My_iter	operator+=(const difference_type	&m)
		{
			_iter += m;
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
		reference	operator*()const {return (*_iter);}

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

	template <class iter>
	class	reverse_iterator
	{
		public:
		typedef	iter													iterator_type;
		typedef	typename ft::iterator_traits<iter>::value_type			value_type;
		typedef typename ft::iterator_traits<iter>::difference_type     difference_type;
        typedef typename ft::iterator_traits<iter>::pointer             pointer;
        typedef typename ft::iterator_traits<iter>::reference           reference;
        typedef typename ft::iterator_traits<iter>::iterator_category   iterator_category;
			reverse_iterator(iter	iter2): _iter(iter2)
			{

			}
			reverse_iterator()
			{

			}

			operator reverse_iterator <const iter>() const 
			{
        		return reverse_iterator<const	iter>(_iter);
    		}

			reverse_iterator	&operator=(const reverse_iterator &rhs)
			{
				if (this != &rhs)
				{
					this->_iter = rhs._iter;
				}
				return (*this);
			}
			reverse_iterator(const	reverse_iterator &other):_iter(other._iter)
			{
			}

			bool	operator==(const reverse_iterator &other)
			{
				return (this->_iter == other._iter);
			}

			bool	operator!=(const reverse_iterator	&other)
			{
				return(this->_iter != other._iter);
			}

			reverse_iterator*	operator->(){return this->_iter->getPointer();}

	 		reverse_iterator	operator++(int)
			{
				const reverse_iterator		temp(*this);

				--this->_iter;
				return	temp;
			}

			reverse_iterator	&operator++()
			{
				--this->_iter;
				return	*this;
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator		temp(*this);

				++this->_iter;
				return	temp;
			}

			reverse_iterator	&operator--()
			{
				++this->_iter;
				return	*this;
			}

			reference	operator+=(const difference_type	&m)
			{
				if (m >= 0 )
					while(m--)
						--this->_iter;
				else
					while(m++)
						++this->_iter;
				return *this;		
			}

			reverse_iterator	&operator-=(const difference_type	&m)
			{
				_iter -= m;
				return *this;		
			}

			reverse_iterator	operator+(const difference_type	&m)
			{
				iter	store;

				store = _iter;
				_iter += m;
				reverse_iterator	temp(*this);
				_iter = store;
				return	temp;
			}

			reverse_iterator	operator-(const difference_type	&m)
			{
				iter	store;

				store = this->_iter;
				this->_iter -= m;
				reverse_iterator	temp(*this);
				this->_iter = store;
				return	temp;
			}
			difference_type	operator-(const reverse_iterator &obj)
			{
				return (obj.getPointer() - this->getPointer());
			}
			reference	operator*() const{
				iter tmp = _iter;
                return (*(--tmp));
				}

			value_type	operator[](size_t	index)
			{
				return ConvertToType(this->_iter + index);
			}

			bool	operator>(const reverse_iterator &othr)
			{
				return	(this->_iter > othr._iter);
			}

			bool	operator>=(const reverse_iterator &othr)
			{
				return	(this->_iter >= othr._iter);
			}

			bool	operator<(const reverse_iterator &othr)
			{
				return	(this->_iter < othr._iter);
			}

			bool	operator<=(const reverse_iterator &othr)
			{
				return	(this->_iter <= othr._iter);
			}

			pointer		getPointer()const
			{
				return this->_iter;
			}
		protected:
			iter	_iter;
	};
}   	
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