// #include "vector.hpp"
// #include <iostream>
// namespace ft {

// template <typename Category,
// 	typename	T,
// 	typename	Distance = std::ptrdiff_t,
// 	typename	Pointer = T*,
// 	typename	Reference = T&>
//    class iterator_traits
//    {
// 		typedef	iterator_category 	Category;
// 		typedef	value_type  		T;
// 		typedef	difference_type  	Distance;
// 		typedef	pointer  			Pointer;
// 		typedef	reference  			Reference;
//    };
   
// 	template<class Category, class T, class Distance = ptrdiff_t,
// 				class Pointer = T*, class Reference = T&>
//    class Iterator :public iterator_traits<std::random_access_iterator_tag, class T>
//    {
// 		// typedef T* pointer;
// 		// typedef T& reference;
// 		// typedef typename Iterator_traits::difference_type difference_type;

// 		// typedef typename Iterator_traits::value_type value_type;

// 		// typedef typename Iterator_traits::pointer pointer;

// 		// typedef typename Iterator_traits::reference reference;

// 		// typedef typename iterator_traits::Category iterator_category;


// 		Iterator(const Iterator &other):_vec(other._vec), _index(other._index)
// 		{
// 		}
// 		Iterator	&operator=(const Iterator &Other)
// 		{
// 			if (this != &Other)
// 			{
// 				this->_vec = Other._vec;
// 				this->_index = Other._index;
// 			}
// 		}
	
// 	private:
// 		Pointer			ptr;	
// 		size_t			_index;
//    };
   
   
   
	
// }