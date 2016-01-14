// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 18:12:25 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/14 15:00:27 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "VMStack.hpp"

using VMS = VMStack;
namespace PH {
using std::placeholders::_1;
using std::placeholders::_2;
};

VMS::opmap_t const		opmap = { /*static*/
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

void		VMS::arithmetic(VMS::arithfun_t f, std::string const &)
{
	IOperand const		*a;
	IOperand const		*b;

	if (this->size() < 2)
		throw std::out_of_range("Stack size too low for arithmetic");
	a = this->top();
	MStack::pop();
	b = this->top();
	MStack::pop();
	if (b->getType() > a->getType()) // normal case
		(b ->* f)(*a);
	else // reverse case
		(a ->* f)(*b);
	return ;
}
