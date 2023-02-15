/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:57:20 by snagat            #+#    #+#             */
/*   Updated: 2023/02/15 09:40:06 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace   ft
{
    template<class T1, class T2>
    class pair
    {
        public:
            T1  first;
            T2  second;
            pair(){}
            
            operator T1() const
            {
                return first;
            } 
            pair(const T1 &a, const T2 &b):first(a), second(b){}
            template<class U, class V>
            pair(const  pair<U, V> &pr)
            {
                first = pr.first;
                second = pr.second;
            }
            pair &operator=(const pair  &rhs)
            {
                if (this != &rhs)
                {
                    this->first = rhs.first;
                    this->second = rhs.second;
                }
                return *this;
            }
    };
}
#endif