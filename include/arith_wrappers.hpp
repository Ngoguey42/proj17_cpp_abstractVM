// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_wrappers.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:56:07 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/12 18:06:32 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARITH_WRAPPERS_HPP
# define ARITH_WRAPPERS_HPP

# include "arith_types.hpp"

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
template <class T>
class Operand : public IOperand
{
	OpFactory const &_fact;
	std::string const _val;

	static const eOperandType _tEnumVal;

public:

	~Operand();
	Operand(OpFactory const &fact, std::string const &str);

	Operand() = delete;
	Operand(Operand const &src) = delete;
	Operand(Operand &&src) = delete;
	Operand &operator=(Operand const &rhs) = delete;
	Operand &operator=(Operand &&rhs) = delete;

	int getPrecision(void) const override;
	eOperandType getType(void) const override;
	std::string const &toString(void) const override;

	IOperand const *operator +(IOperand const &rhs) const override;
	IOperand const *operator -(IOperand const &rhs) const override;
	IOperand const *operator *(IOperand const &rhs) const override;
	IOperand const *operator /(IOperand const &rhs) const override;
	IOperand const *operator %(IOperand const &rhs) const override;

};

#endif /* ************************************************ ARITH_WRAPPERS_HPP */
