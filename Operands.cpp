// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operands.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:03:21 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 11:09:18 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <cstdint>
#include <type_traits>
#include <algorithm>
#include <cmath>

#include "Operands.hpp"

using OF = OpFactory;

IOperand const *OF::createInt8(std::string const &value) const {
	return new Operand<int8_t>(*this, value);
}
IOperand const *OF::createInt16(std::string const &value) const {
	return new Operand<int16_t>(*this, value);
}
IOperand const *OF::createInt32(std::string const &value) const {
	return new Operand<int32_t>(*this, value);
}
IOperand const *OF::createFloat(std::string const &value) const {
	return new Operand<float>(*this, value);
}
IOperand const *OF::createDouble(std::string const &value) const {
	return new Operand<double>(*this, value);
}

OF::fun_t const		OF::funs[5] = {
	&OF::createInt8,
	&OF::createInt16,
	&OF::createInt32,
	&OF::createFloat,
	&OF::createDouble,
};

IOperand const *OF::createOperand(eOperandType type, std::string const &value) const
{
	return (this ->* funs[static_cast<int>(type)])(value);
}
