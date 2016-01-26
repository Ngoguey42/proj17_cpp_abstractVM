// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   arith_types.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2016/01/24 15:53:27 by ngoguey           #+#    #+#             //
//   Updated: 2016/01/24 15:53:34 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ARITH_TYPES_HPP
# define ARITH_TYPES_HPP

#include <unordered_map>

// Enum *************************************** //
enum class eOperandType // eOperandType from subject.pdf
{
	Int8 = 0,
		Int16,
		Int32,
		Float,
		Double
		};

// Type -> Enum (static) ********************** //
template <class T>	struct operand_enum;

template <>			struct operand_enum<int8_t>
	: std::integral_constant<eOperandType, eOperandType::Int8> {};

template <>			struct operand_enum<int16_t>
	: std::integral_constant<eOperandType, eOperandType::Int16> {};

template <>			struct operand_enum<int32_t>
	: std::integral_constant<eOperandType, eOperandType::Int32> {};

template <>			struct operand_enum<float>
	: std::integral_constant<eOperandType, eOperandType::Float> {};

template <>			struct operand_enum<double>
	: std::integral_constant<eOperandType, eOperandType::Double> {};

// TypeName -> Enum (runtime) ***************** //
extern std::unordered_map<std::string, eOperandType> const operandMap;

// Type -> TypeName (static) ****************** //
template <class T>	struct TypeToString;

template <>			struct TypeToString<int8_t> {
	static constexpr char const *name = "Int8";
};
template <>			struct TypeToString<int16_t> {
	static constexpr char const *name = "Int16";
};
template <>			struct TypeToString<int32_t> {
	static constexpr char const *name = "Int32";
};
template <>			struct TypeToString<float> {
	static constexpr char const *name = "Float";
};
template <>			struct TypeToString<double> {
	static constexpr char const *name = "Double";
};

#endif /* *************************************************** ARITH_TYPES_HPP */
