// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   numbersTests.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 17:24:22 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 18:40:04 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "numbersFixture.hpp"

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

namespace bdata = boost::unit_test::data;

// #include <boost/mpl/list.hpp>

// typedef boost::mpl::list<int8_t, int16_t, int32_t, float, double> all_types;
// typedef boost::mpl::list<float, double> fp_types;
// typedef boost::mpl::list<int8_t, int16_t, int32_t> i_types;


// BOOST_AUTO_TEST_SUITE(numbers)
BOOST_FIXTURE_TEST_SUITE(numbers, NFixture)

BOOST_DATA_TEST_CASE(int8_all, bdata::xrange<int16_t>(
					 	 (bdata::begin=-128, bdata::end=127, bdata::step=1)))
{
	NFixture f{};

	f.fx_ref_valld = sample;
	f.fx_oss_cin << "push int8(" << nbrToString<int8_t>(sample) << ")\n";
	f.fx_oss_cin << "dump\n";
	f.fx_oss_cin << "assert int8(" << nbrToString<int8_t>(sample) << ")\n";
	f.fx_oss_cin << "print\n";
	f.fx_oss_cin << "exit\n";
	f.fx_oss_cin << ";;\n";
	if (sample >= 0)
		f.fx_exec([&f](std::string const &) {
				return f.fx_validate_ok<int8_t>();});
	else
		f.fx_exec([&f](std::string const &) {
				return f.fx_validate_ok<int8_t>()
					&& PRINTBADTYPE(f.fx_output.str());});
}


// BOOST_AUTO_TEST_CASE_TEMPLATE(tmp, T, fp_types)
// {
// 	int const bound = std::numeric_limits<T>::max_digits10 + 2;

// 	auto makeNbr = [](int i){

// 		return nbrToString<T>(std::pow(10.L, static_cast<long double>(i)));
// 	};

// 	for (int i = bound; i >= -bound; i--)
// 		fx_oss_cin << "push " << TypeToString<T>::name << "(" << makeNbr(i) << ")\n";
// 	fx_oss_cin << "dump\n";
// 	for (int i = -bound; i <= bound; i++)
// 	{
// 		fx_oss_cin << "assert " << TypeToString<T>::name << "(" << makeNbr(i) << ")\n";
// 		fx_oss_cin << "pop\n";
// 	}
// 	fx_oss_cin << "exit\n";
// 	fx_oss_cin << ";;\n";
// 	fx_exec([](std::string const &str){return !ERROROCCURED(str);});
// }



BOOST_AUTO_TEST_SUITE_END()
