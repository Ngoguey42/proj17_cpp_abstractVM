// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   boost_test_1.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 20:06:12 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 18:12:40 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>
using boost::test_tools::output_test_stream;

#define CYEL std::string("\033[33m")
#define CEND std::string("\033[0m")

#include <deque>

#include "limitsTestsTools.hpp"
#include "testTools.hpp"
#include "Controller.hpp"

// void push_add0_assert_dump(
// 	boost::test_tools::output_test_stream &output
// 	, std::string const &type, std::string const &val)
// {
// 	std::stringstream oss;
// 	std::string const valstr = type + "(" + val + ")";
// 	BOOST_TEST_MESSAGE(CYEL + "push_add0_assert_dump over "
// 					   + truncate(valstr) + CEND);
// 	cout_redirect guardout(output.rdbuf());
// 	cin_redirect guardin(oss.rdbuf());

// 	output.str(""); //reset output stream

// 	oss << "push ";
// 	oss << valstr;
// 	oss << "\n";

// 	oss << "push int8(0)\n";
// 	oss << "add\n";

// 	oss << "assert ";
// 	oss << valstr;
// 	oss << "\n";

// 	oss << "dump\n";
// 	oss << "exit\n";
// 	oss << ";;";
// 	Controller()(1, nullptr); //run abstract vm program with ac=1 av=nullptr
// 	return ;
// }

template <class T>
void push_add0_assert_dump(
	boost::test_tools::output_test_stream &output, std::string const &val)
{
	std::stringstream oss;
	std::string const valstr = std::string(TypeToString<T>::name)
		+ "(" + val + ")";
	BOOST_TEST_MESSAGE(CYEL + "push_add0_assert_dump over "
					   + truncate(valstr) + CEND);
	cout_redirect guardout(output.rdbuf());
	cin_redirect guardin(oss.rdbuf());

	output.str(""); //reset output stream

	oss << "push ";
	oss << valstr;
	oss << "\n";

	oss << "push int8(0)\n";
	oss << "add\n";

	oss << "assert ";
	oss << valstr;
	oss << "\n";

	oss << "dump\n";
	oss << "exit\n";
	oss << ";;";
	Controller()(1, nullptr); //run abstract vm program with ac=1 av=nullptr
	return ;
}

// BOOST_AUTO_TEST_CASE(limits)
// {
// 	boost::test_tools::output_test_stream output;
// 	Limits const limits[] = {
// 		Limits("int8", int8_t{}),
// 		Limits("int16", int16_t{}),
// 		Limits("int32", int32_t{}),
// 		Limits("float", float{}),
// 		Limits("double", double{}),
// 	};
// 	long double ref;
// 	long double dumped;

// 	for (auto const &l : limits)
// 	{
// 		push_add0_assert_dump(output, l._type, l._max);
// 		ref = strToLD(l._max, l._type);
// 		dumped = strToLD(output.str(), l._type);
// 		BOOST_CHECK(ref == dumped);

// 		push_add0_assert_dump(output, l._type, l._min);
// 		ref = strToLD(l._min, l._type);
// 		dumped = strToLD(output.str(), l._type);
// 		BOOST_CHECK(ref == dumped);

// 		push_add0_assert_dump(output, l._type, l._lowest);
// 		ref = strToLD(l._lowest, l._type);
// 		dumped = strToLD(output.str(), l._type);
// 		BOOST_CHECK(ref == dumped);
// 	}
// }

typedef boost::mpl::list<int8_t, int16_t, int32_t, float, double> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(max, T, test_types)
{
	T const ref_val = std::numeric_limits<T>::max();
	boost::test_tools::output_test_stream output;
	long double const ref_valld = ref_val;
	long double dumped_valld;
	std::string const ref_valstr = [ref_val](){

		std::stringstream iss;

		iss << std::fixed << std::noshowpos << std::setprecision(1);
		nbrToStream(ref_val, iss);
		return iss.str();
	}();
	push_add0_assert_dump<T>(output, ref_valstr);
	dumped_valld = strToLD<T>(output.str());
	BOOST_CHECK(ref_valld != dumped_valld);
}
