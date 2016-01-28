// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stackLogicFixture.cpp                              :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 15:07:18 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 15:39:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "stackLogicFixture.hpp"

using F = SLFixture;

F::SLFixture() {
}
F::~SLFixture() {
}

void F::fx_validate_underflow(void) {

	BOOST_CHECK(UNDERFLOWED(fx_output.str()));
	return ;
}

void F::fx_validate_overflow(void) {

	// PRINT_OUTPUT(fx_output);
	BOOST_CHECK_MESSAGE(OVERFLOWED(fx_output.str())
						, CRED + fx_output.str() + CEND);
	return ;
}

void F::fx_exec(std::function< bool(std::string const&) > pred) {

	BOOST_TEST_CONTEXT(ssFormat(fx_oss_cin, CCYA)) {
		{
			cout_redirect guardout(fx_output.rdbuf());
			cin_redirect guardin(fx_oss_cin.rdbuf());

			RUN_ABSTRACT_VM;
		}
		BOOST_TEST_INFO(ssFormat(fx_output, CRED));
		BOOST_CHECK(pred(fx_output.str()));
	};
	return ;
}
