// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   testConf.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 19:34:12 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 15:45:37 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TESTCONF_HPP
# define TESTCONF_HPP

# include <regex>
# include "Controller.hpp"

#define RUN_ABSTRACT_VM							\
	Controller()(1, nullptr)

#define UNDERFLOWED(OUTPUT)										\
	std::regex_search((OUTPUT), std::regex("underflow_error"))

#define OVERFLOWED(OUTPUT)										\
	std::regex_search((OUTPUT), std::regex("overflow_error"))

#define STACKSIZELOW(OUTPUT)										\
	std::regex_search((OUTPUT), std::regex("Stack size too low"))

#define ASSERTNOMATCH(OUTPUT)											\
	std::regex_search((OUTPUT), std::regex("does not match given value"))

#define PRINTBADTYPE(OUTPUT)											\
	std::regex_search((OUTPUT), std::regex("as an ascii character"))

// #define PRINT_OUTPUT(STREAM)							\
// 	BOOST_TEST_MESSAGE(std::string("Output:") + CCYA	\
// 					   + killTrailingEOL((STREAM).str()) + CEND)

#define PRINT_OUTPUT(STREAM)

#endif /* ****************************************************** TESTCONF_HPP */
