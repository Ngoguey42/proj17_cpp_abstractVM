// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stackLogicTests.cpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 15:04:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 15:48:34 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "stackLogicFixture.hpp"

BOOST_FIXTURE_TEST_SUITE(stack_logic, SLFixture)

BOOST_AUTO_TEST_CASE(pop_empty)
{
	fx_oss_cin << "pop\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return STACKSIZELOW(str);});
}

BOOST_AUTO_TEST_CASE(assert_empty)
{
	fx_oss_cin << "assert int8(0)\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return STACKSIZELOW(str);});
}

BOOST_AUTO_TEST_CASE(assert_badtype)
{
	fx_oss_cin << "push int8(0)\n";
	fx_oss_cin << "assert int16(42)\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return ASSERTNOMATCH(str);});
}

BOOST_AUTO_TEST_CASE(assert_badval)
{
	fx_oss_cin << "push int16(0)\n";
	fx_oss_cin << "assert int16(42)\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return ASSERTNOMATCH(str);});
}

BOOST_AUTO_TEST_CASE(arith_empty)
{
	fx_oss_cin << "add\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return STACKSIZELOW(str);});
}

BOOST_AUTO_TEST_CASE(arith_one)
{
	fx_oss_cin << "push float(0.0)\n";
	fx_oss_cin << "add\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return STACKSIZELOW(str);});
}

BOOST_AUTO_TEST_CASE(print_empty)
{
	fx_oss_cin << "print\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return STACKSIZELOW(str);});
}

BOOST_AUTO_TEST_CASE(print_bad_type)
{
	fx_oss_cin << "push float(42.42)\n";
	fx_oss_cin << "print\n";
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return PRINTBADTYPE(str);});
}

BOOST_AUTO_TEST_SUITE_END()
