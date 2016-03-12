// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_serializations.hpp                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:54:40 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/12 17:11:50 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARITH_SERIALIZATIONS_HPP
# define ARITH_SERIALIZATIONS_HPP

# include <sstream>
# include <iomanip>
# include <limits>
# include <cfenv>

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

// T -> string
template <typename T>
std::string serial(typename std::enable_if_t<ISFLOAT(T), T> const &x);
template <typename T>
std::string serial(typename std::enable_if_t<!ISFLOAT(T), T> const &x);

// ========================================================================== //

// string -> T
// (does not check str correctness)
template <typename T>
T unserial_unsafe(std::string const &str);

// ========================================================================== //


std::string clean(eOperandType e, std::string const &input);


// ========================================================================== //


}; // ~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE SER //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# undef OK_IF
# undef ISFLOAT

#endif /* ****************************************** ARITH_SERIALIZATIONS_HPP */
