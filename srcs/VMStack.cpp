// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 18:12:25 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 13:57:19 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "VMStack.hpp"

using VMS = VMStack;
namespace PH {
using std::placeholders::_1;
using std::placeholders::_2;
};

VMS::actmap_t const VMS::actmap = { /*static*/
	{"push", &VMS::push},
	{"pop", &VMS::pop},
	{"dump", &VMS::dump},
	{"assert", &VMS::assert},
	{"add", std::bind(&VMS::arithmetic, PH::_1, &IOperand::operator+, PH::_2)},
	{"sub", std::bind(&VMS::arithmetic, PH::_1, &IOperand::operator-, PH::_2)},
	{"mul", std::bind(&VMS::arithmetic, PH::_1, &IOperand::operator*, PH::_2)},
	{"div", std::bind(&VMS::arithmetic, PH::_1, &IOperand::operator/, PH::_2)},
	{"mod", std::bind(&VMS::arithmetic, PH::_1, &IOperand::operator%, PH::_2)},
	{"print", &VMS::print},
	{"exit", &VMS::exit}
};

VMS::VMStack(OpFactory const &opFact) : MStack(), _opFact(opFact)
{}

VMS::~VMStack()
{
	for (auto const &op : *this)
		delete(op);
	MStack::operator=({}); /*super call*/
	return ;
}

bool VMS::push(std::string const &arg)
{
	IOperand const *const op =
		this->_opFact.createOperandFromString(arg);

	MStack::push(op); /*super call*/
	return false;
}

bool VMS::pop(std::string const &) /*unused argument*/
{
	if (this->size() < 1)
		throw std::out_of_range("Stack size too low for pop");
	delete(MStack::top()); /*super call*/
	MStack::pop(); /*super call*/
	return false;
}

bool VMS::dump(std::string const &) /*unused argument*/
{
	for (auto const &op : *this)
		std::cout << op->toString() << std::endl;
	return false;
}

bool VMS::assert(std::string const &arg)
{
	auto opToStr = [](IOperand const& op) {

		return operandStringsMap.at(op.getType()) + '(' + op.toString() + ')';
	};
	std::unique_ptr<IOperand const> const pred{
		this->_opFact.createOperandFromString(arg)};
	IOperand const *cur;

	if (this->size() < 1)
		throw std::out_of_range("Stack size too low for assert");
	cur = MStack::top();
	if (cur->getType() != pred->getType()
		|| cur->toString() != pred->toString())
		throw std::invalid_argument(
			opToStr(*cur) + " does not match given value " + opToStr(*pred)
			+ " (aka " + arg + ')');
	return false;
}

bool VMS::arithmetic(VMS::arithfun_t f, std::string const &) /*unused arg2*/
{
	std::unique_ptr<IOperand const> v1, v2;
	IOperand const *newop;

	if (this->size() < 2)
		throw std::out_of_range("Stack size too low for arithmetic");
	v1.reset(this->top());
	MStack::pop(); /*super call*/
	v2.reset(this->top());
	MStack::pop(); /*super call*/
	newop = (v2.get() ->* f)(*v1.get());
	MStack::push(newop); /*super call*/
	return false;
}

bool VMS::print(std::string const &)
{
	auto opToStr = [](IOperand const& op) {

		return operandStringsMap.at(op.getType()) + '(' + op.toString() + ')';
	};
	IOperand const *topop;
	int8_t val;

	if (this->size() < 1)
		throw std::out_of_range("Stack size too low for print");
	topop = MStack::top();
	val = ser::unserial_unsafe<int8_t>(topop->toString());
	if (topop->getType() != eOperandType::Int8 || val < 0)
		throw std::invalid_argument("Trying to print " + opToStr(*topop)
									+ " as an ascii character.");
	std::cout << val << std::endl;
	return false;
}

bool VMS::exit(std::string const &)
{
	for (auto const &op : *this)
		delete(op);
	MStack::operator=({}); /*super call*/
	return true;
}
