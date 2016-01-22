// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Evalexpr.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:02:52 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/22 16:23:17 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVALEXPR_HPP
# define EVALEXPR_HPP

#include <cstdlib>
#include <functional>
#include <cfenv>
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

namespace tmp // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

enum eOperation
{
	Add = 0,
	Sub,
	Div,
	Mul,
	Mod
};

namespace detail // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

// Is operand Div or Mod ================================ //
template <eOperation> struct IsDivOrMod
	: std::integral_constant<bool, false>
{};
template <> struct IsDivOrMod<eOperation::Div>
	: std::integral_constant<bool, true>
{};
template <> struct IsDivOrMod<eOperation::Mod>
	: std::integral_constant<bool, true>
{};

// Operations =========================================== //

template <class T, eOperation> struct FloatOperation;

template <class T> struct FloatOperation<T, eOperation::Add> {
	static const auto func = std::plus<T>();
};
template <class T> struct FloatOperation<T, eOperation::Sub> {
	static const auto func = std::minus<T>();
};
template <class T> struct FloatOperation<T, eOperation::Div> {
	static const auto func = std::divides<T>();
};
template <class T> struct FloatOperation<T, eOperation::Mul> {
	static const auto func = std::multiplies<T>();
};
template <class T> struct FloatOperation<T, eOperation::Mod> {
	static const auto func = static_cast< T(T, T) >(std::fmod);
};

// Evalexpr implementations ============================= //
template <class T, eOperation Operation, bool IsFloat, bool IsDivOrMod>
class Evalexpr;

template <class T, eOperation Operation, bool IsDivOrMod>
class Evalexpr<T, Operation, true, IsDivOrMod>
{

};

template <class T>
class Evalexpr<T, eOperation::Mod, true, true>
{

};

template <class T, eOperation Operation>
class Evalexpr<T, Operation, false, false>
{

};

template <class T, eOperation Operation, bool IsDivOrMod>
class Evalexpr<T, Operation, false, IsDivOrMod>
{
	T operator ()(T const &x, T const &y) {

		std::function< T(T const &, T const &) > const arr[] = {
			[eOperation::Mod] = std::fmod,
			[eOperation::Div] = std::divides<T>(),
		};
		T ret;

		std::feclearexcept(FE_ALL_EXCEPT);
		// ret = arr[Operation](x, y);
		ret = FloatOperation<T, Operation>(x, y);
		// if (std::fpclassify() == FP_ZERO)
		// 	throw std::domain_error("msg");
		return ret;
	}
};


}; // ~~~~~~~~~~~~~~~~~ END OF NAMESPACE DETAIL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class T, eOperation Operation>
class Evalexpr : detail::Evalexpr<
	T, Operation, ISFLOAT(T), detail::IsDivOrMod<Operation>::value>
{};

static inline void lol(void) {
	Evalexpr<float, eOperation::Add>();
	Evalexpr<float, eOperation::Sub>();
	Evalexpr<float, eOperation::Div>();
	Evalexpr<float, eOperation::Mul>();
	Evalexpr<float, eOperation::Mod>();
	Evalexpr<short, eOperation::Add>();
	Evalexpr<short, eOperation::Sub>();
	Evalexpr<short, eOperation::Div>();
	Evalexpr<short, eOperation::Mul>();
	Evalexpr<short, eOperation::Mod>();

}


}; // ~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE TMP //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


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
