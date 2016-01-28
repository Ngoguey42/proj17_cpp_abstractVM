// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   limitsFixture.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 13:17:05 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 16:11:19 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LIMITSFIXTURE_HPP
# define LIMITSFIXTURE_HPP

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;

struct LFixture {
	LFixture();
	~LFixture();
	LFixture(LFixture const &src) = delete;
	LFixture(LFixture &&src) = delete;
	LFixture &operator=(LFixture const &rhs) = delete;
	LFixture &operator=(LFixture &&rhs) = delete;

	boost::test_tools::output_test_stream fx_output;
	std::stringstream fx_oss_cin;
	long double fx_ref_valld;
	std::string fx_ref_valstr;
	std::string fx_ref_valtypestr;
	bool fx_isfloat;
	bool (LFixture::*fx_pred)(void);

	template <class T>
	void fx_init(T const &val);

	template <class T>
	void fx_run_paad(void);

	template <class T>
	void fx_run_selfmult(void);

	template <class T>
	void fx_run_oneover(void);

	template <class T>
	bool fx_validate_ok(void);
	bool fx_validate_underflow(void);
	bool fx_validate_overflow(void);

	void _fx_exec1(void);
	void _fx_exec2(void);

};

#endif /* ************************************************* LIMITSFIXTURE_HPP */
