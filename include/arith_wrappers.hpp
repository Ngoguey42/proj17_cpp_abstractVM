// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_wrappers.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:56:07 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/26 20:18:11 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARITH_WRAPPERS_HPP
# define ARITH_WRAPPERS_HPP

# include <type_traits>
# include <string>
# include <memory>
# include <iostream> //tmp

# include "arith_operations.hpp"

// IOperand defined in subject.pdf
//		interface with all allowed operations on operands

// OpFactory required by subject.pdf
//		factory

// Operand required by subject.pdf
//		wrapper around a value

// IOperand operator +
//		may throw std::overflow_error from Evalexpr call
// IOperand operator -
//		may throw std::overflow_error from Evalexpr call
// IOperand operator /
//		may throw std::domain_error from Evalexpr call
//		may throw std::underflow_error from Evalexpr call
//		may throw std::overflow_error from Evalexpr call
// IOperand operator *
//		may throw std::overflow_error from Evalexpr call
//		may throw std::underflow_error from Evalexpr call
// IOperand operator %
//		may throw std::domain_error from Evalexpr call

// Interface ********************************** //
class IOperand // IOperand from subject.pdf
{
public:
	virtual int getPrecision(void) const = 0;
	virtual eOperandType		getType(void) const = 0;
	virtual IOperand const		*operator+(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator-(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator*(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator/(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator%(IOperand const &rhs) const = 0;
	virtual std::string const	&toString(void) const = 0;
	virtual ~IOperand() {}
};

// Operand Factory **************************** //
class OpFactory // OpFactory from subject.pdf
{

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

	IOperand const		*createOperandFromString(
		std::string const &str) const;

};

// Operand ************************************ //
template <class T, eOperandType TEnumVal = operand_enum<T>::value>
class Operand : public IOperand
{
	OpFactory const		&_fact;
	std::string const	_val;

public:

	~Operand(){}
	Operand(OpFactory const &fact, std::string const &str)
		: _fact(fact), _val(str)
		{}

	Operand() = delete;
	Operand(Operand const &src) = delete;
	Operand(Operand &&src) = delete;
	Operand				&operator=(Operand const &rhs) = delete;
	Operand				&operator=(Operand &&rhs) = delete;

	int					getPrecision(void) const override {
		return static_cast<int>(TEnumVal);
	}

	eOperandType		getType(void) const override {
		return TEnumVal;
	}

	std::string const	&toString(void) const override {
		return _val;
	}

# define DEFINE_OPERATOR(OP, OPNAME)									\
	IOperand const		*operator OP(IOperand const &rhs) const override { \
																		\
																		\
		eOperandType const	dstType = std::max(rhs.getType(), TEnumVal); \
		std::unique_ptr<IOperand const> tmp;							\
		IOperand const *ret;											\
																		\
		if (dstType == TEnumVal)										\
		{																\
			return _fact.createOperand(									\
				dstType, eval::eval<T, eval::OPNAME>(_val, rhs.toString())); \
		}																\
		else															\
		{																\
			tmp.reset(this->_fact.createOperand(dstType, _val));		\
			ret = *tmp.get() OP rhs;									\
			return ret;													\
		}																\
	}

	DEFINE_OPERATOR(+, Add)
	DEFINE_OPERATOR(-, Sub)
	DEFINE_OPERATOR(*, Mul)
	DEFINE_OPERATOR(/, Div)
	DEFINE_OPERATOR(%, Mod)

# undef DEFINE_OPERATOR

};

#endif /* ************************************************ ARITH_WRAPPERS_HPP */
