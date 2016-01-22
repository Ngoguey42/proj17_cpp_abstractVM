// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/22 14:11:02 by ngoguey          ###   ########.fr       //
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



char plus(char a, char b)
{
	char const res = a + b;

	if (b > char(0))
	{
		if (res < a)
			throw std::overflow_error("bordel!");
	}
	else
	{
		if (res > a)
			throw std::overflow_error("bordel!");
	}
	return res;
}

char minus(char a, char b)
{
	char const res = a - b;

	if (b > char(0))
	{
		if (res > a)
			throw std::overflow_error("bordel!");
	}
	else
	{
		if (res < a)
			throw std::overflow_error("bordel!");
	}
	return res;
}

char multiplies(char a, char b)
{
	char const res = a * b;

	if ((a > char(0)) == (b > char(0)))
	{
		if (res < a)
			throw std::overflow_error("bordel!");
	}
	else
	{
		if (res > a)
			throw std::overflow_error("bordel!");
	}
	return res;
}


void test(char (*fc)(char, char), std::function< int(int, int) > fi)
{
	char i = -128;
	int nsucc = 0;

	do {
		char j = -128;
		// std::cout << int(i) << " ";
		do {
			int const resi = fi(i, j);
			char res;
			bool thrown;
			bool overflow;

			try {
				res = fc(i, j);
				thrown = false;
			} catch (...) {
				thrown = true;
			}
			overflow = resi != int(res);

			if (overflow != thrown)
			{
				std::cout << "thrown(" << std::boolalpha << thrown
						  << ") at op(" << int(i) << ", " << int (j)
						  << ")"
						  << std::endl;
			}
			else
				nsucc++;
		} while (j++ < 127);
	} while (i++ < 127);
	std::cout << "Done " << nsucc << " success" << std::endl;
	return ;
}


int	main(void)
{

	test(&minus, std::minus<int>());
	test(&plus, std::plus<int>());
	test(&multiplies, std::multiplies<int>());

	return (0);
}


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
