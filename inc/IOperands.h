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


static const char *strRepresentation[5] = {"Int8", "Int16", "Int32", "Float", "Double"};

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
	virtual int getPrecision( void ) const = 0;
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
	Operand(Operand const &op) {
		this->_type = op._type;
		this->_value = op._value;
		this->_precision = op._precision;
		this->*_factory = op.*_factory;
	}
	Operand &operator=(Operand const & op) {
		if (this != &op) {
			this->_type = op._type;
			this->_value = op._value;
			this->_precision = op._precision;
			this->*_factory = op.*_factory;
		}
		return *this;
	}
	Operand(std::string const & v, eOperandType type, size_t precision, const CreateOperands * factory): _type(type), _precision(precision), _factory(factory) {
		std::stringstream stream;

		stream << std::fixed << std::setprecision(_precision) << v;
		__v__ = stream.str();

		try {
			if (_type >= Float)
			{
				long double v_ = boost::lexical_cast<T>(v);
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
			throw Error(std::string("Error: Overflowing operand ") + std::string(strRepresentation[_type]));
		_value = static_cast<U>(v_);
	}

	long double const return_operands_floated_point(std::string str) const
	{
		long double v_ = 0;
		try {
			v_ = std::stold(str);
		}
		catch (boost::bad_lexical_cast &e)
		{throw Error(std::string("Error: overflowed value"));}
		return (v_);
	}

	int64_t const return_operands_fixed_point(std::string const & str) const
	{
		int64_t v_ = 0;
		try {
			v_ = boost::lexical_cast<int64_t>(str);
		}
		catch (boost::bad_lexical_cast &e)
		{throw Error(std::string("Error: overflowed value"));}
		return (v_);
	}

	std::string const & toString(void) const 		{
		return this->__v__;
	}

	int 				getPrecision( void ) const 				{ return this->_precision; }
	eOperandType		getType(void) const 					{ return this->_type; }
	T const &			get_value(void) const 					{ return this->_value; }

	IOperand const * operator+(IOperand const & rhs) const	{
		const IOperand * ptr = nullptr;
		std::string _value_;
		eOperandType _type_ = Int8;

		if (rhs.getPrecision() >= this->_precision)
		{
			if (rhs.getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs.toString()) + this->return_operands_floated_point(this->toString()));
			else if (rhs.getType() < Float and rhs.getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) + this->return_operands_fixed_point(this->toString()));
			_type_ = rhs.getType();
		}
		else if (rhs.getPrecision() < this->_precision)
		{
			if (this->getType() >= Float) {
				_value_ = std::to_string(this->return_operands_floated_point(rhs.toString()) + this->return_operands_floated_point(this->toString()));
			}
			else if (this->getType() < Float and this->getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) + this->return_operands_fixed_point(this->toString()));
			_type_ = this->getType();
		}
		return (this->_factory->createOperand(_type_, _value_));
	}
	IOperand const * operator-(IOperand const & rhs) const	{
		const IOperand * ptr = nullptr;
		std::string _value_;
		eOperandType _type_ = Int8;

		if (rhs.getPrecision() >= this->_precision)
		{
			if (rhs.getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs.toString()) - this->return_operands_floated_point(this->toString()));
			else if (rhs.getType() < Float and rhs.getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) - this->return_operands_fixed_point(this->toString()));
			_type_ = rhs.getType();
		}
		else if (rhs.getPrecision() < this->_precision)
		{
			if (this->getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs.toString()) - this->return_operands_floated_point(this->toString()));
			else if (this->getType() < Float and this->getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) - this->return_operands_fixed_point(this->toString()));
			_type_ = this->getType();
		}
		return (this->_factory->createOperand(_type_, _value_));
	}
	IOperand const * operator*(IOperand const & rhs) const	{
		const IOperand * ptr = nullptr;
		std::string _value_;
		eOperandType _type_ = Int8;

		if (rhs.getPrecision() >= this->_precision)
		{
			if (rhs.getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs.toString()) * this->return_operands_floated_point(this->toString()));
			else if (rhs.getType() < Float and rhs.getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) * this->return_operands_fixed_point(this->toString()));
			_type_ = rhs.getType();
		}
		else if (rhs.getPrecision() < this->_precision)
		{
			if (this->getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs.toString()) * this->return_operands_floated_point(this->toString()));
			else if (this->getType() < Float and this->getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) * this->return_operands_fixed_point(this->toString()));
			_type_ = this->getType();
		}
		return (this->_factory->createOperand(_type_, _value_));
	}
	IOperand const * operator/(IOperand const & rhs) const	{
		const IOperand * ptr = nullptr;
		std::string _value_;
		eOperandType _type_ = Int8;

		if (rhs.getPrecision() >= this->_precision)
		{
			if (rhs.getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs.toString()) / this->return_operands_floated_point(this->toString()));
			else if (rhs.getType() < Float and rhs.getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) / this->return_operands_fixed_point(this->toString()));
			_type_ = rhs.getType();
		}
		else if (rhs.getPrecision() < this->_precision)
		{
			if (this->getType() >= Float)
				_value_ = std::to_string(this->return_operands_floated_point(rhs.toString()) / this->return_operands_floated_point(this->toString()));
			else if (this->getType() < Float and this->getType() >= Int8)
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) / this->return_operands_fixed_point(this->toString()));
			_type_ = this->getType();
		}
		return (this->_factory->createOperand(_type_, _value_));
	}
	IOperand const * operator%(IOperand const & rhs) const	{
		const IOperand * ptr = nullptr;
		std::string _value_;
		eOperandType _type_ = Int8;

		if (rhs.getPrecision() >= this->_precision)
		{
			if (rhs.getType() < Float and rhs.getType() >= Int8) {
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) %
										 this->return_operands_fixed_point(this->toString()));
				_type_ = rhs.getType();
			}
		}
		else if (rhs.getPrecision() < this->_precision)
		{
			if (this->getType() < Float and this->getType() >= Int8)
			{
				_value_ = std::to_string(this->return_operands_fixed_point(rhs.toString()) %
						this->return_operands_fixed_point(this->toString()));
				_type_ = this->getType();
			}
		}
		return (this->_factory->createOperand(_type_, _value_));
	}
	~Operand() {};
private:
	eOperandType			_type;
	T						_value;
	size_t					_precision;
	const CreateOperands	*_factory;
	std::string				__v__;
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


#endif
