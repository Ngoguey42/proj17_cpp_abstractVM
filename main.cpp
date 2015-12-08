// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/12/08 19:29:27 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/08 20:27:39 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <cstdint>
#include <type_traits>
#include <algorithm>
#include <cmath>


// eOperandType.hpp
enum class eOperandType
{
	Int8 = 0,
		Int16,
		Int32,
		Float,
		Double
		};

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


// IOperand.hpp
class IOperand {
public:
	// virtual int getPrecision(void) const = 0; // Precision of the type of the instance
	virtual eOperandType		getType(void) const = 0;
	virtual IOperand const		*operator+(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator-(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator*(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator/(IOperand const &rhs) const = 0;
	virtual IOperand const		*operator%(IOperand const &rhs) const = 0;
	virtual std::string const	&toString(void) const = 0;
	virtual ~IOperand(void) {}
};




// OpFactory.hpp
template <class T, eOperandType TEnumVal>
class Operand;

class OpFactory
{
	typedef IOperand const *(OpFactory::*fun_t)(std::string const &value) const;

	IOperand const 		*createInt8(std::string const &value) const;
	IOperand const 		*createInt16(std::string const &value) const;
	IOperand const 		*createInt32(std::string const &value) const;
	IOperand const 		*createFloat(std::string const &value) const;
	IOperand const 		*createDouble(std::string const &value) const;

	static fun_t const	funs[5];

public:
	IOperand const		*createOperand(
		eOperandType type, std::string const &value) const;

};



// Evalexpr.hpp
template <class T>
class Evalexpr
{

	static std::string		conv(T v) {
		return std::to_string(v);
	}

# define OK_IF(PRED) typename std::enable_if<PRED>::type* = nullptr
# define ISFLOAT(V) std::is_floating_point<V>::value

	template <class U = T, OK_IF(ISFLOAT(U))>
	static T				conv(std::string const &v) {
		return std::atof(v.c_str());
	}
	template <class U = T, OK_IF(!ISFLOAT(U))>
	static T				conv(std::string const &v) {
		return std::atol(v.c_str());
	}

# undef OF_IF
# undef ISFLOAT

	static const std::function< T(T, T) > operations[5];

public:

	enum eOperation
	{
		Add = 0,
		Sub,
		Div,
		Mul,
		Mod
	};

	static std::string		eval(
		std::string const &lhs, eOperation o, std::string const &rhs) {
		T const		res = operations[o](conv(lhs), conv(rhs));

		return conv(res);
	}
};

template <class T>
const std::function< T(T, T) >		Evalexpr<T>::operations[5] = {
	std::plus<T>(),
	std::minus<T>(),
	std::multiplies<T>(),
	std::divides<T>(),
	[](T a, T b){ return std::fmod(a, b); },
};
// fmod has a special overload working with integer types
// Promoted		fmod(Arithmetic1 x, Arithmetic2 y);
// http://en.cppreference.com/w/cpp/numeric/math/fmod




// Operand.hpp
template <class T, eOperandType TEnumVal = operand_enum<T>::value>
class Operand : public IOperand
{
	OpFactory const		&_fact;
	std::string const	_val;

public:

	~Operand() {}
	Operand(OpFactory const &fact, std::string const &str)
		: _fact(fact), _val(str) {}

	Operand() = delete;
	Operand(Operand const &src) = delete;
	Operand(Operand &&src) = delete;
	Operand				&operator=(Operand const &rhs) = delete;
	Operand				&operator=(Operand &&rhs) = delete;

	eOperandType		getType(void) const override {
		return TEnumVal;
	}

	std::string const	&toString(void) const override {
		return _val;
	}

# define DEFINE_OPERATOR(OP, OPNAME)									\
	IOperand const		*operator OP(IOperand const &rhs) const override { \
		using Ee = Evalexpr<T>;											\
																		\
		eOperandType const	dstType = std::max(rhs.getType(), TEnumVal); \
																		\
		if (dstType != TEnumVal)										\
			return rhs + *this;											\
		else															\
			return _fact.createOperand(									\
				dstType, Ee::eval(_val, Ee::OPNAME, rhs.toString()));	\
	}

	DEFINE_OPERATOR(+, Add)
	DEFINE_OPERATOR(-, Sub)
	DEFINE_OPERATOR(*, Mul)
	DEFINE_OPERATOR(/, Div)
	DEFINE_OPERATOR(%, Mod)

# undef DEFINE_OPERATOR

};




// OpFactory.cpp
IOperand const *OpFactory::createInt8(std::string const &value) const {
	return new Operand<int8_t>(*this, value);
}
IOperand const *OpFactory::createInt16(std::string const &value) const {
	return new Operand<int16_t>(*this, value);
}
IOperand const *OpFactory::createInt32(std::string const &value) const {
	return new Operand<int32_t>(*this, value);
}
IOperand const *OpFactory::createFloat(std::string const &value) const {
	return new Operand<float>(*this, value);
}
IOperand const *OpFactory::createDouble(std::string const &value) const {
	return new Operand<double>(*this, value);
}

OpFactory::fun_t const		OpFactory::funs[5] = {
	&OpFactory::createInt8,
	&OpFactory::createInt16,
	&OpFactory::createInt32,
	&OpFactory::createFloat,
	&OpFactory::createDouble,
};

IOperand const *OpFactory::createOperand(eOperandType type, std::string const &value) const
{
	return (this ->* funs[static_cast<int>(type)])(value);
}













namespace internal // ~~~~~~~~~~~~~~~~~~~~~~~~~ //
{ // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

template <class A, class B, bool, bool>
struct result_type {
	typedef typename std::conditional<(sizeof(A) > sizeof(B)), A, B>::type type;
};

template <class A, class B>
struct result_type<A, B, true, false> {
	typedef A	type;
};

template <class A, class B>
struct result_type<A, B, false, true> {
	typedef B	type;
};

}; // ~~~~~~~~~~~~~~~ END OF NAMESPACE INTERNAL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

# define ISFLOAT(T) std::is_floating_point<T>::value

template <class A, class B>
struct result_type : public internal::result_type<A, B, ISFLOAT(A), ISFLOAT(B)>
{};

# undef ISFLOAT

#define TESTFUN(T)								\
	void	testfun(T)							\
	{											\
		std::cout << #T << std::endl;			\
		return ;								\
	}

TESTFUN(int8_t)
TESTFUN(int16_t)
TESTFUN(int32_t)
TESTFUN(float)
TESTFUN(double)

int							main(void)
{
	int8_t		i8 = 8;
	int16_t		i16 = 16;
	int32_t		i32 = 32;
	float		f = 40.f;
	double		d = 80.;

// #define TEST(A, B) testfun(A + B)
#define TEST(A, B) testfun(static_cast< result_type<decltype(A), decltype(B)>::type >(A + B))

	TEST(i8, i8);
	TEST(i8, i16);
	TEST(i8, i32);
	TEST(i8, f);
	TEST(i8, d);
	std::cout << "" << std::endl;
	TEST(i16, i8);
	TEST(i16, i16);
	TEST(i16, i32);
	TEST(i16, f);
	TEST(i16, d);
	std::cout << "" << std::endl;
	TEST(i32, i8);
	TEST(i32, i16);
	TEST(i32, i32);
	TEST(i32, f);
	TEST(i32, d);
	std::cout << "" << std::endl;
	TEST(f, i8);
	TEST(f, i16);
	TEST(f, i32);
	TEST(f, f);
	TEST(f, d);
	std::cout << "" << std::endl;
	TEST(d, i8);
	TEST(d, i16);
	TEST(d, i32);
	TEST(d, f);
	TEST(d, d);
	std::cout << "" << std::endl;
	return (0);
}
