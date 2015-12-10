// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operands.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:04:37 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/10 12:26:01 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OPERANDS_HPP
# define OPERANDS_HPP

#include <type_traits>
#include <string>
#include <stack>

#include "Evalexpr.hpp"

// eOperandType from subject.pdf
// IOperand from subject.pdf
// OpFactory from subject.pdf

// Enum *************************************** //
enum class eOperandType // eOperandType from subject.pdf
{
	Int8 = 0,
		Int16,
		Int32,
		Float,
		Double
		};

template <class T>	struct operand_enum;

template <>			struct operand_enum<int8_t>
	: std::integral_constant<eOperandType, eOperandType::Int8> {};

template <>			struct operand_enum<int16_t>
	: std::integral_constant<eOperandType, eOperandType::Int16> {};

template <>			struct operand_enum<int32_t>
	: std::integral_constant<eOperandType, eOperandType::Int32> {};

template <>			struct operand_enum<float>
	: std::integral_constant<eOperandType, eOperandType::Float> {};

template <>			struct operand_enum<double>
	: std::integral_constant<eOperandType, eOperandType::Double> {};

// Interface ********************************** //
class IOperand // IOperand from subject.pdf
{
public:
	// virtual int getPrecision(void) const = 0; // Precision of the type of the instance
	virtual eOperandType		getType(void) const = 0;
	virtual IOperand const		*operator+(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator-(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator*(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator/(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator%(IOperand const &rhs) const = 0;
	virtual std::string const	&toString(void) const = 0;
	virtual ~IOperand() {}
};

// Operand ** forward declaration ************* //
template <class T, eOperandType TEnumVal>
class Operand;

// Operand Factory **************************** //
class OpFactory // OpFactory from subject.pdf
{
	static std::stack<IOperand *>	_garbageCollector;

	typedef IOperand const *(OpFactory::*fun_t)(std::string const &value) const;

	IOperand const 		*createInt8(std::string const &value) const;
	IOperand const 		*createInt16(std::string const &value) const;
	IOperand const 		*createInt32(std::string const &value) const;
	IOperand const 		*createFloat(std::string const &value) const;
	IOperand const 		*createDouble(std::string const &value) const;

	static fun_t const	funs[5];

public:
	IOperand const		*createOperand(
		eOperandType type, std::string const &value) const;

};

// Operand ************************************ //
template <class T, eOperandType TEnumVal = operand_enum<T>::value>
class Operand : public IOperand
{
	OpFactory const		&_fact;
	std::string const	_val;

public:

	~Operand() {}
	Operand(OpFactory const &fact, std::string const &str)
		: _fact(fact), _val(str) {}

	Operand() = delete;
	Operand(Operand const &src) = delete;
	Operand(Operand &&src) = delete;
	Operand				&operator=(Operand const &rhs) = delete;
	Operand				&operator=(Operand &&rhs) = delete;

	eOperandType		getType(void) const override {
		return TEnumVal;
	}

	std::string const	&toString(void) const override {
		return _val;
	}

# define DEFINE_OPERATOR(OP, OPNAME)									\
	IOperand const		*operator OP(IOperand const &rhs) const override { \
		using Ee = Evalexpr<T>;											\
																		\
		eOperandType const	dstType = std::max(rhs.getType(), TEnumVal); \
																		\
		if (dstType != TEnumVal) // nornmal case						\
			return rhs OP *this;										\
		else // reverse case											\
			return _fact.createOperand(									\
				dstType, Ee::eval(_val, Ee::OPNAME, rhs.toString()));	\
	}

	DEFINE_OPERATOR(+, Add)
	DEFINE_OPERATOR(-, Sub)
	DEFINE_OPERATOR(*, Mul)
	DEFINE_OPERATOR(/, Div)
	DEFINE_OPERATOR(%, Mod)

# undef DEFINE_OPERATOR

};

#endif /* ****************************************************** OPERANDS_HPP */
