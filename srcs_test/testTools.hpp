// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   testTools.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 17:18:52 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 17:18:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TESTTOOLS_HPP
# define TESTTOOLS_HPP


// fichier <- stream << data        ofstream
// fichier -> stream >> data        ifstream

// STREAM REDIRECTIONS
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

struct cin_redirect {
	cin_redirect(std::streambuf *new_buffer)
		: old(std::cin.rdbuf(new_buffer)) {
	}

	~cin_redirect() {
		std::cin.rdbuf(old);
	}

private:
	std::streambuf *old;
};

// string to number in long double
long double strToLD(std::string const &str, std::string const &type)
{
	std::stringstream iss(str);
	long double ld;
	double d;
	float f;

	if (type == "float")
	{
		iss >> f;
		ld = f;
	}
	else if (type == "double")
	{
		iss >> d;
		ld = d;
	}
	else
		iss >> ld;
	return ld;
}

// T number to stream
template <class T>
void nbrToStream(T const &val, std::stringstream &iss)
{
	iss << val;
	return ;
}

template <>
inline void nbrToStream<int8_t>(int8_t const &val, std::stringstream &oss)
{
	oss << int(val);
	return ;
}

#endif /* ***************************************************** TESTTOOLS_HPP */
