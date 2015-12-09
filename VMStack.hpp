// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   VMStack.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/09 17:44:53 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/09 18:49:07 by ngoguey          ###   ########.fr       //
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

class VMStack : public MStack<IOperand const *>
{
public:

	typedef std::function<void(VMStack *, std::string const &arg)>	operation_t;
	typedef std::unordered_map<std::string, operation_t> opmap_t;

	static opmap_t const opmap;

	typedef IOperand const *(IOperand::*arithfun_t)(IOperand const &) const;

	void		push(std::string const &arg) {}
	void		pop(std::string const &) {}
	void		dump(std::string const &) {}
	void		assert(std::string const &arg) {}
	void		arithmetic(arithfun_t f, std::string const &) {}
	void		print(std::string const &) {}
	void		exit(std::string const &) {}
	// enum class Operation
	// {
	// 	Push = 0,
	// 		Pop,
	// 		Dump,
	// 		Assert,
	// 		Add,
	// 		Sub,
	// 		Mul,
	// 		Div,
	// 		Mod,
	// 		Print,
	// 		Exit
	// 		};


	/* CONSTRUCTION ***************** */
	VMStack();
	// virtual ~VMStack();
	virtual ~VMStack() {}

	// VMStack() = delete;
	VMStack(VMStack const &src) = delete;
	VMStack(VMStack &&src) = delete;
	VMStack					&operator=(VMStack const &rhs) = delete;
	VMStack					&operator=(VMStack &&rhs) = delete;

protected:
private:
};
//std::ostream			&operator<<(std::ostream &o, VMStack const &rhs);

#endif /* ******************************************************* VMSTACK_HPP */
