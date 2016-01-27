// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_serializations.hpp                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:54:40 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 14:09:18 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARITH_SERIALIZATIONS_HPP
# define ARITH_SERIALIZATIONS_HPP

# include <sstream>
# include <iomanip>
# include <limits>

# include "arith_types.hpp"

# define OK_IF(PRED) typename std::enable_if<PRED, int>::type = 42
# define ISFLOAT(V) std::is_floating_point<V>::value


namespace ser // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// ========================================================================== //

/*
** %fails on floating point serial+deserial operation
** *
** 0% with std::setprecision(std::numeric_limits<float>::max_digits10 + 2)
** 0% with std::setprecision(std::numeric_limits<double>::max_digits10 + 2)
** 0% with std::setprecision(std::numeric_limits<float>::max_digits10 + 1)
** 0% with std::setprecision(std::numeric_limits<double>::max_digits10 + 1)
** 0% with std::setprecision(std::numeric_limits<float>::max_digits10)
** 0% with std::setprecision(std::numeric_limits<double>::max_digits10)
** 1.5% with std::setprecision(std::numeric_limits<float>::max_digits10 - 1)
** 37% with std::setprecision(std::numeric_limits<double>::max_digits10 - 1)
** 67% with std::setprecision(std::numeric_limits<float>::max_digits10 - 2)
** 79% with std::setprecision(std::numeric_limits<double>::max_digits10 - 2)
** 96% with std::setprecision(std::numeric_limits<float>::max_digits10 - 3)
** 85% with std::setprecision(std::numeric_limits<double>::max_digits10 - 3)
*/

// T -> string		floating point overload
template <typename T, OK_IF(ISFLOAT(T))>
std::string serial(T const &x) {

	std::stringstream iss;

    iss << std::setprecision(std::numeric_limits<T>::max_digits10);
	iss << std::defaultfloat; //TODO: undefined with cygwin
	iss << std::noshowpos;
	iss << x;
	return iss.str();
}

// T -> string		integer overload
template <typename T, OK_IF(!ISFLOAT(T))>
std::string serial(T const &x) {

	std::stringstream iss;

	iss << x;
	return iss.str();
}

// T -> string		char overload
template <>
inline std::string serial<int8_t>(int8_t const &x) {

	std::stringstream iss;

	iss << static_cast<int>(x);
	return iss.str();
}

// ========================================================================== //

// string -> T
// (does not check str correctness)
template <typename T>
T unserial_unsafe(std::string const &str) {

	T val;

	std::stringstream(str) >> val;
	return val;
}

// string -> T		char overload
// (does not check str correctness)
template <>
inline int8_t unserial_unsafe<int8_t>(std::string const &str) {

	int16_t val;

	std::stringstream(str) >> val;
	return static_cast<int8_t>(val);
}

// ========================================================================== //

namespace detail // ~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

template <typename T>
[[ noreturn ]] void unserial_failed(char const *msg, std::string const &str) {

	throw std::invalid_argument(
		std::string(msg) + " occured while unserializing \""
		+ str + "\" to " + TypeToString<T>::name);
}

// string -> T		floating point overload
// (takes [-]?[0..9]+.[0..9]+ only strings, checks str correctness)
template <typename T, OK_IF(ISFLOAT(T))>
T unserial_safe(std::string const &str) {

	T val;
	std::stringstream oss(str);

	oss.clear();
	std::feclearexcept(FE_ALL_EXCEPT);
	oss >> val;
	if (oss.fail() || oss.bad() || !oss.eof())
		detail::unserial_failed<T>("Some error", str);
	if (std::fetestexcept(FE_UNDERFLOW) && std::fpclassify(val) == FP_ZERO)
		detail::unserial_failed<T>("Underflow", str);
	else if (std::fetestexcept(FE_OVERFLOW) || std::isinf(val))
		detail::unserial_failed<T>("Overflow", str);
	return val;
}

// string -> T		integer overload
// (takes [-]?[0..9]+ only strings, checks str correctness)
template <typename T, OK_IF(!ISFLOAT(T))>
T unserial_safe(std::string const &str) {

	T val;
	std::stringstream oss(str);

	oss.clear();
	oss >> val;
	if (oss.fail() || oss.bad() || !oss.eof())
		detail::unserial_failed<T>("Some error", str);
	return val;
}

// string -> T		char overload
// (takes [-]?[0..9]+ only strings, checks str correctness)
template <>
inline int8_t unserial_safe<int8_t>(std::string const &str) {

	int16_t val;
	std::stringstream oss(str);
	std::string reserial;

	oss.clear();
	oss >> val;
	if (oss.fail() || oss.bad() || !oss.eof())
		detail::unserial_failed<int8_t>("Some error", str);
	reserial = serial<int8_t>(val);
	if (str != reserial)
		detail::unserial_failed<int8_t>("Overflow", str);
	return static_cast<int8_t>(val);
}

}; // ~~~~~~~~~~~~~~~~~ END OF NAMESPACE DETAIL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

inline std::string clean(eOperandType e, std::string const &input) {

	std::string (*const func[5])(std::string const &str) = {
		[static_cast<int>(eOperandType::Int8)] = [](std::string const &in) {
			return serial<int8_t>(detail::unserial_safe<int8_t>(in));
		},
		[static_cast<int>(eOperandType::Int16)] = [](std::string const &in) {
			return serial<int16_t>(detail::unserial_safe<int16_t>(in));
		},
		[static_cast<int>(eOperandType::Int32)] = [](std::string const &in) {
			return serial<int32_t>(detail::unserial_safe<int32_t>(in));
		},
		[static_cast<int>(eOperandType::Float)] = [](std::string const &in) {
			return serial<float>(detail::unserial_safe<float>(in));
		},
		[static_cast<int>(eOperandType::Double)] = [](std::string const &in) {
			return serial<double>(detail::unserial_safe<double>(in));
		},
	};

	return func[static_cast<int>(e)](input);
}


// ========================================================================== //


}; // ~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE SER //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# undef OK_IF
# undef ISFLOAT

#endif /* ****************************************** ARITH_SERIALIZATIONS_HPP */
