#ifndef	BIDER_ITERATOR_HPP
# define BIDER_ITERATOR_HPP

#include "map.hpp"
#include "RBT.hpp"
#include "../vector/vector.hpp"
#include <iostream>
#include <map>
#include <cmath>

template<class T, class Compare, class key_type, class Allocator>
class Tree;

namespace ft {

	// template<class Iterator> 
	// struct iterator_traits {
	// 	typedef typename Iterator::difference_type difference_type;

	// 	typedef typename Iterator::value_type value_type;

	// 	typedef typename Iterator::pointer pointer;

	// 	typedef typename Iterator::reference reference;

	// 	typedef typename Iterator::iterator_category iterator_category;
	// };

	// template<class T> 
	// struct iterator_traits<T*> {
	// 	typedef     ptrdiff_t difference_type;
	// 	typedef     T value_type;
	// 	typedef     T* pointer;
	// 	typedef     T& reference;
	// 	typedef     std::random_access_iterator_tag iterator_category;
	// };


	// template<class T, class Category, class Distance = ptrdiff_t,
	// 	 class Pointer = T*, class Reference = T&>
	// struct iterator
	// {
	// 	typedef T         	value_type;
	// 	typedef Distance  	difference_type;
	// 	typedef Pointer   	pointer;
	// 	typedef Reference			reference;
	// 	typedef Category  	iterator_category;
	// };

template <class T, class Node_ptr>
class map_iterator
	{
		public:
			typedef T                               value_type;
        	typedef Node_ptr                         pointer;
        	typedef value_type&                     reference;
        	typedef value_type*                     type_pointer;
        	typedef ptrdiff_t                       difference_type;
        	typedef std::bidirectional_iterator_tag iterator_category;
		public:
			map_iterator(pointer	iter): _iter(iter)
			{

			}
			map_iterator():_iter(nullptr)
			{

			}

			map_iterator(const	map_iterator &other)
			{
				this->_iter = other._iter;
			}
			operator map_iterator<const value_type, Node_ptr>() const 
			{
    			return map_iterator<const	value_type, Node_ptr>(_iter);
    		}
			map_iterator	&operator=(const map_iterator<value_type, Node_ptr> &rhs)
			{
				if (this != &rhs)
				{
					this->_iter = rhs._iter;
				}
				return (*this);
			}

			bool	operator==(const map_iterator &other)
			{
				return (this->_iter == other._iter);
			}

			bool	operator!=(const map_iterator	&other)
			{
				return(this->_iter != other._iter);
			}


			type_pointer		operator->(){
				
				// std::cout << this->_iter->data_ << std::endl;
				return this->_iter->data_;
				}
			type_pointer		operator->() const{ 
				
				// std::cout << this->_iter->data_ << std::endl;
				return this->_iter->data_;
				}

			map_iterator	operator++(int)
			{
				map_iterator		temp(_iter);
					this->_iter = this->_iter->_next;
				return	temp;
			}

			map_iterator	&operator++()
			{
				this->_iter = this->_iter->_next;
				return	*this;
			}

			map_iterator	operator--(int)
			{
				map_iterator		temp(*this);

				this->_iter = this->_iter->_prev;
				return	temp;
			}

			map_iterator	&operator--()
			{
				this->_iter = this->_iter->_prev;
				return	*this;
			}

			reference	operator*(){return *(this->_iter->data_);}

			pointer get_pointer() const{
            	return this->_iter;
        	}

			map_iterator		getPointer()const
			{
				return this->_iter;

			}
	protected:
		pointer		_iter;
	};


// template <class T, class Node_ptr>
template <class iter>
class map_rev_iterator
{
		typedef	iter													iterator_type;
		typedef	typename ft::iterator_traits<iter>::value_type			value_type;
		typedef typename ft::iterator_traits<iter>::difference_type     difference_type;
        typedef typename ft::iterator_traits<iter>::pointer             pointer;
        typedef typename ft::iterator_traits<iter>::reference           reference;
        typedef typename ft::iterator_traits<iter>::iterator_category   iterator_category;
        typedef typename iter::type_pointer                             type_pointer;
		public:
			map_rev_iterator(iter	iter2): _iter(iter2)
			{

			}
			map_rev_iterator():_iter(nullptr)
			{

			}
			map_rev_iterator	&operator=(const map_rev_iterator<iter> &rhs)
			{
				if (this != &rhs)
				{
					this->_iter = rhs._iter;
				}
				return (*this);
			}

			bool	operator==(const map_rev_iterator &other)
			{
				return (this->_iter == other._iter);
			}

			bool	operator!=(const map_rev_iterator	&other)
			{
				return(this->_iter != other._iter);
			}


			type_pointer		operator->(){
				
				iter temp = _iter;
				return ((--temp).get_pointer())->data_;
				}

			map_rev_iterator	operator++(int)
			{
				const map_rev_iterator		temp(*this);

				--this->_iter;
				return	temp;
			}

			map_rev_iterator	&operator++()
			{
				--this->_iter;
				return	*this;
			}

			map_rev_iterator	operator--(int)
			{
				map_rev_iterator		temp(*this);

				this->_iter++;
				return	temp;
			}
			
			map_rev_iterator	&operator--()
			{
				this->_iter++;
				return	*this;
			}

			reference	operator*(){
				iter tmp = _iter;
				return *(--tmp);
				}
	protected:
		iter		_iter;
};
}

#endif