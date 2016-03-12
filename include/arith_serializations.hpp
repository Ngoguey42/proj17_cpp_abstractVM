// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_serializations.hpp                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:54:40 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/12 17:30:00 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARITH_SERIALIZATIONS_HPP
# define ARITH_SERIALIZATIONS_HPP

# include <string>

# include "arith_types.hpp"

# define ISFLOAT(V) std::is_floating_point<V>::value

namespace ser // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


// T -> string
// no error
template <typename T>
std::string serial(typename std::enable_if_t<ISFLOAT(T), T> const &x);
template <typename T>
std::string serial(typename std::enable_if_t<!ISFLOAT(T), T> const &x);

// string -> T
// does not check str correctness
template <typename T>
T unserial_unsafe(std::string const &input);

// string -> T
// raise on error
template <typename T>
typename std::enable_if_t<ISFLOAT(T), T> unserial_safe(std::string const &in);
template <typename T>
typename std::enable_if_t<!ISFLOAT(T), T> unserial_safe(std::string const &in);

// string -> T
// calls the right unserial_safe
std::string clean(eOperandType e, std::string const &input);


}; // ~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE SER //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


# undef ISFLOAT

#endif /* ****************************************** ARITH_SERIALIZATIONS_HPP */
