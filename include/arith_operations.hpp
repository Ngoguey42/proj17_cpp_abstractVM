// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_operations.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:53:42 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/12 17:39:30 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARITH_OPERATIONS_HPP
# define ARITH_OPERATIONS_HPP

# include <string>


namespace eval // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


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

enum eOperation
{
	Add = 0,
	Sub,
	Div,
	Mul,
	Mod
};

template <class T, eOperation Operation>
std::string eval(std::string const &lhs, std::string const &rhs);


}; // ~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE EVAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


#endif /* ********************************************** ARITH_OPERATIONS_HPP */
