// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   limitsFixture.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 13:13:53 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 16:14:11 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <type_traits>

#include "limitsFixture.hpp"

#include "testConf.hpp"
#include "testTools.hpp"

using F = LFixture;

F::LFixture() {
}
F::~LFixture() {
}

template <class T>
void F::fx_init(T const &val) {

	fx_ref_valld = static_cast<long double>(val);
	fx_ref_valstr = nbrToString(val);
	fx_ref_valtypestr = std::string(TypeToString<T>::name)
		+ "(" + fx_ref_valstr + ")";
	fx_isfloat = std::is_floating_point<T>::value;
	return ;
}

template <class T>
void F::fx_run_paad(void) { // paad -> Push Add0 Assert Dump

	fx_oss_cin << "push ";
	fx_oss_cin << fx_ref_valtypestr;
	fx_oss_cin << "\n";

	fx_oss_cin << "push int8(0)\n";
	fx_oss_cin << "add\n";

	fx_oss_cin << "assert ";
	fx_oss_cin << fx_ref_valtypestr;
	fx_oss_cin << "\n";

	fx_oss_cin << "dump\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;";
	_fx_exec1();
	return ;
}

template <class T>
void F::fx_run_selfmult(void) {

	fx_oss_cin << "push ";
	fx_oss_cin << fx_ref_valtypestr;
	fx_oss_cin << "\n";

	fx_oss_cin << "push ";
	fx_oss_cin << fx_ref_valtypestr;
	fx_oss_cin << "\n";

	fx_oss_cin << "mul\n";

	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;";
	_fx_exec1();
	return ;
}

template <class T>
void F::fx_run_oneover(void) {

	fx_oss_cin << "push int8(1)\n";

	fx_oss_cin << "push ";
	fx_oss_cin << fx_ref_valtypestr;
	fx_oss_cin << "\n";

	fx_oss_cin << "div\n";

	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;";
	_fx_exec1();
	return ;
}

template <class T>
bool F::fx_validate_ok(void) {

	long double dumped_valld;

	dumped_valld = strToLD<T>(fx_output.str());
	return fx_ref_valld == dumped_valld;
}

bool F::fx_validate_underflow(void) {

	return UNDERFLOWED(fx_output.str());
}

bool F::fx_validate_overflow(void) {

	return OVERFLOWED(fx_output.str());
}

void F::_fx_exec1(void) {

	BOOST_TEST_CONTEXT(ssFormat(fx_oss_cin, CCYA)) {
		_fx_exec2();
		BOOST_TEST_INFO(ssFormat(fx_output, CRED));
		BOOST_CHECK( (this ->* fx_pred)() );
	};
	return ;
}

void F::_fx_exec2(void) {

	cout_redirect guardout(fx_output.rdbuf());
	cin_redirect guardin(fx_oss_cin.rdbuf());

	RUN_ABSTRACT_VM;
}

#define INSTANCIATE(T)									\
	template void F::fx_init<T>(T const &val);			\
	template void F::fx_run_paad<T>(void);				\
	template void F::fx_run_selfmult<T>(void);			\
	template bool F::fx_validate_ok<T>(void);			\
	template void F::fx_run_oneover<T>(void);			\

INSTANCIATE(int8_t)
INSTANCIATE(int16_t)
INSTANCIATE(int32_t)
INSTANCIATE(float)
INSTANCIATE(double)
