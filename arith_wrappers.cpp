// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_wrappers.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:57:06 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/24 15:57:13 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdint>

#include "arith_wrappers.hpp"

using OF = OpFactory;

std::unordered_map<std::string, eOperandType> const operandMap = {
	{"Int8", eOperandType::Int8},
	{"Int16", eOperandType::Int16},
	{"Int32", eOperandType::Int32},
	{"Float", eOperandType::Float},
	{"Double", eOperandType::Double},
};

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
