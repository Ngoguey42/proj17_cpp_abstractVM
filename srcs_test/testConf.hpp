// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   testConf.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 19:34:12 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 19:44:17 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TESTCONF_HPP
# define TESTCONF_HPP

# include <regex>

#define RUN_ABSTRACT_VM							\
	Controller()(1, nullptr)

#define UNDERFLOWED(OUTPUT)								\
	std::regex_search((OUTPUT), std::regex("underflow_error"))

#define OVERFLOWED(OUTPUT)								\
	std::regex_search((OUTPUT), std::regex("overflow_error"))

#endif /* ****************************************************** TESTCONF_HPP */
