/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:42:59 by snagat            #+#    #+#             */
/*   Updated: 2023/02/22 16:12:47 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <map>
#include <iostream>
#include "pair.hpp"
#include "RBT.hpp"
#include "bider_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> > >

	class map
	{
		public:
			// types:
			typedef Key key_type;

			typedef T mapped_type;

			typedef ft::pair<const key_type, T> value_type;

			class value_compare
				: public std::binary_function<value_type,value_type,bool> {
			friend class map;

			protected:
				Compare comp;

			value_compare(Compare c) : comp(c) {}
			public:
				bool operator()(const value_type& x,const  value_type& y) const {
					 return comp(x.first, y.first);
				}
				bool operator()(const key_type& x,const  value_type& y) const {
					 return comp(x, y.first);
				}
			};
			typedef Compare key_compare;

			typedef Allocator allocator_type;

			typedef typename Allocator::reference reference;

			typedef typename Allocator::const_reference                 const_reference;
			typedef Tree<value_type, value_compare, key_type, Allocator>   		My_Tree;
			typedef typename My_Tree::iterator   						iterator; // See 23.1
			typedef typename My_Tree::const_iterator					const_iterator; // See 23.1
			typedef typename std::size_t								size_type; //See 23.1
			// typedef     difference_type;// See 23.1
			typedef typename Allocator::pointer pointer;

			typedef typename 	Allocator::const_pointer	const_pointer;
			typedef	typename	My_Tree::reverse_iterator	reverse_iterator;
			typedef typename	My_Tree::const_reverse_iterator	const_reverse_iterator;
			// 23.3.1.1 construct/copy/destroy:
			explicit map(const Compare& comp = Compare(),
			const Allocator& alloc_ = Allocator()): tree_(value_compare(comp)), _cmp(comp), alloc(alloc_)
			{
			}
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
			const Compare& comp = Compare(), const Allocator& alloc_= Allocator())
			{
				this->tree_.insert_iterator(first, last);
			}
			map(const map<Key,T,Compare,Allocator>& x):tree_(x.tree_)
			{
				this->_cmp = x._cmp;
			}
			~map(){};
			map<Key,T,Compare,Allocator>&
			operator=(const map<Key,T,Compare,Allocator>& x)
			{
				if (this != &x)
				{
					this(x);
				}
				return *this;
			}
			// iterators:
			iterator begin()
			{
				return tree_.get_value_begin();
			}

			const_iterator begin() const
			{
				return (tree_.get_value_begin());
			}

			iterator end()
			{
				return iterator(tree_.get_value_end());
			}

			const_iterator end() const
			{
				return tree_.get_value_end();
			}

			reverse_iterator rbegin()
			{
				return tree_.get_value_end();
			}

			const_reverse_iterator rbegin() const
			{
				return tree_.get_value_end();
			}

			reverse_iterator rend()
			{
				return tree_.get_value_begin();
			}

			const_reverse_iterator rend() const
			{
				return tree_.get_value_begin();
			}
			// capacity:
			bool empty() const
			{
				if (tree_.size())
					return false;
				return true;	
			}

			size_type size() const
			{
				return this->tree_.size();
			}

			size_type max_size() const
			{
				return 288230376151711743;
			}
			// 23.3.1.2 element access:
			T& operator[](const key_type& x)
			{
				iterator	tmp = find(x);
				if (tmp != this->end())
					return tmp->second;
				ft::pair<iterator, bool> lol = insert(ft::make_pair(x, T()));
				return lol.first->second;
			}
			// modifiers:
			pair<iterator, bool> insert(const value_type& x)
			{
				iterator	new_one = find(x.first);
				if (new_one == this->end())
				{
					std::cout << " lol " << std::endl;
					return ft::make_pair(tree_.insert(x), true);
	
				}
				return	ft::make_pair(new_one, false);
			}

			iterator insert(iterator position, const value_type& x)
			{
				(void)position;
				iterator	new_one = find(x.first);
				if (new_one == this->end())
				{
					tree_.insert(x);
					return find(x);
				}
				return new_one;
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				this->tree_.insert_iterator(first, last);
			}
			void erase(iterator position)
			{
				this->tree_->delete_(position->first);
			}
			size_type erase(const key_type& x)
			{
				iterator	find = this->find(x);
				if (find == this->end())
					return 0;
				this->tree_.delete_(x);
				return 1;
			}

			void erase(iterator first, iterator last)
			{
				this->tree_.erase_iterators(first, last);
			}

			void swap(map<Key,T,Compare,Allocator>& x)
			{
           		map tmp(x);

            	x = *this;
            	*this = tmp;
			}

			void clear()
			{
				erase(this->begin(), this->end());
			}
			// observers:
			key_compare key_comp() const
			{
				return this->_cmp;
			}

			value_compare value_comp() const
			{
				return value_comp(this->_cmp);
			}
			iterator find(const key_type& x)
			{
				return	iterator(tree_.find_pair(x));
			}

			const_iterator find(const key_type& x) const
			{
				return (tree_.find_pair(x));
			}

			size_type count(const key_type& x) const
			{
				iterator	temp = find(x);
				if (temp != this->end())
				{
					std::cerr << "just why ? " << std::endl;
					return 1;
				}
				return 0;
			}
			iterator lower_bound(const key_type& x)
			{
				iterator	it = this->begin();
				for (;it != this->end(); it++)
				{
					if (it->first >= x)
						return it;
				}
				return this->end();
			}
			const_iterator lower_bound(const key_type& x) const
			{
				iterator	it = this->begin();
				for (;it != this->end(); it++)
				{
					if (it->first >= x)
						return it;
				}
				return const_iterator(this->end());
			}

			iterator upper_bound(const key_type& x)
			{
				iterator	it = this->begin();
				for (; it != this->end(); it++)
				{
					if (it->first > x)
						return it;
				}
				return this->end();
			}

			const_iterator upper_bound(const key_type& x) const
			{
				iterator	it = this->begin();
				for (; it != this->end(); it++)
				{
					if (it->first > x)
						return it;
				}
				return this->end();
			}
			pair<iterator,iterator>
			equal_range(const key_type& x)
			{
				return ft::make_pair(lower_bound(x), upper_bound(x));
			}
			pair<const_iterator,const_iterator>
			equal_range(const key_type& x) const
			{
				return ft::make_pair(lower_bound(x), upper_bound(x));
			}
		protected:
			allocator_type		alloc;
			key_compare			_cmp;
			Tree<value_type, value_compare,key_type, Allocator>	tree_;

		};
		template <class Key, class T, class Compare, class Allocator>
		bool operator==(const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y)
		{
			if (x.size() == y.size()){
            	typename ft::map<Key, T, Compare, Allocator>::iterator it = x.begin();
            	typename ft::map<Key, T, Compare, Allocator>::iterator it1 = y.begin();
            	for(; it != x.end(), it1 != y.end(); it++ , it1++)
            	{
                	if (*it != *it1)
                    	return false;
            	}
        	}
			else
            	return false;
        	return true;
		}
		template <class Key, class T, class Compare, class Allocator>
		bool operator< (const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y)
		{
			
		}
		template <class Key, class T, class Compare, class Allocator>
		bool operator!=(const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);
		template <class Key, class T, class Compare, class Allocator>
		bool operator> (const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);
		template <class Key, class T, class Compare, class Allocator>
		bool operator>=(const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);
		template <class Key, class T, class Compare, class Allocator>
		bool operator<=(const map<Key,T,Compare,Allocator>& x,
		const map<Key,T,Compare,Allocator>& y);
		// specialized algorithms:
		template <class Key, class T, class Compare, class Allocator>
		void swap(map<Key,T,Compare,Allocator>& x,
		map<Key,T,Compare,Allocator>& y);
}


#endif