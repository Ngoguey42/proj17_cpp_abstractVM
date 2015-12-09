// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Evalexpr.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:02:52 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 11:03:15 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVALEXPR_HPP
# define EVALEXPR_HPP

#include <iostream>
#include <cstdint>
#include <type_traits>
#include <algorithm>
#include <cmath>

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISFLOAT(V) std::is_floating_point<V>::value

template <class T>
class Evalexpr
{

	static std::string		conv(T v) {
		return std::to_string(v);
	}

	template <class U = T, OK_IF(ISFLOAT(U))>
	static T				conv(std::string const &v) {
		return std::atof(v.c_str());
	}
	template <class U = T, OK_IF(!ISFLOAT(U))>
	static T				conv(std::string const &v) {
		return std::atol(v.c_str());
	}

	static const std::function< T(T, T) > operations[5];

public:

	enum eOperation
	{
		Add = 0,
		Sub,
		Div,
		Mul,
		Mod
	};

	static std::string		eval(
		std::string const &lhs, eOperation o, std::string const &rhs) {
		T const		res = operations[o](conv(lhs), conv(rhs));

		return conv(res);
	}
};

template <class T>
const std::function< T(T, T) >		Evalexpr<T>::operations[5] = {
	std::plus<T>(),
	std::minus<T>(),
	std::multiplies<T>(),
	std::divides<T>(),
	[](T a, T b){ return std::fmod(a, b); },
};
// fmod has a special overload working with integer types
// Promoted		fmod(Arithmetic1 x, Arithmetic2 y);
// http://en.cppreference.com/w/cpp/numeric/math/fmod

# undef OF_IF
# undef ISFLOAT

#endif /* ****************************************************** EVALEXPR_HPP */
