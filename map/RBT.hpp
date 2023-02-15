/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:39:31 by snagat            #+#    #+#             */
/*   Updated: 2023/02/15 11:57:04 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include <iostream>
#include <stdlib.h>
#include "pair.hpp"
#include "map.hpp"

#define RED 1
#define BLCK 0
#define COUNT 10

template<class T, class Compare, class Allocator = std::allocator<T> >
class Tree
{
	public:  
		struct Node
		{
			T       data_;
			Node    *parent;
			Node    *left;
			Node    *right;
			int     color;
		};
		typedef Allocator std::allocator<Node>;
		Tree():root(naher_nill)
		{
			this->color = BLCK;
		}
		// constructor to initialize data_ and pointers
		Tree(T data) : data_(data){};
		
		void    left_rotate(Node *x)
		{
			Node    *y = x->right;

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
			Node    *y = x->left;

			cerr <<"this is the data" <<x->data_ << endl;
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

		void    transpant_algo(Node    *u, Node    *v)
		{
			if (u->parent == naher_nill)
				root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else  
				u->parent->right = v;
			v->parent = u->parent;
		}

		Node    *minimum()
		{
			Node    *current = root;

			while(current->left != naher_nill)
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
					Node    *w = x->parent->right;
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
					Node    *w = x->parent->left;
					if (w->color == RED)
					{
						cerr << "this is w" << w->data_ << endl;
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
						cerr << "l iks " << x->data_ << endl;
						right_rotate(x->parent);
						x = root;
					}
				}
			}
			x->color = BLCK;
		}

		Node    *search_node(T key)
		{
		   Node *curr = root;
			while(curr != naher_nill && key != curr->data_)
			{
				if (_comp(key , curr->data_))
					curr = curr->left;
				else
					curr = curr->right;
			}
			return curr;
		}

		Node   *maximum()
		{
			Node   *curr = root;
			while(curr->right != naher_nill)
			{
				curr = curr->right;
			}
			return curr;
		}



		void    delete_(T key)
		{
			Node    *y;
			Node    *x;
			int     color;

			Node *z = search_node(key);
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
				Node    *y = minimum(z->right);
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
			_alloc.deallocate(z);
			// delete z;
		}
		//case 1: if uncle is red we are just recoloring the parent and uncle as a BLCK and grand parent as black and set elem to grand_parent because his red xD
		void    RB_insert_Fixup(Node *new_elem)
		{
			while(new_elem->parent->color == RED)
			{
				if (new_elem->parent == new_elem->parent->parent->left)
				{
					Node    *y = new_elem->parent->parent->right;
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
					Node    *y = new_elem->parent->parent->left;
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

		void    insert(Node *new_ele)
		{
			Node    *y = naher_nill;
			Node    *tmp = root;
			while(tmp != naher_nill)
			{
				y = tmp;
				if (_comp(new_ele->data_, tmp->data_))
				{
					tmp = tmp->left;
				}
				else
					tmp = tmp->right;
			}
			new_ele->parent = y;
			if (y == naher_nill)
				root = new_ele;
			else if(_comp(new_ele->data_ , y->data_))
				y->left = new_ele;
			else
				y->right = new_ele;
			new_ele->left = naher_nill;
			new_ele->right = naher_nill;
			new_ele->color = RED;
			RB_insert_Fixup(new_ele);
		}
	private:
		Allocator			_alloc;
		Node                *&root;
		Node                *naher_nill = _alloc.allocate(1);
		Compare				_comp;

};



// void print2DUtil(Tree * root, int space)
// {
// 	// Base case
// 	if (root == naher_nill)
// 		return;
 
// 	// Increase distance between levels
// 	space += COUNT;
 
// 	// Process right child first
// 	print2DUtil(root->right, space);
 
// 	// Print current node after space
// 	// count
 
// 	printf("\n");
// 	for (int i = COUNT; i < space; i++)
// 		printf(" ");
// 	if (root->color == RED)
// 		cout << "\033[1;31m" <<root->data_  << "\033[0m" << endl;
// 	else
// 		cerr << "\033[1;34m" <<root->data_  << "\033[0m" << endl;
// 	print2DUtil(root->left, space);
// }


// void print2D(Tree *root)
// {
//    // Pass initial space count as 0
//    print2DUtil(root, 0);
// }
// void    inorder_tree(Tree   *&head)
// {
// 	if (head == naher_nill)
// 		return ;
// 	inorder_tree(head->left);
// 	cerr << head->data_ << " " << head->color << endl;
// 	inorder_tree(head->right);
// 	// delete head;
// }


// Tree    *get_parent(Tree *head, int value)
// {
// 	if (head == naher_nill)
// 		return naher_nill;
// 	if ((head->left != naher_nill && head->left->data_ == value) || (head->right != naher_nill && head->right->data_ == value))
// 		return head;
// 	if (value < head->data_)
// 		return get_parent(head->left, value);
// 	else
// 		return get_parent(head->right, value);
// }


// int main()
// {
// 	Tree    *head;
// 	Tree   *nill;
// 	head = naher_nill;

// 	int     value = 18;
// 	insert(head, new Tree(1));
// 	insert(head, new Tree(2));
// 	insert(head, new Tree(3));
// 	insert(head, new Tree(4));
// 	insert(head, new Tree(5));
// 	insert(head, new Tree(6));
// 	insert(head, new Tree(7));
// 	insert(head, new Tree(8));
// 	insert(head, new Tree(9));
// 	insert(head, new Tree(10));
// 	insert(head, new Tree(11));
// 	insert(head, new Tree(12));
// 	// insert(head, new Tree(13));
// 	delete_(head, 4);
// 	delete_(head, 5);
// 	delete_(head, 6);
// 	delete_(head, 10);
// 	delete_(head, 7);
// 	// delete_(head, 7);
// 	// delete_(head, 5);
// 	// // print2D(head);
// 	// delete_(head, 8);
// 	// print2D(head);
// 	// delete_(head, 7);
// 	print2D(head);
// 	// delete_(head, 4);
// 	// delete_(head, 4);
// 	// delete_(head, 4);
// 	// delete_(head, 4);
// 	// delete_(head, 8);
// 	// print2D(head);

// 	// Tree    *new_elem = new Tree(value);
// 	// insert(head, new_elem);
// 	// Tree    *ybncl = new Tree(69);
// 	// insert(head, ybncl);
// 	// Tree    *helmakh = new Tree(9);
// 	// insert(head, helmakh);

// 	// Tree    *snagat = new Tree(12);
// 	// insert(head, snagat);
// 	// Tree    *lol3 = new Tree(11);
// 	// insert(head, lol3);
// 	// print2D(head);
// 	// delete_(head, lol3);
// 	// Tree    *lol = new Tree(99);
// 	// insert(head, lol);
// 	// Tree    *lol2 = new Tree(55);
// 	// insert(head, lol2);
// 	// Tree *karafi = new Tree(21);
// 	// insert(head, karafi);
// 	// Tree *karafi2 = new Tree(25);
// 	// insert(head, karafi2);
// 	// Tree *karafi3 = new Tree(22);
// 	// insert(head, karafi3);
// 	// print2D(head);
// 	// inorder_tree(head);
// 	// delete_(head, new_elem);

// 	return 0;
// }


#endif