// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   limitsFixture.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 13:13:53 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 14:09:18 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <type_traits>

#include "limitsFixture.hpp"

#include "testConf.hpp"
#include "testTools.hpp"

using F = Fixture;

F::Fixture() {
}
F::~Fixture() {
}

template <class T>
void F::fx_init(T const &val) {

	fx_ref_valld = static_cast<long double>(val);
	fx_ref_valstr = nbrToString(val);
	fx_ref_valtypestr = std::string(TypeToString<T>::name)
		+ "(" + fx_ref_valstr + ")";
	fx_isfloat = std::is_floating_point<T>::value;
	BOOST_TEST_MESSAGE(CYEL + "preparing some test with "
					   + truncate(fx_ref_valtypestr) + CEND);
	return ;
}

template <class T>
void F::fx_run_paad(void) { // paad Push Add0 Assert Dump

	BOOST_TEST_MESSAGE(
		TAB + CYEL + "val+0+assert+dump operations" + CEND);

	std::stringstream oss;
	cout_redirect guardout(fx_output.rdbuf());
	cin_redirect guardin(oss.rdbuf());

	oss << "push ";
	oss << fx_ref_valtypestr;
	oss << "\n";

	oss << "push int8(0)\n";
	oss << "add\n";

	oss << "assert ";
	oss << fx_ref_valtypestr;
	oss << "\n";

	oss << "dump\n";
	oss << "exit\n";
	oss << ";;";
	RUN_ABSTRACT_VM;
	return ;
}

template <class T>
void F::fx_run_selfmult(void) {

	BOOST_TEST_MESSAGE(TAB + CYEL + "val*val operations" + CEND);

	std::stringstream oss;
	cout_redirect guardout(fx_output.rdbuf());
	cin_redirect guardin(oss.rdbuf());

	oss << "push ";
	oss << fx_ref_valtypestr;
	oss << "\n";

	oss << "push ";
	oss << fx_ref_valtypestr;
	oss << "\n";

	oss << "mul\n";

	oss << "exit\n";
	oss << ";;";
	RUN_ABSTRACT_VM;
	return ;
}

template <class T>
void F::fx_run_oneover(void) {

	BOOST_TEST_MESSAGE(TAB + CYEL + "1/val operations" + CEND);

	std::stringstream oss;
	cout_redirect guardout(fx_output.rdbuf());
	cin_redirect guardin(oss.rdbuf());

	oss << "push int8(1)\n";

	oss << "push ";
	oss << fx_ref_valtypestr;
	oss << "\n";

	oss << "div\n";

	oss << "exit\n";
	oss << ";;";
	RUN_ABSTRACT_VM;
	return ;
}

template <class T>
void F::fx_validate_ok(void) {

	long double dumped_valld;

	dumped_valld = strToLD<T>(fx_output.str());
	PRINT_OUTPUT(fx_output);
	BOOST_CHECK_EQUAL(fx_ref_valld, dumped_valld);
	return ;
}

template <class T>
void F::fx_validate_underflow(void) {

	PRINT_OUTPUT(fx_output);
	BOOST_CHECK(UNDERFLOWED(fx_output.str()));
	return ;
}

template <class T>
void F::fx_validate_overflow(void) {

	PRINT_OUTPUT(fx_output);
	BOOST_CHECK_MESSAGE(OVERFLOWED(fx_output.str())
						, CRED + fx_output.str() + CEND);
	return ;
}

#define INSTANCIATE(T)									\
	template void F::fx_init<T>(T const &val);		\
	template void F::fx_run_paad<T>(void);			\
	template void F::fx_run_selfmult<T>(void);		\
	template void F::fx_run_oneover<T>(void);			\
	template void F::fx_validate_ok<T>(void);			\
	template void F::fx_validate_underflow<T>(void);	\
	template void F::fx_validate_overflow<T>(void);

INSTANCIATE(int8_t)
INSTANCIATE(int16_t)
INSTANCIATE(int32_t)
INSTANCIATE(float)
INSTANCIATE(double)
