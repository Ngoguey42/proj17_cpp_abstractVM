// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   InputHandler.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 12:19:29 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 15:41:35 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "InputHandler.hpp"

using IH = InputHandler;

IH::InputHandler(std::istream &stream, bool fd0) noexcept
	: _is(stream), _fd0(fd0), _q(), _line()
{}

IH::~InputHandler() {}

void	IH::extractLine(void)
{
	_is.clear();
	std::getline(_is, _line);
	return ;
}

void	IH::handleCommas(void)
{
	size_t const	commaPos = _line.find(';');

	if (commaPos != std::string::npos)
	{
		if (_fd0 && _line.find(";;") == commaPos)
			_is.setstate(std::ios_base::eofbit);
		_line.resize(commaPos);
	}
	return ;
}

void	IH::storeLine(void)
{
	if (_line.find_first_not_of(" \t") != std::string::npos)
		_q.emplace(std::move(_line));
	return ;
}

bool	IH::endOfInput(void)
{
	return !_is.good();
}

auto	IH::handle(void) noexcept
	-> std::queue<std::string>
{
	do {
		extractLine();
		handleCommas();
		storeLine();
	} while (!endOfInput());
	return _q;
}
