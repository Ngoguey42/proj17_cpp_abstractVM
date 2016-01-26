// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Controller.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/26 15:57:21 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/26 17:35:10 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>
#include <iostream>

#include "VMStack.hpp"
#include "Controller.hpp"
#include "InputHandler.hpp"
#include "cfg_checker.hpp"

Controller::Controller()
{}

Controller::~Controller()
{}

int Controller::operator () (int ac, char const *av[])
{
	_ac = ac;
	_av = av;
	try
	{
		_run();
		return 0;
	}
	catch (std::invalid_argument const &e)
	{
		std::cout << "ERROR, invalid_argument:" << std::endl;
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "ERROR, unknown error" << std::endl;
	}
	return 1;
}


void Controller::_run()
{
	std::deque<std::string> instrQ{_readSource()};
	std::string instr;
	std::string arg1;
	OpFactory fact;
	VMStack vms(fact);

	_validateInstructions(instrQ);
	while (!instrQ.empty())
	{
		// instr = std::move(instrQ.front());
		std::tie(instr, arg1) = _sepInstrArg(std::move(instrQ.front()));
		if (arg1.size() > 0)
			std::cout << "\"" << instr << " "<< arg1 << "\"" << std::endl;
		else
			std::cout << "\"" << instr << '"' << std::endl;
		instrQ.pop_front();
		VMStack::actmap.at(instr)(&vms, arg1);
	}
	return ;
}

auto Controller::_readSource()
	-> std::deque<std::string>
{
	std::ifstream f;

	if (_ac == 1)
		return InputHandler(std::cin, true).handle();
	else if (_ac == 2)
	{
		f.open(_av[1], std::ios_base::in);
		if (!f.good())
			throw std::invalid_argument(
				std::string("Can't open file \"") + _av[1] + '"');
		return InputHandler(f, false).handle();
	}
	else
		throw std::invalid_argument("Wrong number of arguments to program");
}

void Controller::_validateInstructions(std::deque<std::string> const &q)
{
	for (std::string const &str : q)
		if (!cfg::string_in_language(str))
			throw std::invalid_argument(
				std::string("\"") + str + '"' + " not in language");
	return ;
}

auto Controller::_sepInstrArg(std::string &&in)
	-> std::pair<std::string, std::string>
{
	std::string tmp(in);
	size_t const bInst = tmp.find_first_not_of(" \t");
	size_t const eInst = tmp.find_first_of(" \t", bInst);
	std::string inst = tmp.substr(bInst, eInst - bInst);
	size_t bArg1;
	size_t eArg1;
	std::string arg1;

	if (eInst != std::string::npos)
	{
		bArg1 = tmp.find_first_not_of(" \t", eInst);
		if (bArg1 != std::string::npos)
		{
			eArg1 = tmp.find_first_of(" \t", bArg1);
			arg1 = tmp.substr(bArg1, eArg1 - bArg1);
		}
	}
	return {std::move(inst), std::move(arg1)};
}
