// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MStack.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 11:29:14 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 11:47:36 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MSTACK_HPP
# define MSTACK_HPP

#include <stack>
#include <iterator>

/*
** MStack (Mutant Stack) is an iterable stack.
*/

template<typename T>
class MStack: public std::stack<T>
{
public:

	/* CONSTRUCTION ***************** */
	MStack() : std::stack<T>() {}
	virtual ~MStack() {}

	MStack(MStack const &src) : std::stack<T>(src) {}
	MStack(MStack &&src) : std::stack<T>(src) {}
	MStack					&operator=(MStack const &rhs) {
		std::stack<T>::operator=(rhs);
		return (*this);
	}
	MStack					&operator=(MStack &&rhs) {
		std::stack<T>::operator=(rhs);
		return (*this);
	}

	/* ITERATION ******************** */
	using deep_container = typename std::stack<T>::container_type;

	using iterator = typename deep_container::reverse_iterator;
	using const_iterator = typename deep_container::const_reverse_iterator;
	using reverse_iterator = typename deep_container::iterator;
	using const_reverse_iterator = typename deep_container::const_iterator;
	iterator				begin(void) {
		return (this->c.rbegin());
	};
	iterator				end(void) {
		return (this->c.rend());
	};
	const_iterator			begin(void) const {
		return (this->c.crbegin());
	};
	const_iterator			end(void) const {
		return (this->c.crend());
	};

	reverse_iterator		rbegin(void) {
		return (this->c.begin());
	};
	reverse_iterator		rend(void) {
		return (this->c.end());
	};
	const_reverse_iterator	rbegin(void) const {
		return (this->c.cbegin());
	};
	const_reverse_iterator	rend(void) const {
		return (this->c.cend());
	};
};

#endif /* ******************************************************** MSTACK_HPP */
