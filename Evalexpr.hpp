// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Evalexpr.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:02:52 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/22 19:21:27 by ngoguey          ###   ########.fr       //
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


namespace ee // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
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
struct OperationChar
{
	constexpr char operator [] (eOperation const &op) const {

		constexpr char value[] = {
			[eOperation::Add] = '+',
			[eOperation::Sub] = '-',
			[eOperation::Div] = '/',
			[eOperation::Mul] = '*',
			[eOperation::Mod] = '%',
		};
		return value[op];
	}
};

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
	static constexpr auto func = std::plus<T>();
};
template <class T, bool Float> struct RawOperation<T, eOperation::Sub, Float> {
	static constexpr auto func = std::minus<T>();
};
template <class T, bool Float> struct RawOperation<T, eOperation::Div, Float> {
	static constexpr auto func = std::divides<T>();
};
template <class T, bool Float> struct RawOperation<T, eOperation::Mul, Float> {
	static constexpr auto func = std::multiplies<T>();
};
template <class T> struct RawOperation<T, eOperation::Mod, true> {
	static constexpr auto func = static_cast< T(*)(T, T) >(std::fmod);
};
template <class T> struct RawOperation<T, eOperation::Mod, false> {
	static constexpr auto func = std::modulus<T>();
};

// Error handling ======================================= //
template <class T, eOperation Operation>
[[ noreturn ]] void floatThrow(T const &x, T const &y) {

	std::stringstream oss{};

	oss << "( " << x << OperationChar()[Operation] << y << ")";
	if (std::fetestexcept(FE_DIVBYZERO))
	{
		oss << "(div by 0)";
		throw std::domain_error(oss.str());
	}
	else if (std::fetestexcept(FE_INVALID))
		throw std::domain_error(oss.str());
	else if (std::fetestexcept(FE_OVERFLOW))
		throw std::overflow_error(oss.str());
	else if (std::fetestexcept(FE_UNDERFLOW))
		throw std::underflow_error(oss.str());
	oss << __FUNCTION__ << ":" << __LINE__ << "Should not be reached";
	throw std::logic_error(oss.str());
}

template <class T, eOperation Operation>
[[ noreturn ]] void integerOverflowThrow(T const &x, T const &y) {

	std::stringstream oss{};

	oss << "( " << x << OperationChar()[Operation] << y << ") ";
	throw std::overflow_error(oss.str());
}

template <class T, eOperation Operation>
[[ noreturn ]] void integerDivZeroThrow(T const &x, T const &y) {

	std::stringstream oss{};

	oss << "( " << x << OperationChar()[Operation] << y << ") " << "(div by 0)";
	throw std::domain_error(oss.str());
}

// Secured Operations =================================== //
template <class T, eOperation Operation, bool IsFloat, bool IsDivOrMod>
struct SecuredOperation;

template <class T, eOperation Operation, bool IsDivOrMod>
struct SecuredOperation<T, Operation, true, IsDivOrMod>
{
	T operator ()(T const &x, T const &y) {

		T ret;

		std::feclearexcept(FE_ALL_EXCEPT);
		ret = RawOperation<T, Operation, true>::func(x, y);
		if (std::fetestexcept(FE_ALL_EXCEPT & ~FE_INEXACT))
			floatThrow<T, eOperation::Mod>(x, y);
		return ret;
	}
};

template <class T>
struct SecuredOperation<T, eOperation::Mod, true, true>
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
			floatThrow<T, eOperation::Mod>(x, y);
		}
		return ret;
	}
};

template <class T, eOperation Operation>
struct SecuredOperation<T, Operation, false, false>
{
	T operator ()(T const &x, T const &y) {

		T const ret = RawOperation<T, Operation, false>::func(x, y);
		T const reti = RawOperation<int64_t, Operation, false>::func(x, y);

		if (int64_t(ret) != reti)
			integerOverflowThrow<T, Operation>(x, y);
		return ret;

	}
};

template <class T, eOperation Operation, bool IsDivOrMod>
struct SecuredOperation<T, Operation, false, IsDivOrMod>
{
	T operator ()(T const &x, T const &y) {

		T ret;

		if (y == 0)
			integerDivZeroThrow<T, Operation>(x, y);
		ret = RawOperation<T, Operation, false>::func(x, y);
		return ret;
	};
};

// Operations entry point =============================== //
template <class T, eOperation Operation>
struct ExecOperation : public detail::SecuredOperation<
	T, Operation, ISFLOAT(T), detail::IsDivOrMod<Operation>::value>
{};


}; // ~~~~~~~~~~~~~~~~~ END OF NAMESPACE DETAIL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <class T, eOperation Operation>
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

public:

	std::string operator () (std::string const &lhs, std::string const &rhs) {

		T const		res =
			detail::ExecOperation<T, Operation>()(conv(lhs), conv(rhs));

		return conv(res);
	}
};


}; // ~~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE EE //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# undef OF_IF
# undef ISFLOAT

#endif /* ****************************************************** EVALEXPR_HPP */
