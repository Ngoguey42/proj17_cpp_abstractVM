// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/22 11:56:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <iostream>
#include <cfenv>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <iomanip>

#include "MStack.hpp"
#include "VMStack.hpp"

#include "Operands.hpp"
#include "Evalexpr.hpp"

/*
** For non commutative operations, consider the stack v1 on v2 on stack_tail,
** the calculation in infix notation v2 op v1.
** *
** -> v1			30
** -> v2			42
** -> stack tail
** *
** v2 - v1 = 42 - 30 = 12
*/

void add_dump_pop(VMStack &vmst)
{
	VMStack::actmap.at("add")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	return ;
}

#define DUMP(T, F)														\
	std::cout << std::setw(15) << #F ": " << std::numeric_limits<T>::F() << std::endl

void dumpFeExcept(void)
{
#define REPORT(FLAG)									\
	std::cout << std::setw(13) << #FLAG;				\
	if (std::fetestexcept((FLAG)))						\
		std::cout << " \033[31m1\033[0m" << std::endl;	\
	else												\
		std::cout << " 0" << std::endl
	REPORT(FE_DIVBYZERO);
	REPORT(FE_INVALID);
	REPORT(FE_OVERFLOW);
	REPORT(FE_UNDERFLOW);
	std::cout << std::endl;
	return ;
}

#define TESTA(EXPR)														\
	do {																\
		std::feclearexcept(FE_ALL_EXCEPT);								\
		std::cout << #EXPR << std::endl;								\
		EXPR;															\
		bool isflt = std::is_floating_point<decltype(val)>::value;		\
		std::cout << " val -> " << (isflt ? val : (int)val) << std::endl; \
		dumpFeExcept();													\
	} while (0)

#define TESTB(EXPR)														\
	std::cout << #EXPR << " gave type: " << type_of_expr(EXPR) << '\n'

int main()
{
	DUMP(double, min);
	DUMP(double, lowest);
	DUMP(double, max);
	DUMP(double, epsilon);
	DUMP(double, round_error);
	DUMP(double, infinity);
	DUMP(double, denorm_min);
	std::cout << std::endl;

#define DEFINE(TYPE, FUN)												\
	std::cout << "defined: " #TYPE #FUN << std::endl;					\
	volatile const TYPE TYPE##FUN = std::numeric_limits<TYPE>::FUN();	\
	(void)TYPE##FUN

	DEFINE(double, max);
	DEFINE(float, max);
	DEFINE(double, lowest);
	DEFINE(float, lowest);
	DEFINE(double, min);
	DEFINE(float, min);
	DEFINE(double, denorm_min);
	DEFINE(float, denorm_min);

	TESTA(const double val = doublemax + doublemax);
	TESTA(const double val = doublelowest + doublelowest);
	TESTA(const double val = doubledenorm_min / 2);
	return 0;
}
