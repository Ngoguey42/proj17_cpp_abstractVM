// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Evalexpr.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:02:52 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/22 13:41:29 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVALEXPR_HPP
# define EVALEXPR_HPP

#include <cstdlib>
#include <functional>
#include <cmath>

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISFLOAT(V) std::is_floating_point<V>::value

/*
** Floating Point
**  Add std::plus		overflow_error
**  Sub std::minus		overflow_error
**  Div std::divides	overflow_error underflow_error domain_error
**		0. / 0. gives FE_INVALID
**		x / 0. gives FE_DIVBYZERO
**  Mul std::multiplies	overflow_error underflow_error
**  Mod std::ftoi		domain_error
**		0. % 0. gives FE_INVALID
**		x % 0. gives FE_INVALID
**
** Integer
**  Add std::plus		overflow_error
**  Sub std::minus		overflow_error
**  Div std::divides	domain_error
**  Mul std::multiplies	overflow_error
**  Mod std::modulus	domain_error
*/

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

	static std::string eval(
		std::string const &lhs, eOperation o, std::string const &rhs) {
		T const		res = operations[o](conv(lhs), conv(rhs));

		return conv(res);
	}
};


namespace detail // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class T, bool ISFLOAT>
struct Modulo;

template <class T>
struct Modulo<T, true>
{
	T operator () (T const &x, T const &y) const{
		return x;
	}
};

template <class T>
struct Modulo<T, false> : std::modulus<T> {};


}; // ~~~~~~~~~~~~~~~~~ END OF NAMESPACE DETAIL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class T>
const std::function< T(T, T) > Evalexpr<T>::operations[5] = {
	std::plus<T>(),
	std::minus<T>(),
	std::multiplies<T>(),
	std::divides<T>(),
	detail::Modulo<T, ISFLOAT(T)>(),
};

# undef OF_IF
# undef ISFLOAT

#endif /* ****************************************************** EVALEXPR_HPP */
