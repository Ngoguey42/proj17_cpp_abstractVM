// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   limitsTests.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 12:16:07 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 15:19:45 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "limitsFixture.hpp"

#include <boost/mpl/list.hpp>

typedef boost::mpl::list<int8_t, int16_t, int32_t, float, double> all_types;
typedef boost::mpl::list<float, double> fp_types;
typedef boost::mpl::list<int8_t, int16_t, int32_t> i_types;

BOOST_FIXTURE_TEST_SUITE(s, LFixture)

BOOST_AUTO_TEST_CASE_TEMPLATE(max, T, all_types)
{
	fx_init<T>(std::numeric_limits<T>::max());
	fx_run_paad<T>();
	fx_validate_ok<T>();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(min, T, all_types)
{
	fx_init<T>(std::numeric_limits<T>::denorm_min());
	fx_run_paad<T>();
	fx_validate_ok<T>();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(lowest, T, all_types)
{
	fx_init<T>(std::numeric_limits<T>::lowest());
	fx_run_paad<T>();
	fx_validate_ok<T>();
}


BOOST_AUTO_TEST_CASE_TEMPLATE(min_overflow, T, fp_types)
{
	fx_init<T>(std::numeric_limits<T>::denorm_min());
	fx_run_oneover<T>();
	fx_validate_overflow<T>();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(max_overflow, T, all_types)
{
	fx_init<T>(std::numeric_limits<T>::max());
	fx_run_selfmult<T>();
	fx_validate_overflow<T>();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(lowest_overflow, T, all_types)
{
	fx_init<T>(std::numeric_limits<T>::lowest());
	fx_run_selfmult<T>();
	fx_validate_overflow<T>();
}


BOOST_AUTO_TEST_CASE_TEMPLATE(min_underflow, T, fp_types)
{
	fx_init<T>(std::numeric_limits<T>::denorm_min());
	fx_run_selfmult<T>();
	fx_validate_underflow<T>();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(max_underflow, T, fp_types)
{
	fx_init<T>(std::numeric_limits<T>::max());
	fx_run_oneover<T>();
	fx_validate_underflow<T>();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(lowest_underflow, T, fp_types)
{
	fx_init<T>(std::numeric_limits<T>::lowest());
	fx_run_oneover<T>();
	fx_validate_underflow<T>();
}

BOOST_AUTO_TEST_SUITE_END()
