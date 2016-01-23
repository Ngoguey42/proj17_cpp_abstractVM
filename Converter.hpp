// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Converter.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/23 12:42:06 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/23 15:57:50 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONVERTER_HPP
# define CONVERTER_HPP

# include <sstream>
# include <iomanip>
# include <cmath> //tmp
# include <iostream> //debug

// # include ""

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISFLOAT(V) std::is_floating_point<V>::value

namespace conv // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


template <typename T, OK_IF(ISFLOAT(T))>
std::string convert(T const &x) {

	std::stringstream iss;

    iss << std::setprecision(std::numeric_limits<T>::max_digits10 - 1);
	iss << std::defaultfloat;
	iss << std::noshowpos;
	iss << x;
	return iss.str();
}


template <typename T>
T convert(std::string const &x) {

	std::stringstream oss(x);
	T val;

	oss >> val;
    // iss << std::setprecision(std::numeric_limits<T>::max_digits10);
	// iss << std::defaultfloat;
	// iss << std::noshowpos;
	// iss << x;
	return val;
}




template <typename T, OK_IF(!ISFLOAT(T))>
std::string convert(T const &x) {

	std::stringstream iss;

	iss << x;
	return iss.str();
}

template <>
inline std::string convert<int8_t>(int8_t const &x) {

	std::stringstream iss;

	iss << int(x);
	return iss.str();
}


}; // ~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE CONV //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //



// template <typename T>
// struct Converter
// {
// 	std::string operator () (T const &x) {


// 	}

// };

# undef OF_IF
# undef ISFLOAT

#endif /* ***************************************************** CONVERTER_HPP */
