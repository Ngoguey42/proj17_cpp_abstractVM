// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   InputHandler.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 12:24:05 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 17:33:22 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef INPUTHANDLER_HPP
# define INPUTHANDLER_HPP

# include <istream>
# include <string>
# include <queue>

// Ouputs a queue of strings, ready for the grammar given in subject

class InputHandler
{
public:

	/* CONSTRUCTION ***************** */
	InputHandler(std::istream &stream, bool fd0) noexcept;
	~InputHandler();

	InputHandler() = delete;
	InputHandler(InputHandler const &src) = delete;
	InputHandler(InputHandler &&src) = delete;
	InputHandler	&operator=(InputHandler const &rhs) = delete;
	InputHandler	&operator=(InputHandler &&rhs) = delete;

	auto			handle() noexcept
		-> std::queue<std::string>;

private:

	/* INTERNAL ********************* */
	void			extractLine(void);
	void			handleCommas(void);
	void			storeLine(void);
	bool			endOfInput(void);

	/* ATTRIBUTES ******************* */
	std::istream				&_is;
	bool						_fd0;
	std::queue<std::string>		_q;
	std::string					_line;

};

#endif /* ************************************************** INPUTHANDLER_HPP */
