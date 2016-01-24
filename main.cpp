// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/24 18:26:41 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <iostream>
#include <cfenv>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <iomanip>

#include "VMStack.hpp"

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

union Bordel
{
	float f;
	int8_t i8;
	int16_t i16;
	int32_t i32;
	double d;
	size_t i;

	Bordel &randomize(void) {

		size_t j = 0;

		for (unsigned int k = 0; k < sizeof(Bordel) * 8; k++)
		{
			if (k != 0)
				j <<= 1;
			if (std::rand() % 2)
				j |= 1;
			// this->i = (this->i & ~(1 << i)) | ((std::rand() % 2) << i);
		}
		this->i = j;
		return *this;
	}

	operator float (void) {
		return this->f;
	}
	operator double (void) {
		return this->d;
	}
	operator int8_t (void) {
		return this->i8;
	}
	operator int16_t (void) {
		return this->i16;
	}
	operator int32_t (void) {
		return this->i32;
	}


};


template <class T>
void test(VMStack &vmst, std::string const &type) {

	T tmp;
	tmp = Bordel{}.randomize();
	VMStack::actmap.at("push")(&vmst, type + "(" + ser::serial<T>(tmp) + ')');

	for (;;)
	{
		tmp = Bordel{}.randomize();
		if (tmp == tmp && tmp != +1. / 0. && tmp != -1. / 0.)
		{
			VMStack::actmap.at("push")(&vmst, type + "(" + ser::serial<T>(tmp) + ')');
			VMStack::actmap.at("dump")(&vmst, "");
			std::cout << "=" << std::endl;
			// VMStack::actmap.at("mul")(&vmst, "");
			VMStack::actmap.at("add")(&vmst, "");
			// VMStack::actmap.at("mod")(&vmst, "");
			// VMStack::actmap.at("sub")(&vmst, "");
			// VMStack::actmap.at("div")(&vmst, "");
			VMStack::actmap.at("dump")(&vmst, "");
			std::cout << "///////////////////////////////////" << std::endl;
		}
		// if (tmp != tmp)
		// 	return ;
	}

}

int							main(void)
{
	OpFactory fact;
	VMStack vmst(fact);
	std::srand(time(NULL));


	// test<int8_t>(vmst, "Int8");
	// test<int16_t>(vmst, "Int16");
	// test<int32_t>(vmst, "Int32");
	// test<float>(vmst, "Float");
	test<double>(vmst, "Double");



	// do {


	// } while (c++ < 127);
	VMStack::actmap.at("dump")(&vmst, "");

	return (0);
}
