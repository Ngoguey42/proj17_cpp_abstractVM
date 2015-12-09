// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 11:14:12 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "Operands.hpp"
#include "Evalexpr.hpp"

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

int							main(void)
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
