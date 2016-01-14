// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   InputHandler.cpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 12:19:29 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/14 15:44:41 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "InputHandler.hpp"

using IH = InputHandler;

IH::InputHandler(std::istream &stream, bool fd0)
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
	_q.emplace(std::move(_line));
	return ;
}

bool	IH::endOfInput(void)
{
	return !_is.good();
}

auto	IH::handle(void)
	-> std::queue<std::string>
{
	while (!endOfInput())
	{
		extractLine();
		handleCommas();
		storeLine();
	}
	if (_is.bad())
		throw std::runtime_error("I/O error while reading");
	else if (!_is.eof())
		throw std::runtime_error("Line read too long");
	return _q;
}
