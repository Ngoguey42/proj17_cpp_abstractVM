// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 17:44:53 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/26 20:17:11 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef VMSTACK_HPP
# define VMSTACK_HPP

// # include <iostream>
# include <unordered_map>
# include <functional>
# include <string>

# include "MStack.hpp"
# include "arith_wrappers.hpp"

// VMStack is an iterable stack of IOperand const*
//		supports 11 actions (5 arithmetic)
//		all arguments are grammar valid, only 2 actions use argument

// 1 push
//		may throw std::invalid_argument
// 1 pop
//		may throw std::out_of_range if stack size too low
// 1 dump (no throw)
// 5 arithmetic
//		may throw std::out_of_range if stack size too low
//		may throw std::domain_error from Operators call
//		may throw std::underflow_error from Operators call
//		may throw std::overflow_error from Operators call
// 1 exit

class VMStack : public MStack<IOperand const *>
{
public:

	typedef std::function<bool(VMStack *, std::string const &arg)> action_t;
	typedef std::unordered_map<std::string, action_t> actmap_t;

	static actmap_t const actmap;

	typedef IOperand const *(IOperand::*arithfun_t)(IOperand const &) const;

	bool push(std::string const &arg);
	bool pop(std::string const &);
	bool dump(std::string const &);
	bool assert(std::string const &arg);
	bool arithmetic(arithfun_t f, std::string const &);
	bool print(std::string const &) {return false;}
	bool exit(std::string const &);

	/* CONSTRUCTION ***************** */
	VMStack(OpFactory const &opFact);
	~VMStack(); //TODO: check functions implemented in a header

	VMStack() = delete;
	VMStack(VMStack const &src) = delete;
	VMStack(VMStack &&src) = delete;
	VMStack					&operator=(VMStack const &rhs) = delete;
	VMStack					&operator=(VMStack &&rhs) = delete;

private:
	OpFactory const			&_opFact;
};

#endif /* ******************************************************* VMSTACK_HPP */
