// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   testConf.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 19:34:12 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 17:10:18 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TESTCONF_HPP
# define TESTCONF_HPP

# include <regex>
# include "Controller.hpp"

#define RUN_ABSTRACT_VM							\
	Controller()(1, nullptr)

#define ERROROCCURED(OUTPUT)							\
	std::regex_search((OUTPUT), std::regex("ERROR"))

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

#define NOINSTR(OUTPUT)											\
	std::regex_search((OUTPUT), std::regex("No intructions"))

#define NOEXIT(OUTPUT)                                                  \
	std::regex_search((OUTPUT), std::regex("Missing exit statement"))

#define PARSEERROR(OUTPUT)										\
	std::regex_search((OUTPUT), std::regex("not in language"))


#endif /* ****************************************************** TESTCONF_HPP */
