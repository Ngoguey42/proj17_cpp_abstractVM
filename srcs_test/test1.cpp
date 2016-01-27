// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   boost_test_1.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 20:06:12 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 17:23:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
using boost::test_tools::output_test_stream;

#include <deque>

#include "limitsTestsTools.hpp"
#include "testTools.hpp"
#include "Controller.hpp"

void push_add0_assert_dump(
	boost::test_tools::output_test_stream &output
	, std::string const &type, std::string const &val)
{
	std::stringstream oss;
	cout_redirect guardout(output.rdbuf());
	cin_redirect guardin(oss.rdbuf());

	output.str(""); //reset output stream

	oss << "push ";
	oss << type;
	oss << "(";
	oss << val;
	oss << ")\n";

	oss << "push int8(0)\n";
	oss << "add\n";

	oss << "assert ";
	oss << type;
	oss << "(";
	oss << val;
	oss << ")\n";

	oss << "dump\n";
	oss << "exit\n";
	oss << ";;";
	Controller()(1, nullptr);
	return ;
}

BOOST_AUTO_TEST_CASE(limits)
{
	boost::test_tools::output_test_stream output;
	Limits const limits[] = {
		Limits("int8", int8_t{}),
		Limits("int16", int16_t{}),
		Limits("int32", int32_t{}),
		Limits("float", float{}),
		Limits("double", double{}),
	};
	long double ref;
	long double dumped;

	for (auto const &l : limits)
	{
		push_add0_assert_dump(output, l._type, l._max);
		ref = strToLD(l._max, l._type);
		dumped = strToLD(output.str(), l._type);
		BOOST_CHECK(ref == dumped);

		push_add0_assert_dump(output, l._type, l._min);
		ref = strToLD(l._min, l._type);
		dumped = strToLD(output.str(), l._type);
		BOOST_CHECK(ref == dumped);

		push_add0_assert_dump(output, l._type, l._lowest);
		ref = strToLD(l._lowest, l._type);
		dumped = strToLD(output.str(), l._type);
		BOOST_CHECK(ref == dumped);
	}
}
