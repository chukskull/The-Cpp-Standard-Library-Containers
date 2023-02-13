/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snagat <snagat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:30:33 by snagat            #+#    #+#             */
/*   Updated: 2023/02/13 10:43:36 by snagat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
#define LESS_HPP

#include <iostream>
namespace   ft
{
    template<class T>
    class less
    {
        bool    operator(const T &a, const T &b) const
        {
            return a < b;
        }
    };
}




#endif