// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   boost_test_1.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 20:06:12 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 18:58:18 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;
using boost::test_tools::output_test_stream;

#define CYEL std::string("\033[33m")
#define CEND std::string("\033[0m")

#include <deque>

#include "testTools.hpp"
#include "Controller.hpp"

struct Fix {
	Fix() {
	}
	~Fix() {
	}

	boost::test_tools::output_test_stream fx_output;
	long double fx_ref_valld;
	std::string fx_ref_valstr;

	template <class T>
	void fx_run(void) {
		std::stringstream oss;
		std::string const valstr = std::string(TypeToString<T>::name)
			+ "(" + fx_ref_valstr + ")";
		BOOST_TEST_MESSAGE(CYEL + "push_add0_assert_dump over "
						   + truncate(valstr) + CEND);
		cout_redirect guardout(fx_output.rdbuf());
		cin_redirect guardin(oss.rdbuf());

		fx_output.str(""); //reset output stream

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
	template <class T>
	void fx_validate(void) {

		long double dumped_valld;

		dumped_valld = strToLD<T>(fx_output.str());
		BOOST_CHECK(fx_ref_valld == dumped_valld);
		return ;
	}

};

typedef boost::mpl::list<int8_t, int16_t, int32_t, float, double> test_types;

BOOST_FIXTURE_TEST_SUITE(s, Fix)

BOOST_AUTO_TEST_CASE_TEMPLATE(max, T, test_types)
{
	T const ref_val = std::numeric_limits<T>::max();

	fx_ref_valld = static_cast<long double>(ref_val);
	fx_ref_valstr = [ref_val](){
		std::stringstream iss;

		iss << std::fixed << std::noshowpos << std::setprecision(1);
		nbrToStream(ref_val, iss);
		return iss.str();
	}();
	fx_run<T>();
	fx_validate<T>();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(min, T, test_types)
{
	T const ref_val = std::numeric_limits<T>::denorm_min();

	fx_ref_valld = static_cast<long double>(ref_val);
	fx_ref_valstr = [ref_val](){
		std::stringstream iss;
		int tmp;

		tmp = -floor(log10(std::abs(std::numeric_limits<T>::denorm_min())));
		tmp += std::numeric_limits<T>::max_digits10 - 1;
		iss << std::fixed << std::noshowpos << std::setprecision(tmp);
		nbrToStream(ref_val, iss);
		return iss.str();
	}();
	fx_run<T>();
	fx_validate<T>();
}

BOOST_AUTO_TEST_CASE_TEMPLATE(lowest, T, test_types)
{
	T const ref_val = std::numeric_limits<T>::lowest();

	fx_ref_valld = static_cast<long double>(ref_val);
	fx_ref_valstr = [ref_val](){
		std::stringstream iss;

		iss << std::fixed << std::noshowpos << std::setprecision(1);
		nbrToStream(ref_val, iss);
		return iss.str();
	}();
	fx_run<T>();
	fx_validate<T>();
}

BOOST_AUTO_TEST_SUITE_END()
