
#ifndef MAP_HPP
#define MAP_HPP

#include <set>
#include <iostream>
#include <stack>
#include "pair.hpp"
#include "RBT.hpp"
#include "bider_iterator.hpp"
#include "../vector/lexicographical.hpp"

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
			: public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			Compare comp;

			value_compare(Compare c) : comp(c) {}

		public:
			bool operator()(const value_type &x, const value_type &y) const
			{
				return comp(x.first, y.first);
			}
			bool operator()(const key_type &x, const value_type &y) const
			{
				return comp(x, y.first);
			}
		};
		typedef Compare key_compare;

		typedef Allocator allocator_type;

		typedef typename Allocator::reference reference;

		typedef typename Allocator::const_reference const_reference;
		typedef Tree<value_type, value_compare, key_type, Allocator> My_Tree;
		typedef typename My_Tree::iterator iterator;			 // See 23.1
		typedef typename My_Tree::const_iterator const_iterator; // See 23.1
		typedef typename std::size_t size_type;					 // See 23.1
		// typedef     difference_type;// See 23.1
		typedef typename Allocator::pointer pointer;

		typedef typename Allocator::const_pointer const_pointer;
		typedef typename My_Tree::reverse_iterator reverse_iterator;
		typedef typename My_Tree::const_reverse_iterator const_reverse_iterator;
		// 23.3.1.1 construct/copy/destroy:
		explicit map(const Compare &comp = Compare(),
					 const Allocator &alloc_ = Allocator()) : tree_(value_compare(comp)), _cmp(comp), alloc(alloc_)
		{
		}
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const Compare &comp = Compare(), const Allocator &alloc_ = Allocator()) : tree_(value_compare(comp)), _cmp(comp), alloc(alloc_)
		{
			tree_.insert_iterator(first, last);
		}
		map(const map<Key, T, Compare, Allocator> &x) : tree_(value_compare(x._cmp)), _cmp(x._cmp), alloc(x.alloc)
		{
			this->tree_ = x.tree_;
		}
		~map(){};
		map<Key, T, Compare, Allocator> &
		operator=(const map<Key, T, Compare, Allocator> &x)
		{
			this->_cmp = x._cmp;
			this->tree_ = x.tree_;
			this->alloc = x.alloc;
			return *this;
		}
		// iterators:
		iterator begin()
		{
			return tree_.get_value_begin();
		}

		const_iterator begin() const
		{
			return (tree_.get_value_begin_const());
		}

		iterator end()
		{
			return iterator(tree_.get_value_end());
		}

		const_iterator end() const
		{
			return tree_.get_value_end_const();
		}

		reverse_iterator rbegin()
		{
			return tree_.get_value_begin_rev();
		}

		const_reverse_iterator rbegin() const
		{
			return tree_.get_value_begin_const_rev();
		}

		reverse_iterator rend()
		{
			return tree_.get_value_end_rev();
		}

		const_reverse_iterator rend() const
		{
			return tree_.get_value_end_const_rev();
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
		T &operator[](const key_type &x)
		{
			iterator tmp = find(x);
			if (tmp != this->end())
				return tmp->second;
			ft::pair<iterator, bool> lol = insert(ft::make_pair(x, T()));
			return lol.first->second;
		}
		T &at(const key_type &x)
		{
			iterator tmp = find(x);
			if (tmp != this->end())
				return tmp->second;
			ft::pair<iterator, bool> lol = insert(ft::make_pair(x, T()));
			throw std::out_of_range("out of range");
		}
		const T &at(const key_type &x) const
		{
			iterator tmp = find(x);
			if (tmp != this->end())
				return tmp->second;
			ft::pair<iterator, bool> lol = insert(ft::make_pair(x, T()));
			throw std::out_of_range("out of range");
		}
		// modifiers:
		pair<iterator, bool> insert(const value_type &x)
		{
			iterator new_one = find(x.first);
			if (new_one == this->end())
			{
				// std::cout << " lol " << std::endl;
				return ft::make_pair(tree_.insert(x), true);
			}
			return ft::make_pair(new_one, false);
		}

		iterator find(const key_type &x)
		{
			return iterator(tree_.find_pair(x));
		}

		const_iterator find(const key_type &x) const
		{
			return const_iterator(tree_.find_pair(x));
		}

		iterator insert(iterator position, const value_type &x)
		{
			iterator new_one = find(x.first);
			if (new_one == this->end())
			{
				tree_.insert(x);
				return position;
			}
			return new_one;
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				if (find(first->first) == this->end())
				{
					tree_.insert(*first);
				}
				first++;
			}
			// this->tree_.insert_iterator(first, last);
		}
		void erase(iterator position)
		{
			this->tree_.delete_(position->first);
		}
		size_type erase(const key_type &x)
		{
			iterator find = this->find(x);
			if (find == this->end())
				return 0;
			this->tree_.delete_(x);
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			this->tree_.erase_iterators(first, last);
		}

		void swap(map<Key, T, Compare, Allocator> &x)
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
			return this->_cmp;
		}

		size_type count(const key_type &x) const
		{
			const_iterator temp = find(x);
			if (temp != this->end())
			{
				return 1;
			}
			return 0;
		}
		iterator lower_bound(const key_type &x)
		{
			iterator it = this->begin();
			for (; it != this->end(); it++)
			{
				if (it->first >= x)
					return it;
			}
			return this->end();
		}
		const_iterator lower_bound(const key_type &x) const
		{
			iterator it = this->begin();
			for (; it != this->end(); it++)
			{
				if (it->first >= x)
					return it;
			}
			return const_iterator(this->end());
		}

		iterator upper_bound(const key_type &x)
		{
			iterator it = this->begin();
			for (; it != this->end(); it++)
			{
				if (it->first > x)
					return it;
			}
			return this->end();
		}

		const_iterator upper_bound(const key_type &x) const
		{
			iterator it = this->begin();
			for (; it != this->end(); it++)
			{
				if (it->first > x)
					return it;
			}
			return this->end();
		}
		pair<iterator, iterator>
		equal_range(const key_type &x)
		{
			return ft::make_pair(lower_bound(x), upper_bound(x));
		}
		pair<const_iterator, const_iterator>
		equal_range(const key_type &x) const
		{
			return ft::make_pair(lower_bound(x), upper_bound(x));
		}

	protected:
		Tree<value_type, value_compare, key_type, Allocator> tree_;
		key_compare _cmp;
		allocator_type alloc;
	};
	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y)
	{
		return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<(const map<Key, T, Compare, Allocator> &x,
				   const map<Key, T, Compare, Allocator> &y)
	{
		return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y)
	{
		return !(x == y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>(const map<Key, T, Compare, Allocator> &x,
				   const map<Key, T, Compare, Allocator> &y)
	{
		return y < x;
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y)
	{
		return !(x < y);
	}

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator> &x,
					const map<Key, T, Compare, Allocator> &y)
	{
		return !(y < x);
	}

	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key, T, Compare, Allocator> &x,
			  map<Key, T, Compare, Allocator> &y)
	{
		x.swap(y);
	}
}

#endif