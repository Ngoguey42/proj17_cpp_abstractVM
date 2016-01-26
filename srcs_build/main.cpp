// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/26 18:29:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <iostream>
#include <cfenv>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <iomanip>

#include "Controller.hpp"

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

int							main(int ac, char const *av[])
{
	return Controller()(ac, av);
}
