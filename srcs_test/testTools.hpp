// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   testTools.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 17:18:52 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 18:10:54 by ngoguey          ###   ########.fr       //
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
// long double strToLD(std::string const &str, std::string const &type)
// {
// 	std::stringstream iss(str);
// 	long double ld;
// 	double d;
// 	float f;

// 	if (type == "float")
// 	{
// 		iss >> f;
// 		ld = f;
// 	}
// 	else if (type == "double")
// 	{
// 		iss >> d;
// 		ld = d;
// 	}
// 	else
// 		iss >> ld;
// 	return ld;
// }

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

// Truncate string
inline std::string truncate(std::string const &src, size_t len = 30)
{
	auto const srclen = src.size();
	auto const halflen = len / 2;

	if (srclen <= len)
		return src;
	return src.substr(0, halflen) + "[...]"
		+ src.substr(srclen - halflen, halflen);
}

#endif /* ***************************************************** TESTTOOLS_HPP */
