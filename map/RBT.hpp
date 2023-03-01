/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:39:31 by snagat            #+#    #+#             */
/*   Updated: 2023/03/01 20:27:57 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include <iostream>
#include <stdlib.h>
#include "map.hpp"
#include "pair.hpp"
#include "bider_iterator.hpp"

#define RED 1
#define BLCK 0
#define COUNT 10
 namespace ft{

 
template<class T, class Compare,class key_type, class Allocator>
class Tree
{
	public:  
		struct Node
		{
			T       	*data_;
			Node*		parent;
			Node*		left;
			Node*		right;
			int     	color;
			Node*		_next;
			Node*		_prev;
		};
		typedef Node*			node_ptr;
		typedef Compare			value_compare;
		typedef typename		std::allocator<Node>		Allocator_;
		typedef	typename		std::allocator<T>			Allocator_data;
		typedef	typename		ft::map_iterator<T, node_ptr>	iterator;
		typedef typename		ft::map_iterator<const T, node_ptr>	const_iterator;
		typedef typename		ft::map_rev_iterator<iterator>	reverse_iterator;
		typedef	typename		ft::map_rev_iterator<const iterator>	const_reverse_iterator;
		
		Tree(const value_compare &comp):_comp(comp)
		{
			this->size_ = 0;
			this->naher_nill = _alloc.allocate(1);
			_alloc.construct(this->naher_nill, Node());
			this->naher_nill->data_ = data_alloc.allocate(1);
			data_alloc.construct(this->naher_nill->data_, T());
			this->root = naher_nill;
			naher_nill->color = BLCK;
			naher_nill->parent = nullptr;
			naher_nill->left = nullptr;
			naher_nill->right = nullptr;
			naher_nill->_next = nullptr;
			naher_nill->_prev = nullptr;
		}
		~Tree()
		{
			this->clear();
		}
		Tree	&operator=(const Tree &x)
		{
			this->clear_tree(this->root);
			this->size_ = 0;
			this->root = naher_nill;
			this->insert_iterator(x.get_value_begin(), x.get_value_end());
			return *this;
		}

		node_ptr	successor(node_ptr	node)
		{
			if(node->right != naher_nill)
				return minimum(node->right);
			else
			{
				node_ptr	p;
				p = node->parent; // 2
				while (p != naher_nill && p->right == node)
				{
					node = p;//node hiya 2
					p = p->parent;//p d p is 4
				}
				return p;
			}
		}

		node_ptr	predecessor(node_ptr	node)
		{
			if(node->left != naher_nill)
			{
				return	maximum(node->left);
			}
			else
			{
				node_ptr	p = node->parent;
				while (p != naher_nill && p->left == node)
				{
					node = p;
					p = p->parent;
				}	
				return p;
			}
		}
		void    left_rotate(Node *x)
		{
			node_ptr	y = x->right;

			x->right = y->left;
			if (y->left != naher_nill)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == naher_nill)
				root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void    right_rotate(Node *x)
		{
			node_ptr	y = x->left;

			x->left = y->right;
			if (y->right != naher_nill)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == naher_nill)
				root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;

		}

		void    transpant_algo(node_ptr	u, node_ptr	v)
		{
			if (u->parent == naher_nill)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else  
				u->parent->right = v;
			v->parent = u->parent;
		}

		node_ptr	minimum(node_ptr	p) const
		{
			node_ptr	current = p;

			while(current && current->left != naher_nill && current != naher_nill)
			{
				current = current->left;
			}
			return current;
		}

		void    RB_deletion_Fixup(Node *x)
		{
			while(x != root && x->color == BLCK)
			{
				if(x == x->parent->left)
				{
					node_ptr	w = x->parent->right;
					if (w->color == RED)
					{
						w->color = BLCK;
						x->parent->color = RED;
						left_rotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLCK && w->right->color == BLCK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if(w->right->color == BLCK)
						{
						
							w->left->color = BLCK;
							w->color = RED;
							right_rotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLCK;
						w->right->color = BLCK;
						left_rotate(x->parent);
						x = root;
					}
				}
				else
				{
					node_ptr	w = x->parent->left;
					if (w->color == RED)
					{
						// cerr << "this is w" << w->data_ << endl;
						w->color = BLCK;
						x->parent->color = RED;
						right_rotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLCK && w->left->color == BLCK)
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->left->color == BLCK)
						{
							w->right->color = BLCK;
							w->color = RED;
							left_rotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLCK;
						w->left->color = BLCK;
						// cerr << "l iks " << x->data_ << endl;
						right_rotate(x->parent);
						x = root;
					}
				}
			}
			x->color = BLCK;
		}

		node_ptr	search_node(key_type key)
		{
		   Node *curr = root;
			while(curr != naher_nill && key != curr->data_->first)
			{
				if (key < curr->data_->first)
					curr = curr->left;
				else
					curr = curr->right;
			}
			return curr;
		}

		node_ptr	search_node_set(key_type key)
		{
			node_ptr	curr = root;
			while(curr != naher_nill && key != *(curr->data_))
			{
				if (key < *(curr->data_))
					curr = curr->left;
				else
					curr = curr->right;
			}
			return curr;
		}
		Node   *maximum(node_ptr nax)
		{
			node_ptr	curr = nax;
			while(curr && curr->right != naher_nill && curr != naher_nill)
			{
				curr = curr->right;
			}
			return curr;
		}



		void    RB_insert_Fixup(node_ptr new_elem)
		{
			while(new_elem->parent->color == RED)
			{
				if (new_elem->parent == new_elem->parent->parent->left)
				{
					node_ptr	y = new_elem->parent->parent->right;
					if (y && y->color == RED)
					{
						new_elem->parent->color = BLCK;
						y->color = BLCK;
						new_elem->parent->parent->color = RED;
						new_elem = new_elem->parent->parent;
					}
					else 
					{
						if (new_elem == new_elem->parent->right)
						{
							new_elem = new_elem->parent;
							left_rotate(new_elem);
						}
						new_elem->parent->color = BLCK;
						new_elem->parent->parent->color = RED;
						right_rotate(new_elem->parent->parent);
					}
				}
				else
				{
					node_ptr	y = new_elem->parent->parent->left;
					if (y && y->color == RED)
					{
						new_elem->parent->color = BLCK;
						y->color = BLCK;
						new_elem->parent->parent->color = RED;
						new_elem = new_elem->parent->parent;
					}
					else 
					{
						if (new_elem == new_elem->parent->left)
						{
							new_elem = new_elem->parent;
							right_rotate(new_elem);
							Node *new_elem_2 = new_elem->parent;
							// print2D(head);
						}
						new_elem->parent->color = BLCK;
						new_elem->parent->parent->color = RED;
						left_rotate(new_elem->parent->parent);
					}
				}
			}
			root->color = BLCK;
		}
		void    delete_(key_type key)
		{
			node_ptr	y;
			node_ptr	x;
			int     color;

			node_ptr	z = search_node(key);
			z->_prev->_next = z->_next;
			z->_next->_prev = z->_prev;
			y = z;
			color = y->color;
			if(z->left == naher_nill)
			{
				x = z->right;
				transpant_algo(z, z->right);
			}
			else if (z->right == naher_nill)
			{
				x = z->left;
				transpant_algo(z, z->left);
			}
			else{
				node_ptr	y = minimum(z->right);
				color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					transpant_algo(y, y->right);
					y->right = z->right;
					y->right->parent = y; 
				}
				transpant_algo(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (color == BLCK)
			{
				RB_deletion_Fixup(x);
			}
			data_alloc.destroy(z->data_);
			data_alloc.deallocate(z->data_,  1);
			_alloc.destroy(z);
			_alloc.deallocate(z, 1);
			z = nullptr;
			this->size_--;
		}
		void    delete_set(key_type key)
		{
			node_ptr	y;
			node_ptr	x;
			int     color;

			node_ptr	z = search_node_set(key);
			z->_prev->_next = z->_next;
			z->_next->_prev = z->_prev;
			y = z;
			color = y->color;
			if(z->left == naher_nill)
			{
				x = z->right;
				transpant_algo(z, z->right);
			}
			else if (z->right == naher_nill)
			{
				x = z->left;
				transpant_algo(z, z->left);
			}
			else{
				node_ptr	y = minimum(z->right);
				color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					transpant_algo(y, y->right);
					y->right = z->right;
					y->right->parent = y; 
				}
				transpant_algo(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (color == BLCK)
			{
				RB_deletion_Fixup(x);
			}
			data_alloc.destroy(z->data_);
			data_alloc.deallocate(z->data_,  1);
			_alloc.destroy(z);
			_alloc.deallocate(z, 1);
			z = nullptr;
			this->size_--;
		}
		//case 1: if uncle is red we are just recoloring the parent and uncle as a BLCK and grand parent as black and set elem to grand_parent because his red xD

		iterator    insert(const T	 data)
		{
			//
			node_ptr	y = naher_nill;
			node_ptr	tmp = root;
			node_ptr	new_ele = _alloc.allocate(1);
			_alloc.construct(new_ele, Node());
			new_ele->data_ = data_alloc.allocate(1);
			data_alloc.construct(new_ele->data_, data);
			new_ele->_next = naher_nill;
			new_ele->_prev = naher_nill;
			while(tmp != naher_nill)
			{
				y = tmp;
				if (_comp(*(new_ele->data_), *(tmp->data_)))
				{
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			new_ele->parent = y;
			if (y == naher_nill)
				root = new_ele;
			else if(_comp(*(new_ele->data_) , *(y->data_)))
				y->left = new_ele;
			else
				y->right = new_ele;
			new_ele->left = naher_nill;
			new_ele->right = naher_nill;
			new_ele->_prev = predecessor(new_ele);
            new_ele->_next = successor(new_ele);
            new_ele->_prev->_next = new_ele;
            new_ele->_next->_prev = new_ele;
            this->naher_nill->_prev = maximum(this->root);
			// this->naher_nill->_prev->_next = naher_nill;
            this->naher_nill->_next = nullptr;
			this->naher_nill->left = nullptr;
			new_ele->color = RED;
			this->size_++;
			RB_insert_Fixup(new_ele);
			return iterator(new_ele);
		}
		template<class iterator>
		void	insert_iterator(iterator first, iterator last)
		{
			for(; first != last; first++)
			{
				this->insert(*first);
			}
		}
		template<class iterator>
		void	erase_iterators(iterator first, iterator last)
		{
			iterator temp = first;
           for(; first != last;)
		   {
				temp++;
				delete_(first->first);
				first = temp;
		   }
		}
		template<class iterator>
		void	erase_iterators_sets(iterator first, iterator last)
		{
			iterator temp = first;
           for(; first != last;)
		   {
				temp++;
				delete_set(*first);
				first = temp;
		   }
		}
		iterator	get_value_begin() const
		{
			node_ptr temp = minimum(this->root);
			return (iterator(temp));
		}
		iterator	get_value_end()const
		{
			return iterator(this->naher_nill);
		}
		const_iterator	get_value_begin_const() const{
			node_ptr	temp = minimum(this->root);

			return (const_iterator(temp));
		}

		const_iterator	get_value_end_const() const{
			return (const_iterator(this->naher_nill));
		}
		const_reverse_iterator	get_value_begin_const_rev() const{
			return const_reverse_iterator(this->naher_nill);
		}
		const_reverse_iterator	get_value_end_const_rev() const{

			node_ptr	temp = minimum(this->root);

			return (const_reverse_iterator(temp));
		}

		reverse_iterator	get_value_begin_rev()const
		{
			return reverse_iterator(this->naher_nill);
		}
		
		reverse_iterator	get_value_end_rev()const
		{

			return (reverse_iterator(minimum(this->root)));
		}


		size_t	size()const
		{
			return this->size_;
		}

		iterator	find_set(const	key_type &key)const
		{
			node_ptr	curr = this->root;
			for(;curr && curr != naher_nill;)
			{
				if (*(curr->data_) == key)
					return iterator(curr);
				if (_comp(key,  *(curr->data_)))
					curr = curr->left;
				else
					curr = curr->right;
			}
			return iterator(this->naher_nill);
		}
		iterator	find_pair(const	key_type &key)const
		{
			node_ptr	curr = this->root;
			for(;curr && curr != naher_nill;)
			{
				if (curr->data_->first == key)
					return iterator(curr);
				if (_comp(key,  *(curr->data_)))
					curr = curr->left;
				else
					curr = curr->right;
			}
			return iterator(this->naher_nill);
		}
		void	clear_tree(node_ptr &head)
		{
			// print2D();
			if (head == naher_nill)
				return ;
			clear_tree(head->left);
			clear_tree(head->right);
			data_alloc.destroy(head->data_);
			data_alloc.deallocate(head->data_, 1);
			_alloc.destroy(head);
			_alloc.deallocate(head, 1);
			head = nullptr;
		}
		void	clear()
		{
			clear_tree(this->root);
			data_alloc.destroy(this->naher_nill->data_);
			data_alloc.deallocate(this->naher_nill->data_, 1);
			_alloc.destroy(this->naher_nill);
			_alloc.deallocate(this->naher_nill, 1);
			naher_nill = nullptr;
			this->size_ = 0;
		}
		//tools i debug 

	// void print2DUtil(node_ptr root, int space)
	// {
	// 	// Base case
	
	// 	// Increase distance between levels
	// 	space += COUNT;
	
	// 	if (root == nullptr)
	// 	{
	// 		return;
	// 	}
	// 	// Process right child first
	// 	print2DUtil(root->right, space);
	
	// 	// Print current node after space
	// 	// count
	
	// 	printf("\n");
	// 	for (int i = COUNT; i < space; i++)
	// 		printf(" ");
	// 	if (root->color == RED)
	// 		std::cout << "\033[1;31m" << root->data_->first  << "\033[0m" << std::endl;
	// 	else if (root->color == BLCK && root != naher_nill)
	// 		std::cerr << "\033[1;34m" << root->data_->first  << "\033[0m" << std::endl;
	// 	else
	// 		std::cerr << "nil" << std::endl;
	// 	print2DUtil(root->left, space);
	// }
	
	
	// void print2D()
	// {
	//    // Pass initial space count as 0
	//    print2DUtil(root, 0);
	// }
	protected:
		size_t				size_;
		Allocator_			_alloc;
		Allocator_data		data_alloc;
		node_ptr			root;
		node_ptr 			naher_nill;
		value_compare		_comp;

	};

 }

#endif