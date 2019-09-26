//
// Created by Andrei BLIZNIUK on 2019-08-19.
//

#ifndef ABSTRACTVM_IOPERANDS_H
#define ABSTRACTVM_IOPERANDS_H

#include <iostream>

#include "Error.h"
#include <boost/lexical_cast.hpp>
#include <iomanip>
#include <sstream>
#include <string>

static const char * str_repr[5] = {"Int8", "Int16", "Int32", "Float", "Double"};

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double,
};

class IOperand {
public:
	virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
	virtual eOperandType getType( void ) const = 0; // Type of the instance
	virtual IOperand const * operator+(IOperand const & rhs) const = 0; // Sum
	virtual IOperand const * operator-(IOperand const & rhs) const = 0; // Difference
	virtual IOperand const * operator*(IOperand const & rhs) const = 0; // Product
	virtual IOperand const * operator/(IOperand const & rhs) const = 0; // Quotient
	virtual IOperand const * operator%(IOperand const & rhs) const = 0; // Modulo
	virtual std::string const & toString(void) const = 0; // String representation of the instance
	virtual ~IOperand( void ) {}
};

class CreateOperands;

template <typename T>
class Operand:public IOperand
{
public:
	Operand () {}
	Operand(std::string const & v, eOperandType type, size_t precision, const CreateOperands * factory): _type(type), _precision(precision), _factory(factory) {
		try {
			if (_type >= Float)
			{
				long double v_ = boost::lexical_cast<long double >(v);
				overflow<T, long double>(v_);
			}
			else
			{
				if (_type <= Int8)
				{
					int32_t v_ = boost::lexical_cast<int32_t>(v);
					overflow<int8_t, int32_t>(v_);
				}
				else
				{
					int64_t v_ = boost::lexical_cast<int64_t>(v);
					overflow<T, int64_t>(v_);
				}
			}
		}
		catch (boost::bad_lexical_cast &e){
			throw Error(std::string("Error: unknown error"));
		}
	}
	template <typename U, typename Z>
	void overflow(Z v_)								{
		if (v_  > static_cast<U>(std::numeric_limits<U>::max()) or
			v_  < static_cast<U>(std::numeric_limits<U>::min()))
			throw Error(std::string("Error: Overflowing operand ") + _operand);
		_value = static_cast<U>(v_);
	}

	long double const return_operands_floated_point(IOperand const &op) const
	{
		long double v_ = 0;
		try {
			std::string  a = op.toString();
//			long double v_ = std::stold(op.toString());
		}
		catch (boost::bad_lexical_cast &e)
		{throw Error(std::string("Error: overflowed value"));}
		return (v_);
	}

	int64_t const return_operands_fixed_point(IOperand const &op) const
	{
		int64_t v_ = 0;
		try {
			int64_t v_ = boost::lexical_cast<int64_t>(op.toString());
		}
		catch (boost::bad_lexical_cast &e)
		{throw Error(std::string("Error: overflowed value"));}
		return (v_);
	}

	std::string const & toString(void) const 		{
		std::stringstream stream;
		std::string res;

		stream << std::fixed << std::setprecision(_precision) << this->_value;
		res = stream.str();
		return std::move(res);
	}

	std::string const & getOperand(void) const 		{ return this->_operand; }
	int 				getPrecision( void ) const 	{ return this->_precision; }
	eOperandType		getType(void) const 		{ return this->_type; }
	T const &			get_value(void) const 		{ return this->_value; }

	IOperand const * operator+(IOperand const & rhs) const	{
		const IOperand * ptr = nullptr;
		std::string _value_;
		eOperandType _type_;

		if (rhs.getPrecision() >= this->_precision)
		{
			if (rhs.getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs) + this->return_operands_floated_point(*this));
			else if (rhs.getType() < Float and rhs.getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs) + this->return_operands_fixed_point(*this));
			_type_ = rhs.getType();
		}
		else if (rhs.getPrecision() < this->_precision)
		{
			if (this->getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs) + this->return_operands_floated_point(*this));
			else if (this->getType() < Float and this->getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs) + this->return_operands_fixed_point(*this));
			_type_ = this->getType();
		}
		return (this->_factory->createOperand(_type_, _value_));
	}
	IOperand const * operator-(IOperand const & rhs) const	{
		return (nullptr);
	}
	IOperand const * operator*(IOperand const & rhs) const	{
		return (nullptr);
	}
	IOperand const * operator/(IOperand const & rhs) const	{
		return (nullptr);
	}
	IOperand const * operator%(IOperand const & rhs) const	{
		return (nullptr);
	}

	~Operand() {};
private:
	eOperandType			_type;
	std::string				_operand = str_repr[_type];
	std::string				_str_value;
	T						_value;
	size_t					_precision;
	const CreateOperands	*_factory;
};

template <typename T>
std::ostream &operator<<(std::ostream &stream, Operand<T> const &op)
{
	stream << "The value is  - " << static_cast<T>(op.get_value());
	return stream;
}

class CreateOperands
{
public:
	CreateOperands();
	~CreateOperands();
	CreateOperands(CreateOperands const & c);
	CreateOperands &operator=(CreateOperands const &r);

	IOperand const * createOperand(eOperandType type, std::string const & value) const;

private:
	eOperandType	type_;
	std::vector<IOperand const *(CreateOperands::*)(std::string const &) const> factory;

	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;
};


#endif //ABSTRACTVM_IOPERANDS_H
