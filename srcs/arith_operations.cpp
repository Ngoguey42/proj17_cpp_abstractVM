// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_operations.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/03/12 17:35:00 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/12 17:44:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdlib>
#include <functional>
#include <cfenv>
#include <cmath>
#include <sstream>

#include "arith_operations.hpp"
#include "arith_serializations.hpp"

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISFLOAT(V) std::is_floating_point<V>::value


namespace eval // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

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

// eOperation to char =================================== //
struct OperationChar
{
	char operator [] (eOperation const &op) const {

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

// Operation to ostringstream =========================== //
template <class T, eOperation Operation>
struct OperationToOss
{
	void operator () (std::stringstream &oss, T const &x, T const &y) const {

		oss << TypeToString<T>::name
			<< "(" << ser::serial<T>(x)
			<< " " << OperationChar()[Operation]
			<< " " << ser::serial<T>(y) << ")";
		return ;
	}
};

// Error handling ======================================= //
template <class T, eOperation Operation>
[[ noreturn ]] void floatThrow(T const &x, T const &y) {

	std::stringstream oss{};

	OperationToOss<T, Operation>()(oss, x, y);
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
	oss << __FUNCTION__ << ":" << __LINE__ << " Should not be reached";
	throw std::logic_error(oss.str());
}

template <class T, eOperation Operation>
[[ noreturn ]] void integerOverflowThrow(T const &x, T const &y) {

	std::stringstream oss{};

	OperationToOss<T, Operation>()(oss, x, y);
	throw std::overflow_error(oss.str());
}

template <class T, eOperation Operation>
[[ noreturn ]] void integerDivZeroThrow(T const &x, T const &y) {

	std::stringstream oss{};

	OperationToOss<T, Operation>()(oss, x, y);
	oss << "(div by 0)";
	throw std::domain_error(oss.str());
}

// Secured Operations =================================== //
#define HANDLED_FLAGS (FE_DIVBYZERO |  FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW)

template <class T, eOperation Operation, bool IsFloat, bool IsDivOrMod>
struct SecuredOperation;

template <class T, eOperation Operation, bool IsDivOrMod>
struct SecuredOperation<T, Operation, true, IsDivOrMod>
{
	T operator () (T const &x, T const &y) const {

		T volatile ret;

		std::feclearexcept(HANDLED_FLAGS);
		ret = RawOperation<T, Operation, true>::func(
			static_cast<T volatile>(x), static_cast<T volatile>(y));
		if (std::fetestexcept(HANDLED_FLAGS))
			floatThrow<T, Operation>(x, y);
		return ret;
	}
};

template <class T>
struct SecuredOperation<T, eOperation::Mod, true, true>
{
	T operator () (T const &x, T const &y) const {

		T volatile ret;

		std::feclearexcept(HANDLED_FLAGS);
		ret = RawOperation<T, eOperation::Mod, true>::func(
			static_cast<T volatile>(x), static_cast<T volatile>(y));
		if (std::fetestexcept(HANDLED_FLAGS))
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
	T operator () (T const &x, T const &y) const {

		using ROp = RawOperation<T, Operation, false>;
		using ROpi = RawOperation<int64_t, Operation, false>;

		T const volatile ret = ROp::func(
			static_cast<T volatile>(x), static_cast<T volatile>(y));
		int64_t const volatile reti = ROpi::func(
			static_cast<T volatile>(x), static_cast<T volatile>(y));

		if (int64_t(ret) != reti)
			integerOverflowThrow<T, Operation>(x, y);
		return ret;

	}
};

template <class T, eOperation Operation, bool IsDivOrMod>
struct SecuredOperation<T, Operation, false, IsDivOrMod>
{
	T operator () (T const &x, T const &y) const {

		T ret;

		if (y == 0)
			integerDivZeroThrow<T, Operation>(x, y);
		ret = RawOperation<T, Operation, false>::func(x, y);
		return ret;
	};
};


}; // ~~~~~~~~~~~~~~~~~ END OF NAMESPACE DETAIL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// Operations entry point =============================== //
template <class T, eOperation Operation>
std::string eval(std::string const &lhs, std::string const &rhs) {

	using Op = detail::SecuredOperation<
		T, Operation, ISFLOAT(T), detail::IsDivOrMod<Operation>::value>;

	T const x = ser::unserial_unsafe<T>(lhs);
	T const y = ser::unserial_unsafe<T>(rhs);
	T const res = Op()(x, y);

	return ser::serial<T>(res);
}

#define DEF(T, O)															\
	template std::string eval<T, O>(std::string const &l, std::string const &r)

DEF(int8_t, Add);
DEF(int8_t, Sub);
DEF(int8_t, Div);
DEF(int8_t, Mul);
DEF(int8_t, Mod);
DEF(int16_t, Add);
DEF(int16_t, Sub);
DEF(int16_t, Div);
DEF(int16_t, Mul);
DEF(int16_t, Mod);
DEF(int32_t, Add);
DEF(int32_t, Sub);
DEF(int32_t, Div);
DEF(int32_t, Mul);
DEF(int32_t, Mod);
DEF(float, Add);
DEF(float, Sub);
DEF(float, Div);
DEF(float, Mul);
DEF(float, Mod);
DEF(double, Add);
DEF(double, Sub);
DEF(double, Div);
DEF(double, Mul);
DEF(double, Mod);


}; // ~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE EVAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
