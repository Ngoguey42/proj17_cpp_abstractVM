// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 18:12:25 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 18:50:45 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "VMStack.hpp"

# include <functional>

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
	{"exit", &VMS::exit},
};
