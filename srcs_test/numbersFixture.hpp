// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   numbersFixture.hpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 17:24:38 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 18:06:57 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef NUMBERSFIXTURE_HPP
# define NUMBERSFIXTURE_HPP

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include "testConf.hpp"
#include "testTools.hpp"

class NFixture
{
public:

	boost::test_tools::output_test_stream fx_output;
	std::stringstream fx_oss_cin;
	long double fx_ref_valld;

	/* CONSTRUCTION ***************** */
	NFixture();
	~NFixture();

	NFixture(NFixture const &src) = delete;
	NFixture(NFixture &&src) = delete;
	NFixture		&operator=(NFixture const &rhs) = delete;
	NFixture		&operator=(NFixture &&rhs) = delete;

	void fx_exec(std::function< bool(std::string const&) > pred);

	template <class T>
	bool fx_validate_ok(void);

private:

	void _fx_exec(void);

};

#endif /* ************************************************ NUMBERSFIXTURE_HPP */
