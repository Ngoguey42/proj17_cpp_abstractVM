// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Evalexpr.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:02:52 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/22 17:23:15 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EVALEXPR_HPP
# define EVALEXPR_HPP

#include <cstdlib>
#include <functional>
#include <cfenv>
#include <cmath>
#include <sstream>

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
	: public std::integral_constant<bool, false>
{};
template <> struct IsDivOrMod<eOperation::Div>
	: public std::integral_constant<bool, true>
{};
template <> struct IsDivOrMod<eOperation::Mod>
	: public std::integral_constant<bool, true>
{};

// Raw Operations ======================================= //
template <class T, eOperation, bool> struct RawOperation;

template <class T, bool Float> struct RawOperation<T, eOperation::Add, Float> {
	static const auto func = std::plus<T>();
};
template <class T, bool Float> struct RawOperation<T, eOperation::Sub, Float> {
	static const auto func = std::minus<T>();
};
template <class T, bool Float> struct RawOperation<T, eOperation::Div, Float> {
	static const auto func = std::divides<T>();
};
template <class T, bool Float> struct RawOperation<T, eOperation::Mul, Float> {
	static const auto func = std::multiplies<T>();
};
template <class T> struct RawOperation<T, eOperation::Mod, true> {
	static constexpr auto func = static_cast< T(*)(T, T) >(std::fmod);
};
template <class T> struct RawOperation<T, eOperation::Mod, false> {
	static const auto func = std::modulus<T>();
};

// Error msg builder ==================================== //
template <class T>
[[ noreturn ]] void floatErr(T const &x, T const &y) {

	std::stringstream ret;

	ret << "( " << x << " todo " << y << ") ";
	if (std::fetestexcept(FE_DIVBYZERO))
	{
		ret << "Division by 0";
		throw std::domain_error(ret.str());
	}
	throw 42;
}


// Secured Operations =================================== //
template <class T, eOperation Operation, bool IsFloat, bool IsDivOrMod>
struct Evalexpr;

template <class T, eOperation Operation, bool IsDivOrMod>
struct Evalexpr<T, Operation, true, IsDivOrMod>
{

};

template <class T>
struct Evalexpr<T, eOperation::Mod, true, true>
{
	T operator ()(T const &x, T const &y) {

		T ret;

		std::feclearexcept(FE_ALL_EXCEPT);
		ret = RawOperation<T, eOperation::Mod, true>::func(x, y);
		if (std::fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT))
		{
			if (std::fpclassify(y) == FP_ZERO)
			{
				std::feclearexcept(FE_INVALID);
				std::feraiseexcept(FE_DIVBYZERO);
			}
				// throw std::domain_error("msg div by zero");

		}
		return ret;
	}
};

template <class T, eOperation Operation>
struct Evalexpr<T, Operation, false, false>
{

};

template <class T, eOperation Operation, bool IsDivOrMod>
struct Evalexpr<T, Operation, false, IsDivOrMod>
{
};


}; // ~~~~~~~~~~~~~~~~~ END OF NAMESPACE DETAIL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class T, eOperation Operation>
struct Evalexpr : public detail::Evalexpr<
	T, Operation, ISFLOAT(T), detail::IsDivOrMod<Operation>::value>
{};

static inline void lol(void) {
	// Evalexpr<float, eOperation::Add>()(42, 42);
	// Evalexpr<float, eOperation::Sub>()(42, 42);
	// Evalexpr<float, eOperation::Div>()(42, 42);
	// Evalexpr<float, eOperation::Mul>()(42, 42);
	Evalexpr<float, eOperation::Mod>()(42, 42);
	// Evalexpr<short, eOperation::Add>()(42, 42);
	// Evalexpr<short, eOperation::Sub>()(42, 42);
	// Evalexpr<short, eOperation::Div>()(42, 42);
	// Evalexpr<short, eOperation::Mul>()(42, 42);
	// Evalexpr<short, eOperation::Mod>()(42, 42);

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
