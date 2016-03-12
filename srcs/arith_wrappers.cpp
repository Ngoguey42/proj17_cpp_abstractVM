// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_wrappers.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:57:06 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/12 18:07:45 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "arith_serializations.hpp"
#include "arith_wrappers.hpp"
#include "arith_operations.hpp"

template <class T>
using OP = Operand<T>;
using OF = OpFactory;

std::unordered_map<std::string, eOperandType> const operandMap = {
	{"int8", eOperandType::Int8},
	{"int16", eOperandType::Int16},
	{"int32", eOperandType::Int32},
	{"float", eOperandType::Float},
	{"double", eOperandType::Double},
};

std::unordered_map<eOperandType, std::string, HasheOperandType> const operandStringsMap = {
	{eOperandType::Int8, "int8"},
	{eOperandType::Int16, "int16"},
	{eOperandType::Int32, "int32"},
	{eOperandType::Float, "float"},
	{eOperandType::Double, "double"},
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

IOperand const *OF::createOperand(
	eOperandType type, std::string const &value) const
{
	return (this ->* funs[static_cast<int>(type)])(value);
}

IOperand const *OF::createOperandFromString(std::string const &str) const
{
	std::size_t const opparen = str.find('(');
	std::string const type = str.substr(0, opparen);
	eOperandType const etype = operandMap.at(type);
	std::string const n = str.substr(opparen + 1, str.find(')') - opparen - 1);
	std::string const nClean = ser::clean(etype, n);

	return this->createOperand(etype, nClean);
}

template <class T>
const eOperandType OP<T>::_tEnumVal = operand_enum<T>::value;

template <class T>
OP<T>::~Operand()
{}

template <class T>
OP<T>::Operand(OpFactory const &fact, std::string const &str)
	: _fact(fact), _val(str)
{}

template <class T>
int OP<T>::getPrecision(void) const
{
	return static_cast<int>(_tEnumVal);
}

template <class T>
eOperandType OP<T>::getType(void) const
{
	return _tEnumVal;
}

template <class T>
std::string const	&OP<T>::toString(void) const
{
	return _val;
}

# define DEFINE_OPERATOR(OPER, OPNAME)									\
	template <class T>													\
	IOperand const		*OP<T>::operator OPER(IOperand const &rhs) const { \
																		\
		eOperandType const	dstType = std::max(rhs.getType(), _tEnumVal); \
		std::unique_ptr<IOperand const> tmp;							\
		IOperand const *ret;											\
																		\
		if (dstType == _tEnumVal)										\
		{																\
			return _fact.createOperand(									\
				dstType, eval::eval<T, eval::OPNAME>(_val, rhs.toString())); \
		}																\
		else															\
		{																\
			tmp.reset(this->_fact.createOperand(dstType, _val));		\
			ret = *tmp.get() OPER rhs;									\
			return ret;													\
		}																\
	}

DEFINE_OPERATOR(+, Add)
DEFINE_OPERATOR(-, Sub)
DEFINE_OPERATOR(*, Mul)
DEFINE_OPERATOR(/, Div)
DEFINE_OPERATOR(%, Mod)

template class Operand<int8_t>;
template class Operand<int16_t>;
template class Operand<int32_t>;
template class Operand<float>;
template class Operand<double>;
