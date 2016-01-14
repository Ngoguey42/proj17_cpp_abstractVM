// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/14 19:52:26 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
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

namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

template <class A, class B, bool, bool>
struct result_type {
	typedef typename std::conditional<(sizeof(A) > sizeof(B)), A, B>::type type;
};

template <class A, class B>
struct result_type<A, B, true, false> {
	typedef A	type;
};

template <class A, class B>
struct result_type<A, B, false, true> {
	typedef B	type;
};

}; // ~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

# define ISFLOAT(T) std::is_floating_point<T>::value

template <class A, class B>
struct result_type : public internal::result_type<A, B, ISFLOAT(A), ISFLOAT(B)>
{};

# undef ISFLOAT

#define TESTFUN(T)								\
	void	testfun(T)							\
	{											\
		std::cout << #T << std::endl;			\
		return ;								\
	}

TESTFUN(int8_t)
TESTFUN(int16_t)
TESTFUN(int32_t)
TESTFUN(float)
TESTFUN(double)

int							ololmainold(void)
{
	int8_t		i8 = 8;
	int16_t		i16 = 16;
	int32_t		i32 = 32;
	float		f = 40.f;
	double		d = 80.;

// #define TEST(A, B) testfun(A + B)
#define TEST(A, B) testfun(static_cast< result_type<decltype(A), decltype(B)>::type >(A + B))

	TEST(i8, i8);
	TEST(i8, i16);
	TEST(i8, i32);
	TEST(i8, f);
	TEST(i8, d);
	std::cout << "" << std::endl;
	TEST(i16, i8);
	TEST(i16, i16);
	TEST(i16, i32);
	TEST(i16, f);
	TEST(i16, d);
	std::cout << "" << std::endl;
	TEST(i32, i8);
	TEST(i32, i16);
	TEST(i32, i32);
	TEST(i32, f);
	TEST(i32, d);
	std::cout << "" << std::endl;
	TEST(f, i8);
	TEST(f, i16);
	TEST(f, i32);
	TEST(f, f);
	TEST(f, d);
	std::cout << "" << std::endl;
	TEST(d, i8);
	TEST(d, i16);
	TEST(d, i32);
	TEST(d, f);
	TEST(d, d);
	std::cout << "" << std::endl;
	return (0);
}

int							mainoulol(void)
{
	MStack<int>		s;

	for (int i = 0; i < 10; i++)
	{
		s.push(i);
	}
	MStack<int> const		&sptr = s;
	for (auto const &elt : sptr)
	{
		std::cout << elt << std::endl;
	}
	return (0);
}

void add_dump_pop(VMStack &vmst)
{
	VMStack::actmap.at("add")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	return ;
}


#include <iomanip>

#define DUMP(T, F)														\
	std::cout << std::setw(15) << #F ": " << std::numeric_limits<T>::F() << std::endl



int							mainn(void)
{
	OpFactory fact;
	VMStack vmst(fact);


	for (int i = 0; i < 45; i++)
	{
		VMStack::actmap.at("push")(&vmst, std::string("Float(1") + std::string(i, '0') + ")");
		VMStack::actmap.at("push")(&vmst, "Float(+0)");
		VMStack::actmap.at("add")(&vmst, "");
	}
	VMStack::actmap.at("dump")(&vmst, "");
	// add_dump_pop(vmst);
	std::cout << "" << std::endl;

	return 0;
	VMStack::actmap.at("push")(&vmst, "Int16(-128)");
	VMStack::actmap.at("push")(&vmst, "Int16(2)");
	VMStack::actmap.at("sub")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	std::cout << "" << std::endl;

	VMStack::actmap.at("push")(&vmst, "Int8(-128)");
	VMStack::actmap.at("push")(&vmst, "Int16(2)");
	VMStack::actmap.at("sub")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	std::cout << "" << std::endl;

	VMStack::actmap.at("push")(&vmst, "Int16(-128)");
	VMStack::actmap.at("push")(&vmst, "Int8(2)");
	VMStack::actmap.at("sub")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	std::cout << "" << std::endl;
	return (0);
}

#include <iostream>
#include <cfenv>
#include <cmath>
#include <cerrno>
#include <cstring>
// #pragma STDC FENV_ACCESS ON
int mainnn()
{
	std::feclearexcept(FE_ALL_EXCEPT);
	errno = 0;
	std::cout <<  "log(0) = " << std::log(0) << '\n';
	if(errno == ERANGE)
		std::cout << "errno = ERANGE (" << std::strerror(errno) << ")\n";
	if(std::fetestexcept(FE_DIVBYZERO))
		std::cout << "FE_DIVBYZERO (pole error) reported\n";
	return 0;
}



template <class T>
std::string		type_of_expr(T const &) {
	return typeid(T).name();
}


#define I8(V) static_cast<int8_t>((V))
#define I16(V) static_cast<int16_t>((V))
#define I32(V) static_cast<int16_t>((V))


void dumpFeExcept(void)
{
#define REPORT(FLAG)									\
	std::cout << std::setw(13) << #FLAG;				\
	if (std::fetestexcept((FLAG)))						\
		std::cout << " \033[31m1\033[0m" << std::endl;	\
	else												\
		std::cout << " 0" << std::endl
	REPORT(FE_DIVBYZERO);
	REPORT(FE_INEXACT);
	REPORT(FE_INVALID);
	REPORT(FE_OVERFLOW);
	REPORT(FE_UNDERFLOW);
	// REPORT(FE_ALL_EXCEPT);
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



#define DMAX std::numeric_limits<double>::max()
#define DMIN std::numeric_limits<double>::min()
#define DLOWEST std::numeric_limits<double>::lowest()

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
	std::cout << "defined: " #TYPE #FUN << std::endl;				\
	volatile const TYPE TYPE##FUN = std::numeric_limits<TYPE>::FUN()

	DEFINE(double, max);
	DEFINE(float, max);
	DEFINE(double, lowest);
	DEFINE(float, lowest);
	DEFINE(double, min);
	DEFINE(float, min);
	DEFINE(double, denorm_min);
	DEFINE(float, denorm_min);

	volatile const double zero = 0.0;
	volatile const double one = 1.0;
	volatile const double dmax = DMAX;


	// double (*ftsqrt)(double, double) = static_cast<double (*)(double, double)>(std::pow);

	TESTA(const double val = doublemax + doublemax);
	TESTA(const double val = doublelowest + doublelowest);
	// TESTA(const double val = doublemin);
	// TESTA(const double val = doublemin / 2);
	// TESTA(const double val = doubledenorm_min);
	TESTA(const double val = doubledenorm_min / 2);
	// TESTA(const double val = 0. / 0.);
	// TESTA(const double val = zero / zero);
	// TESTA(const double val = zero + zero);
	// TESTA(const double val = -zero);
	// TESTA(const double val = zero);
	// TESTA(const double val = one);
	// TESTA(const double val = 1.);

	// TESTA(const float val = floatmax);
	// TESTA(const float val = floatmax + floatmax);
	// TESTA(const double val = doublelowest);
	// TESTA(const float val = floatlowest);
	// TESTA(const float val = floatlowest + floatlowest);
	// TESTA(const float val = floatlowest - 1.f);
	// TESTA(const double val = dmax + dmax);
	// TESTA(const double val = DMAX + DMAX);
	// TESTA(volatile const double val = DMAX + DMAX);
	// TESTA(volatile const double val = dmax + dmax);
	// double (*ftsqrt)(double) = static_cast<double (*)(double)>(std::sqrt);

	// TESTA(volatile const double val = std::plus<double>()(DMAX, DMAX));
	// TESTA(volatile const double val = std::plus<double>()(DMAX, 1.));
	// TESTA(volatile const double val = DMAX + DMAX);
	// TESTA(volatile const double val = std::pow<double>(std::numeric_limits<double>::max(), 2));
	// TESTA(volatile const double val = DMAX);
	// TESTA(volatile const double val = DMIN);
	// TESTA(volatile const double val = DMIN * 1000);
	// TESTA(volatile const double val = ftsqrt(DMIN, 2.));
	// TESTA(volatile const double val = ftsqrt(DMIN * 10000000000., 2.));
	// TESTA(volatile const double val = std::sqrt<double>(DLOWEST));


	return 0;

	// TESTA(volatile const double val = one / zero);
	// TESTA(volatile const float val = zero / zero);
	// TESTA(volatile const double val = 2.);
	// TESTA(volatile const double val = one / one);
	// TESTA(volatile const int8_t val = I8(I8(-128) - I8(1)));
	// TESTA(volatile const float val = std::numeric_limits<float>::max());
	TESTA(volatile const double val = std::numeric_limits<double>::min() * std::numeric_limits<double>::min());
	// TESTA(volatile const float val = std::numeric_limits<float>::max() * 2.f);
	// TESTA(volatile const float val = std::numeric_limits<float>::max() + 10000000000000000000000000000000000000.f);

	DUMP(float, min);
	DUMP(float, lowest);
	DUMP(float, max);
	DUMP(float, epsilon);
	DUMP(float, round_error);
	DUMP(float, infinity);
	DUMP(float, denorm_min);
	std::cout << std::endl;

	// std::feclearexcept(FE_ALL_EXCEPT);
	// std::cout << "sqrt(-1) = " << std::sqrt(-1) << '\n';
	// dumpFeExcept();
	return 0;
}
