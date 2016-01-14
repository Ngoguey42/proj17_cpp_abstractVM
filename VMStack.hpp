// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 17:44:53 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/14 16:56:56 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VMSTACK_HPP
# define VMSTACK_HPP

// # include <iostream>
# include <unordered_map>
# include <functional>
# include <string>

# include "MStack.hpp"
# include "Operands.hpp"

// VMStack is an iterable stack of IOperand const
//		supports 11 actions (5 arithmetic)
//		all arguments are grammar valid, only 2 actions use argument


// 1 pop
//		may throw std::out_of_range if stack size too low
// 1 push
//		may throw std::invalid_argument from OpFactory.createOperand()
// 5 arithmetic
//		may throw std::out_of_range if stack size too low
//		may throw std::?

class VMStack : public MStack<IOperand const *>
{
public:

	typedef std::function<void(VMStack *, std::string const &arg)>	action_t;
	typedef std::unordered_map<std::string, action_t> actmap_t;

	static actmap_t const actmap;

	typedef IOperand const *(IOperand::*arithfun_t)(IOperand const &) const;

	void		push(std::string const &arg);
	void		pop(std::string const &);
	void		dump(std::string const &);
	void		assert(std::string const &arg) {}
	void		arithmetic(arithfun_t f, std::string const &);
	void		print(std::string const &) {}
	void		exit(std::string const &) {}

	/* CONSTRUCTION ***************** */
	VMStack(OpFactory const &opFact);
	~VMStack() {}

	VMStack() = delete;
	VMStack(VMStack const &src) = delete;
	VMStack(VMStack &&src) = delete;
	VMStack					&operator=(VMStack const &rhs) = delete;
	VMStack					&operator=(VMStack &&rhs) = delete;

private:
	OpFactory const			&_opFact;
};
//std::ostream			&operator<<(std::ostream &o, VMStack const &rhs);

#endif /* ******************************************************* VMSTACK_HPP */
