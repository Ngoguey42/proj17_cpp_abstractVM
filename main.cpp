// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/14 16:52:51 by ngoguey          ###   ########.fr       //
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

int							main(void)
{
	OpFactory fact;
	VMStack vmst(fact);

	VMStack::actmap.at("push")(&vmst, "Int8(42)");
	VMStack::actmap.at("push")(&vmst, "Int8(30)");
	VMStack::actmap.at("sub")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	std::cout << "" << std::endl;

	VMStack::actmap.at("push")(&vmst, "Int8(42)");
	VMStack::actmap.at("push")(&vmst, "Int16(30)");
	VMStack::actmap.at("sub")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	std::cout << "" << std::endl;

	VMStack::actmap.at("push")(&vmst, "Int16(42)");
	VMStack::actmap.at("push")(&vmst, "Int8(30)");
	VMStack::actmap.at("sub")(&vmst, "");
	VMStack::actmap.at("dump")(&vmst, "");
	VMStack::actmap.at("pop")(&vmst, "");
	std::cout << "" << std::endl;
	return (0);
}
