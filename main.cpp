// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/24 13:38:21 by ngoguey          ###   ########.fr       //
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
#include "serialization.hpp"

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




template <class T, class Stream>
void setflags(Stream &s)
{
	s << std::setprecision(std::numeric_limits<T>::max_digits10);
	s << std::fixed;
	return ;
}


template <class T>
void dotest(T const &f)
{
	// setflags<T>(std::cout);
	std::cout << "direct output: " << f << std::endl;
	std::cout << "built output:  " << ser::serial<T>(f) << std::endl;
	std::cout << "" << std::endl;
	return ;
}
#define DUMP(T, F)														\
	std::cout << std::setw(15) << #F ": " << std::numeric_limits<T>::F() << std::endl



union Bordel
{
	float f;
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
		return this->f;
	}

};


template <typename T>
void testerloop(void)
{
	T ref;
	std::string tostr;
	int err = 0;
	int max = 1 * 1000 * 1000;
	T toT;
	int clas;
	std::unordered_map<int, size_t> occ_map = {

		{FP_INFINITE, 0u},
		{FP_NAN, 0u},
		{FP_NORMAL, 0u},
		{FP_SUBNORMAL, 0u},
		{FP_ZERO, 0u},
	};

	for (int i = 0; i < max; i++)
	{
		ref = Bordel{}.randomize();
		clas = std::fpclassify(ref);
		occ_map[clas]++;
		if (clas != FP_NAN && clas != FP_INFINITE)
		{
			tostr = ser::serial<T>(ref);
			toT = ser::unserial_unsafe<T>(tostr);

			if (ref != toT)
			{
				err++;
				// std::cout << "Bordel" << std::endl;

				// std::cout << ref << std::endl;
				// std::cout << tostr << std::endl;
				// std::cout << toT << std::endl;

				// break;
			}

		}
	}

	for (auto occ : occ_map)
	{
		switch(occ.first) {
		case FP_INFINITE:  std::cout << "Inf"; break;
		case FP_NAN:       std::cout << "NaN"; break;
		case FP_NORMAL:    std::cout << "normal"; break;
		case FP_SUBNORMAL: std::cout << "subnormal"; break;
		case FP_ZERO:      std::cout << "zero"; break;
		default:           std::cout << "unknown"; break;
		}
		std::cout << " (" << occ.second << ") times" << std::endl;
	}
	std::cout << "Fails: (" << err << ")" << std::endl;
	std::cout << float(err) / float(max) * 100.f << "%" << std::endl;

	return ;
}

template <class T>
void test12(T const &x)
{
	std::cout << "test12 with: " << x << std::endl;

	auto tostr = ser::serial(x);
	std::cout << "tostr: " << tostr << std::endl;

	T tot = ser::unserial_unsafe<T>(tostr);
	std::cout << "back to T: " << tot << std::endl;
	std::cout << "identical? " << std::boolalpha << (x == tot) << std::endl;

	std::cout << "" << std::endl;
}



template <class T>
void test_unserial_safe(std::string const &str)
{
	std::cout << std::endl;

	std::cout << "From " << '"' << str << '"'  << std::endl;
	T val;
	try {
		val = ser::unserial_safe<T>(str);
		std::cout << "To (" << ser::serial(val) << ")" << std::endl;
	} catch (std::invalid_argument e) {
		std::cout << "Failed: " << e.what() << std::endl;
	}
	return ;
}


int							main(void)
{

	std::srand(time(NULL));

	test_unserial_safe<int16_t>("-32769");
	test_unserial_safe<int16_t>("-32768");
	test_unserial_safe<int16_t>("-32767");
	test_unserial_safe<int16_t>("-32766");
	test_unserial_safe<int16_t>("-32765");

	test_unserial_safe<int16_t>("32769");
	test_unserial_safe<int16_t>("32768");
	test_unserial_safe<int16_t>("32767");
	test_unserial_safe<int16_t>("32766");
	test_unserial_safe<int16_t>("32765");


	test_unserial_safe<int8_t>("128");
	test_unserial_safe<int8_t>("127");
	test_unserial_safe<int8_t>("126");

	test_unserial_safe<int8_t>("-129");
	test_unserial_safe<int8_t>("-128");
	test_unserial_safe<int8_t>("-127");

	char c = -128;

	do {


	} while (c++ < 127);

	// test12<double>(9007199254740990.);
	// test12<double>(9007199254740991.);
	// test12<double>(9007199254740992.);
	// test12<double>(9007199254740993.);
	// test12<double>(9007199254740994.);
	// test12<double>(9007199254740995.);

	// test12<float>(42.42f);
	// test12<double>(42.42f);
	// test12<int8_t>(42);
	// test12<int16_t>(42);
	// test12<int32_t>(42);
	// testerloop<double>();
	// testerloop<float>();

	return (0);
}

int mainoldlu(void)
{

	DUMP(float, min);
	DUMP(float, lowest);
	DUMP(float, max);
	DUMP(float, epsilon);
	DUMP(float, infinity);
	DUMP(float, denorm_min);


// dotest<float>((int32_t(42) + int32_t(33)) * float(44.55f));
	// dotest<double>(42.42);
#define DEFINE(TYPE, FUN)										\
	const TYPE TYPE##FUN = std::numeric_limits<TYPE>::FUN();	\
	(void)TYPE##FUN

	DEFINE(double, max);
	DEFINE(float, max);
	DEFINE(double, epsilon);
	DEFINE(float, epsilon);
	DEFINE(double, lowest);
	DEFINE(float, lowest);
	DEFINE(double, min);
	DEFINE(float, min);
	DEFINE(double, denorm_min);
	DEFINE(float, denorm_min);
	std::cout << std::endl;

	// float f = floatmax;

	std::cout << "min" << std::endl;
	dotest<float>(floatmin);
	dotest<float>(doublemin);
	dotest<double>(doublemin);
	std::cout << std::endl;
	std::cout << "lowest" << std::endl;
	dotest<float>(floatlowest);
	dotest<float>(doublelowest);
	dotest<double>(doublelowest);
	std::cout << std::endl;
	std::cout << "max" << std::endl;
	dotest<float>(floatmax);
	dotest<float>(doublemax);
	dotest<double>(doublemax);
	std::cout << std::endl;
	std::cout << "epsilon" << std::endl;
	dotest<float>(floatepsilon);
	dotest<float>(doubleepsilon);
	dotest<double>(doubleepsilon);
	std::cout << std::endl;
	std::cout << "denorm_min" << std::endl;
	dotest<float>(floatdenorm_min);
	dotest<float>(doubledenorm_min);
	dotest<double>(doubledenorm_min);
	std::cout << std::endl;
	std::cout << "curstom:" << std::endl;
	// dotest<float>(0.00004242f);
	// dotest<float>(0.0004242f);
	// dotest<float>(0.004242f);
	// dotest<float>(0.04242f);
	// dotest<float>(0.4242f);
	// dotest<float>(4.242f);
	// dotest<float>(42.42f);
	// dotest<float>(42.42f);
	// dotest<float>(42.42f);
	for (int i = -8; i < 9; i++)
	{
		std::cout << "42.42f * 10.f ^ " << i << ".f:" << std::endl;
		dotest<float>(42.42f * std::pow(10.f, float(i)));
	}



	// DUMP(float, min);
	// DUMP(float, lowest);
	// DUMP(float, max);
	// DUMP(float, epsilon);
	// DUMP(float, round_error);
	// DUMP(float, infinity);
	// DUMP(float, denorm_min);
	// std::cout << std::endl;


// OpFactory fact;
	// VMStack vmst(fact);

	// VMStack::actmap.at("push")(&vmst, "Int8(127)");
	// VMStack::actmap.at("push")(&vmst, "Int8(1)");
	// VMStack::actmap.at("dump")(&vmst, "");
	// std::cout << std::endl;
	// add_dump_pop(vmst);

	// VMStack::actmap.at("push")(&vmst, "Int16(-32768)");
	// VMStack::actmap.at("push")(&vmst, "Int16(1)");
	// VMStack::actmap.at("dump")(&vmst, "");
	// std::cout << std::endl;
	// sub_dump_pop(vmst);


	// int a = 42;
	// int b = 12;

	// auto d = ee::detail::RawOperation<float, ee::Add, true>::func(a, b);

	// std::cout << d << std::endl;
	// std::cout << typeid(decltype(a)).name() << std::endl;
	// std::cout << typeid(decltype(b)).name() << std::endl;
	// std::cout << typeid(decltype(d)).name() << std::endl;

	return (0);
}






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
	// DEFINE(float, denorm_min);
	// volatile const double doublezero = 0.; (void)doublezero;
	// volatile const float floatzero = 0.; (void)floatzero;

	// std::cout << "==================================================" << std::endl;
	// TESTA(const double val = doublemax + doublemax);
	// TESTA(const double val = doublelowest + doublelowest);
	// TESTA(const double val = doublelowest * 2.);
	// TESTA(const double val = 1. / doubledenorm_min);
	// std::cout << "==================================================" << std::endl;
	// TESTA(const double val = doubledenorm_min / 2.);
	// TESTA(const double val = 1. / doublemax);
	// TESTA(const double val = doubledenorm_min * doubledenorm_min);
	// std::cout << "==================================================" << std::endl;
	// TESTA(const double val = 1. / doublezero);
	// std::cout << "==================================================" << std::endl;
	// TESTA(const double val = doublezero / doublezero);
	// TESTA(const double val = fmod(doublezero, doublezero));
	// TESTA(const double val = fmod(1., doublezero));
	// TESTA(const double val = fmod(doubledenorm_min, doubledenorm_min));
	// TESTA(const double val = fmod(doublemax, doubledenorm_min));
	// TESTA(const double val = fmod(doubledenorm_min, doublemax));
	// TESTA(const double val = fmod(doublemax, doublemax));


	return 0;
}
