// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   testTools.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 17:18:52 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/28 16:14:26 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TESTTOOLS_HPP
# define TESTTOOLS_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

#define TAB std::string("    ")
#define CYEL std::string("\033[33m")
#define CCYA std::string("\033[36m")
#define CRED std::string("\033[31m")
#define CEND std::string("\033[0m")

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

template <class T>
long double strToLD(std::string const &str)
{
	std::stringstream iss(str);
	T val;

	iss >> val;
	return static_cast<long double>(val);
}

template <>
inline long double strToLD<int8_t>(std::string const &str)
{
	std::stringstream iss(str);
	int16_t val;

	iss >> val;
	return static_cast<long double>(val);
}

// T to string
template <class T>  struct TypeToString;

template <>         struct TypeToString<int8_t> {
	static constexpr char const *name = "int8";
};
template <>         struct TypeToString<int16_t> {
	static constexpr char const *name = "int16";
};
template <>         struct TypeToString<int32_t> {
	static constexpr char const *name = "int32";
};
template <>         struct TypeToString<float> {
	static constexpr char const *name = "float";
};
template <>         struct TypeToString<double> {
	static constexpr char const *name = "double";
};

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

template <class T>
std::string nbrToString(T const &val) {

	std::stringstream iss;
	float const log10res = log10(std::abs(val));
	int tmp;

	tmp = std::numeric_limits<T>::max_digits10;
	if (log10res < 0)
	{
		tmp += -floor(log10res) - 1;
		iss << std::fixed << std::noshowpos << std::setprecision(tmp);
		nbrToStream(val, iss);
	}
	else
	{
		iss << std::fixed << std::noshowpos << std::setprecision(tmp);
		nbrToStream(val, iss);
	}
	return iss.str();
}

// Truncate string
// inline std::string truncate(std::string const &src, size_t len = 50)
// {
// 	auto const srclen = src.size();
// 	auto const halflen = len / 2;
// 	std::stringstream iss;

// 	if (srclen <= len)
// 		return src;
// 	iss << "[ " << (srclen - halflen * 2) << "chars ]";
// 	return src.substr(0, halflen) + iss.str()
// 		+ src.substr(srclen - halflen, halflen);
// }

//Kill last EOL
inline std::string killTrailingEOL(std::string const &str) {

	auto where = str.find_last_not_of(" \t\n");

	if (where != std::string::npos)
		return str.substr(0, where + 1);
	return str;
}

//Format a string stream for output
template <class T, class = decltype( ((T*)(0x0))->str() )>
std::string ssFormat(T const &ss, std::string const &color) {

	return color + killTrailingEOL(ss.str()) + CEND;
}

#endif /* ***************************************************** TESTTOOLS_HPP */
