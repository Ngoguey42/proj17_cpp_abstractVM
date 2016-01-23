// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Converter.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 12:42:06 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/23 16:21:05 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONVERTER_HPP
# define CONVERTER_HPP

# include <sstream>
# include <iomanip>
// # include <cmath> //tmp
// # include <iostream> //debug

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISFLOAT(V) std::is_floating_point<V>::value

namespace conv // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

/*
** %errors on floating point serial/deserial:
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
std::string convert(T const &x) {

	std::stringstream iss;

    iss << std::setprecision(std::numeric_limits<T>::max_digits10);
	iss << std::defaultfloat;
	iss << std::noshowpos;
	iss << x;
	return iss.str();
}

// T -> string		integer overload
template <typename T, OK_IF(!ISFLOAT(T))>
std::string convert(T const &x) {

	std::stringstream iss;

	iss << x;
	return iss.str();
}

// T -> string		char overload
template <>
inline std::string convert<int8_t>(int8_t const &x) {

	std::stringstream iss;

	iss << int(x);
	return iss.str();
}

// string -> T
// (does not check str correctness)
template <typename T>
T convert(std::string const &str) {

	T val;

	std::stringstream(str) >> val;
	return val;
}

// string -> T		char overload
// (does not check str correctness)
template <>
inline int8_t convert<int8_t>(std::string const &str) {

	int16_t val;

	std::stringstream(str) >> val;
	return val;
}

}; // ~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE CONV //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

# undef OF_IF
# undef ISFLOAT

#endif /* ***************************************************** CONVERTER_HPP */
