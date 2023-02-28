#ifndef STACK_HPP
# define STACK_HPP


#include "../vector/vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >

	class stack {

	public:
		typedef Container                                   container_type;
		typedef typename container_type::value_type         value_type;
		typedef typename container_type::reference          reference;
		typedef typename container_type::const_reference    const_reference;
		typedef typename container_type::size_type          size_type;
		protected:
	protected:
		container_type	con;
	public:
		explicit stack(const Container& c= Container()):con()
		{

		}
		stack(const stack &rh):con(rh.con)
		{

		}
		stack &operator=(const	stack &rh)
		{
			if (this != &rh)
			{
				con = rh.con;
			}
			return *this;
		}
		
		bool empty() const { return con.empty(); }
		size_type size()  const { return con.size(); }

		value_type& top() { return con.back(); }

		const value_type& top() const { return con.back(); }

		void push(const value_type& x) { con.push_back(x); }

		void pop() { con.pop_back(); }
		
	
	friend
	bool operator==(const stack<T, Container>& x,
	const stack<T, Container>& y)
	{
		return x.con == y.con;
	}

	
	friend
	bool operator< (const stack<T, Container>& x,
	const stack<T, Container>& y)
	{
		return x.con < y.con;
	}

	
	friend
	bool operator!=(const stack<T, Container>& x,
	const stack<T, Container>& y)
	{
		return x.con != y.con;
	}
	
	friend
	bool operator> (const stack<T, Container>& x,
	const stack<T, Container>& y)
	{
		return x.con > y.con;
	}
	
	friend
	bool operator>=(const stack<T, Container>& x,
	const stack<T, Container>& y)
	{
		return x.con >= y.con;
	}
	
	friend
	bool operator<=(const stack<T, Container>& x,
	const stack<T, Container>& y)
	{
		return x.con <= y.con;
	}
	};

}

#endif