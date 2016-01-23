// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 18:12:25 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/14 17:16:15 by ngoguey          ###   ########.fr       //
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

void VMS::push(std::string const &arg)
{
	std::size_t const opparen = arg.find('(');
	std::string const type = arg.substr(0, opparen);
	std::string const n = arg.substr(opparen + 1, arg.find(')') - opparen - 1);
	eOperandType const etype = operandMap.at(type);
	IOperand const *const op = this->_opFact.createOperand(etype, n);
//TODO:  std::invalid_argument
	MStack::push(op);
	return ;
}

void VMS::pop(std::string const &) /*unused argument*/
{
	if (this->size() < 1)
		throw std::out_of_range("Stack size too low for pop");
	delete(MStack::top());
	MStack::pop();
	return ;
}

void VMS::dump(std::string const &) /*unused argument*/
{
	for (auto const &op : *this)
		std::cout << op->toString() << std::endl;
	return ;
}

void VMS::arithmetic(VMS::arithfun_t f, std::string const &) /*unused arg2*/
{
	IOperand const *v1, *v2;
	IOperand const *newop;

	if (this->size() < 2)
		throw std::out_of_range("Stack size too low for arithmetic");
	v1 = this->top();
	MStack::pop();
	v2 = this->top();
	MStack::pop();
	newop = (v2 ->* f)(*v1);
	MStack::push(newop);
	delete(v1);
	delete(v2);
	return ;
}
