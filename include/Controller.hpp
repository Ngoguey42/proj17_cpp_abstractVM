// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Controller.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/26 15:56:17 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 16:20:38 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

# include <string>
# include <deque>

class Controller
{
public:

	/* CONSTRUCTION ***************** */
	Controller();
	~Controller();

	Controller(Controller const &src) = delete;
	Controller(Controller &&src) = delete;
	Controller				&operator=(Controller const &rhs) = delete;
	Controller				&operator=(Controller &&rhs) = delete;

	int operator () (int ac, char const *av[]);

private:
	int _ac;
	char const **_av;

	void _run();
	auto _readSource() -> std::deque<std::string>;
	void _validateInstructions(std::deque<std::string> const &);
	auto _sepInstrArg(std::string const &)
		-> std::pair<std::string, std::string>;

};

#endif /* **************************************************** CONTROLLER_HPP */
