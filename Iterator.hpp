#include "vector.hpp"
#include <iostream>
namespace ft {

template <class type_value>
   class Iterator_traits
   {
	public:
		using	iterator_category = std::random_access_iterator_tag;
		using	value_type = type_value;
		using	difference_type = std::ptrdiff_t;
		using	pointer = type_value*;
		using	reference = type_valueI&;
   };
template<class type_value>
   class Iterator :public ft::Iterator_traits
   {
	Iterator(type_value* ptr=nullptr)
	{

	}

   	private:
		type_value*		my_ptr;
   };
	
}