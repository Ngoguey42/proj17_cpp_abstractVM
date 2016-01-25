// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   boost_test_1.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/25 20:06:12 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/25 20:28:48 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
using boost::test_tools::output_test_stream;

struct cout_redirect {
	cout_redirect(std::streambuf *new_buffer)
		: old(std::cout.rdbuf(new_buffer)) {
	}

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf *old;
};

BOOST_AUTO_TEST_CASE( test1 )
{
	boost::test_tools::output_test_stream output;

	{
		cout_redirect guard( output.rdbuf( ) );

		std::cout << "Bordel" << std::endl;
	}

	BOOST_CHECK( output.is_equal( "Bordel\n" ) );
	// BOOST_CHECK( output.is_equal( "Bordel" ) );
}



// BOOST_AUTO_TEST_CASE( test )
// {
// output_test_stream output;
// int i=2;
// bordel();
// output << "i=" << i;
// BOOST_CHECK( !output.is_empty( false ) );
// BOOST_CHECK( output.check_length( 3, false ) );
// BOOST_CHECK( output.is_equal( "i=3" ) );
// return ;
// }

// int							main(void)
// {

// 	return (0);
// }
