/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:54:55 by snagat            #+#    #+#             */
/*   Updated: 2023/02/27 17:13:37 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "../map/RBT.hpp"
#include "../map/pair.hpp"
#include <iostream>
#include <map>


namespace ft
{
    template <class Key, class Compare = std::less<Key>,
                class Allocator = std::allocator<Key> >
    class set
    {
        public:
// types:
        typedef Key key_type;

        typedef Key value_type;

        typedef Compare key_compare;

        // typedef Compare value_compare;

        typedef Allocator allocator_type;

        typedef typename Allocator::reference reference;

        typedef typename Allocator::const_reference const_reference;

        class   value_compare : public std::binary_function<value_type,value_type,bool>
        {
            friend class set;

            protected:
                Compare comp;
            value_compare(Compare c):comp(c){}
            public:
            bool operator()(const value_type  &x, const value_type &y)const
            {
                return (comp(x , y));
            }

        };
        typedef Tree<value_type, value_compare, key_type, Allocator>   		My_Tree;
		typedef typename My_Tree::iterator   						iterator; // See 23.1
		typedef typename My_Tree::const_iterator					const_iterator; // See 23.1
		typedef typename std::size_t								size_type; //See 23.1
		// typedef     difference_type;// See 23.1
		typedef typename Allocator::pointer pointer;
		typedef	typename	My_Tree::reverse_iterator	reverse_iterator;
		typedef typename	My_Tree::const_reverse_iterator	const_reverse_iterator;

        typedef typename Allocator::const_pointer const_pointer;
        // 23.3.3.1 construct/copy/destroy:
        explicit set(const Compare& comp = Compare(),
        const Allocator& alloc= Allocator()):tree_(value_compare(comp)), _cmp(comp), alloc_(alloc)
        {

        }
        template <class InputIterator>
        set(InputIterator first, InputIterator last,
        const Compare& comp = Compare(), const Allocator& alloc= Allocator()):tree_(value_compare(comp)), _cmp(comp), alloc_(alloc)
        {
            tree_.insert_iterator(first, last);
        }
        set(const set<Key,Compare,Allocator>& x):tree_(value_compare(x._cmp)), _cmp(x._cmp), alloc_(x.alloc_)
        {
            this->tree_ = x.tree_;
        }
        ~set()
        {

        };
        set<Key, Compare, Allocator>& operator=
        (const set<Key, Compare, Allocator>& x)
        {
            this->_cmp = x._cmp;
            this->tree_ = x.tree_;
            this->alloc_ = x.alloc_;
            return *this;

        }
        allocator_type get_allocator() const
        {
            return this->alloc_;
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
            return 576460752303423487;
        }
        pair<iterator,bool> insert(const value_type& x)
        {
            iterator    new_one = find(x);
            if (new_one == this->end())
            {
                return ft::make_pair(tree_.insert(x),true);
            }
            return ft::make_pair(new_one, false);
        }

        iterator insert(iterator position, const value_type& x)
        {
            (void)position;
			iterator	new_one = find(x);
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
            this->tree_.delete_set(*position);
        }
        size_type erase(const key_type& x)
        {
            iterator find = this->find(x);
            if (find == this->end())
                return 0;
            this->tree_.delete_set(x);
            return 1;
        }
        
        void erase(iterator first, iterator last)
        {
            this->tree_.erase_iterators_sets(first, last);
        }
        
        void swap(set<Key,Compare,Allocator>& x)
        {
            set temp(x);
            x = *this;
            *this = temp;
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
        value_compare  value_comp()    const {return this->_cmp;}
        // set operations:
        iterator  find(const key_type& x) const
        {
            return iterator(tree_.find_set(x));
        }
        
        size_type count(const key_type& x) const
        {
            const_iterator	temp = find(x);
			if (temp != this->end())
			{
				return 1;
			}
			return 0;
        }
        iterator  lower_bound(const key_type& x)
        {
            iterator	it = this->begin();
				for (;it != this->end(); it++)
				{
					if (*(it) >= x)
						return it;
				}
				return this->end();
        }
        iterator  upper_bound(const key_type& x)
        {
           iterator	it = this->begin();
			for (; it != this->end(); it++)
			{
				if (*(it) > x)
					return it;
			}
			return this->end();
        }
        
        pair<iterator,iterator> equal_range(const key_type& x)
        {
            return ft::make_pair(lower_bound(x), upper_bound(x));
        }
        protected:
            allocator_type  alloc_;
            key_compare     _cmp;
            Tree<value_type, value_compare, value_type, Allocator > tree_;
    };
    template <class Key, class Compare, class Allocator>
		bool operator==(const set<Key,Compare,Allocator>& x,
		const set<Key,Compare,Allocator>& y)
		{
			return x.size() == y.size() && std::equal(x.begin(), x.end(), y.begin());
		}
		
		template <class Key, class Compare, class Allocator>
		bool operator< (const set<Key,Compare,Allocator>& x,
		const set<Key,Compare,Allocator>& y)
		{
			return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
		}
		
		template <class Key, class Compare, class Allocator>
		bool operator!=(const set<Key,Compare,Allocator>& x,
		const set<Key,Compare,Allocator>& y)
		{
			return !(x == y);
		}
		
		template <class Key, class Compare, class Allocator>
		bool operator> (const set<Key,Compare,Allocator>& x,
		const set<Key,Compare,Allocator>& y)
		{
			return y < x;
		}
		
		template <class Key, class Compare, class Allocator>
		bool operator>=(const set<Key,Compare,Allocator>& x,
		const set<Key,Compare,Allocator>& y)
		{
			return !(x < y);
		}
		
		template <class Key, class Compare, class Allocator>
		bool operator<=(const set<Key,Compare,Allocator>& x,
		const set<Key,Compare,Allocator>& y)
		{
			return !(y < x);
		}
		
		template <class Key, class Compare, class Allocator>
		void swap(set<Key,Compare,Allocator>& x,
		set<Key,Compare,Allocator>& y)
		{
			x.swap(y);
		}
}





#endif