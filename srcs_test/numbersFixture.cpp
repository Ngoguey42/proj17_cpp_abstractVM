// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   numbersFixture.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 17:24:54 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 17:25:03 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "numbersFixture.hpp"

using F = NFixture;

F::NFixture() {
}
F::~NFixture() {
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
