// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   cfg_checker.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/26 14:23:16 by ngoguey           #+#    #+#             //
//   Updated: 2016/03/12 16:08:47 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream> //debug
#include <regex> //debug

// TODO: constexpr regex construction (+ compilation?)

namespace cfg // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //


static char const *n{"[-]?[0-9]+"};
static char const *z{"[-]?[0-9]+[.][0-9]+"};
static char const *blank_star{"[ \t]*"};
static char const *blank_plus{"[ \t]+"};
static char const *termN[] = {
	"int8", "int16", "int32"
};
static char const *termZ[] = {
	"float", "double"
};
static char const *terma[] = {
	"pop", "dump", "add", "sub", "mul", "div", "mod", "print", "exit"
};
static char const *termb[] = {
	"push", "assert"
};

static std::string make_value(void)
{
	std::string ret;

	ret += "(";
	for (char const *term : termN)
	{
		if (term == *termN)
			ret += "(";
		else
			ret += "|(";
		ret += term;
		ret += "[(]";
		ret += n;
		ret += "[)]";
		ret += ")";
	}
	for (char const *term : termZ)
	{
		ret += "|(";
		ret += term;
		ret += "[(]";
		ret += z;
		ret += "[)]";
		ret += ")";
	}
	ret += ")";
	return ret;
}

static std::string make_instr(void)
{
	std::string const value{make_value()};
	std::string ret;

	ret += blank_star;
	ret += "(";
	for (char const *term : terma)
	{
		if (term == *terma)
			ret += "(";
		else
			ret += "|(";
		ret += term;
		ret += ")";
	}
	for (char const *term : termb)
	{
		ret += "|(";
		ret += term;
		ret += blank_plus;
		ret += value;
		ret += ")";
	}
	ret += ")";
	ret += blank_star;
	return ret;
}

static std::regex const re{make_instr()};

bool string_in_language(std::string const &str)
{
	return std::regex_match(str, re);
}

}; // ~~~~~~~~~~~~~~~~~~~~ END OF NAMESPACE CFG //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
