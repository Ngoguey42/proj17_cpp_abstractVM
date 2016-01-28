// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   numbersTests.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 17:24:22 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 17:25:29 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "numbersFixture.hpp"

#include <boost/mpl/list.hpp>

typedef boost::mpl::list<int8_t, int16_t, int32_t, float, double> all_types;
typedef boost::mpl::list<float, double> fp_types;
typedef boost::mpl::list<int8_t, int16_t, int32_t> i_types;

BOOST_FIXTURE_TEST_SUITE(numbers, NFixture)

BOOST_AUTO_TEST_CASE_TEMPLATE(tmp, T, fp_types)
{
	int const bound = std::numeric_limits<T>::max_digits10 + 2;

	auto makeNbr = [](int i){

		return nbrToString<T>(std::pow(10.L, static_cast<long double>(i)));
	};

	for (int i = bound; i >= -bound; i--)
		fx_oss_cin << "push " << TypeToString<T>::name << "(" << makeNbr(i) << ")\n";
	fx_oss_cin << "dump\n";
	for (int i = -bound; i <= bound; i++)
	{
		fx_oss_cin << "assert " << TypeToString<T>::name << "(" << makeNbr(i) << ")\n";
		fx_oss_cin << "pop\n";
	}
	fx_oss_cin << "exit\n";
	fx_oss_cin << ";;\n";
	fx_exec([](std::string const &str){return !ERROROCCURED(str);});
}

BOOST_AUTO_TEST_SUITE_END()
