// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   stackLogicFixture.hpp                              :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 15:06:34 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 16:00:36 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef STACKLOGICFIXTURE_HPP
# define STACKLOGICFIXTURE_HPP

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include "testConf.hpp"
#include "testTools.hpp"

class SLFixture
{
public:

	boost::test_tools::output_test_stream fx_output;
	std::stringstream fx_oss_cin;

	/* CONSTRUCTION ***************** */
	SLFixture();
	~SLFixture();

	SLFixture(SLFixture const &src) = delete;
	SLFixture(SLFixture &&src) = delete;
	SLFixture		&operator=(SLFixture const &rhs) = delete;
	SLFixture		&operator=(SLFixture &&rhs) = delete;

	void fx_exec(std::function< bool(std::string const&) > pred);

private:

	void _fx_exec(void);

};

#endif /* ********************************************* STACKLOGICFIXTURE_HPP */
