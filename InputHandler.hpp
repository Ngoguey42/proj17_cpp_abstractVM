// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   InputHandler.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 12:24:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 15:41:49 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef INPUTHANDLER_HPP
# define INPUTHANDLER_HPP

# include <istream>
# include <string>
# include <queue>

class InputHandler
{
public:

	/* CONSTRUCTION ***************** */
	InputHandler(std::istream &stream, bool fd0) noexcept;
	~InputHandler();

	std::queue<std::string>		handle() noexcept;

	InputHandler() = delete;
	InputHandler(InputHandler const &src) = delete;
	InputHandler(InputHandler &&src) = delete;
	InputHandler			&operator=(InputHandler const &rhs) = delete;
	InputHandler			&operator=(InputHandler &&rhs) = delete;

private:

	void		extractLine(void);
	void		handleCommas(void);
	void		storeLine(void);
	bool		endOfInput(void);

	std::istream				&_is;
	bool						_fd0;
	std::queue<std::string>		_q;
	std::string					_line;

};

#endif /* ************************************************** INPUTHANDLER_HPP */
