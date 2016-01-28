// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   limitsFixture.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 13:17:05 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 15:19:35 by ngoguey          ###   ########.fr       //
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
	long double fx_ref_valld;
	std::string fx_ref_valstr;
	std::string fx_ref_valtypestr;
	bool fx_isfloat;

	template <class T>
	void fx_init(T const &val);

	template <class T>
	void fx_run_paad(void);

	template <class T>
	void fx_run_selfmult(void);

	template <class T>
	void fx_run_oneover(void);

	template <class T>
	void fx_validate_ok(void);

	template <class T>
	void fx_validate_underflow(void);

	template <class T>
	void fx_validate_overflow(void);

};

#endif /* ************************************************* LIMITSFIXTURE_HPP */
