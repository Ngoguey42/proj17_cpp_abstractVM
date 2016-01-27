// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   limitsTestsTools.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/27 17:19:03 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/27 17:19:09 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LIMITSTESTSTOOLS_HPP
# define LIMITSTESTSTOOLS_HPP

#include "testTools.hpp"

class Limits
{

	template <class T>
	std::string _makeMax(void) const {

		std::stringstream iss;

		iss << std::fixed;
		iss << std::noshowpos;
		iss << std::setprecision(1);
		nbrToStream(std::numeric_limits<T>::max(), iss);
		return iss.str();
	}
	template <class T>
	std::string _makeMin(void) const {

		std::stringstream iss;
		int tmp;

		iss << std::fixed;
		iss << std::noshowpos;
		tmp = -floor(log10(std::abs(std::numeric_limits<T>::denorm_min())));
		tmp += std::numeric_limits<T>::max_digits10 - 1;
		iss << std::setprecision(tmp);
		nbrToStream(std::numeric_limits<T>::denorm_min(), iss);
		return iss.str();
	}
	template <class T>
	std::string _makeLowest(void) const {

		std::stringstream iss;

		iss << std::fixed;
		iss << std::noshowpos;
		iss << std::setprecision(1);
		nbrToStream(std::numeric_limits<T>::lowest(), iss);
		return iss.str();
	}
public:
	std::string const _type;
	std::string const _max;
	std::string const _min;
	std::string const _lowest;

	template <class T>
	Limits(char const *name, T)
		: _type(name)
		, _max(_makeMax<T>()), _min(_makeMin<T>()), _lowest(_makeLowest<T>()) {


	}
	Limits(Limits const &src)
		: _type(src._type)
		, _max(src._max), _min(src._min), _lowest(src._lowest) {

	}
	~Limits(){}

	Limits() = delete;
	Limits &operator=(Limits const &) = delete;
};

#endif /* ********************************************** LIMITSTESTSTOOLS_HPP */
