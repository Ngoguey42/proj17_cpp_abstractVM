// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/28 13:52:34 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 14:12:27 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

// initialization function:
bool init_unit_test()
{
	return true;
}

// entry point:
int main(int argc, char* argv[])
{
	return boost::unit_test::unit_test_main(&init_unit_test, argc, argv);
}
