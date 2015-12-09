// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operands.cpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:03:21 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 17:58:14 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <cstdint>

#include "Operands.hpp"

using OF = OpFactory;

std::stack<IOperand *>	OF::_garbageCollector{};

IOperand const *OF::createInt8(std::string const &value) const {
	auto 	i = new Operand<int8_t>(*this, value);

	_garbageCollector.push(i);
	return i;
}
IOperand const *OF::createInt16(std::string const &value) const {
	auto 	i = new Operand<int16_t>(*this, value);

	_garbageCollector.push(i);
	return i;
}
IOperand const *OF::createInt32(std::string const &value) const {
	auto 	i = new Operand<int32_t>(*this, value);

	_garbageCollector.push(i);
	return i;
}
IOperand const *OF::createFloat(std::string const &value) const {
	auto 	i = new Operand<float>(*this, value);

	_garbageCollector.push(i);
	return i;
}
IOperand const *OF::createDouble(std::string const &value) const {
	auto 	i = new Operand<double>(*this, value);

	_garbageCollector.push(i);
	return i;
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
