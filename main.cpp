// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/22 19:49:04 by ngoguey          ###   ########.fr       //
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

void sub_dump_pop(VMStack &vmst)
{
	VMStack::actmap.at("sub")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	return ;
}



int							main(void)
{
	OpFactory fact;
	VMStack vmst(fact);

	VMStack::actmap.at("push")(&vmst, "Int8(127)");
	VMStack::actmap.at("push")(&vmst, "Int8(1)");
	VMStack::actmap.at("dump")(&vmst, "");
	std::cout << std::endl;
	add_dump_pop(vmst);

	VMStack::actmap.at("push")(&vmst, "Int16(-32768)");
	VMStack::actmap.at("push")(&vmst, "Int16(1)");
	VMStack::actmap.at("dump")(&vmst, "");
	std::cout << std::endl;
	sub_dump_pop(vmst);


	// int a = 42;
	// int b = 12;

	// auto d = ee::detail::RawOperation<float, ee::Add, true>::func(a, b);

	// std::cout << d << std::endl;
	// std::cout << typeid(decltype(a)).name() << std::endl;
	// std::cout << typeid(decltype(b)).name() << std::endl;
	// std::cout << typeid(decltype(d)).name() << std::endl;

	return (0);
}





#define DUMP(T, F)														\
	std::cout << std::setw(15) << #F ": " << std::numeric_limits<T>::F() << std::endl

void dumpFeExcept(void)
{
#define REPORT(FLAG)							\
	if (std::fetestexcept((FLAG)))				\
		std::cout << std::setw(13) << #FLAG <<	\
			" \033[31m1\033[0m" << std::endl
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
		std::cout << #EXPR << ";" << std::endl;							\
		EXPR;															\
		bool isflt = std::is_floating_point<decltype(val)>::value;		\
		std::cout << " val -> " << (isflt ? val : (int)val) << std::endl; \
		dumpFeExcept();													\
	} while (0)


int mainold()
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
	std::cout << "defined: " #TYPE #FUN << ";" << std::endl;			\
	volatile const TYPE TYPE##FUN = std::numeric_limits<TYPE>::FUN();	\
	(void)TYPE##FUN

	DEFINE(double, max);
	// DEFINE(float, max);
	DEFINE(double, lowest);
	// DEFINE(float, lowest);
	DEFINE(double, min);
	// DEFINE(float, min);
	DEFINE(double, denorm_min);
	// DEFINE(float, denorm_min);
	volatile const double doublezero = 0.; (void)doublezero;
	// volatile const float floatzero = 0.; (void)floatzero;

	std::cout << "==================================================" << std::endl;
	TESTA(const double val = doublemax + doublemax);
	TESTA(const double val = doublelowest + doublelowest);
	TESTA(const double val = doublelowest * 2.);
	TESTA(const double val = 1. / doubledenorm_min);
	std::cout << "==================================================" << std::endl;
	TESTA(const double val = doubledenorm_min / 2.);
	TESTA(const double val = 1. / doublemax);
	TESTA(const double val = doubledenorm_min * doubledenorm_min);
	std::cout << "==================================================" << std::endl;
	TESTA(const double val = 1. / doublezero);
	std::cout << "==================================================" << std::endl;
	TESTA(const double val = doublezero / doublezero);
	TESTA(const double val = fmod(doublezero, doublezero));
	TESTA(const double val = fmod(1., doublezero));
	TESTA(const double val = fmod(doubledenorm_min, doubledenorm_min));
	TESTA(const double val = fmod(doublemax, doubledenorm_min));
	TESTA(const double val = fmod(doubledenorm_min, doublemax));
	TESTA(const double val = fmod(doublemax, doublemax));


	return 0;
}
