// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   InputHandler.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 12:24:05 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/26 16:42:54 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef INPUTHANDLER_HPP
# define INPUTHANDLER_HPP

# include <istream>
# include <string>
# include <deque>

// Constructor() takes istream informations
// handle() - ouputs a deque of strings read from stream
//			- does not close the stream
//			- may throw std::runtime_error

class InputHandler
{
public:

	/* CONSTRUCTION ***************** */
	InputHandler(std::istream &stream, bool fd0);
	~InputHandler();

	InputHandler() = delete;
	InputHandler(InputHandler const &src) = delete;
	InputHandler(InputHandler &&src) = delete;
	InputHandler	&operator=(InputHandler const &rhs) = delete;
	InputHandler	&operator=(InputHandler &&rhs) = delete;

	auto			handle(void)
		-> std::deque<std::string>;

private:

	/* INTERNAL ********************* */
	void			extractLine(void);
	void			handleCommas(void);
	void			storeLine(void);
	bool			endOfInput(void);

	/* ATTRIBUTES ******************* */
	std::istream				&_is;
	bool						_fd0;
	std::deque<std::string>	_q;
	std::string					_line;

};

#endif /* ************************************************** INPUTHANDLER_HPP */
