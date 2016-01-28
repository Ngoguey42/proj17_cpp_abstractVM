// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   numbersFixture.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 17:24:54 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 18:23:25 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "numbersFixture.hpp"

using F = NFixture;

F::NFixture() {
}
F::~NFixture() {
}

template <class T>
bool F::fx_validate_ok(void) {

	long double dumped_valld;

	dumped_valld = strToLD<T>(fx_output.str());
	return fx_ref_valld == dumped_valld;
}

void F::fx_exec(std::function< bool(std::string const&) > pred) {

	BOOST_TEST_CONTEXT(ssFormat(fx_oss_cin, CCYA)) {
		_fx_exec();
		BOOST_TEST_INFO(ssFormat(fx_output, CRED));
		BOOST_CHECK(pred(fx_output.str()));
	};
	return ;
}

void F::_fx_exec(void) {

	cout_redirect guardout(fx_output.rdbuf());
	cin_redirect guardin(fx_oss_cin.rdbuf());

	RUN_ABSTRACT_VM;
}

#define INSTANCIATE(T)                                  \
	template bool F::fx_validate_ok<T>(void);

INSTANCIATE(int8_t)
INSTANCIATE(int16_t)
INSTANCIATE(int32_t)
INSTANCIATE(float)
INSTANCIATE(double)
