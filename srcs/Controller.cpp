// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Controller.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/26 15:57:21 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/26 16:11:02 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <fstream>
#include <iostream>

#include "Controller.hpp"
#include "InputHandler.hpp"

Controller::Controller()
{

}

Controller::~Controller()
{

}




int Controller::operator () (int ac, char const *av[])
{
	_ac = ac;
	_av = av;
	try
	{
		_run();
		return 0;
	}
	catch (...)
	{

	}


	return 0;
}


void Controller::_run()
{
	std::queue<std::string> const instr{_readSource()};

	return ;
}

auto Controller::_readSource()
	-> std::queue<std::string>
{
	std::ifstream f;

	if (_ac == 1)
		return InputHandler(std::cin, true).handle();
	else if (_ac == 2)
	{
		f.open(_av[1], std::ios_base::in);
		if (!f.good())
			; //TODO: throw
		return InputHandler(f, false).handle();
	}
	else
		; //TODO: throw
}
