// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   boost_test_1.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 20:06:12 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 20:27:42 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;
using boost::test_tools::output_test_stream;

#include <deque>
#include <type_traits>

#include "testConf.hpp"
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
	std::string fx_ref_valtypestr;
	bool fx_isfloat;

	template <class T>
	void fx_init(T const &val) {

		fx_ref_valld = static_cast<long double>(val);
		fx_ref_valstr = nbrToString(val);
		fx_ref_valtypestr = std::string(TypeToString<T>::name)
			+ "(" + fx_ref_valstr + ")";
		fx_isfloat = std::is_floating_point<T>::value;
		BOOST_TEST_MESSAGE(CYEL + "preparing some test with "
						   + truncate(fx_ref_valtypestr) + CEND);
		return ;
	}

	template <class T>
	void fx_run_paad(void) { // paad Push Add0 Assert Dump

		BOOST_TEST_MESSAGE(
			TAB + CYEL + "val+0+assert+dump operations" + CEND);

		std::stringstream oss;
		cout_redirect guardout(fx_output.rdbuf());
		cin_redirect guardin(oss.rdbuf());

		oss << "push ";
		oss << fx_ref_valtypestr;
		oss << "\n";

		oss << "push int8(0)\n";
		oss << "add\n";

		oss << "assert ";
		oss << fx_ref_valtypestr;
		oss << "\n";

		oss << "dump\n";
		oss << "exit\n";
		oss << ";;";
		RUN_ABSTRACT_VM;
		return ;
	}

	template <class T>
	void fx_run_selfmult(void) {

		BOOST_TEST_MESSAGE(TAB + CYEL + "val*val operations" + CEND);

		std::stringstream oss;
		cout_redirect guardout(fx_output.rdbuf());
		cin_redirect guardin(oss.rdbuf());

		oss << "push ";
		oss << fx_ref_valtypestr;
		oss << "\n";

		oss << "push ";
		oss << fx_ref_valtypestr;
		oss << "\n";

		oss << "mul\n";

		oss << "exit\n";
		oss << ";;";
		RUN_ABSTRACT_VM;
		return ;
	}

	template <class T>
	void fx_run_oneover(void) {

		BOOST_TEST_MESSAGE(TAB + CYEL + "1/val operations" + CEND);

		std::stringstream oss;
		cout_redirect guardout(fx_output.rdbuf());
		cin_redirect guardin(oss.rdbuf());

		oss << "push int8(1)\n";

		oss << "push ";
		oss << fx_ref_valtypestr;
		oss << "\n";

		oss << "div\n";

		oss << "exit\n";
		oss << ";;";
		RUN_ABSTRACT_VM;
		return ;
	}

	template <class T>
	void fx_validate_ok(void) {

		long double dumped_valld;

		dumped_valld = strToLD<T>(fx_output.str());
		PRINT_OUTPUT(fx_output);
		BOOST_CHECK_EQUAL(fx_ref_valld, dumped_valld);
		return ;
	}

	template <class T>
	void fx_validate_underflow(void) {

		PRINT_OUTPUT(fx_output);
		BOOST_CHECK(UNDERFLOWED(fx_output.str()));
		return ;
	}

	template <class T>
	void fx_validate_overflow(void) {

		PRINT_OUTPUT(fx_output);
		BOOST_CHECK_MESSAGE(OVERFLOWED(fx_output.str())
							, CRED + fx_output.str() + CEND);
		return ;
	}
};

typedef boost::mpl::list<int8_t, int16_t, int32_t, float, double> all_types;
typedef boost::mpl::list<float, double> fp_types;
typedef boost::mpl::list<int8_t, int16_t, int32_t> i_types;

BOOST_FIXTURE_TEST_SUITE(s, Fix)

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

BOOST_AUTO_TEST_SUITE_END()
