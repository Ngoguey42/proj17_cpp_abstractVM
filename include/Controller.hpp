// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Controller.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/26 15:56:17 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/26 16:06:33 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONTROLLER_HPP
# define CONTROLLER_HPP

// # include <iostream>
# include <string>
# include <queue>

// # include ""

class Controller
{
public:

	/* CONSTRUCTION ***************** */
	Controller();
	// virtual ~Controller();
	~Controller();

	// Controller() = delete;
	Controller(Controller const &src) = delete;
	Controller(Controller &&src) = delete;
	Controller				&operator=(Controller const &rhs) = delete;
	Controller				&operator=(Controller &&rhs) = delete;

	int operator () (int ac, char const *av[]);

protected:


private:
	int _ac;
	char const **_av;

	void _run();
	auto _readSource() -> std::queue<std::string>;

};
//std::ostream			&operator<<(std::ostream &o, Controller const &rhs);

#endif /* **************************************************** CONTROLLER_HPP */
